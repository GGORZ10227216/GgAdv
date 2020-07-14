//
// Created by orzgg on 2020-07-10.
//

#include <system_components.h>
#include <arm_implement_tools.h>

#ifndef TEST_ARM_HEADER_H
#define TEST_ARM_HEADER_H

namespace ArmHandler {
    static void AND(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) & op2; }
        );
    }

    static void MUL(Components::System &system) {}

    static void STRH(Components::System &system) {}

    static void ANDS(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) & op2; }
        );
    }

    static void MULS(Components::System &system) {}

    static void LDRH(Components::System &system) {}

    static void LDRSB(Components::System &system) {}

    static void LDRSH(Components::System &system) {}

    static void EOR(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) ^ op2; }
        );
    }

    static void MLA(Components::System &system) {}

    static void EORS(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) ^ op2; }
        );
    }

    static void MLAS(Components::System &system) {}

    static void SUB(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) - op2; }
        );
    }

    static void SUBS(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) - op2; }
        );
    }

    static void RSB(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (op2) - Rn; }
        );
    }

    static void RSBS(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (op2) - Rn; }
        );
    }

    static void ADD(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + op2; }
        );
    }

    static void UMULL(Components::System &system) {}

    static void ADDS(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + op2; }
        );
    }

    static void UMULLS(Components::System &system) {}

    static void ADC(Components::System &system) {
        unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C));
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) + op2 + carry;
                }
        );
    }

    static void UMLAL(Components::System &system) {}

    static void ADCS(Components::System &system) {
        unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C));
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) + op2 + carry;
                }
        );
    }

    static void UMLALS(Components::System &system) {}

    static void SBC(Components::System &system) {
        unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C));
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) - op2 + carry - 1;
                }
        );
    }

    static void SMULL(Components::System &system) {}

    static void SBCS(Components::System &system) {
        unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C));
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) - op2 + carry - 1;
                }
        );
    }

    static void SMULLS(Components::System &system) {}

    static void RSC(Components::System &system) {
        unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C));
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (op2) - Rn + carry - 1;
                }
        );
    }

    static void SMLAL(Components::System &system) {}

    static void RSCS(Components::System &system) {
        unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C));
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (op2) - Rn + carry - 1;
                }
        );
    }

    static void SMLALS(Components::System &system) {}

    static void MRS(Components::System &system) {}

    static void SWP(Components::System &system) {}

    static void TST(Components::System &system) {
        ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::TEST>(
                system,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) & op2;
                }
        );
    }

    static void MSR(Components::System &system) {}

    static void BX(Components::System &system) {}

    static void TEQ(Components::System &system) {
        ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::TEST>(
                system,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) ^ op2;
                }
        );
    }

    static void SWPB(Components::System &system) {}

    static void CMP(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::TEST>(
                system,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) - op2;
                }
        );
    }

    static void CMN(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::TEST>(
                system,
                [](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t>(Rn) + op2;
                }
        );
    }

    static void ORR(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) | op2;
                }
        );
    }

    static void ORRS(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) | op2;
                }
        );
    }

    static void MOV(Components::System &system) {
        ALUProcessor<ALUType::LOGICAL, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
        );
    } // MOV()

    static void MOVS(Components::System &system) {
        ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
        );
    } // MOVS()

    static void BIC(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) & (~op2);
                }
        );
    }

    static void BICS(Components::System &system) {
        ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [&](unsigned Rn, unsigned op2) {
                    return static_cast<uint64_t> (Rn) & (~op2);
                }
        );
    }

    static void MVN(Components::System &system) {
        ALUProcessor<ALUType::LOGICAL, CPSRaffect::NON_S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
        );
    } // MVN()

    static void MVNS(Components::System &system) {
        ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::NORMAL>(
                system,
                [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
        );
    } // MVNS()


    static void STR(Components::System &system) {}

    static void LDR(Components::System &system) {}

    static void STRT(Components::System &system) {}

    static void LDRT(Components::System &system) {}

    static void STRB(Components::System &system) {}

    static void LDRB(Components::System &system) {}

    static void STRBT(Components::System &system) {}

    static void LDRBT(Components::System &system) {}

    static void STMDA(Components::System &system) {}

    static void LDMDA(Components::System &system) {}

    static void STM(Components::System &system) {}

    static void LDM(Components::System &system) {}

    static void STMDB(Components::System &system) {}

    static void LDMDB(Components::System &system) {}

    static void STMIB(Components::System &system) {}

    static void LDMIB(Components::System &system) {}

    static void B(Components::System &system) {}

    static void BL(Components::System &system) {}

    static void STC(Components::System &system) {}

    static void LDC(Components::System &system) {}

    static void STCL(Components::System &system) {}

    static void LDCL(Components::System &system) {}

    static void CDP(Components::System &system) {}

    static void MCR(Components::System &system) {}

    static void MRC(Components::System &system) {}

    static void SVC(Components::System &system) {}

    static void UDF(Components::System &system) {}
}

#endif //TEST_ARM_HEADER_H
