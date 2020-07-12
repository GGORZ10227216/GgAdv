//
// Created by orzgg on 2020-06-25.
//

#include <register.h>
#include <utility>
#include <exception>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum;
using namespace CPUString;

std::string Components::Registers::ToString() {
    if (!Utility::TestBit(_cpsr, T)) {
        switch (_cpsr & cpuModeMask) {
            case USR : case SYS :
                return fmt::format(
                        CPUString::UserSysRegFormat_Arm,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_usersys[8], _registers_usersys[9], _registers_usersys[10],
                        _registers_usersys[11],
                        _registers_usersys[12], _registers_usersys[13], _registers_usersys[14],
                        _registers_usersys[15]
                );
            case FIQ :
                return fmt::format(
                        CPUString::FIQRegFormat_Arm,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_fiq[0], _registers_fiq[1], _registers_fiq[2], _registers_fiq[3],
                        _registers_fiq[4], _registers_fiq[5], _registers_fiq[6], _registers_usersys[15]
                );
            case IRQ :
                return fmt::format(
                        CPUString::IRQRegFormat_Arm,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_usersys[8], _registers_usersys[9], _registers_usersys[10],
                        _registers_usersys[11],
                        _registers_usersys[12], _registers_irq[0], _registers_irq[1],
                        _registers_usersys[15]
                );
            case SVC :
                return fmt::format(
                        CPUString::SVCRegFormat_Arm,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_usersys[8], _registers_usersys[9], _registers_usersys[10],
                        _registers_usersys[11],
                        _registers_usersys[12], _registers_svc[0], _registers_svc[1],
                        _registers_usersys[15]
                );
            case ABT :
                return fmt::format(
                        CPUString::ABTRegFormat_Arm,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_usersys[8], _registers_usersys[9], _registers_usersys[10],
                        _registers_usersys[11],
                        _registers_usersys[12], _registers_abt[0], _registers_abt[1],
                        _registers_usersys[15]
                );
            case UND :
                return fmt::format(
                        CPUString::UNDRegFormat_Arm,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_usersys[8], _registers_usersys[9], _registers_usersys[10],
                        _registers_usersys[11],
                        _registers_usersys[12], _registers_und[0], _registers_und[1],
                        _registers_usersys[15]
                );
            default :
                throw std::logic_error("Unknown CPU Mode!");
        } // switch
    } // if
    else {
        switch (_cpsr & cpuModeMask) {
            case USR : case SYS :
                return fmt::format(
                        CPUString::UserSysRegFormat_Thumb,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_usersys[13], _registers_usersys[14],
                        _registers_usersys[15]
                );
            case FIQ :
                return fmt::format(
                        CPUString::FIQRegFormat_Thumb,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                         _registers_fiq[0], _registers_fiq[1], _registers_usersys[15]
                );
            case IRQ :
                return fmt::format(
                        CPUString::IRQRegFormat_Thumb,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_irq[0], _registers_irq[1], _registers_usersys[15]
                );
            case SVC :
                return fmt::format(
                        CPUString::SVCRegFormat_Thumb,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_svc[0], _registers_svc[1], _registers_usersys[15]
                );
            case ABT :
                return fmt::format(
                        CPUString::ABTRegFormat_Thumb,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_abt[0], _registers_abt[1], _registers_usersys[15]
                );
            case UND :
                return fmt::format(
                        CPUString::UNDRegFormat_Thumb,
                        _registers_usersys[0], _registers_usersys[1], _registers_usersys[2],
                        _registers_usersys[3],
                        _registers_usersys[4], _registers_usersys[5], _registers_usersys[6],
                        _registers_usersys[7],
                        _registers_und[0], _registers_und[1], _registers_usersys[15]
                );
            default :
                throw std::logic_error("Unknown CPU Mode!");
        } // switch
    } // else

    return "" ;
}
