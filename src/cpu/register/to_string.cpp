//
// Created by orzgg on 2020-06-25.
//

#include <cpu.h>
#include <utility>
#include <exception>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum ;
using namespace ModeString ;

std::string Components::CPU::Registers::ToString() {
    std::string Status = PrintStatus();
    std::string GeneralRegister = PrintGeneralReg( std::make_index_sequence<8>{} ) ;
    std::string ModeSpecificRegister ;

    return fmt::format( "{}\n{}\n{}\n", Status, GeneralRegister, ModeSpecificRegister ) ;
}

std::string Components::CPU::Registers::PrintStatus() {
    std::string decodeMode = TestFlag( T ) ? "Thumb" : "Arm" ;
    std::string cpuMode ;
    char flagV = TestFlag( V ) ? 'V' : 'v' ;
    char flagC = TestFlag( C ) ? 'C' : 'c' ;
    char flagZ = TestFlag( Z ) ? 'Z' : 'z' ;
    char flagN = TestFlag( N ) ? 'N' : 'n' ;
    char flagI = TestFlag( I ) ? 'I' : 'i' ;
    char flagF = TestFlag( F ) ? 'F' : 'f' ;

    switch (_cpsr & cpuModeMask) {
        case FIQ :
            cpuMode = ModeString::ModeName[ Str_Fiq ] ;
            break ;
        case IRQ :
            cpuMode = ModeString::ModeName[ Str_Irq ] ;
            break ;
        case SVC :
            cpuMode = ModeString::ModeName[ Str_Svc ] ;
            break ;
        case ABT :
            cpuMode = ModeString::ModeName[ Str_Abt ] ;
            break ;
        case UND :
            cpuMode = ModeString::ModeName[ Str_Und ] ;
            break ;
        case USR :
            cpuMode = ModeString::ModeName[ Str_Usr ] ;
            break ;
        case SYS :
            cpuMode = ModeString::ModeName[ Str_Sys ] ;
            break ;
        default :
            throw std::logic_error( "Unknown CPU Mode!" ) ;
    } // switch

    return fmt::format( "Mode: <{},{}>, flags:[{} {} {} {} : {} {}]",
        decodeMode, cpuMode, flagN, flagZ, flagC, flagV, flagI, flagF
    ) ;
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