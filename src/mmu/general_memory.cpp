//
// Created by orzgg on 2020-07-04.
//

#include <general_memory.h>

using namespace MMU_Enum ;

uint8_t& MMU::Region<Region_t::General>::Access(unsigned addr, WIDTH width) {
    if (addr <= BIOS_end)
        return BIOS[addr];
    else if (addr >= onboardStart && addr <= onboardEnd) {
        return WRAM_Onboard[addr - onboardStart];
    } // else if()
    else if (addr >= onchipStart && addr <= onchipEnd) {
        return WRAM_Onchip[addr - onboardStart];
    } // else if
    else if (addr >= ioStart && addr <= ioEnd) {
        return IOReg[ addr - ioStart ] ;
    } // else

    OutOfBound(addr) ;
    return BIOS.at( BIOS.size() ) ;
} // Access()

void MMU::Region<Region_t::General>::Reset() {
    BIOS.fill( 0 ) ;
    WRAM_Onboard.fill( 0 ) ;
    WRAM_Onchip.fill( 0 ) ;
    IOReg.fill( 0 ) ;
} // Reset()