//
// Created by orzgg on 2020-07-04.
//

#include <system_components.h>
#include <cpu.h>

#include <cycle_tools.h>
#include <system_enum.h>
#include <bit_manipulate.h>

Components::CycleCounter::CycleCounter(Components::System* parentPtr) :
    Component_t(parentPtr)
{

}

unsigned Components::CycleCounter::S(unsigned int addr) {
    unsigned waitstates = 0;
    unsigned addrTrait = (addr & 0x0f000000) >> 24;
    DecodeMode decodeMode = EMU_CPU.CurrentDecodeMode() ;

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
        case EWRAM :
            waitstates = 2 ;
            break ;
    } // switch

    if (decodeMode == ModeEnum::ARM && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += waitstates + 1;
    return 1 + waitstates;
}

unsigned Components::CycleCounter::SD(unsigned int addr, MMU_Enum::WIDTH width) {
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
        case EWRAM :
            waitstates = 2 ;
            break ;
    } // switch

    if (width == MMU_Enum::WIDTH::WORD && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += waitstates + 1;
    return 1 + waitstates;
}

unsigned Components::CycleCounter::N(unsigned int addr) {
    unsigned waitstates = 0;
    unsigned addrTrait = (addr & 0x0f000000) >> 24;
    DecodeMode decodeMode = EMU_CPU.CurrentDecodeMode();

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
        case EWRAM :
            waitstates = 2 ;
            break ;
    } // switch

    if (decodeMode == ModeEnum::ARM && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += S(addr + 4);
    return 1 + waitstates;
}

unsigned Components::CycleCounter::ND(unsigned int addr, MMU_Enum::WIDTH width) {
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
        case EWRAM :
            waitstates = 2 ;
            break ;
    } // switch

    if (width == MMU_Enum::WIDTH::WORD && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += 1 + SD(addr+4, MMU_Enum::WIDTH::HALFWORD) ;
    return 1 + waitstates ;
}

std::string Components::CycleCounter::ToString() {
    return fmt::format("cycles: {}", emuInstance.cycles);
}

unsigned Components::CycleCounter::SRAM_Speed() {
    unsigned speedBit =  IO_Map::WAITCNT.Read(emuInstance.memory) & 0x3;
    return WS_NclkSpeedTable[speedBit];
}

unsigned Components::CycleCounter::WS0_SclkSpeed() {
    unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(emuInstance.memory), 4);
    return WS0_SclkSpeedTable[speedBit];
}

unsigned Components::CycleCounter::WS0_NclkSpeed() {
    unsigned speedBit = (IO_Map::WAITCNT.Read(emuInstance.memory) & 0xf) >> 2;
    return WS_NclkSpeedTable[speedBit];
}

unsigned Components::CycleCounter::WS1_SclkSpeed() {
    unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(emuInstance.memory), 7);
    return WS1_SclkSpeedTable[speedBit];
}

unsigned Components::CycleCounter::WS1_NclkSpeed() {
    unsigned speedBit = (IO_Map::WAITCNT.Read(emuInstance.memory) & 0x7f) >> 5;
    return WS_NclkSpeedTable[speedBit];
}

unsigned Components::CycleCounter::WS2_SclkSpeed() {
    unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(emuInstance.memory), 10);
    return WS2_SclkSpeedTable[speedBit];
}

unsigned Components::CycleCounter::WS2_NclkSpeed() {
    unsigned speedBit = (IO_Map::WAITCNT.Read(emuInstance.memory) & 0x3ff) >> 8;
    return WS_NclkSpeedTable[speedBit];
}







