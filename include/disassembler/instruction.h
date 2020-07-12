//
// Created by orzgg on 2020-06-18.
//

#ifndef TABLE_GEN_INSTRUCTION_H
#define TABLE_GEN_INSTRUCTION_H

#include <cstdint>
#include <cpu_decode.h>
#include <disassemble/instruction_access.h>

struct RawInstruction {
    union Binary {
        uint32_t word ; uint16_t half[2] ;
    };

    Binary raw ;

    constexpr bool operator== ( const int& i ) const {
        return i == raw.word ;
    }

    constexpr operator unsigned int() const {
        return raw.word ;
    }
};

struct ArmInstruction : RawInstruction {};

struct ThumbInstruction : RawInstruction {
    const unsigned type ;
    ThumbInstruction( unsigned int rawI ) ;
    uint32_t DecodeBLOffset() const ;
};

#endif //TABLE_GEN_INSTRUCTION_H
