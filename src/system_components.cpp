//
// Created by orzgg on 2020-07-01.
//

#include <exception>

#include <system_components.h>
#include <cpu.h>
#include <mmu.h>
#include <cycle_tools.h>
#include <disassembler.h>

#include <fmt/ostream.h>

Components::System::System() :
        cycleCounter(new CycleCounter(this)),
        cpu(new CPU(this)),
        memory(new Memory(this)),
        disassembler(new Disassembler(this)) {}

Components::System::~System() {
    delete cycleCounter ;
    delete cpu ;
    delete memory ;
    delete disassembler ;
}

void Components::System::Start(std::optional<const char*> romPath) {
    try {
        std::fstream rom ;
        rom.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        if ( romPath != std::nullopt ) {
            // Emulator will execute BIOS only if romPath == nullopt
            rom.open( *romPath, std::fstream::in | std::fstream::binary ) ;
            LoadRom( rom ) ;
        } // if

        EmulationLoop() ;
    } catch (std::exception &e) {
        fmt::print( "Error: ", e.what() ) ;
    } // catch()
}

void Components::System::LoadRom( std::fstream& romStream ) {

}

void Components::System::EmulationLoop() {
    cpu->FillPipeline() ;
    /// TODO: fix
    cycles = 0 ;
    while (true) {
        /// TODO: using "true" before GUI is finished.
        cpu->Tick() ;
        fmt::print( "{}", cpu->ToString() ) ;
        /// TODO: manually set clk to 0 for cpu debugging
        cycles = 0 ;
        getchar() ;
    } // while
}
