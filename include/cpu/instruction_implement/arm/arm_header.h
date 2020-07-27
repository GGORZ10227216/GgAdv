//
// Created by orzgg on 2020-07-10.
//

#include <system_components.h>
#include <arm_implement_tools.h>

#ifndef TEST_ARM_HEADER_H
#define TEST_ARM_HEADER_H

namespace ArmHandler {
    static void AND(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) & op2; }
        );
    }

    static void MUL(Components::System &emuInstance) {
        Multiply<Accumulate::NO, AffectCPSR::NO>(emuInstance) ;
    }

    static void STRH(Components::System &emuInstance) {
        MemoryAccess<AccessSize::HALFWORD, SIGNED::NO, AccessMode::STORE> (emuInstance) ;
    }

    static void ANDS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) & op2; }
        );
    }

    static void MULS(Components::System &emuInstance) {
        Multiply<Accumulate::NO, AffectCPSR::NO>(emuInstance) ;
    }

    static void LDRH(Components::System &emuInstance) {
        MemoryAccess<AccessSize::HALFWORD, SIGNED::NO, AccessMode::LOAD> (emuInstance) ;
    }

    static void LDRSB(Components::System &emuInstance) {
        MemoryAccess<AccessSize::BYTE, SIGNED::YES, AccessMode::LOAD> (emuInstance) ;
    }

    static void LDRSH(Components::System &emuInstance) {
        MemoryAccess<AccessSize::HALFWORD, SIGNED::YES, AccessMode::LOAD> (emuInstance) ;
    }

    static void EOR(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) ^ op2; }
        );
    }

    static void MLA(Components::System &emuInstance) {
        Multiply<Accumulate::YES, AffectCPSR::NO>(emuInstance) ;
    }

    static void EORS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) ^ op2; }
        );
    }

    static void MLAS(Components::System &emuInstance) {
        Multiply<Accumulate::YES, AffectCPSR::YES>(emuInstance) ;
    }

    static void SUB(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + ~op2 + 1; }
        );
    }

    static void SUBS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + ~op2 + 1; }
        );
    }

    static void RSB(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (op2) + ~Rn + 1; }
        );
    }

    static void RSBS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (op2) + ~Rn + 1; }
        );
    }

    static void ADD(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + op2; }
        );
    }

    static void UMULL(Components::System &emuInstance) {
        MultiplyLong<Signed::NO, Accumulate::NO, AffectCPSR::NO>(emuInstance) ;
    }

    static void ADDS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + op2; }
        );
    }

    static void UMULLS(Components::System &emuInstance) {
        MultiplyLong<Signed::NO, Accumulate::NO, AffectCPSR::YES>(emuInstance) ;
    }

    static void ADC(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    unsigned carry = static_cast<unsigned> (EMU_CPU.TestPSRFlag(PSRBit::C));
                    return static_cast<uint64_t> (Rn) + op2 + EMU_CPU.TestPSRFlag(PSRBit::C);
                }
        );
    }

    static void UMLAL(Components::System &emuInstance) {
        MultiplyLong<Signed::NO, Accumulate::YES, AffectCPSR::NO>(emuInstance) ;
    }

    static void ADCS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    unsigned carry = static_cast<unsigned> (EMU_CPU.TestPSRFlag(PSRBit::C));
                    return static_cast<uint64_t> (Rn) + op2 + carry;
                }
        );
    }

    static void UMLALS(Components::System &emuInstance) {
        MultiplyLong<Signed::NO, Accumulate::YES, AffectCPSR::YES>(emuInstance) ;
    }

    static void SBC(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    unsigned carry = static_cast<unsigned> (EMU_CPU.TestPSRFlag(PSRBit::C));
                    return static_cast<uint64_t> (Rn) + ~op2 + 1 + carry + 0xffffffff;
                }
        );
    }

    static void SMULL(Components::System &emuInstance) {
        MultiplyLong<Signed::YES, Accumulate::NO, AffectCPSR::NO>(emuInstance) ;
    }

    static void SBCS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    unsigned carry = static_cast<unsigned> (EMU_CPU.TestPSRFlag(PSRBit::C));
                    return static_cast<uint64_t> (Rn) + ~op2 + 1 + carry + 0xffffffff;
                }
        );
    }

    static void SMULLS(Components::System &emuInstance) {
        MultiplyLong<Signed::YES, Accumulate::NO, AffectCPSR::YES>(emuInstance) ;
    }

    static void RSC(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    unsigned carry = static_cast<unsigned> (EMU_CPU.TestPSRFlag(PSRBit::C));
                    return static_cast<uint64_t> (op2) + ~Rn + 1 + carry + 0xffffffff;
                }
        );
    }

    static void SMLAL(Components::System &emuInstance) {
        MultiplyLong<Signed::YES, Accumulate::YES, AffectCPSR::NO>(emuInstance) ;
    }

    static void RSCS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    unsigned carry = static_cast<unsigned> (EMU_CPU.TestPSRFlag(PSRBit::C));
                    return static_cast<uint64_t> (op2) + ~Rn + 1 + carry + 0xffffffff;
                }
        );
    }

    static void SMLALS(Components::System &emuInstance) {
        MultiplyLong<Signed::YES, Accumulate::YES, AffectCPSR::YES>(emuInstance) ;
    }

    static void MRS(Components::System &emuInstance) {
        ACCESS(Type_ALU) ;
        bool PsBit = Utility::TestBit(EMU_CPU.Instruction(), 22);
        if (PsBit) {
            // Transfer from SPSR_<current_mode>
            unsigned currentSpsr = EMU_CPU.ReadSpsr(EMU_CPU.CurrentCPUMode()) ;
            RegName dstName = static_cast<RegName>(Get(Type::Rd));
            EMU_CPU.WriteReg(dstName, currentSpsr) ;
        } // if
        else {
            // Transfer from CPSR
            unsigned currentCpsr = EMU_CPU.ReadCpsr() ;
            RegName dstName = static_cast<RegName>(Get(Type::Rd));
            EMU_CPU.WriteReg(dstName, currentCpsr) ;
        } // else
    }

    static void SWP(Components::System &emuInstance) {
        ACCESS(Type_SWP) ;
        RegName RnName = GetRegName(Type::Rn) ;
        RegName RdName = GetRegName(Type::Rd) ;
        RegName RmName = GetRegName(Type::Rm) ;

        unsigned targetAddr = EMU_CPU.ReadReg(RnName) ;
        EMU_CLK += CLK_CONT.S(EMU_CPU.ProgramCounter()) ;
//        if (Get(Type::B)) {
//            EMU_CPU.WriteReg(RdName, EMU_MEM.Read8(targetAddr)) ;
//            EMU_CLK += CLK_CONT.ND(targetAddr, MMU_Enum::WIDTH::BYTE) ;
//            EMU_MEM.Write8(static_cast<uint8_t>(EMU_CPU.ReadReg(RmName))) ;
//            EMU_CLK += CLK_CONT.ND(targetAddr, MMU_Enum::WIDTH::BYTE) ;
//        } // if
//        else {
//            EMU_CPU.WriteReg(RdName, EMU_MEM.Read32(targetAddr)) ;
//            EMU_CLK += CLK_CONT.ND(targetAddr, MMU_Enum::WIDTH::WORD) ;
//            EMU_MEM.Write32(EMU_CPU.ReadReg(RmName)) ;
//            EMU_CLK += CLK_CONT.ND(targetAddr, MMU_Enum::WIDTH::WORD) ;
//        } // else

        EMU_CLK += CLK_CONT.I() ;
    }

    static void TST(Components::System &emuInstance) {
        ALUProcessor<ALUType::LOGICAL, AffectCPSR::YES, HasResult::TEST>(
                emuInstance,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) & op2;
                }
        );
    }

    static void MSR(Components::System &emuInstance) {
        ACCESS(0);
        EMU_CLK += CLK_CONT.S(EMU_CPU.ProgramCounter()) ;
        bool IBit = Utility::TestBit(EMU_CPU.Instruction(), 25) ;
        bool PdBit = Utility::TestBit(EMU_CPU.Instruction(), 22) ;
        bool flagOnly = !Utility::TestBit(EMU_CPU.Instruction(), 16) ;
        unsigned srcValue = 0 ;
        if (IBit)
            srcValue = Utility::rotr(Get(Type::imm), Get(Type::rotate)*2) ;
        else
            srcValue = EMU_CPU.ReadReg(static_cast<RegName>(Get(Type::Rm))) ;

        if (EMU_CPU.CurrentCPUMode() == CpuMode::USR || flagOnly)
            srcValue &= 0xf0000000 ;

        if (PdBit)
            EMU_CPU.WriteSpsr(EMU_CPU.CurrentCPUMode(), srcValue) ;
        else
            EMU_CPU.WriteCpsr(srcValue) ;
    }

    static void BX(Components::System &emuInstance) {
        ACCESS(Type_BX);
        EMU_CLK += CLK_CONT.S(EMU_CPU.R15()) ;
        unsigned newPC = EMU_CPU.ReadReg(static_cast<RegName>(Get(Type::Rn))) ;
        if (newPC & 0x1) {
            // switch to Thumb mode
            EMU_CPU.SetFlag(PSRBit::T) ;
            newPC -= 1 ;
        } // if
        else
            EMU_CPU.ClearFlag(PSRBit::T) ;
        EMU_CPU.WriteReg(RegName::pc, newPC) ;
    }

    static void TEQ(Components::System &emuInstance) {
        ALUProcessor<ALUType::LOGICAL, AffectCPSR::YES, HasResult::TEST>(
                emuInstance,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) ^ op2;
                }
        );
    }

    static void SWPB(Components::System &emuInstance) {}

    static void CMP(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::TEST>(
                emuInstance,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) + ~op2 + 1;
                }
        );
    }

    static void CMN(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::TEST>(
                emuInstance,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) + op2;
                }
        );
    }

    static void ORR(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) | op2;
                }
        );
    }

    static void ORRS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) | op2;
                }
        );
    }

    static void MOV(Components::System &emuInstance) {
        ALUProcessor<ALUType::LOGICAL, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
        );
    } // MOV()

    static void MOVS(Components::System &emuInstance) {
        ALUProcessor<ALUType::LOGICAL, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
        );
    } // MOVS()

    static void BIC(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) & (~op2);
                }
        );
    }

    static void BICS(Components::System &emuInstance) {
        ALUProcessor<ALUType::ARITHMETIC, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) & (~op2);
                }
        );
    }

    static void MVN(Components::System &emuInstance) {
        ALUProcessor<ALUType::LOGICAL, AffectCPSR::NO, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
        );
    } // MVN()

    static void MVNS(Components::System &emuInstance) {
        ALUProcessor<ALUType::LOGICAL, AffectCPSR::YES, HasResult::NORMAL>(
                emuInstance,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
        );
    } // MVNS()


    static void STR(Components::System &emuInstance) {
        MemoryAccess<AccessSize::WORD, AccessMode::STORE> (emuInstance) ;
    }

    static void LDR(Components::System &emuInstance) {
        MemoryAccess<AccessSize::WORD, AccessMode::LOAD> (emuInstance) ;
    }

    static void STRT(Components::System &emuInstance) {
        MemoryAccess<AccessSize::WORD, AccessMode::STORE> (emuInstance) ;
    }

    static void LDRT(Components::System &emuInstance) {
        MemoryAccess<AccessSize::WORD, AccessMode::LOAD> (emuInstance) ;
    }

    static void STRB(Components::System &emuInstance) {
        MemoryAccess<AccessSize::BYTE, AccessMode::STORE> (emuInstance) ;
    }

    static void LDRB(Components::System &emuInstance) {
        MemoryAccess<AccessSize::BYTE, AccessMode::LOAD> (emuInstance) ;
    }

    static void STRBT(Components::System &emuInstance) {
        MemoryAccess<AccessSize::BYTE, AccessMode::STORE> (emuInstance) ;
    }

    static void LDRBT(Components::System &emuInstance) {
        MemoryAccess<AccessSize::BYTE, AccessMode::LOAD> (emuInstance) ;
    }

    static void STMDA(Components::System &emuInstance) {}

    static void LDMDA(Components::System &emuInstance) {}

    static void STM(Components::System &emuInstance) {}

    static void LDM(Components::System &emuInstance) {}

    static void STMDB(Components::System &emuInstance) {}

    static void LDMDB(Components::System &emuInstance) {}

    static void STMIB(Components::System &emuInstance) {}

    static void LDMIB(Components::System &emuInstance) {}

    static void B(Components::System &emuInstance) {
        ACCESS(Type_B) ;
        const unsigned oldPC = EMU_CPU.ProgramCounter() ;
        unsigned newPC = 0 ;
        unsigned realOffset = (Get(Type::offset) << 2) ;

        EMU_CLK += CLK_CONT.S(oldPC) ;
        if (Utility::TestBit(realOffset, 25))
            realOffset |= 0xfc000000 ; // sign extend
        newPC = realOffset + 8 ;
        EMU_CPU.WriteReg(RegName::pc, newPC) ;
    }

    static void BL(Components::System &emuInstance) {
        ACCESS(Type_B) ;
        const unsigned oldPC = EMU_CPU.ProgramCounter() ;
        unsigned newPC = 0 ;
        unsigned realOffset = (Get(Type::offset) << 2) ;

        EMU_CLK += CLK_CONT.S(oldPC) ;
        EMU_CPU.WriteReg(RegName::lr, oldPC) ;

        if (Utility::TestBit(realOffset, 25))
            realOffset |= 0xfc000000 ; // sign extend
        newPC = realOffset + 8 ;
        EMU_CPU.WriteReg(RegName::pc, newPC) ;
    }

    static void STC(Components::System &emuInstance) {}

    static void LDC(Components::System &emuInstance) {}

    static void STCL(Components::System &emuInstance) {}

    static void LDCL(Components::System &emuInstance) {}

    static void CDP(Components::System &emuInstance) {}

    static void MCR(Components::System &emuInstance) {}

    static void MRC(Components::System &emuInstance) {}

    static void SVC(Components::System &emuInstance) {}

    static void UDF(Components::System &emuInstance) {}
}

#endif //TEST_ARM_HEADER_H
