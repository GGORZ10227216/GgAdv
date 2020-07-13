//
// Created by orzgg on 2020-07-11.
//
#include <arm_header.h>
#include <arm_implement_tools.h>
#include <macro.h>

void ArmHandler::AND(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn & op2; }
    );
}

void ArmHandler::ANDS(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn & op2; }
    );
}

void ArmHandler::EOR(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn ^ op2; }
    );
}

void ArmHandler::EORS(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn ^ op2; }
    );
}

void ArmHandler::SUB(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn - op2; }
    );
}

void ArmHandler::SUBS(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn - op2; }
    );
}

void ArmHandler::RSB(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return op2 - Rn; }
    );
}

void ArmHandler::RSBS(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return op2 - Rn; }
    );
}

void ArmHandler::ADD(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn + op2 ; }
    );
}

void ArmHandler::ADDS(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [](unsigned Rn, unsigned op2) { return Rn + op2; }
    );
}

void ArmHandler::ADC(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::NON_S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) { return Rn + op2; }
    );
}

void ArmHandler::ADCS(Components::System* system) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::NORMAL>(
            system,
            [&](unsigned Rn, unsigned op2) { return Rn + op2; }
    );
}