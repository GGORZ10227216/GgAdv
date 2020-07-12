//
// Created by orzgg on 2020-06-10.
//

#ifndef TABLE_GEN_THUMB_INFO_H
#define TABLE_GEN_THUMB_INFO_H

#include <utility>
#include <disassemble/utility.h>
#include <disassemble/information/instruction_info.h>

namespace disassemble {
    using uint = unsigned int;
    enum { reg_thumb = 3, offset5 = 5, Op = 2, flag_thumb = 1, word8 = 8, word7 = 7, Rlist = 8,
        Op4 = 4, condition_thumb = 4, offset8_thumb = 8, value8 = 8, offset11 = 11, offset23 = 23 };

    template<>
    struct instruction_info<DecodeMode::THUMB, 1> {
        enum class Field {
            Op, Offset5, Rs, Rd
        };

        enum Mnemonics { LSL, LSR, ASR, MOV } ;
        enum Formats { F_MOV, F_SHIFT } ;

        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rs),
                static_cast<uint>(Field::Offset5)
        >{};

        constexpr static auto signature = MakeSignature<0b000, 13, 3, 11>() ;
        constexpr static auto mnemonics = MakeArray ( "lsls", "lsrs", "asrs", "movs" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, Op, offset5, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 11, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {:r}, {:r}", "{} {:r}, {:r}, #{:iz}"
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,2> {
        enum class Field {
            I, Op, Rn, Offset3 = Rn, Rs, Rd
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rs),
                static_cast<uint>(Field::Rn)
        >{};
        constexpr static auto signature = MakeSignature<0b00011, 11, 4, 9>() ;
        constexpr static auto mnemonics = MakeArray( "adds", "subs" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, flag_thumb, reg_thumb, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 10, 9, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} {:r}, {:r}, {:r}", "{} {:r}, {:r}, #{:i}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,3> {
        enum class Field {
            Op, Rd, Offset8
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Offset8)
        >{};
        constexpr static auto signature = MakeSignature<0b001, 13, 4, 11>() ;
        constexpr static auto mnemonics = MakeArray( "movs", "cmp", "adds", "subs" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, Op, reg_thumb, offset8_thumb>{},
                                                  std::integer_sequence<uint, 11, 8, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} {:r}, #{:i}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,4> {
        enum class Field {
            Op, Rs, Rd
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rs)
        >{};
        constexpr static auto signature = MakeSignature<0b010000, 10, 16, 6>() ;
        constexpr static auto mnemonics = MakeArray( "ands", "eors", "lsls", "lsrs", "asrs",
                "adcs", "sbcs", "rors", "tst", "rsbs", "cmp",
                "cmn", "orrs", "muls", "bics", "mvns" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, Op4, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} {:r}, {:r}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,5> {
        enum class Field {
            Op, H1, H2, Rs, Hs = Rs, Rd, Hd = Rd
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rs)
        >{};
        constexpr static auto signature = MakeSignature<0b010001, 10, 6>( 0b0001, 0b0010, 0b0011, 0b0101, 0b0110,
                0b0111, 0b1001, 0b1010, 0b1011, 0b1100, 0b1101 ) ;
        constexpr static auto mnemonics = MakeArray( "add", "cmp", "mov", "bx" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, Op, flag_thumb, flag_thumb, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 8, 7, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {:r}, {:rh}",
                "{} {:rh}, {:r}",
                "{} {:rh}, {:rh}",
                "{}{:x} {:r}",
                "{}{:x} {:rh}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,6> {
        enum class Field {
            Rd, Word8
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Word8)
        >{};
        constexpr static auto signature = MakeSignature<0b01001, 11>() ;
        constexpr static auto mnemonics = MakeArray( "ldr" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, reg_thumb, word8>{},
                                                  std::integer_sequence<uint, 8, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} {:r}, [pc, #{:i2}]" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,7> {
        enum class Field {
            L, B, Ro, Rb, Rd
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rb),
                static_cast<uint>(Field::Ro)
        >{};
        constexpr static auto signature = MakeSignature<0b0101000, 9, 4, 10>() ;
        constexpr static auto mnemonics = MakeArray( "str", "strb", "ldr", "ldrb" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, flag_thumb, reg_thumb, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 11, 10, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} {:r}, [{:r}, {:r}]" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,8> {
        enum class Field {
            H, S, Ro, Rb, Rd
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rb),
                static_cast<uint>(Field::Ro)
        >{};
        constexpr static auto signature = MakeSignature<0b0101001, 9, 4, 10>() ;
        constexpr static auto mnemonics = MakeArray( "strh", "ldrh", "ldrsb", "ldrsh" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, flag_thumb, reg_thumb, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 11, 10, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} {:r}, [{:r}, {:r}]" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,9> {
        enum class Field {
            B, L, Offset5, Rb, Rd
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rb),
                static_cast<uint>(Field::Offset5)
        >{};
        constexpr static auto signature = MakeSignature<0b011, 13, 4, 11>() ;
        constexpr static auto mnemonics = MakeArray( "str", "ldr", "strb", "ldrb" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, flag_thumb, offset5, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 12, 11, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {:r}, [{:r}{:ix}]",
                "{} {:r}, [{:r}, #{:i2}]",
                "{} {:r}, [{:r}, #{:i}]"
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,10> {
        enum class Field {
            L, Offset5, Rb, Rd
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Rb),
                static_cast<uint>(Field::Offset5)
        >{};
        constexpr static auto signature = MakeSignature<0b1000, 12, 2, 11>() ;
        constexpr static auto mnemonics = MakeArray( "strh", "ldrh" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, offset5, reg_thumb, reg_thumb>{},
                                                  std::integer_sequence<uint, 11, 6, 3, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {:r}, [{:r}{:ix}]",
                "{} {:r}, [{:r}, #{:i1}]"
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,11> {
        enum class Field {
            L, Rd, Word8
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Word8)
        >{};
        constexpr static auto signature = MakeSignature<0b1001, 12, 2, 11>() ;
        constexpr static auto mnemonics = MakeArray( "str", "ldr" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, reg_thumb, word8>{},
                                                  std::integer_sequence<uint, 11, 8, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {:r}, [sp{:ix}]",
                "{} {:r}, [sp, #{:i2}]"
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,12> {
        enum class Field {
            SP, Rd, Word8
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rd),
                static_cast<uint>(Field::Word8)
        >{};
        constexpr static auto signature = MakeSignature<0b1010, 12, 2, 11>() ;
        constexpr static auto mnemonics = MakeArray( "adr", "add" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, reg_thumb, word8>{},
                                                  std::integer_sequence<uint, 11, 8, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {:r}, #{:i2}",
                "{} {:r}, sp, #{:i2}"
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,13> {
        enum class Field {
            S, SWord7
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::SWord7)
        >{};
        constexpr static auto signature = MakeSignature<0b10110000, 8, 2, 7>() ;
        constexpr static auto mnemonics = MakeArray( "add", "sub" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, word7>{},
                                                  std::integer_sequence<uint, 7, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} sp, #{:i2}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,14> {
        enum class Field {
            L, R, Rlist
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rlist)
        >{};
		constexpr static auto signature = MakeSignature<0b10110100, 8, 8>( 0b0000, 0b0001, 0b1000, 0b1001 ) ;
        constexpr static auto mnemonics = MakeArray( "push", "pop" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, flag_thumb, Rlist>{},
                                                  std::integer_sequence<uint, 11, 8, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {{{:l}}}", "{} {{{:l}, lr}}", "{} {{{:l}, pc}}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,15> {
        enum class Field {
            L, Rb, Rlist
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Rb),
                static_cast<uint>(Field::Rlist)
        >{};
		constexpr static auto signature = MakeSignature<0b1100, 12, 2, 11>() ;
        constexpr static auto mnemonics = MakeArray( "stm", "ldm" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, reg_thumb, Rlist>{},
                                                  std::integer_sequence<uint, 11, 8, 0>{}) ;
        constexpr static auto formats = MakeArray (
                "{} {:r}!, {{{:l}}}"
        ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,16> {
        enum class Field {
            Cond, SOffset8
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::SOffset8)
        >{};
		constexpr static auto signature = MakeSignature<0b1101, 12, 14, 8>() ;
        constexpr static auto mnemonics = MakeArray( "beq", "bne", "bhs", "blo", "bmi", "bpl", "bvs",
                "bvc", "bhi", "bls", "bge", "blt", "bgt", "ble" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, condition_thumb, offset8_thumb>{},
                                                  std::integer_sequence<uint, 8, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} #{:i1+4e7}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,17> {
        enum class Field {
            Value8
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Value8)
        >{};
		constexpr static auto signature = MakeSignature<0b11011111, 8>() ;
        constexpr static auto mnemonics = MakeArray( "svc" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, value8>{},
                                                  std::integer_sequence<uint, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} #{:i}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,18> {
        enum class Field {
            Offset11
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Offset11)
        >{};
		constexpr static auto signature = MakeSignature<0b11100, 11>() ;
        constexpr static auto mnemonics = MakeArray( "b" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, offset11>{},
                                                  std::integer_sequence<uint, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} #{:i1+4e10}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,19> {
        enum class Field {
            Offset
        };
        constexpr static auto Args = std::integer_sequence<uint,
                static_cast<uint>(Field::Offset)
        >{};
		constexpr static auto signature = MakeSignature<0b1111, 12>() ;
        constexpr static auto mnemonics = MakeArray( "bl" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, offset23>{},
                                                  std::integer_sequence<uint, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} #{:i+4e22}" ) ;
    };

    template<>
    struct instruction_info<DecodeMode::THUMB,0> {
        enum class Field {
            H, Offset
        };
        constexpr static auto Args = std::integer_sequence<uint,
            static_cast<uint>(Field::H),
            static_cast<uint>(Field::Offset)
        >{};

        constexpr static auto signature = MakeSignature<0b1111, 12, 1, 11>() ;
        constexpr static auto mnemonics = MakeArray( "bl_hi", "bl_lo" ) ;
        constexpr static auto mask = InitInsnType(std::integer_sequence<uint, flag_thumb, offset11>{},
                                                  std::integer_sequence<uint, 11, 0>{}) ;
        constexpr static auto formats = MakeArray ( "{} #{:i}" ) ;
    };
}

#endif //TABLE_GEN_THUMB_INFO_H
