//
// Created by orzgg on 2020-07-11.
//

#include <system_enum.h>
#include <arm_info.h>
#include <system_components.h>
#include <functional>
#include <type_traits>

#ifndef TEST_ARM_IMPLEMENT_TOOLS_H
#define TEST_ARM_IMPLEMENT_TOOLS_H

namespace ArmHandler {
    using AccessLambda = std::function<unsigned(unsigned)> ;

    template<typename T>
    unsigned Operand2_reg(Components::CPU &cpu, AccessLambda Get, bool& carry) {
        unsigned shAmount = Get(T::RsMark) ? cpu.ReadReg(static_cast<RegName>(Get(T::Rs))) : Get(T::shAmount);
        unsigned RmValue = cpu.ReadReg(static_cast<RegName>(Get(T::Rm)));

        if ( Get(T::RsMark) )
            EMU_CYCLE += cpu.cycleTools.I() ;

        switch (Get(T::shType)) {
            case ShiftType::LSL :
                if (shAmount == 0) {
                    return RmValue;
                } // if
                else if (shAmount > 32) {
                    // cpu.ClearFlag(PSRBit::C);
                    carry = false ;
                    return 0;
                } // if

                carry = Utility::TestBit(RmValue, 32 - shAmount) ;
                return RmValue << shAmount;
            case ShiftType::LSR :
                if (shAmount == 0) {
                    shAmount = 32;
                } // if
                else if (shAmount > 32) {
                    carry = false ;
                    return 0;
                } // if

                carry = Utility::TestBit(RmValue, shAmount - 1) ;
                return RmValue >> shAmount;
            case ShiftType::ASR :
                if (shAmount == 0 || shAmount > 32)
                    shAmount = 32;
                carry = Utility::TestBit(RmValue, shAmount - 1) ;
                return static_cast<int32_t> (RmValue) >> shAmount;
            case ShiftType::ROR :
                if (shAmount == 0) {
                    unsigned rrxVal = cpu.TestPSRFlag(PSRBit::C) ? Utility::_BV(31) : 0;
                    return Utility::rotr(RmValue, 1) | rrxVal;
                } // if
                else if (shAmount > 32)
                    shAmount -= 32;
                carry = Utility::TestBit(RmValue, shAmount - 1) ;
                return Utility::rotr(RmValue, shAmount);
            default :
                throw std::logic_error("unknown shift type");
        } // switch
    }

    template<typename T>
    unsigned Operand2(Components::CPU &cpu, AccessLambda Get, bool& carry) {
        if (!Get(T::I))
            return Operand2_reg<T>(cpu, Get, carry);
        else {
            return Utility::rotr(Get(T::imm), Get(T::rotate) * 2);
        } // else
    }

    static void CPSR_Logical(Components::CPU &cpu, unsigned result, const bool carry) {
        using namespace CPU_Enum ;
        Utility::TestBit(result, 31) ? cpu.SetFlag(N) : cpu.ClearFlag(N);
        carry ? cpu.SetFlag(C) : cpu.ClearFlag(C);
        result == 0 ? cpu.SetFlag(Z) : cpu.ClearFlag(Z);
    }

    template <typename T>
    static void CPSR_Arithmetic(Components::CPU &cpu, unsigned Rn, unsigned op2, T result)
    requires std::is_same_v<T, uint64_t>
    {
        using namespace CPU_Enum ;
        const bool RnSigned = Utility::TestBit( Rn, 31 ) ;
        const bool op2Signed = Utility::TestBit( op2, 31 ) ;
        const bool resultSigned = Utility::TestBit( result, 31 ) ;

        (RnSigned == op2Signed) && (RnSigned != resultSigned) ? cpu.SetFlag(V) : cpu.ClearFlag(V) ;
        result > 0xffffffff ? cpu.SetFlag(C) : cpu.ClearFlag(C) ;
        result == 0 ? cpu.SetFlag(Z) : cpu.ClearFlag(Z);
        Utility::TestBit(result, 31) ? cpu.SetFlag(N) : cpu.ClearFlag(N) ;
    }

    enum class ALUType { ARITHMETIC, LOGICAL } ;
    enum class CPSRaffect { S, NON_S } ;
    enum class HasResult { NORMAL, TEST } ;

    template<ALUType T, CPSRaffect S, HasResult R>
    struct ALUProcessor {
        template<typename F>
        ALUProcessor(Components::CPU &cpu, F operation) requires
            std::is_same_v<std::invoke_result_t<F, unsigned, unsigned>, uint64_t>
        {
            EMU_CYCLE += cpu.cycleTools.S(cpu.ReadReg(RegName::pc)) ;

            using Type = disassemble::instruction_info<DecodeMode::ARM, 0>;
            auto Get = [&](unsigned idx) {
                return Type::access[idx](cpu.Instruction()) ;
            } ;

            dstName = static_cast<RegName>( Get(Type::Rd) );
            Rn = Get(Type::Rn) ;
            op2 = Operand2<Type>(cpu, Get, shiftCarry) ;
            result = operation(Rn, op2) ;

            if constexpr (S == CPSRaffect::S) {
                if constexpr (T == ALUType::ARITHMETIC)
                    CPSR_Arithmetic(cpu, Rn, op2, result ) ;
                else
                    CPSR_Logical(cpu, result, shiftCarry) ;
            } // if constexpr

            if constexpr (R == HasResult::NORMAL) {
                cpu.WriteReg(dstName, result) ;
                if (Get(Type::Rd) == RegName::pc)
                    cpu.FillPipeline() ;
            } // if constexpr
        }

        bool shiftCarry ;
        RegName dstName ;
        unsigned Rn, op2 ;
        uint64_t result ;
    };
}

#endif //TEST_ARM_IMPLEMENT_TOOLS_H
