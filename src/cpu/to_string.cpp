//
// Created by orzgg on 2020-06-25.
//

#include <utility>
#include <exception>

#include <system_components.h>
#include <disassembler.h>
#include <cpu.h>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum ;
using namespace CPUString ;

std::string Components::CPU::ToString() {
    std::string Status = PrintStatus();
    std::string registerStatus = _regs.ToString() ;
    return fmt::format("clk:{} [{:#04x}] {}(0x{:08x})\n{}\n{}\n",
            EMU_CLK,
            R15(),
            PRINT_ASM(Instruction()),
            Instruction(),
            Status, registerStatus
    ) ;
}

std::string Components::CPU::PrintStatus() {
    std::string decodeMode = TestPSRFlag(T) ? "Thumb" : "Arm" ;
    std::string cpuMode ;
    char flagV = TestPSRFlag(V) ? 'V' : 'v' ;
    char flagC = TestPSRFlag(C) ? 'C' : 'c' ;
    char flagZ = TestPSRFlag(Z) ? 'Z' : 'z' ;
    char flagN = TestPSRFlag(N) ? 'N' : 'n' ;
    char flagI = TestPSRFlag(I) ? 'I' : 'i' ;
    char flagF = TestPSRFlag(F) ? 'F' : 'f' ;

    switch (_regs._cpsr & cpuModeMask) {
        case FIQ :
            cpuMode = CPUString::ModeName[ Str_Fiq ] ;
            break ;
        case IRQ :
            cpuMode = CPUString::ModeName[ Str_Irq ] ;
            break ;
        case SVC :
            cpuMode = CPUString::ModeName[ Str_Svc ] ;
            break ;
        case ABT :
            cpuMode = CPUString::ModeName[ Str_Abt ] ;
            break ;
        case UND :
            cpuMode = CPUString::ModeName[ Str_Und ] ;
            break ;
        case USR :
            cpuMode = CPUString::ModeName[ Str_Usr ] ;
            break ;
        case SYS :
            cpuMode = CPUString::ModeName[ Str_Sys ] ;
            break ;
        default :
            throw std::logic_error( "Unknown CPU Mode!" ) ;
    } // switch

    return fmt::format( "Mode: <{},{}>, flags:[{} {} {} {} : {} {}]",
                        decodeMode, cpuMode, flagN, flagZ, flagC, flagV, flagI, flagF
    ) ;
}

