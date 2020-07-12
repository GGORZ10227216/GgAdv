//
// Created by orzgg on 2020-07-10.
//

#include <arm_header.h>
#include <arm_implement_tools.h>
#include <macro.h>

using namespace Cycle;

void ArmHandler::MOV(Components::CPU &cpu) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::NON_S, HasResult::NORMAL>(
            cpu,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
    );
} // MOV()

void ArmHandler::MOVS(Components::CPU &cpu) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::NORMAL>(
            cpu,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
    );
} // MOVS()

void ArmHandler::MVN(Components::CPU &cpu) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::NON_S, HasResult::NORMAL>(
            cpu,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
    );
} // MVN()

void ArmHandler::MVNS(Components::CPU &cpu) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::NORMAL>(
            cpu,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
    );
} // MVNS()



void ArmHandler::MUL(Components::CPU &cpu) {

}

void ArmHandler::STRH(Components::CPU &cpu) {

}

void ArmHandler::MULS(Components::CPU &cpu) {

}

void ArmHandler::LDRH(Components::CPU &cpu) {

}

void ArmHandler::LDRSB(Components::CPU &cpu) {

}

void ArmHandler::LDRSH(Components::CPU &cpu) {

}


void ArmHandler::MLA(Components::CPU &cpu) {

}


void ArmHandler::MLAS(Components::CPU &cpu) {

}


void ArmHandler::RSB(Components::CPU &cpu) {

}

void ArmHandler::RSBS(Components::CPU &cpu) {

}

void ArmHandler::ADD(Components::CPU &cpu) {

}

void ArmHandler::UMULL(Components::CPU &cpu) {

}

void ArmHandler::ADDS(Components::CPU &cpu) {

}

void ArmHandler::UMULLS(Components::CPU &cpu) {

}

void ArmHandler::ADC(Components::CPU &cpu) {

}

void ArmHandler::UMLAL(Components::CPU &cpu) {

}

void ArmHandler::ADCS(Components::CPU &cpu) {

}

void ArmHandler::UMLALS(Components::CPU &cpu) {

}

void ArmHandler::SBC(Components::CPU &cpu) {

}

void ArmHandler::SMULL(Components::CPU &cpu) {

}

void ArmHandler::SBCS(Components::CPU &cpu) {

}

void ArmHandler::SMULLS(Components::CPU &cpu) {

}

void ArmHandler::RSC(Components::CPU &cpu) {

}

void ArmHandler::SMLAL(Components::CPU &cpu) {

}

void ArmHandler::RSCS(Components::CPU &cpu) {

}

void ArmHandler::SMLALS(Components::CPU &cpu) {

}

void ArmHandler::MRS(Components::CPU &cpu) {

}

void ArmHandler::SWP(Components::CPU &cpu) {

}

void ArmHandler::MSR(Components::CPU &cpu) {

}

void ArmHandler::BX(Components::CPU &cpu) {

}

void ArmHandler::SWPB(Components::CPU &cpu) {

}

void ArmHandler::ORR(Components::CPU &cpu) {

}

void ArmHandler::ORRS(Components::CPU &cpu) {

}

void ArmHandler::BIC(Components::CPU &cpu) {

}

void ArmHandler::BICS(Components::CPU &cpu) {

}

void ArmHandler::STR(Components::CPU &cpu) {

}

void ArmHandler::LDR(Components::CPU &cpu) {

}

void ArmHandler::STRT(Components::CPU &cpu) {

}

void ArmHandler::LDRT(Components::CPU &cpu) {

}

void ArmHandler::STRB(Components::CPU &cpu) {

}

void ArmHandler::LDRB(Components::CPU &cpu) {

}

void ArmHandler::STRBT(Components::CPU &cpu) {

}

void ArmHandler::LDRBT(Components::CPU &cpu) {

}

void ArmHandler::STMDA(Components::CPU &cpu) {

}

void ArmHandler::LDMDA(Components::CPU &cpu) {

}

void ArmHandler::STM(Components::CPU &cpu) {

}

void ArmHandler::LDM(Components::CPU &cpu) {

}

void ArmHandler::STMDB(Components::CPU &cpu) {

}

void ArmHandler::LDMDB(Components::CPU &cpu) {

}

void ArmHandler::STMIB(Components::CPU &cpu) {

}

void ArmHandler::LDMIB(Components::CPU &cpu) {

}

void ArmHandler::B(Components::CPU &cpu) {

}

void ArmHandler::BL(Components::CPU &cpu) {

}

void ArmHandler::STC(Components::CPU &cpu) {

}

void ArmHandler::LDC(Components::CPU &cpu) {

}

void ArmHandler::STCL(Components::CPU &cpu) {

}

void ArmHandler::LDCL(Components::CPU &cpu) {

}

void ArmHandler::CDP(Components::CPU &cpu) {

}

void ArmHandler::MCR(Components::CPU &cpu) {

}

void ArmHandler::MRC(Components::CPU &cpu) {

}

void ArmHandler::SVC(Components::CPU &cpu) {

}

void ArmHandler::UDF(Components::CPU &cpu) {

}
