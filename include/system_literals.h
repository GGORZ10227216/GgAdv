//
// Created by orzgg on 2020-06-25.
//

#include <array>
#include <string>

#include <utility.h>

#ifndef CPU_SYSTEM_LITERALS_H
#define CPU_SYSTEM_LITERALS_H

namespace MsgString {
    constexpr auto errorMsg = Utility::MakeArray(
        "invisible_register_had_been_read"
    ) ;
}

namespace ModeString {
   constexpr auto ModeName = Utility::MakeArray(
       "User", "Fiq", "Irq", "Supervisor", "Abort", "Undefined", "System"
   ) ;
} ;

#endif //CPU_SYSTEM_LITERALS_H
