//
// Created by orzgg on 2020-07-04.
//

#include <interrupt_waitstate_powerdown_control.h>
#include <component_type.h>
#include <array_tool.h>

#ifndef TEST_ARM_IMPLEMENT_H
#define TEST_ARM_IMPLEMENT_H

namespace Components {
    enum RegionTrait {
        BIOS = 0, EWRAM = 2, IWRAM = 3, IO = 4, Palette = 5,
        VRAM = 6, OAM = 7, WS0_0 = 8, WS0_1 = 9, WS1_0 = 0xA,
        WS1_1 = 0xB, WS2_0 = 0xC, WS2_1 = 0xD, SRAM = 0xE
    };

    struct CycleCounter : public Components::Component_t<Components::System> {
        CycleCounter(Components::System* parentPtr) ;

        unsigned S(unsigned addr) ;

        unsigned SD(unsigned addr, MMU_Enum::WIDTH width) ;

        unsigned N(unsigned addr) ;

        unsigned ND(unsigned addr, MMU_Enum::WIDTH width) ;

        constexpr unsigned I() { return 1; }

        std::string ToString() override ;

    private :
        constexpr static auto WS0_SclkSpeedTable = Utility::MakeArray(
                2, 1
        );

        constexpr static auto WS1_SclkSpeedTable = Utility::MakeArray(
                4, 1
        );

        constexpr static auto WS2_SclkSpeedTable = Utility::MakeArray(
                8, 1
        );

        constexpr static auto WS_NclkSpeedTable = Utility::MakeArray(
                4, 3, 2, 8
        );

        unsigned SRAM_Speed() ;
        unsigned WS0_SclkSpeed() ;
        unsigned WS0_NclkSpeed() ;
        unsigned WS1_SclkSpeed() ;
        unsigned WS1_NclkSpeed();
        unsigned WS2_SclkSpeed() ;
        unsigned WS2_NclkSpeed() ;
    };
}

#endif //TEST_ARM_IMPLEMENT_H
