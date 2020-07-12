//
// Created by orzgg on 2020-06-28.
//

#include <fmt/format.h>
#include <system_enum.h>

#ifndef CPU_REGION_BASE_H
#define CPU_REGION_BASE_H

namespace MMU {
    using ReadEventHandler   = void (*)(unsigned) ;
    using WriteEventHandler  = void (*)(unsigned, unsigned) ;

    class RegionBase {
    protected:
        RegionBase(const char *regionName) :
                _name(regionName) {}

        virtual uint8_t &Access(unsigned, MMU_Enum::WIDTH) = 0;
        virtual void Reset() = 0 ;
        virtual void OutOfBound(unsigned addr) {
            throw std::logic_error(fmt::format("{} Invalid access at address {:#x}",
                                               _name, addr
            ));
        } // OutOfBound()

        const char *_name;
    };

    template<Region_t>
    struct Region {
    };
}

#endif //CPU_REGION_BASE_H
