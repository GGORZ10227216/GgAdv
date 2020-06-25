//
// Created by orzgg on 2020-06-24.
//

#include <cpu.h>
#include <utility>
#include <system_components.h>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum ;

unsigned Components::CPU::Registers::ReadReg(DecodeMode dMode, size_t regNum) {
    if ( !IsVisible( dMode, regNum ) )
        _parent.ErrorHandler( E_ErrorType::invisible_register_had_been_read ) ;

    switch (_parent._cpuMode) {
        case CpuMode::FIQ :
            if ( regNum >= r8 && regNum <= lr )
                return _registers_fiq[ regNum - r8 ] ;
        case CpuMode::IRQ :
            if ( regNum >= sp && regNum <= lr )
                return _registers_irq[ regNum - sp ] ;
            break;
        case CpuMode::SVC :
            if ( regNum >= sp && regNum <= lr )
                return _registers_svp[ regNum - sp ] ;
            break;
        case CpuMode::ABT :
            if ( regNum >= sp && regNum <= lr )
                return _registers_abt[ regNum - sp ] ;
            break;
        case CpuMode::UND :
            if ( regNum >= sp && regNum <= lr )
                return _registers_und[ regNum - sp ] ;
            break;
    } // switch

    return _registers_usersys[ regNum ] ;
} // ReadReg()

bool Components::CPU::Registers::IsVisible( DecodeMode dMode, size_t regNum ) {
    if (dMode == E_DecodeMode::THUMB && regNum > r7 && regNum < sp ) {
        fmt::format("Invalid reg number: {:d} in thumb mode.({})",
                    regNum, _parent.ToString()
        );

        return false ;
    } // if

    return true ;
}

unsigned Components::CPU::Registers::ReadCpsr() {
    return _cpsr;
}

unsigned Components::CPU::Registers::ReadSpsr() {
    switch (_parent._cpuMode) {
        case CpuMode::FIQ :
            return _spsr_fiq ;
        case CpuMode::IRQ :
            return _spsr_irq ;
        case CpuMode::SVC :
            return _spsr_svc ;
        case CpuMode::ABT :
            return _spsr_abt ;
        case CpuMode::UND :
            return _spsr_und ;
    } // switch

    return INVALID_VALUE ;
}
std::string Components::CPU::Registers::ToString() {
    return PrintGeneralReg( std::make_index_sequence<8>{} );
}

template<size_t... Idx>
std::string Components::CPU::Registers::PrintGeneralReg(std::integer_sequence<size_t, Idx...> ) {
    return fmt::format(
        "General register (r0~r7) :\n"
            "\tr0: {:#010x}, r1: {:#010x}, r2: {:#010x}, r3: {:#010x}\n"
            "\tr4: {:#010x}, r5: {:#010x}, r6: {:#010x}, r7: {:#010x}\n",
            _registers_usersys[ Idx ]...
    ) ;
}
// IsVisible()