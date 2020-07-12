#include <ioreg_type.h>

#ifndef CPU_KEYPAD_INPUT_H
#define CPU_KEYPAD_INPUT_H

namespace IO_Map {
	constexpr static IOReg_t<uint16_t, AccessMode::R> KEYINPUT = {0x4000130};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> KEYCNT = {0x4000132};
}

#endif // CPU_KEYPAD_INPUT_H