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

    enum E_PSRBit {
        T = 5, F = 6, I = 7, V = 28, C = 29, Z = 30, N = 31
    };

    constexpr unsigned INVALID_VALUE = 0xffffffff;
}

using RegName = CPU_Enum::E_RegName ;

#endif // CPU_SYSTEM_ENUM_H

