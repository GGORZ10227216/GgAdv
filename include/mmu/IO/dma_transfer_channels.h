#include <ioreg_type.h>

#ifndef CPU_DMA_TRANSFER_CHANNELS_H
#define CPU_DMA_TRANSFER_CHANNELS_H

namespace IO_Map {
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA0SAD = {0x40000b0};
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA0DAD = {0x40000b4};
	constexpr static IOReg_t<uint16_t, AccessMode::W> DMA0CNT_L = {0x40000b8};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> DMA0CNT_H = {0x40000ba};
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA1SAD = {0x40000bc};
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA1DAD = {0x40000c0};
	constexpr static IOReg_t<uint16_t, AccessMode::W> DMA1CNT_L = {0x40000c4};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> DMA1CNT_H = {0x40000c6};
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA2SAD = {0x40000c8};
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA2DAD = {0x40000cc};
	constexpr static IOReg_t<uint16_t, AccessMode::W> DMA2CNT_L = {0x40000d0};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> DMA2CNT_H = {0x40000d2};
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA3SAD = {0x40000d4};
	constexpr static IOReg_t<uint32_t, AccessMode::W> DMA3DAD = {0x40000d8};
	constexpr static IOReg_t<uint16_t, AccessMode::W> DMA3CNT_L = {0x40000dc};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> DMA3CNT_H = {0x40000de};
}

#endif // CPU_DMA_TRANSFER_CHANNELS_H