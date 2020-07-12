//
// Created by orzgg on 2020-06-18.
//

#ifndef TABLE_GEN_ARM_INFO_H
#define TABLE_GEN_ARM_INFO_H

#include <utility>
#include <instruction.h>
#include <disassemble/utility.h>
#include <disassemble/information/instruction_info.h>

namespace disassemble {
    namespace arm_field_size {
        enum {
            offset24 = 24,
            regList = 16,
            offset12 = 12,
            op2Imm = 8, offset8 = 8,
            op2ShAmount = 5,
            op2Rot = 4, cond = 4, reg = 4, opcode = 4,
            op2ShType = 2,
            flag = 1
        } ;
    } ;

    using namespace arm_field_size ;

    template<>
    struct instruction_info<DecodeMode::ARM, 0> {
        enum Field {
            condition, I, op, S, Rn, Rd, shAmount, shType, RsMark, Rs, Rm, rotate, imm
        };
        constexpr static auto access = GenerateAccessHandler (
            std::integer_sequence<uint, cond, flag, opcode, flag, reg, reg, op2ShAmount, op2ShType, flag, reg, reg, op2Rot, op2Imm>{},
            std::integer_sequence<uint, 28, 25, 21, 20, 16, 12, 7, 5, 4, 8, 0, 8, 0>{}
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 1> {
        enum Field { condition, A, S, Rd, Rn, Rs, Rm } ;
        constexpr static auto access = GenerateAccessHandler (
                std::integer_sequence<uint, cond, flag, flag, reg, reg, reg, reg>{},
                std::integer_sequence<uint, 28, 21, 20, 16, 12, 8, 0>{}
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 2> {
        enum Field { condition, U, A, S, RdHi, RdLo, Rs, Rm } ;
        constexpr static auto access = GenerateAccessHandler (
                std::integer_sequence<uint, cond, flag, flag, flag, reg, reg, reg, reg>{},
                std::integer_sequence<uint, 28, 22, 21, 20, 16, 12, 8, 0>{}
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 3> {
        enum Field { condition, B, Rn, Rd, Rm } ;
        constexpr static auto access = GenerateAccessHandler (
                std::integer_sequence<uint, cond, flag, reg, reg, reg>{},
                std::integer_sequence<uint, 28, 22, 16, 12, 0>{}
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 4> {
        enum Field {
            condition, Rn
        };
        constexpr static auto access = GenerateAccessHandler (
                std::integer_sequence<uint, cond, reg>{}, std::integer_sequence<uint, 28, 0>{}
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 5> {
        enum Field {
            condition, P, U, I, W, L, Rn, Rd, S, H, Rm, offset
        };

        constexpr static auto access = []() {
            std::array<unsigned(*)(unsigned), 12> result {} ;
            constexpr auto normalHandler = GenerateAccessHandler (
                    std::integer_sequence<uint, cond, flag, flag, flag, flag, flag, reg, reg, flag, flag, reg>{},
                    std::integer_sequence<uint, 28, 24, 23, 22, 21, 20, 16, 12, 6, 5, 0>{}
            ) ;

            for ( size_t i = 0 ; i < normalHandler.size() ; ++i )
                result[ i ] = normalHandler[ i ] ;

            result.back() = [](unsigned insn) {
                return ((insn & 0xf00) >> 4) | ( insn & 0xf ) ;
            } ;

            return result ;
        }() ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 6> {
        enum Field {
            condition, I, P, U, B, W, L, Rn, Rd, imm, shAmount, shType, Rm
        };
        constexpr static auto access = GenerateAccessHandler (
                std::integer_sequence<uint, cond, flag, flag, flag, flag, flag, flag, reg, reg, offset12, op2ShAmount, op2ShType, reg>{},
                std::integer_sequence<uint, 28, 25, 24, 23, 22, 21, 20, 16, 12, 0, 7, 5, 0>{}
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 8> {
        enum Field {
            condition, P, U, S, W, L, Rn, rList
        };
        constexpr static auto access = GenerateAccessHandler (
                std::integer_sequence<uint, cond, flag, flag, flag, flag, flag, reg, regList>{},
                std::integer_sequence<uint, 28, 24, 23, 22, 21, 20, 16, 0>{}
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 9> {
        enum Field {
            condition, L, offset
        };
        constexpr static auto access = GenerateAccessHandler (
            std::integer_sequence<uint, cond, flag, offset24>{},
            std::integer_sequence<uint, 28, 24, 0>{}
        );
    };

    template<>
    struct instruction_info<DecodeMode::ARM, 13> {
        enum Field {
            condition, interruptNumber
        };
        constexpr static auto access = GenerateAccessHandler (
                std::integer_sequence<uint, cond, offset24>{},
                std::integer_sequence<uint, 28, 0>{}
        );
    };
}

#endif //TABLE_GEN_ARM_INFO_H
