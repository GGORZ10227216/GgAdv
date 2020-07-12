//
// Created by orzgg on 2020-07-11.
//
#include <arm_header.h>
#include <arm_implement_tools.h>
#include <macro.h>

using namespace Cycle ;

void ArmHandler::CMP(Components::CPU &cpu) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::TEST> (
            cpu,
            [](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t>(Rn) - op2 ;
            }
    );
}

void ArmHandler::CMN(Components::CPU &cpu) {
    ALUProcessor<ALUType::ARITHMETIC, CPSRaffect::S, HasResult::TEST> (
            cpu,
            [](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t>(Rn) + op2 ;
            }
    );
}

void ArmHandler::TST(Components::CPU &cpu) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::TEST> (
            cpu,
            [](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t>(Rn) & op2 ;
            }
    );
}

void ArmHandler::TEQ(Components::CPU &cpu) {
    ALUProcessor<ALUType::LOGICAL, CPSRaffect::S, HasResult::TEST> (
            cpu,
            [](unsigned Rn, unsigned op2) {
                return static_cast<uint64_t>(Rn) ^ op2 ;
            }
    );
}