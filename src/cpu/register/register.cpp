//
// Created by orzgg on 2020-06-25.
//
#include <cpu.h>
#include <utility>
#include <exception>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum ;

unsigned Components::CPU::Registers::ReadReg(RegName reg ) {
    return GetRegRef( reg ) ;
} // ReadReg()

bool Components::CPU::Registers::IsVisible( bool inThumb, size_t regNum ) {
    if (inThumb && regNum > r7 && regNum < sp ) {
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
    switch (_cpsr & cpuModeMask) {
        case FIQ :
            return _spsr_fiq ;
        case IRQ :
            return _spsr_irq ;
        case SVC :
            return _spsr_svc ;
        case ABT :
            return _spsr_abt ;
        case UND :
            return _spsr_und ;
        case USR : case SYS :
            throw std::logic_error( "Illegal CPU Mode!" ) ;
        default :
            throw std::logic_error( "Unknown CPU Mode!" ) ;
    } // switch

    return INVALID_VALUE ;
}

void Components::CPU::Registers::WriteCpsr( unsigned newCpsr ) {
    _cpsr = newCpsr ;
}

void Components::CPU::Registers::WriteReg(RegName reg, unsigned int val) {
    GetRegRef( reg ) = val ;
}

CpuMode Components::CPU::Registers::ReadCPUMode() {
    switch (_cpsr & cpuModeMask) {
        case USR :
        case FIQ :
        case IRQ :
        case SVC :
        case ABT :
        case UND :
        case SYS :
            return static_cast<CpuMode>( _cpsr & ModeEnum::cpuModeMask ) ;
        default :
            throw std::logic_error( "Unknown CPU Mode!" ) ;
    } // switch
}

unsigned &Components::CPU::Registers::GetRegRef(RegName reg) {
    if ( !IsVisible( TestFlag( T ), reg ) )
        throw std::logic_error( "Trying to access Hi register directly in Thumb mode." ) ;

    switch (_cpsr & cpuModeMask) {
        case FIQ :
            if (reg >= r8 && reg <= lr)
            if (reg >= r8 && reg <= lr)
                return _registers_fiq[reg - r8 ] ;
        case IRQ :
            if (reg >= sp && reg <= lr)
                return _registers_irq[reg - sp ] ;
            break;
        case SVC :
            if (reg >= sp && reg <= lr)
                return _registers_svp[reg - sp ] ;
            break;
        case ABT :
            if (reg >= sp && reg <= lr)
                return _registers_abt[reg - sp ] ;
            break;
        case UND :
            if (reg >= sp && reg <= lr)
                return _registers_und[reg - sp ] ;
            break;
    } // switch

    return _registers_usersys[ reg ] ;
}