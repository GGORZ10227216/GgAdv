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

    for (int i= 0 ; i < 8192 ; ++i ) {
        generalMemory.BIOS[ i ] = test[ i % test.size() ] ;
    } // for
}

std::string Components::Memory::ToString() {
    // TODO: list all handler infomation
    return std::string();
}

void Components::Memory::Tick() {

}

void Components::Memory::Reset() {
    generalMemory.Reset() ;
    displayMemory.Reset() ;
    gamepakMemory.Reset() ;
} // Reset()

uint8_t Components::Memory::Read8(unsigned int addr){
    using WIDTH = MMU_Enum::WIDTH ;
    uint8_t &result = Access(addr, WIDTH::BYTE);
    CheckEvents(_readEventHandler, addr);
    return result;
}

uint16_t Components::Memory::Read16(unsigned int addr) {
    using WIDTH = MMU_Enum::WIDTH ;
    if (addr % 2 != 0)
        throw std::logic_error("Attempt to read a 16bit data from a not 2 aligned address");
    CheckEvents(_readEventHandler, addr);
    uint16_t &result = reinterpret_cast<uint16_t &> (Access(addr, WIDTH::HALFWORD));
    return result;
}

uint32_t Components::Memory::Read32(unsigned int addr) {
    using WIDTH = MMU_Enum::WIDTH ;
    if (addr % 4 != 0)
        throw std::logic_error("Attempt to read a 16bit data from a not 4 aligned address");
    CheckEvents(_readEventHandler, addr);
    uint32_t &result = reinterpret_cast<uint32_t &> (Access(addr, WIDTH::WORD));
    return result;
}

uint8_t &Components::Memory::Access(unsigned int addr, MMU_Enum::WIDTH width) {
    if (addr >= 0x0 && addr <= 0x4ffffff) {
        return generalMemory.Access(addr, width);
    } // if
    else if (addr >= 0x5000000 && addr <= 0x7FFFFFF) {
        return displayMemory.Access(addr, width);
    } // else if
    else if (addr >= 0x8000000 && addr <= 0xFFFFFFF) {
        return gamepakMemory.Access(addr, width);
    } // else if

    OutOfBound(addr);
    return generalMemory.Access(addr, width);
} // Access()

