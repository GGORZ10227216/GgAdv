//
// Created by orzgg on 2020-07-11.
//
#include <arm_header.h>
#include <arm_implement_tools.h>
#include <macro.h>

void ArmHandler::AND(Components::CPU &cpu) {
    ALU_PROLOGUE
    RegName RnName = static_cast<RegName> (Get(Type::Rn));
    RegName RdName = static_cast<RegName> (Get(Type::Rd));
    unsigned RnValue = cpu.ReadReg(RnName) ;
    unsigned op2 = Operand2<Type>(cpu, Get, shiftCarry);
    unsigned result = RnValue & op2 ;
    cpu.WriteReg(RdName, result);
    ALU_EPILOGUE
}

void ArmHandler::ANDS(Components::CPU &cpu) {
    ALU_PROLOGUE
    RegName RnName = static_cast<RegName> (Get(Type::Rn));
    RegName RdName = static_cast<RegName> (Get(Type::Rd));
    unsigned RnValue = cpu.ReadReg(RnName) ;
    unsigned op2 = Operand2<Type>(cpu, Get, shiftCarry);
    unsigned result = RnValue & op2 ;
    cpu.WriteReg(RdName, result);
    CPSR_Logical(cpu, op2, shiftCarry) ;
    ALU_EPILOGUE
}

void ArmHandler::EOR(Components::CPU &cpu) {
    ALU_PROLOGUE
    RegName RnName = static_cast<RegName> (Get(Type::Rn));
    RegName RdName = static_cast<RegName> (Get(Type::Rd));
    unsigned RnValue = cpu.ReadReg(RnName) ;
    unsigned op2 = Operand2<Type>(cpu, Get, shiftCarry);
    unsigned result = RnValue ^ op2 ;
    cpu.WriteReg(RdName, result);
    ALU_EPILOGUE
}

void ArmHandler::EORS(Components::CPU &cpu) {
    ALU_PROLOGUE
    RegName RnName = static_cast<RegName> (Get(Type::Rn));
    RegName RdName = static_cast<RegName> (Get(Type::Rd));
    unsigned RnValue = cpu.ReadReg(RnName) ;
    unsigned op2 = Operand2<Type>(cpu, Get, shiftCarry);
    unsigned result = RnValue ^ op2 ;
    cpu.WriteReg(RdName, result);
    CPSR_Logical(cpu, op2, shiftCarry) ;
    ALU_EPILOGUE
}

void ArmHandler::SUB(Components::CPU &cpu) {
    ALU_PROLOGUE
    RegName RnName = static_cast<RegName> (Get(Type::Rn));
    RegName RdName = static_cast<RegName> (Get(Type::Rd));
    uint64_t RnValue = cpu.ReadReg(RnName) ;
    unsigned op2 = Operand2<Type>(cpu, Get, shiftCarry);
    unsigned result = RnValue - op2 ;
    cpu.WriteReg(RdName, result);
    ALU_EPILOGUE
}

void ArmHandler::SUBS(Components::CPU &cpu) {
    ALU_PROLOGUE
    RegName RnName = static_cast<RegName> (Get(Type::Rn));
    RegName RdName = static_cast<RegName> (Get(Type::Rd));
    uint64_t RnValue = cpu.ReadReg(RnName) ;
    unsigned op2 = Operand2<Type>(cpu, Get, shiftCarry);
    uint64_t result = RnValue - op2 ;
    cpu.WriteReg(RdName, result);
    CPSR_Arithmetic(cpu, RnValue, op2, result) ;
    ALU_EPILOGUE
}