//
// Created by orzgg on 2020-07-09.
//

#include <system_enum.h>
#include <display_memory.h>

using namespace MMU_Enum;

uint8_t &MMU::Region<Region_t::Display>::Access(unsigned addr, WIDTH width) {
    if (addr >= paletteStart && addr <= paletteEnd)
        return palette[addr];
    else if (addr >= VRAM_Start && addr <= VRAM_End) {
        return VRAM[addr - VRAM_Start];
    } // else if()
    else if (addr >= OAM_Start && addr <= OAM_End) {
        return OAM[addr - OAM_Start];
    } // else if

    OutOfBound(addr);
    return palette.at(palette.size());
} // Access()

void MMU::Region<Region_t::Display>::Reset() {
    palette.fill( '\0' ) ;
    VRAM.fill( '\0' ) ;
    OAM.fill( '\0' ) ;
} // Reset()