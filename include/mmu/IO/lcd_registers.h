#include <ioreg_type.h>

#ifndef CPU_LCD_REGISTERS_H
#define CPU_LCD_REGISTERS_H

namespace IO_Map {
	constexpr static IOReg_t<uint16_t, AccessMode::RW> DISPCNT = {0x4000000};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> DISPSTAT = {0x4000004};
	constexpr static IOReg_t<uint16_t, AccessMode::R> VCOUNT = {0x4000006};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> BG0CNT = {0x4000008};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> BG1CNT = {0x400000a};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> BG2CNT = {0x400000c};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> BG3CNT = {0x400000e};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG0HOFS = {0x4000010};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG0VOFS = {0x4000012};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG1HOFS = {0x4000014};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG1VOFS = {0x4000016};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG2HOFS = {0x4000018};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG2VOFS = {0x400001a};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG3HOFS = {0x400001c};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG3VOFS = {0x400001e};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG2PA = {0x4000020};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG2PB = {0x4000022};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG2PC = {0x4000024};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG2PD = {0x4000026};
	constexpr static IOReg_t<uint32_t, AccessMode::W> BG2X = {0x4000028};
	constexpr static IOReg_t<uint32_t, AccessMode::W> BG2Y = {0x400002c};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG3PA = {0x4000030};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG3PB = {0x4000032};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG3PC = {0x4000034};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BG3PD = {0x4000036};
	constexpr static IOReg_t<uint32_t, AccessMode::W> BG3X = {0x4000038};
	constexpr static IOReg_t<uint32_t, AccessMode::W> BG3Y = {0x400003c};
	constexpr static IOReg_t<uint16_t, AccessMode::W> WIN0H = {0x4000040};
	constexpr static IOReg_t<uint16_t, AccessMode::W> WIN1H = {0x4000042};
	constexpr static IOReg_t<uint16_t, AccessMode::W> WIN0V = {0x4000044};
	constexpr static IOReg_t<uint16_t, AccessMode::W> WIN1V = {0x4000046};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WININ = {0x4000048};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WINOUT = {0x400004a};
	constexpr static IOReg_t<uint16_t, AccessMode::W> MOSAIC = {0x400004c};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> BLDCNT = {0x4000050};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> BLDALPHA = {0x4000052};
	constexpr static IOReg_t<uint16_t, AccessMode::W> BLDY = {0x4000054};
}

#endif // CPU_LCD_REGISTERS_H