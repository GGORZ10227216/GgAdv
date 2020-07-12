//
// Created by orzgg on 2020-05-20.
//
#pragma once

#include <array>
#include <string>
#include <cpu_decode.h>
#include <instruction.h>

#ifndef TABLE_GEN_HELPER_H
#define TABLE_GEN_INSTRUCTION_HANDLER_H
class instruction ;

namespace disassemble {
    using ToStringHandler = std::string(*)(const ArmInstruction& self);

    std::string DP_ToString(const ArmInstruction&); // 0
    std::string MUL_ToString(const ArmInstruction&); // 1
    std::string MULL_ToString(const ArmInstruction&); // 2
    std::string SWP_ToString(const ArmInstruction&); // 3
    std::string BX_ToString(const ArmInstruction&); // 4
    std::string HDT_ToString(const ArmInstruction&); // 5
    std::string DT_ToString(const ArmInstruction&); // 6
    std::string UDF_ToString(const ArmInstruction&); // 7
    std::string MDT_ToString(const ArmInstruction&); // 8
    std::string B_ToString(const ArmInstruction&); // 9
    std::string CDT_ToString(const ArmInstruction&); // 10
    std::string CDP_ToString(const ArmInstruction&); // 11
    std::string CRT_ToString(const ArmInstruction&); // 12
    std::string SWI_ToString(const ArmInstruction&); // 13

    constexpr std::array<ToStringHandler, 14> handlerTable{
            DP_ToString,
            MUL_ToString,
            MULL_ToString,
            SWP_ToString,
            BX_ToString,
            HDT_ToString,
            DT_ToString,
            UDF_ToString,
            MDT_ToString,
            B_ToString,
            CDT_ToString,
            CDP_ToString,
            CRT_ToString,
            SWI_ToString
    };
};

#endif //TABLE_GEN_HELPER_H
