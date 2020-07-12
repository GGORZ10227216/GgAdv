//
// Created by orzgg on 2020-07-04.
//

#include <cpu.h>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum;

void Components::CPU::ChangeCPUMode(CpuMode newMode) {
    _regs._cpsr = (_regs._cpsr >> 5) << 5;
    _regs._cpsr |= newMode;
} // ChangeCPUMode()

unsigned Components::CPU::ReadReg(RegName reg) {
    return GetRegRef(reg);
} // ReadReg()

void Components::CPU::CheckVisible(bool inThumb, size_t regNum) {
    if (inThumb && regNum > r7 && regNum < sp)
        throw std::logic_error("Trying to access Hi register directly in Thumb mode.");
}

unsigned Components::CPU::ReadCpsr() {
    return _regs._cpsr;
}

void Components::CPU::RestoreCpsr(CpuMode mode) {
    switch (mode) {
        case FIQ :
            _regs._cpsr = _regs._spsr_fiq;
        case IRQ :
            _regs._cpsr = _regs._spsr_irq;
        case SVC :
            _regs._cpsr = _regs._spsr_svc;
        case ABT :
            _regs._cpsr = _regs._spsr_abt;
        case UND :
            _regs._cpsr = _regs._spsr_und;
        case USR :
        case SYS :
            throw std::logic_error("Illegal CPU Mode!");
        default :
            throw std::logic_error("Unknown CPU Mode!");
    } // switch
}

void Components::CPU::WriteCpsr(unsigned newCpsr) {
    _regs._cpsr = newCpsr;
}

void Components::CPU::WriteReg(RegName reg, unsigned int val) {
    GetRegRef(reg) = val;
}

CpuMode Components::CPU::CurrentCPUMode() {
    switch (_regs._cpsr & cpuModeMask) {
        case USR :
        case FIQ :
        case IRQ :
        case SVC :
        case ABT :
        case UND :
        case SYS :
            return static_cast<CpuMode>( _regs._cpsr & ModeEnum::cpuModeMask );
        default :
            throw std::logic_error("Unknown CPU Mode!");
    } // switch
}

unsigned &Components::CPU::GetRegRef(RegName reg) {
    CheckVisible(TestPSRFlag(T), reg);
    switch (_regs._cpsr & cpuModeMask) {
        case FIQ :
            if (reg >= r8 && reg <= lr)
                return _regs._registers_fiq[reg - r8];
        case IRQ :
            if (reg >= sp && reg <= lr)
                return _regs._registers_irq[reg - sp];
        case SVC :
            if (reg >= sp && reg <= lr)
                return _regs._registers_svc[reg - sp];
        case ABT :
            if (reg >= sp && reg <= lr)
                return _regs._registers_abt[reg - sp];
        case UND :
            if (reg >= sp && reg <= lr)
                return _regs._registers_und[reg - sp];
    } // switch

    return _regs._registers_usersys[reg];
}

bool Components::CPU::TestPSRFlag(CPU_Enum::E_PSRBit bitName) {
    return Utility::TestBit(_regs._cpsr, bitName);
}

DecodeMode Components::CPU::CurrentDecodeMode() {
    return TestPSRFlag(CPU_Enum::T) ? DecodeMode::THUMB : DecodeMode::ARM;
}

void Components::CPU::SetFlag(PSRBit bitName) {
    _regs._cpsr |= Utility::_BV(bitName);
}

void Components::CPU::ClearFlag(PSRBit bitName) {
    _regs._cpsr &= ~(Utility::_BV(bitName));
}






