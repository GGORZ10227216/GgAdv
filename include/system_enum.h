//
// Created by orzgg on 2020-06-25.
//

#ifndef CPU_SYSTEM_ENUM_H
#define CPU_SYSTEM_ENUM_H

namespace ModeEnum {
    enum class E_CpuMode {
        USR = 0b10000, FIQ = 0b10001,
        IRQ = 0b10010, SVC = 0b10011,
        ABT = 0b10111, UND = 0b11011,
        SYS = 0b11111
    } ;

    enum class E_DecodeMode { ARM, THUMB } ;
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
    enum {
        r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc
    };

    constexpr unsigned INVALID_VALUE = 0xffffffff;
}

#endif // CPU_SYSTEM_ENUM_H

