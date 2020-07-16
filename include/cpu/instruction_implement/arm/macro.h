//
// Created by orzgg on 2020-07-10.
//

#ifndef TEST_MACRO_H
#define TEST_MACRO_H

#define ACCESS(typeCode) \
    using Type = disassemble::instruction_info<DecodeMode::ARM, typeCode> ;\
    auto Get = [&](unsigned idx) {\
        return Type::access[ idx ](emuInstance.cpu.Instruction()) ;\
    }

#endif //TEST_MACRO_H
