//
// Created by orzgg on 2020-06-28.
//

#include <exception>
#include <utility>
#include <array>
#include <vector>

#include <system_enum.h>
#include <system_literals.h>
#include <RegionBase.h>

#ifndef CPU_ACCESS_RULES_H
#define CPU_ACCESS_RULES_H

namespace MMU {
    template<>
    struct Region<Region_t::General> : RegionBase {
        std::array<uint8_t, 0x4000> BIOS{};
        std::array<uint8_t, 0x40000> WRAM_Onboard{};
        std::array<uint8_t, 0x8000> WRAM_Onchip{};
        std::array<uint8_t, 0x3ff> IOReg{};

        Region() : RegionBase(MMUString::MemRegionName[Region_t::General]) {}

        uint8_t &Access(unsigned addr, MMU_Enum::WIDTH width) override;

        void Reset() override;
    };
}

#endif //CPU_ACCESS_RULES_H
