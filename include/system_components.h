//
// Created by orzgg on 2020-06-25.
//
#include <optional>
#include <fstream>

#include <cpu.h>
#include <mmu.h>
#include <disassembler.h>

#ifndef CPU_SYSTEM_COMPONENETS_H
#define CPU_SYSTEM_COMPONENETS_H

namespace Components {
    struct System {
        size_t cycles = 0 ;
        CPU cpu ;
        Memory memory ;
        Disassembler disassembler ;

        void Start(std::optional<const char*> romPath) ;
    private :
        void LoadRom( std::fstream& romStream ) ;
        void EmulationLoop() ;
    };

    extern System emulator ;
}

#define EMU_CPU Components::emulator.cpu
#define EMU_MEM Components::emulator.memory
#define EMU_CYCLE Components::emulator.cycles
#define PRINT_ASM(x) Components::emulator.disassembler.Disassemble(x)

#endif // CPU_SYSTEM_COMPONENETS_H
