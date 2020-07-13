//
// Created by orzgg on 2020-07-10.
//

#include <system_components.h>

#ifndef TEST_ARM_HEADER_H
#define TEST_ARM_HEADER_H

namespace ArmHandler {
    void AND(Components::System* system);

    void MUL(Components::System* system);

    void STRH(Components::System* system);

    void ANDS(Components::System* system);

    void MULS(Components::System* system);

    void LDRH(Components::System* system);

    void LDRSB(Components::System* system);

    void LDRSH(Components::System* system);

    void EOR(Components::System* system);

    void MLA(Components::System* system);

    void EORS(Components::System* system);

    void MLAS(Components::System* system);

    void SUB(Components::System* system);

    void SUBS(Components::System* system);

    void RSB(Components::System* system);

    void RSBS(Components::System* system);

    void ADD(Components::System* system);

    void UMULL(Components::System* system);

    void ADDS(Components::System* system);

    void UMULLS(Components::System* system);

    void ADC(Components::System* system);

    void UMLAL(Components::System* system);

    void ADCS(Components::System* system);

    void UMLALS(Components::System* system);

    void SBC(Components::System* system);

    void SMULL(Components::System* system);

    void SBCS(Components::System* system);

    void SMULLS(Components::System* system);

    void RSC(Components::System* system);

    void SMLAL(Components::System* system);

    void RSCS(Components::System* system);

    void SMLALS(Components::System* system);

    void MRS(Components::System* system);

    void SWP(Components::System* system);

    void TST(Components::System* system);

    void MSR(Components::System* system);

    void BX(Components::System* system);

    void TEQ(Components::System* system);

    void SWPB(Components::System* system);

    void CMP(Components::System* system);

    void CMN(Components::System* system);

    void ORR(Components::System* system);

    void ORRS(Components::System* system);

    void MOV(Components::System* system);

    void MOVS(Components::System* system);

    void BIC(Components::System* system);

    void BICS(Components::System* system);

    void MVN(Components::System* system);

    void MVNS(Components::System* system);

    void STR(Components::System* system);

    void LDR(Components::System* system);

    void STRT(Components::System* system);

    void LDRT(Components::System* system);

    void STRB(Components::System* system);

    void LDRB(Components::System* system);

    void STRBT(Components::System* system);

    void LDRBT(Components::System* system);

    void STMDA(Components::System* system);

    void LDMDA(Components::System* system);

    void STM(Components::System* system);

    void LDM(Components::System* system);

    void STMDB(Components::System* system);

    void LDMDB(Components::System* system);

    void STMIB(Components::System* system);

    void LDMIB(Components::System* system);

    void B(Components::System* system);

    void BL(Components::System* system);

    void STC(Components::System* system);

    void LDC(Components::System* system);

    void STCL(Components::System* system);

    void LDCL(Components::System* system);

    void CDP(Components::System* system);

    void MCR(Components::System* system);

    void MRC(Components::System* system);

    void SVC(Components::System* system);

    void UDF(Components::System* system);
}

#endif //TEST_ARM_HEADER_H
