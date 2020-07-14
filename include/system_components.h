//
// Created by orzgg on 2020-06-25.
//
#include <optional>
#include <fstream>
#include <memory>

#include <cycle_tools.h>
#include <cpu.h>
#include <mmu.h>
#include <disassembler.h>
#include <optional>

#ifndef CPU_SYSTEM_COMPONENETS_H
#define CPU_SYSTEM_COMPONENETS_H

namespace Components {
    struct System {
        unsigned cycles = 0;
        System() :
            cycleCounter(this),
            cpu(this),
            memory(this),
            disassembler(this)
        {

        }

        CycleCounter cycleCounter;
        CPU cpu;
        Memory memory;
        Disassembler disassembler;

        void Start(std::optional<const char *> romPath);
        void BenchmarkStart(std::optional<const char *> romPath) ;
    private :
        void LoadRom(std::fstream &romStream);
        void EmulationLoop();
        void Benchmark() ;
    };
}

#endif // CPU_SYSTEM_COMPONENETS_H
