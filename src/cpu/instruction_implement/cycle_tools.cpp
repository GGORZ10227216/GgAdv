//
// Created by orzgg on 2020-07-04.
//

#include <cycle_tools.h>
#include <system_enum.h>
#include <system_components.h>
#include <bit_manipulate.h>
#include <interrupt_waitstate_powerdown_control.h>

using namespace MMU_Enum;
using namespace ModeEnum;

unsigned Cycle::CycleTools::S(unsigned addr)  {
    unsigned waitstates = 0;
    unsigned addrTrait = (addr & 0x0f000000) >> 24;
    DecodeMode decodeMode = EMU_CPU.CurrentDecodeMode();

    switch (addrTrait) {
        case WS0_0 :
        case WS0_1 :
            waitstates = WS0_SclkSpeed() ;
            break;
        case WS1_0 :
        case WS1_1 :
            waitstates = WS1_SclkSpeed() ;
            break;
        case WS2_0 :
        case WS2_1 :
            waitstates = WS2_SclkSpeed() ;
            break;
        default :
            waitstates = WaitStateTb[ addrTrait ] ;
    } // switch

    if (decodeMode == ModeEnum::ARM && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += waitstates + 1 ;
    return 1 + waitstates ;
}

unsigned Cycle::CycleTools::SD(unsigned addr, MMU_Enum::WIDTH width){
    unsigned waitstates = 0;
    unsigned addrTrait = (addr & 0x0f000000) >> 24;

    switch (addrTrait) {
        case WS0_0 :
        case WS0_1 :
            waitstates = WS0_SclkSpeed() ;
            break;
        case WS1_0 :
        case WS1_1 :
            waitstates = WS1_SclkSpeed() ;
            break;
        case WS2_0 :
        case WS2_1 :
            waitstates = WS2_SclkSpeed() ;
            break;
        default :
            waitstates = WaitStateTb[ addrTrait ] ;
    } // switch

    if (width == WIDTH::WORD && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += waitstates + 1 ;
    return 1 + waitstates ;
}

unsigned Cycle::CycleTools::N(unsigned addr){
    unsigned waitstates = 0;
    unsigned addrTrait = (addr & 0x0f000000) >> 24;
    DecodeMode decodeMode = EMU_CPU.CurrentDecodeMode();

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

    if (decodeMode == ModeEnum::ARM && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += S(addr+4) ;
    return 1 + waitstates ;
}

unsigned Cycle::CycleTools::ND(unsigned addr, MMU_Enum::WIDTH width) {
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

    if (width == WIDTH::WORD && addrTrait >= EWRAM && addrTrait <= WS2_1)
        waitstates += 1 + SD(addr+4, WIDTH::HALFWORD) ;
    return 1 + waitstates ;
}

unsigned Cycle::CycleTools::SRAM_Speed() {
    unsigned speedBit =  IO_Map::WAITCNT.Read() & 0x3;
    return WS_NclkSpeedTable[speedBit];
}

unsigned Cycle::CycleTools::WS0_SclkSpeed() {
    unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(), 4);
    return WS0_SclkSpeedTable[speedBit];
}

unsigned Cycle::CycleTools::WS0_NclkSpeed() {
    unsigned speedBit = (IO_Map::WAITCNT.Read() & 0xf) >> 2;
    return WS_NclkSpeedTable[speedBit];
}

unsigned Cycle::CycleTools::WS1_SclkSpeed() {
    unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(), 7);
    return WS1_SclkSpeedTable[speedBit];
}

unsigned Cycle::CycleTools::WS1_NclkSpeed() {
    unsigned speedBit = (IO_Map::WAITCNT.Read() & 0x7f) >> 5;
    return WS_NclkSpeedTable[speedBit];
}

unsigned Cycle::CycleTools::WS2_SclkSpeed() {
    unsigned speedBit = Utility::TestBit(IO_Map::WAITCNT.Read(), 10);
    return WS2_SclkSpeedTable[speedBit];
}

unsigned Cycle::CycleTools::WS2_NclkSpeed() {
    unsigned speedBit = (IO_Map::WAITCNT.Read() & 0x3ff) >> 8;
    return WS_NclkSpeedTable[speedBit];
}






