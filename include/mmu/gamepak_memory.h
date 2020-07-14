//
// Created by orzgg on 2020-06-28.
//

#include <memory>

#include <system_enum.h>
#include <system_literals.h>
#include <RegionBase.h>

#ifndef CPU_GAME_PAK_MEMORY_H
#define CPU_GAME_PAK_MEMORY_H

namespace MMU {
    template<>
    struct Region<Region_t::GamePak> : RegionBase {
        std::unique_ptr<uint8_t[]> state1 ;
        std::unique_ptr<uint8_t[]> state2{};
        std::unique_ptr<uint8_t[]> state3{};

        std::array<uint8_t, 0x10000> SRAM{};

        Region() : RegionBase(MMUString::MemRegionName[ Region_t::GamePak ]) {}

        uint8_t &Access(unsigned addr, MMU_Enum::WIDTH width) override ;
        void Reset() override ;
    };
}

#endif //CPU_GAME_PAK_MEMORY_H
