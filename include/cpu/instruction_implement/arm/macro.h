//
// Created by orzgg on 2020-07-10.
//

#ifndef TEST_MACRO_H
#define TEST_MACRO_H

#define ALU_PROLOGUE \
    EMU_CYCLE += cpu.cycleTools.S(cpu.ReadReg(RegName::pc)) ; \
    using Type = disassemble::instruction_info<DecodeMode::ARM, 0>; \
    auto Get = [&](unsigned idx) { return Type::access[idx](cpu.Instruction()) ;};\
    bool shiftCarry = false ;\

#define ALU_EPILOGUE \
    if (Get(Type::Rd) == RegName::pc) \
        cpu.FillPipeline() ;
#endif //TEST_MACRO_H
