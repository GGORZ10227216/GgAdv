//
// Created by orzgg on 2020-06-28.
//

#include <mmu.h>
#include <gba_bios.h>

Components::Memory::Memory(Components::System* parentPtr) :
    ClkDrivenComponent_t(parentPtr),
    MMU::RegionBase("SystemMemory")
{
    /// TODO: temporary cancel the BIOS load
//    static_assert( std::tuple_size_v<decltype(generalMemory.BIOS)> == biosData.size(), "BIOS size mismatch." ) ;
//    memcpy( generalMemory.BIOS.data(), biosData.data(), generalMemory.BIOS.size() ) ;

    auto test = Utility::MakeArray(
        0x02, 0x11, 0xa0, 0xe3, 0x01, 0x20, 0xa0, 0xe3, 0x11,
        0x02, 0xa0, 0xe1, 0x11, 0x02, 0xb0, 0xe1
    ) ;

    for (int i= 0 ; i < test.size() ; ++i ) {
        generalMemory.BIOS[ i ] = test[ i ] ;
    } // for

    generalMemory.WRAM_Onboard[ 0 ] = 0x00 ;
    generalMemory.WRAM_Onboard[ 1 ] = 0x10 ;
    generalMemory.WRAM_Onboard[ 2 ] = 0x92 ;
    generalMemory.WRAM_Onboard[ 3 ] = 0xe5 ;
}