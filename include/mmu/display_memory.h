//
// Created by orzgg on 2020-06-28.
//

#include <array>

#include <system_enum.h>
#include <system_literals.h>
#include <RegionBase.h>

#ifndef CPU_DISPLAYMEMORY_H
#define CPU_DISPLAYMEMORY_H

namespace MMU {
    template<>
    struct Region<Region_t::Display> : RegionBase {
        std::array<uint8_t, 0x400> palette{};
        std::array<uint8_t, 0x18000> VRAM{};
        std::array<uint8_t, 0x400> OAM{};

        Region() : RegionBase(MMUString::MemRegionName[ Region_t::Display ]) {}
        uint8_t &Access(unsigned addr, MMU_Enum::WIDTH width) override ;

        void Reset() override ;
    };
}

#endif //CPU_DISPLAYMEMORY_H
