//
// Created by orzgg on 2020-06-25.
//
#include <optional>
#include <fstream>
#include <memory>

#ifndef CPU_SYSTEM_COMPONENETS_H
#define CPU_SYSTEM_COMPONENETS_H

namespace Components {
    struct CycleCounter;
    struct CPU;
    struct Memory;
    struct Disassembler;

    struct System final {
        unsigned cycles = 0;
        System() ;
        ~System() ;

        CycleCounter *cycleCounter = nullptr ;
        CPU *cpu = nullptr ;
        Memory *memory = nullptr ;
        Disassembler *disassembler = nullptr ;

        void Start(std::optional<const char *> romPath);
    private :
        void LoadRom(std::fstream &romStream);
        void EmulationLoop();
    };
}

#endif // CPU_SYSTEM_COMPONENETS_H
