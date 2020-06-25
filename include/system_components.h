//
// Created by orzgg on 2020-06-25.
//
#include <memory>
#include <cpu.h>

#ifndef CPU_SYSTEM_COMPONENETS_H
#define CPU_SYSTEM_COMPONENETS_H

namespace Components {
    struct System {
        CPU cpu ;
    };

    extern System emulator ;
}

#endif // CPU_SYSTEM_COMPONENETS_H
