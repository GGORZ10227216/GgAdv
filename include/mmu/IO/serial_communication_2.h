#include <ioreg_type.h>

#ifndef CPU_SERIAL_COMMUNICATION_2_H
#define CPU_SERIAL_COMMUNICATION_2_H

namespace IO_Map {
	constexpr static IOReg_t<uint16_t, AccessMode::RW> RCNT = {0x4000134};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> JOYCNT = {0x4000140};
	constexpr static IOReg_t<uint32_t, AccessMode::RW> JOY_RECV = {0x4000150};
	constexpr static IOReg_t<uint32_t, AccessMode::RW> JOY_TRANS = {0x4000154};
	constexpr static IOReg_t<uint16_t, AccessMode::R?> JOYSTAT = {0x4000158};
}

#endif // CPU_SERIAL_COMMUNICATION_2_H