#include <ioreg_type.h>

#ifndef CPU_SOUND_REGISTERS_H
#define CPU_SOUND_REGISTERS_H

namespace IO_Map {
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND1CNT_L = {0x4000060};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND1CNT_H = {0x4000062};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND1CNT_X = {0x4000064};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND2CNT_L = {0x4000068};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND2CNT_H = {0x400006c};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND3CNT_L = {0x4000070};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND3CNT_H = {0x4000072};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND3CNT_X = {0x4000074};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND4CNT_L = {0x4000078};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUND4CNT_H = {0x400007c};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUNDCNT_L = {0x4000080};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUNDCNT_H = {0x4000082};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SOUNDCNT_X = {0x4000084};
	constexpr static IOReg_t<uint16_t, AccessMode::BIOS> SOUNDBIAS = {0x4000088};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM0_L = {0x4000090};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM0_H = {0x4000092};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM1_L = {0x4000094};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM1_H = {0x4000096};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM2_L = {0x4000098};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM2_H = {0x400009a};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM3_L = {0x400009c};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM3_H = {0x400009e};
	constexpr static IOReg_t<uint32_t, AccessMode::W> FIFO_A = {0x40000a0};
	constexpr static IOReg_t<uint32_t, AccessMode::W> FIFO_B = {0x40000a4};
}

#endif // CPU_SOUND_REGISTERS_H