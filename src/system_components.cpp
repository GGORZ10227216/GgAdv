//
// Created by orzgg on 2020-07-01.
//

#include <exception>

#include <system_components.h>
#include <fmt/ostream.h>

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
    EMU_CPU.FillPipeline() ;
    EMU_CYCLE = 0 ;
    while (true) {
        /// TODO: using "true" before GUI is finished.
        EMU_CPU.Tick() ;
        fmt::print( "{}", EMU_CPU.ToString() ) ;
        /// TODO: manually set clk to 0 for cpu debugging
        EMU_CYCLE = 0 ;
        getchar() ;
    } // while
}
