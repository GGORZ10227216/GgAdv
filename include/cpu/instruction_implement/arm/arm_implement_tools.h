//
// Created by orzgg on 2020-07-11.
//

#include <system_components.h>
#include <cycle_tools.h>
#include <arm_info.h>
#include <cpu.h>
#include <macro.h>

#include <system_enum.h>
#include <functional>
#include <type_traits>

#ifndef TEST_ARM_IMPLEMENT_TOOLS_H
#define TEST_ARM_IMPLEMENT_TOOLS_H

namespace ArmHandler {
    enum {
        Type_ALU, Type_MUL, Type_MULL, Type_SWP,
        Type_BX, Type_HDT, Type_DT, Type_UDF,
        Type_MDT, Type_B, Type_CDT, Type_CDP,
        Type_CRT, Type_SWI
    };

    enum class AffectCPSR {
        YES, NO
    };

    enum class ALUType {
        ARITHMETIC, LOGICAL
    };

    enum class HasResult {
        NORMAL, TEST
    };

    enum class Accumulate {
        YES, NO
    };
    enum class MulMode {
        WORD, DWORD
    };
    enum class Signed {
        YES, NO
    };

    template<typename T>
    unsigned Operand2(Components::System &emuInstance, bool &carry) {
        auto Get = [&](unsigned idx) {
            return T::access[idx](EMU_CPU.Instruction());
        };

        bool shiftedRm = !Get(T::I), shAmount = false ;
        if constexpr (std::is_same_v<T, disassemble::instruction_info<DecodeMode::ARM, Type_DT>>) {
            shiftedRm = !shiftedRm ;
            shAmount = Get(T::shAmount) ;
        } // if
        else {
            if (Get(T::RsMark)) {
                shAmount = EMU_CPU.ReadReg(static_cast<RegName>(Get(T::Rs))) ;
                EMU_CLK += CLK_CONT.I();
            } // if
            else
                shAmount = Get(T::shAmount) ;
        } // else

        if (shiftedRm) {
            unsigned RmValue = EMU_CPU.ReadReg(static_cast<RegName>(Get(T::Rm)));

            switch (Get(T::shType)) {
                case ShiftType::LSL :
                    if (shAmount == 0) {
                        return RmValue;
                    } // if
                    else if (shAmount > 32) {
                        carry = false;
                        return 0;
                    } // if

                    carry = Utility::TestBit(RmValue, 32 - shAmount);
                    return RmValue << shAmount;
                case ShiftType::LSR :
                    if (shAmount == 0) {
                        shAmount = 32;
                    } // if
                    else if (shAmount > 32) {
                        carry = false;
                        return 0;
                    } // if

                    carry = Utility::TestBit(RmValue, shAmount - 1);
                    return RmValue >> shAmount;
                case ShiftType::ASR :
                    if (shAmount == 0 || shAmount > 32)
                        shAmount = 32;
                    carry = Utility::TestBit(RmValue, shAmount - 1);
                    return static_cast<int32_t> (RmValue) >> shAmount;
                case ShiftType::ROR :
                    if (shAmount == 0) {
                        unsigned rrxVal = EMU_CPU.TestPSRFlag(PSRBit::C) ? Utility::_BV(31) : 0;
                        return Utility::rotr(RmValue, 1) | rrxVal;
                    } // if
                    else if (shAmount > 32)
                        shAmount -= 32;
                    carry = Utility::TestBit(RmValue, shAmount - 1);
                    return Utility::rotr(RmValue, shAmount);
                default :
                    throw std::logic_error("unknown shift type");
            } // switch
        } // if
        else {
            if constexpr (std::is_same_v<T, disassemble::instruction_info<DecodeMode::ARM, Type_DT>>)
                return Get(T::imm) ;
            else
                return Utility::rotr(Get(T::imm), Get(T::rotate) * 2);
        } // else
    }

    static void CPSR_Logical(Components::CPU &cpu, unsigned result, const bool carry) {
        using namespace CPU_Enum;
        Utility::TestBit(result, 31) ? cpu.SetFlag(N) : cpu.ClearFlag(N);
        carry ? cpu.SetFlag(C) : cpu.ClearFlag(C);
        result == 0 ? cpu.SetFlag(Z) : cpu.ClearFlag(Z);
    }

    template<typename T>
    static void
    CPSR_Arithmetic(Components::CPU &cpu, unsigned Rn, unsigned op2, T result)requires std::is_same_v<T, uint64_t> {
        using namespace CPU_Enum;
        const bool RnSigned = Utility::TestBit(Rn, 31);
        const bool op2Signed = Utility::TestBit(op2, 31);
        const bool resultSigned = Utility::TestBit(result, 31);

        (RnSigned == op2Signed) && (RnSigned != resultSigned) ? cpu.SetFlag(V) : cpu.ClearFlag(V);
        result > 0xffffffff ? cpu.SetFlag(C) : cpu.ClearFlag(C); // ARM's Carry flag is inverted?
        (result & 0xffffffff) == 0 ? cpu.SetFlag(Z) : cpu.ClearFlag(Z);
        Utility::TestBit(result, 31) ? cpu.SetFlag(N) : cpu.ClearFlag(N);
    }

    template<ALUType T, AffectCPSR S, HasResult R, typename F>
    void ALUProcessor(Components::System &emuInstance, F operation) requires
        std::is_same_v<std::invoke_result_t<F, unsigned, unsigned>, uint64_t>
    {
        bool shiftCarry;
        RegName dstName, RnName;
        unsigned Rn, op2;
        uint64_t result;

        EMU_CLK += CLK_CONT.S(EMU_CPU.ReadReg(RegName::pc));

        using Type = disassemble::instruction_info<DecodeMode::ARM, 0>;
        auto Get = [&](unsigned idx) {
            return Type::access[idx](EMU_CPU.Instruction());
        };

        dstName = static_cast<RegName>( Get(Type::Rd));
        RnName = static_cast<RegName>( Get(Type::Rn));
        Rn = EMU_CPU.ReadReg(RnName);
        op2 = Operand2<Type>(emuInstance, shiftCarry);
        result = operation(Rn, op2);

        if constexpr (S == AffectCPSR::YES) {
            if constexpr (T == ALUType::ARITHMETIC) {
                CPSR_Arithmetic(EMU_CPU, Rn, op2, result);
            } // if
            else {
                CPSR_Logical(EMU_CPU, result, shiftCarry);
            } // else
        } // if constexpr

        if constexpr (R == HasResult::NORMAL)
            EMU_CPU.WriteReg(dstName, result);
    } // ALU

    template<Accumulate A, AffectCPSR S>
    void Multiply(Components::System &emuInstance) {
        ACCESS(Type_MUL);
        RegName RsName = static_cast<RegName>(Get(Type::Rs));
        RegName RdName = static_cast<RegName>(Get(Type::Rd));
        RegName RmName = static_cast<RegName>(Get(Type::Rm));
        unsigned RsValue = EMU_CPU.ReadReg(RsName);
        unsigned RmValue = EMU_CPU.ReadReg(RmName);

        unsigned boothValue = 4;
        for (int i = 1; i < 4; ++i) {
            unsigned boothCheck = RsValue >> (8 * i);
            const unsigned allOneMask = 0xffffffff;
            if (boothCheck == 0 || boothCheck == allOneMask >> (8 * i)) {
                boothValue = i;
                break;
            } // if
        } // for

        unsigned result = RmValue * RsName;
        EMU_CLK += CLK_CONT.S(EMU_CPU.ProgramCounter()) + CLK_CONT.I() * boothValue;

        if constexpr (A == Accumulate::YES) {
            RegName RnName = static_cast<RegName>(Get(Type::Rn));
            unsigned RnValue = EMU_CPU.ReadReg(RnName);
            result += RnValue;
            EMU_CLK += +CLK_CONT.I() * boothValue;
        } // if

        EMU_CPU.WriteReg(RdName, RmValue * RsName);

        if constexpr (S == AffectCPSR::YES) {
            // Result of C is meaningless, V is unaffected.
            result == 0 ? EMU_CPU.SetFlag(PSRBit::Z) : EMU_CPU.ClearFlag(PSRBit::Z);
            Utility::TestBit(result, 31) ? EMU_CPU.SetFlag(PSRBit::N) : EMU_CPU.ClearFlag(PSRBit::N);
        } // if
    } // Multiply()

    template<Signed U, Accumulate A, AffectCPSR S>
    void MultiplyLong(Components::System &emuInstance) {
        ACCESS(Type_MULL) ;
        uint64_t RsVal = EMU_CPU.ReadReg(GetRegName(Type::Rs)) ;
        uint64_t RmVal = EMU_CPU.ReadReg(GetRegName(Type::Rm)) ;

        RegName RdLoName = GetRegName(Type::RdLo) ;
        RegName RdHiName = GetRegName(Type::RdHi) ;

        union Mull_t {
            uint64_t dword ;
            uint32_t word[2] ;
            Mull_t(uint64_t val) {dword = val;}
        };

        Mull_t result = RsVal * RmVal ;

        unsigned boothValue = 4;
        for (int i = 1; i < 4; ++i) {
            unsigned boothCheck = RsVal >> (8 * i);
            if constexpr (U == Signed::YES) {
                const unsigned allOneMask = 0xffffffff;
                if (boothCheck == 0 || boothCheck == allOneMask >> (8 * i)) {
                    boothValue = i;
                    break;
                } // if
            } // if constexpr
            else {
                if (boothCheck == 0) {
                    boothValue = i;
                    break;
                } // if
            } // else
        } // for

        EMU_CLK += CLK_CONT.S(EMU_CPU.ProgramCounter()) + CLK_CONT.I() * (boothValue + 1);

        if constexpr (A == Accumulate::YES) {
            result.dword += result.dword ;
            EMU_CLK += CLK_CONT.I() ;
        } // if constexpr

        if constexpr (S == AffectCPSR::YES) {
            Utility::TestBit(result.dword, 63) ? EMU_CPU.SetFlag(PSRBit::N) : EMU_CPU.ClearFlag(PSRBit::N) ;
            result.dword == 0 ? EMU_CPU.SetFlag(PSRBit::Z) : EMU_CPU.ClearFlag(PSRBit::Z) ;
        } // if constexpr

        EMU_CPU.WriteReg(RdLoName, result.word[0]) ;
        EMU_CPU.WriteReg(RdHiName, result.word[1]) ;
    }

    enum class OffsetType { IMM, REG } ;
    enum class IndexMode { PRE, POST } ;
    enum class UpDown { UP, DOWN } ;
    enum class AccessSize { WORD, HALFWORD,  BYTE } ;
    enum class AccessMode { LOAD, STORE } ;
    enum class WriteBack { YES, NO } ;

    template <AccessSize B, AccessMode L>
    void MemoryAccess(Components::System &emuInstance) {
        // TODO: Cycle counting
        ACCESS(Type_DT);
        bool carryFlag = false ;
        RegName RdName = GetRegName(Type::Rd) ;
        RegName RmName = GetRegName(Type::Rm) ;
        RegName RnName = GetRegName(Type::Rn) ;
        unsigned offset = Operand2<Type> (emuInstance, carryFlag);
        unsigned targetAddr = EMU_CPU.ReadReg(RnName) ;

        if (Get(Type::P)) {
            if (Get(Type::U))
                targetAddr += offset ;
            else
                targetAddr -= offset ;
        } // if

        if constexpr (L == AccessMode::LOAD) {
            if constexpr (B == AccessSize::WORD) {
                EMU_CPU.WriteReg( RdName, EMU_MEM.Read8(targetAddr) ) ;
            } // if
            else {
                EMU_CPU.WriteReg( RdName, EMU_MEM.Read32(targetAddr) ) ;
            } // EMU
        } // if
        else {
            if constexpr (B == AccessSize::WORD) {
                EMU_MEM.Write8( targetAddr, static_cast<uint8_t>(EMU_CPU.ReadReg(RdName)) ) ;
            } // if
            else {
                EMU_MEM.Write32( targetAddr, EMU_CPU.ReadReg(RdName) ) ;
            } // EMU
        } // else

        if (!Get(Type::P)) {
            if (Get(Type::U))
                targetAddr += offset ;
            else
                targetAddr -= offset ;
        } // if

        if (Get(Type::W)) {
            EMU_CPU.WriteReg(RnName, targetAddr) ;
        } // if
    }

    enum class SIGNED { YES, NO } ;

    template <AccessSize B, SIGNED S, AccessMode L>
    void MemoryAccess(Components::System &emuInstance) {
        // TODO: Cycle counting
        ACCESS(Type_HDT);
        bool carryFlag = false ;
        RegName RdName = GetRegName(Type::Rd) ;
        RegName RnName = GetRegName(Type::Rn) ;
        unsigned offset = Get(Type::I) ? Get(Type::offset) : EMU_CPU.ReadReg(GetRegName(Type::Rm)) ;
        unsigned targetAddr = EMU_CPU.ReadReg(RnName) ;
        unsigned result = 0 ;

        if (Get(Type::P)) {
            if (Get(Type::U))
                targetAddr += offset ;
            else
                targetAddr -= offset ;
        } // if

        if constexpr (L == AccessMode::LOAD) {
            if constexpr (B == AccessSize::BYTE) {
                if constexpr (S == SIGNED::YES) // LDRSB
                    EMU_CPU.WriteReg( RdName, EMU_MEM.Read8(targetAddr) | 0xffffff00 ) ;
                else
                    static_assert("Illegal instruction") ;
            } // if
            else {
                if constexpr (S == SIGNED::YES) // LDRSH
                    EMU_CPU.WriteReg( RdName, EMU_MEM.Read16(targetAddr) | 0xffff0000 ) ;
                else // LDRH
                    EMU_CPU.WriteReg( RdName, EMU_MEM.Read16(targetAddr) ) ;
            } // EMU
        } // if
        else {
            if constexpr (B == AccessSize::HALFWORD) { // STRH
                EMU_MEM.Write16( targetAddr, static_cast<uint16_t>(EMU_CPU.ReadReg(RdName)) ) ;
            } // if
            else
                static_assert("Illegal instruction") ;
        } // else

        if (!Get(Type::P)) {
            if (Get(Type::U))
                targetAddr += offset ;
            else
                targetAddr -= offset ;
        } // if

        if (Get(Type::W)) {
            EMU_CPU.WriteReg(RnName, targetAddr) ;
        } // if
    }
}

#endif //TEST_ARM_IMPLEMENT_TOOLS_H
