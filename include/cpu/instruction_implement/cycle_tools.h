//
// Created by orzgg on 2020-07-04.
//

#include <system_components.h>
#include <interrupt_waitstate_powerdown_control.h>
#include <component_type.h>
#include <arm_info.h>
#include <array_tool.h>
#include <cpu.h>

#ifndef TEST_ARM_IMPLEMENT_H
#define TEST_ARM_IMPLEMENT_H

namespace Components {
    enum RegionTrait {
        BIOS = 0, EWRAM = 2, IWRAM = 3, IO = 4, Palette = 5,
        VRAM = 6, OAM = 7, WS0_0 = 8, WS0_1 = 9, WS1_0 = 0xA,
        WS1_1 = 0xB, WS2_0 = 0xC, WS2_1 = 0xD, SRAM = 0xE
    };

    constexpr std::array<uint8_t, 7> WaitStateTb{
            0, 0, 2, 0, 0, 0, 0
    };

    struct CycleCounter : public Components::Component_t<Components::System> {
        CycleCounter(Components::System* parentPtr) :
            Component_t(parentPtr) {}

        unsigned S(unsigned addr) {
            unsigned waitstates = 0;
            unsigned addrTrait = (addr & 0x0f000000) >> 24;
            DecodeMode decodeMode = emuInstance->cpu->CurrentDecodeMode();

            switch (addrTrait) {
                case WS0_0 :
                case WS0_1 :
                    waitstates = WS0_SclkSpeed();
                    break;
                case WS1_0 :
                case WS1_1 :
                    waitstates = WS1_SclkSpeed();
                    break;
                case WS2_0 :
                case WS2_1 :
                    waitstates = WS2_SclkSpeed();
                    break;
                default :
                    waitstates = WaitStateTb[addrTrait];
            } // switch

            if (decodeMode == ModeEnum::ARM && addrTrait >= EWRAM && addrTrait <= WS2_1)
                waitstates += waitstates + 1;
            return 1 + waitstates;
        }

        unsigned SD(unsigned addr, MMU_Enum::WIDTH width) {
            unsigned waitstates = 0;
            unsigned addrTrait = (addr & 0x0f000000) >> 24;

            switch (addrTrait) {
                case WS0_0 :
                case WS0_1 :
                    waitstates = WS0_SclkSpeed();
                    break;
                case WS1_0 :
                case WS1_1 :
                    waitstates = WS1_SclkSpeed();
                    break;
                case WS2_0 :
                case WS2_1 :
                    waitstates = WS2_SclkSpeed();
                    break;
                default :
                    waitstates = WaitStateTb[addrTrait];
            } // switch

            if (width == MMU_Enum::WIDTH::WORD && addrTrait >= EWRAM && addrTrait <= WS2_1)
                waitstates += waitstates + 1;
            return 1 + waitstates;
        }

        unsigned N(unsigned addr) {
            unsigned waitstates = 0;
            unsigned addrTrait = (addr & 0x0f000000) >> 24;
            DecodeMode decodeMode = emuInstance->cpu->CurrentDecodeMode();

            switch (addrTrait) {
                case WS0_0 :
                case WS0_1 :
                    waitstates = WS0_NclkSpeed();
                    break;
                case WS1_0 :
                case WS1_1 :
                    waitstates = WS1_NclkSpeed();
                    break;
                case WS2_0 :
                case WS2_1 :
                    waitstates = WS2_NclkSpeed();
                    break;
                default :
                    waitstates = WaitStateTb[addrTrait];
            } // switch

            if (decodeMode == ModeEnum::ARM && addrTrait >= EWRAM && addrTrait <= WS2_1)
                waitstates += S(addr + 4);
            return 1 + waitstates;
        }

        unsigned ND(unsigned addr, MMU_Enum::WIDTH width) {
            unsigned waitstates = 0;
            unsigned addrTrait = (addr & 0x0f000000) >> 24;

            switch (addrTrait) {
                case WS0_0 :
                case WS0_1 :
                    waitstates = WS0_NclkSpeed() ;
                    break;
                case WS1_0 :
                case WS1_1 :
                    waitstates = WS1_NclkSpeed() ;
                    break;
                case WS2_0 :
                case WS2_1 :
                    waitstates = WS2_NclkSpeed() ;
                    break;
                default :
                    waitstates = WaitStateTb[ addrTrait ] ;
            } // switch

            if (width == MMU_Enum::WIDTH::WORD && addrTrait >= EWRAM && addrTrait <= WS2_1)
                waitstates += 1 + SD(addr+4, MMU_Enum::WIDTH::HALFWORD) ;
            return 1 + waitstates ;
        }

        constexpr unsigned I() { return 1; }

        std::string ToString() override {
            return fmt::format("cycles: {}", emuInstance->cycles);
        }

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

        unsigned SRAM_Speed() {
            unsigned speedBit =  IO_Map::WAITCNT.Read(emuInstance->memory) & 0x3;
            return WS_NclkSpeedTable[speedBit];
        }

        unsigned WS0_SclkSpeed() {
            unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(emuInstance->memory), 4);
            return WS0_SclkSpeedTable[speedBit];
        }

        unsigned WS0_NclkSpeed() {
            unsigned speedBit = (IO_Map::WAITCNT.Read(emuInstance->memory) & 0xf) >> 2;
            return WS_NclkSpeedTable[speedBit];
        }

        unsigned WS1_SclkSpeed() {
            unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(emuInstance->memory), 7);
            return WS1_SclkSpeedTable[speedBit];
        }

        unsigned WS1_NclkSpeed() {
            unsigned speedBit = (IO_Map::WAITCNT.Read(emuInstance->memory) & 0x7f) >> 5;
            return WS_NclkSpeedTable[speedBit];
        }

        unsigned WS2_SclkSpeed() {
            unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(emuInstance->memory), 10);
            return WS2_SclkSpeedTable[speedBit];
        }

        unsigned WS2_NclkSpeed() {
            unsigned speedBit = (IO_Map::WAITCNT.Read(emuInstance->memory) & 0x3ff) >> 8;
            return WS_NclkSpeedTable[speedBit];
        }
    };
}

#endif //TEST_ARM_IMPLEMENT_H
