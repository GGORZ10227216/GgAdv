//
// Created by orzgg on 2020-06-25.
//

#ifndef CPU_SYSTEM_ENUM_H
#define CPU_SYSTEM_ENUM_H

namespace ModeEnum {
    enum E_CpuMode {
        USR = 0b10000, FIQ = 0b10001,
        IRQ = 0b10010, SVC = 0b10011,
        ABT = 0b10111, UND = 0b11011,
        SYS = 0b11111
    } ;

    enum E_DecodeMode { ARM, THUMB } ;
    constexpr unsigned cpuModeMask = 0x1f ;
} // namespace SYS_ENUM

using CpuMode = ModeEnum::E_CpuMode ;
using DecodeMode = ModeEnum::E_DecodeMode ;

namespace ErrorEnum {
    enum class E_ErrorType {
        invisible_register_had_been_read = 1
    } ;
}

using ErrType = ErrorEnum::E_ErrorType ;

namespace CPU_Enum {
    enum E_RegName {
        r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc
    };

    enum E_ShiftType {
        LSL, LSR, ASR, ROR
    };

    enum E_DataProcess {
        AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, BIC, MVN
    };

    enum E_CondName {
        EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL
    };

    enum E_PSRBit {
        T = 5, F = 6, I = 7, V = 28, C = 29, Z = 30, N = 31
    };

    enum E_PipelineStage {
        Execute, Decode, Fetched
    };

    constexpr unsigned INVALID_VALUE = 0xffffffff;
}

using RegName = CPU_Enum::E_RegName ;
using PSRBit = CPU_Enum::E_PSRBit ;
using ShiftType = CPU_Enum::E_ShiftType ;
using ALU = CPU_Enum::E_DataProcess ;

namespace MMU_Enum {
    enum class WIDTH { BYTE = 8, HALFWORD = 16, WORD = 32 } ;

    enum MemoryRegion {
        General,
        Display,
        GamePak,
        Unused
    };

    constexpr static unsigned BIOS_start = 0x0000000, BIOS_end = 0x0003fff;
    constexpr static unsigned onboardStart = 0x2000000, onboardEnd = 0x203ffff;
    constexpr static unsigned onchipStart = 0x3000000, onchipEnd = 0x3007fff;
    constexpr static unsigned ioStart = 0x4000000, ioEnd = 0x40003fe;
    enum GeneralRegion {
        BIOS = 0,
        WRAM_Board = 1,
        WRAM_Chip = 2,
        IO = 3
    };

    constexpr static unsigned paletteStart = 0x05000000, paletteEnd = 0x050003ff;
    constexpr static unsigned VRAM_Start = 0x06000000, VRAM_End = 0x06017FFF;
    constexpr static unsigned OAM_Start = 0x07000000, OAM_End = 0x070003FF;
    enum DisplayRegion {
        Palette = 4,
        VRAM = 5,
        OAM = 6
    };

    constexpr static unsigned state1Start = 0x08000000, state1End = 0x09FFFFFF;
    constexpr static unsigned state2Start = 0x0A000000, state2End = 0x0BFFFFFF;
    constexpr static unsigned state3Start = 0x0C000000, state3End = 0x0DFFFFFF;
    constexpr static unsigned  SRAM_Start = 0x0E000000, SRAM_End = 0x0E00FFFF;
    enum GamePakRegion {
        ROM1 = 7,
        ROM2 = 8,
        ROM3 = 9,
        SRAM = 10
    };

    constexpr int regionNumber = SRAM + 1 ;
}

using Region_t = MMU_Enum::MemoryRegion ;

#endif // CPU_SYSTEM_ENUM_H

