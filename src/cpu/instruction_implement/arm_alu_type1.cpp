//
// Created by orzgg on 2020-07-10.
//

#include <arm_header.h>
#include <arm_implement_tools.h>
#include <macro.h>

void ArmHandler::MOV(Components::System* system) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
    );
} // MOV()

void ArmHandler::MOVS(Components::System* system) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(op2); }
    );
} // MOVS()

void ArmHandler::MVN(Components::System* system) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
    );
} // MVN()

void ArmHandler::MVNS(Components::System* system) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return static_cast<uint64_t>(~op2); }
    );
} // MVNS()



void ArmHandler::MUL(Components::System* system) {

}

void ArmHandler::STRH(Components::System* system) {

}

void ArmHandler::MULS(Components::System* system) {

}

void ArmHandler::LDRH(Components::System* system) {

}

void ArmHandler::LDRSB(Components::System* system) {

}

void ArmHandler::LDRSH(Components::System* system) {

}


void ArmHandler::MLA(Components::System* system) {

}


void ArmHandler::MLAS(Components::System* system) {

}






void ArmHandler::UMULL(Components::System* system) {

}



void ArmHandler::UMULLS(Components::System* system) {

}



void ArmHandler::UMLAL(Components::System* system) {

}



void ArmHandler::UMLALS(Components::System* system) {

}

void ArmHandler::SBC(Components::System* system) {

}

void ArmHandler::SMULL(Components::System* system) {

}

void ArmHandler::SBCS(Components::System* system) {

}

void ArmHandler::SMULLS(Components::System* system) {

}

void ArmHandler::RSC(Components::System* system) {

}

void ArmHandler::SMLAL(Components::System* system) {

}

void ArmHandler::RSCS(Components::System* system) {

}

void ArmHandler::SMLALS(Components::System* system) {

}

void ArmHandler::MRS(Components::System* system) {

}

void ArmHandler::SWP(Components::System* system) {

}

void ArmHandler::MSR(Components::System* system) {

}

void ArmHandler::BX(Components::System* system) {

}

void ArmHandler::SWPB(Components::System* system) {

}

void ArmHandler::ORR(Components::System* system) {

}

void ArmHandler::ORRS(Components::System* system) {

}

void ArmHandler::BIC(Components::System* system) {

}

void ArmHandler::BICS(Components::System* system) {

}

void ArmHandler::STR(Components::System* system) {

}

void ArmHandler::LDR(Components::System* system) {

}

void ArmHandler::STRT(Components::System* system) {

}

void ArmHandler::LDRT(Components::System* system) {

}

void ArmHandler::STRB(Components::System* system) {

}

void ArmHandler::LDRB(Components::System* system) {

}

void ArmHandler::STRBT(Components::System* system) {

}

void ArmHandler::LDRBT(Components::System* system) {

}

void ArmHandler::STMDA(Components::System* system) {

}

void ArmHandler::LDMDA(Components::System* system) {

}

void ArmHandler::STM(Components::System* system) {

}

void ArmHandler::LDM(Components::System* system) {

}

void ArmHandler::STMDB(Components::System* system) {

}

void ArmHandler::LDMDB(Components::System* system) {

}

void ArmHandler::STMIB(Components::System* system) {

}

void ArmHandler::LDMIB(Components::System* system) {

}

void ArmHandler::B(Components::System* system) {

}

void ArmHandler::BL(Components::System* system) {

}

void ArmHandler::STC(Components::System* system) {

}

void ArmHandler::LDC(Components::System* system) {

}

void ArmHandler::STCL(Components::System* system) {

}

void ArmHandler::LDCL(Components::System* system) {

}

void ArmHandler::CDP(Components::System* system) {

}

void ArmHandler::MCR(Components::System* system) {

}

void ArmHandler::MRC(Components::System* system) {

}

void ArmHandler::SVC(Components::System* system) {

}

void ArmHandler::UDF(Components::System* system) {

}
