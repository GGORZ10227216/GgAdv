//
// Created by orzgg on 2020-05-04.
//
#pragma once

#ifndef DECODER_DECODE_TOOLS_H
#define DECODER_DECODE_TOOLS_H

#include <string>
#include <array>
#include <tuple>
#include <iostream>
#include <disassemble/utility.h>
#include <cstdint>

namespace cpu_decode {
    static constexpr int invalid_value = INT32_MAX ;
    static constexpr int unknown_opcode = -1 ;
    static constexpr int not_implemented_yet = -2 ;

    using InstructionFormat = uint32_t ;

    enum Field {
        cond, Rd, RdHi = Rd, Rn,
        RdLo = Rn, Rs, Rm, shType,
        shAmount, rotate, imm, regList, offset, post, // post is not a real field
        A, B, H, I, L, N, P, S, U, W, O1, O2, O3, O4, RsM, opcode
    } ;

    enum Mode { ARM, THUMB } ;

    enum FunctionType {
        DataProcessing, Multiply, MultiplyLong, SingleDataSwap,
        BranchAndExchange, DataTransferH, DataTransfer, Undefined,
        DataTransferM, Branch, CoDataTransfer, CoDataOperation,
        CoRegTransfer, SoftInterrupt
    };

    enum COND_CODE {
        EQ, NE, CS, CC,
        MI, PL, VS, VC,
        HI, LS, GE, LT,
        GT, LE, AL
    };

    enum DP_OPCODE {
        And, Eor, Sub, Rsb,
        Add, Adc, Sbc, Rsc,
        Tst, Teq, Cmp, Cmn,
        Orr, Mov, Bic, Mvn
    };

    enum REG {
            r0, r1, r2, r3, r4, r5, r6,
            r7, r8, r9, r10, r11, r12, r13,
            r14, r15, sb = r9, sl = r10, fp = r11,
            ip = r12, sp = r13, lr = r14, pc = r15
    };

    enum SHIFT_TYPE {
            LSL, LSR, ASR, ROR
    };
    
    constexpr std::array<const char*, 15> condition_name = {
            "eq", "ne", "cs", "cc",
            "mi", "pl", "vs", "vc",
            "hi", "ls", "ge", "lt",
            "gt", "le", ""
    };
    
    const std::array<std::string,16> data_processing_opcode = {
        "and", "eor", "sub", "rsb",
        "add", "adc", "sbc", "rsc",
        "tst", "teq", "cmp", "cmn",
        "orr", "mov", "bic", "mvn"
    };

    const std::string register_name[] = {
        "r0", "r1", "r2", "r3", "r4", "r5", "r6",
        "r7", "r8", "sb", "sl", "fp", "ip", "sp",
        "lr", "pc"
    };

    const std::string shift_type_name[] {
        "lsl", "lsr", "asr", "ror"
    };

    constexpr static std::array<std::tuple<unsigned,unsigned>,11> limitTable = {
            std::make_tuple(cpu_decode::EQ, cpu_decode::AL),
            std::make_tuple(cpu_decode::r0, cpu_decode::r15),
            std::make_tuple(cpu_decode::r0, cpu_decode::r15),
            std::make_tuple(cpu_decode::r0, cpu_decode::r15),
            std::make_tuple(cpu_decode::r0, cpu_decode::r15),
            std::make_tuple(cpu_decode::LSL, cpu_decode::ROR),
            std::make_tuple(0, 31),
            std::make_tuple(0, 15),
            std::make_tuple(0, 255),
            std::make_tuple(1, 65535),
            std::make_tuple(0, 0xffffff)
    } ;

    class HexStr {
    public :
        int32_t num ;
        HexStr( const int& number ) : num( number ) {}
        friend std::ostream& operator<<( std::ostream& out, const HexStr& h ) {
            if ( h.num < 0xa && h.num >= 0 )
                out << h.num ;
            else
                out << std::hex << std::showbase << h.num ;
            return out ;
        }
    };
}

using condition = cpu_decode::COND_CODE ;

#endif //DECODER_DECODE_TOOLS_H
