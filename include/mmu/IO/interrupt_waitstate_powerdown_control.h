#include <ioreg_type.h>

#ifndef CPU_INTERRUPT_WAITSTATE_POWERDOWN_CONTROL_H
#define CPU_INTERRUPT_WAITSTATE_POWERDOWN_CONTROL_H

namespace IO_Map {
	constexpr static IOReg_t<uint16_t, AccessMode::RW> IE = {0x4000200};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> IF = {0x4000202};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> WAITCNT = {0x4000204};
	constexpr static IOReg_t<uint16_t, AccessMode::RW> IME = {0x4000208};
	constexpr static IOReg_t<uint32_t, AccessMode::RW> POSTFLG = {0x4000300};
	constexpr static IOReg_t<uint32_t, AccessMode::W> HALTCNT = {0x4000301};
}

#endif // CPU_INTERRUPT_WAITSTATE_POWERDOWN_CONTROL_H