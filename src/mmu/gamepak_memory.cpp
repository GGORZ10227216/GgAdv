//
// Created by orzgg on 2020-07-09.
//

#include <system_enum.h>
#include <gamepak_memory.h>

using namespace MMU_Enum ;

uint8_t &MMU::Region<Region_t::GamePak>::Access(unsigned addr, WIDTH width) {
    if (addr >= state1Start && addr <= state1End)
        return state1[addr];
    else if (addr >= state2Start && addr <= state2End) {
        return state2[addr - state2Start];
    } // else if()
    else if (addr >= state3Start && addr <= state3End) {
        return state3[addr - state3End];
    } // else if
    else if (addr >= SRAM_Start && addr <= SRAM_End) {
        return SRAM[addr - SRAM_Start];
    } // else if

    OutOfBound(addr);
    return state1.at( state1.size() ) ;
} // Access()

void MMU::Region<Region_t::GamePak>::Reset() {
    state1.fill( 0 ) ;
    state2.fill( 0 ) ;
    state3.fill( 0 ) ;
    SRAM.fill( 0 ) ;
} // Reset()
