//
// Created by orzgg on 2020-07-11.
//
#include <arm_header.h>
#include <arm_implement_tools.h>
#include <macro.h>

//void ArmHandler::AND(Components::System& system) {
//    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
//            system,
//            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) & op2; }
//    );
//}

void ArmHandler::ANDS(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) & op2; }
    );
}

void ArmHandler::EOR(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) ^ op2; }
    );
}

void ArmHandler::EORS(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) ^ op2; }
    );
}

void ArmHandler::SUB(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) - op2; }
    );
}

void ArmHandler::SUBS(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) - op2; }
    );
}

void ArmHandler::RSB(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (op2) - Rn; }
    );
}

void ArmHandler::RSBS(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (op2) - Rn; }
    );
}

void ArmHandler::ADD(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + op2 ; }
    );
}

void ArmHandler::ADDS(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t> (Rn) + op2; }
    );
}

void ArmHandler::ADC(Components::System& system) {
    unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C)) ;
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) + op2 + carry ;
            }
    );
}

void ArmHandler::ADCS(Components::System& system) {
    unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C)) ;
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) + op2 + carry;
            }
    );
}

void ArmHandler::SBC(Components::System& system) {
    unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C)) ;
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) - op2 + carry - 1;
            }
    );
}

void ArmHandler::SBCS(Components::System& system) {
    unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C)) ;
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) - op2 + carry - 1;
            }
    );
}

void ArmHandler::RSC(Components::System& system) {
    unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C)) ;
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (op2) - Rn + carry - 1;
            }
    );
}

void ArmHandler::RSCS(Components::System& system) {
    unsigned carry = static_cast<unsigned> (system.cpu.TestPSRFlag(PSRBit::C)) ;
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (op2) - Rn + carry - 1;
            }
    );
}

void ArmHandler::ORR(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) | op2 ;
            }
    );
}

void ArmHandler::ORRS(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) | op2 ;
            }
    );
}

void ArmHandler::BIC(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) & (~op2) ;
            }
    );
}

void ArmHandler::BICS(Components::System& system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t> (Rn) & (~op2) ;
            }
    );
}