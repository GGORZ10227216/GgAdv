#include <ioreg_type.h>

#ifndef CPU_SERIAL_COMMUNICATION_1_H
#define CPU_SERIAL_COMMUNICATION_1_H

namespace IO_Map {
	constexpr static IOReg_t<uint32_t, AccessMode::RW> SIODATA32 = {0x4000120};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SIOMULTI0 = {0x4000120};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SIOMULTI1 = {0x4000122};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SIOMULTI2 = {0x4000124};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SIOMULTI3 = {0x4000126};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SIOCNT = {0x4000128};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SIOMLT_SEND = {0x400012a};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> SIODATA8 = {0x400012a};
}

#endif // CPU_SERIAL_COMMUNICATION_1_H