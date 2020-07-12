//
// Created by orzgg on 2020-07-10.
//

#include <cpu.h>

#ifndef TEST_ARM_HEADER_H
#define TEST_ARM_HEADER_H

namespace ArmHandler {
    void AND(Components::CPU &cpu);

    void MUL(Components::CPU &cpu);

    void STRH(Components::CPU &cpu);

    void ANDS(Components::CPU &cpu);

    void MULS(Components::CPU &cpu);

    void LDRH(Components::CPU &cpu);

    void LDRSB(Components::CPU &cpu);

    void LDRSH(Components::CPU &cpu);

    void EOR(Components::CPU &cpu);

    void MLA(Components::CPU &cpu);

    void EORS(Components::CPU &cpu);

    void MLAS(Components::CPU &cpu);

    void SUB(Components::CPU &cpu);

    void SUBS(Components::CPU &cpu);

    void RSB(Components::CPU &cpu);

    void RSBS(Components::CPU &cpu);

    void ADD(Components::CPU &cpu);

    void UMULL(Components::CPU &cpu);

    void ADDS(Components::CPU &cpu);

    void UMULLS(Components::CPU &cpu);

    void ADC(Components::CPU &cpu);

    void UMLAL(Components::CPU &cpu);

    void ADCS(Components::CPU &cpu);

    void UMLALS(Components::CPU &cpu);

    void SBC(Components::CPU &cpu);

    void SMULL(Components::CPU &cpu);

    void SBCS(Components::CPU &cpu);

    void SMULLS(Components::CPU &cpu);

    void RSC(Components::CPU &cpu);

    void SMLAL(Components::CPU &cpu);

    void RSCS(Components::CPU &cpu);

    void SMLALS(Components::CPU &cpu);

    void MRS(Components::CPU &cpu);

    void SWP(Components::CPU &cpu);

    void TST(Components::CPU &cpu);

    void MSR(Components::CPU &cpu);

    void BX(Components::CPU &cpu);

    void TEQ(Components::CPU &cpu);

    void SWPB(Components::CPU &cpu);

    void CMP(Components::CPU &cpu);

    void CMN(Components::CPU &cpu);

    void ORR(Components::CPU &cpu);

    void ORRS(Components::CPU &cpu);

    void MOV(Components::CPU &cpu);

    void MOVS(Components::CPU &cpu);

    void BIC(Components::CPU &cpu);

    void BICS(Components::CPU &cpu);

    void MVN(Components::CPU &cpu);

    void MVNS(Components::CPU &cpu);

    void STR(Components::CPU &cpu);

    void LDR(Components::CPU &cpu);

    void STRT(Components::CPU &cpu);

    void LDRT(Components::CPU &cpu);

    void STRB(Components::CPU &cpu);

    void LDRB(Components::CPU &cpu);

    void STRBT(Components::CPU &cpu);

    void LDRBT(Components::CPU &cpu);

    void STMDA(Components::CPU &cpu);

    void LDMDA(Components::CPU &cpu);

    void STM(Components::CPU &cpu);

    void LDM(Components::CPU &cpu);

    void STMDB(Components::CPU &cpu);

    void LDMDB(Components::CPU &cpu);

    void STMIB(Components::CPU &cpu);

    void LDMIB(Components::CPU &cpu);

    void B(Components::CPU &cpu);

    void BL(Components::CPU &cpu);

    void STC(Components::CPU &cpu);

    void LDC(Components::CPU &cpu);

    void STCL(Components::CPU &cpu);

    void LDCL(Components::CPU &cpu);

    void CDP(Components::CPU &cpu);

    void MCR(Components::CPU &cpu);

    void MRC(Components::CPU &cpu);

    void SVC(Components::CPU &cpu);

    void UDF(Components::CPU &cpu);
}

#endif //TEST_ARM_HEADER_H
