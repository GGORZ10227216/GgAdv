//
// Created by orzgg on 2020-06-25.
//

#include <array>
#include <string>

#include <gg_utility/array_tool.h>
#include <gg_utility/bit_manipulate.h>

#ifndef CPU_SYSTEM_LITERALS_H
#define CPU_SYSTEM_LITERALS_H

namespace MsgString {
    constexpr auto errorMsg = Utility::MakeArray(
        "invisible_register_had_been_read"
    ) ;
}

namespace CPUString {
    enum { Str_Usr, Str_Fiq, Str_Irq, Str_Svc, Str_Abt, Str_Und, Str_Sys } ;
    constexpr auto ModeName = Utility::MakeArray(
        "User", "Fiq", "Irq", "Supervisor", "Abort", "Undefined", "System"
    ) ;

    constexpr auto RegName = Utility::MakeArray(
       "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11",
       "r12", "sp", "lr", "pc"
    ) ;

    constexpr auto UserSysRegFormat_Arm =
            "\tr0: {:#010x},  r1: {:#010x},  r2: {:#010x},  r3: {:#010x}\n"
            "\tr4: {:#010x},  r5: {:#010x},  r6: {:#010x},  r7: {:#010x}\n"
            "\tr8: {:#010x},  r9: {:#010x}, r10: {:#010x}, r11: {:#010x}\n"
            "\tr12: {:#010x}, sp: {:#010x},  lr: {:#010x},  pc: {:#010x}\n" ;

    constexpr auto FIQRegFormat_Arm =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tr8_fiq: {:#010x},  r9_fiq: {:#010x}, r10_fiq: {:#010x}, r11_fiq: {:#010x}\n"
            "\tr12_fiq: {:#010x}, sp_fiq: {:#010x},  lr_fiq: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto IRQRegFormat_Arm =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tr8: {:#010x}, r9: {:#010x}, r10: {:#010x}, r11: {:#010x}\n"
            "\tr12: {:#010x}, sp_irq: {:#010x}, lr_irq: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto SVCRegFormat_Arm =
            "\tr0: {:#010x}, r1: {:#010x},  r2: {:#010x},  r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x},  r6: {:#010x},  r7: {:#010x}\n"
            "\tr8: {:#010x}, r9: {:#010x}, r10: {:#010x}, r11: {:#010x}\n"
            "\tr12: {:#010x}, sp_svc: {:#010x}, lr_svc: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto ABTRegFormat_Arm =
            "\tr0: {:#010x}, r1: {:#010x},  r2: {:#010x},  r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x},  r6: {:#010x},  r7: {:#010x}\n"
            "\tr8: {:#010x}, r9: {:#010x}, r10: {:#010x}, r11: {:#010x}\n"
            "\tr12: {:#010x}, sp_abt: {:#010x}, lr_abt: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto UNDRegFormat_Arm =
            "\tr0: {:#010x}, r1: {:#010x},  r2: {:#010x},  r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x},  r6: {:#010x},  r7: {:#010x}\n"
            "\tr8: {:#010x}, r9: {:#010x}, r10: {:#010x}, r11: {:#010x}\n"
            "\tr12: {:#010x}, sp_und: {:#010x}, lr_und: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto UserSysRegFormat_Thumb =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tsp: {:#010x}, lr: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto FIQRegFormat_Thumb =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tsp_fiq: {:#010x}, lr_fiq: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto IRQRegFormat_Thumb =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tsp_irq: {:#010x}, lr_irq: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto SVCRegFormat_Thumb =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tsp_svc: {:#010x}, lr_svc: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto ABTRegFormat_Thumb =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tsp_abt: {:#010x}, lr_abt: {:#010x}, pc: {:#010x}\n" ;

    constexpr auto UNDRegFormat_Thumb =
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n"
            "\tsp_und: {:#010x}, lr_und: {:#010x}, pc: {:#010x}\n" ;
}

namespace MMUString {
    constexpr auto MemRegionName = Utility::MakeArray(
        "General",
        "Display",
        "Game Pak",
        "Unused"
    ) ;

    constexpr auto GeneralSubRegionName = Utility::MakeArray(
         "BIOS", "WRAM_OnBoard", "WRAM_OnChip", "I/O Registers", "Not used"
    ) ;
}

#endif //CPU_SYSTEM_LITERALS_H
