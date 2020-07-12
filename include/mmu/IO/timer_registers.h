#include <ioreg_type.h>

#ifndef CPU_TIMER_REGISTERS_H
#define CPU_TIMER_REGISTERS_H

namespace IO_Map {
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM0CNT_L = {0x4000100};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM0CNT_H = {0x4000102};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM1CNT_L = {0x4000104};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM1CNT_H = {0x4000106};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM2CNT_L = {0x4000108};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM2CNT_H = {0x400010a};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM3CNT_L = {0x400010c};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> TM3CNT_H = {0x400010e};
}

#endif // CPU_TIMER_REGISTERS_H