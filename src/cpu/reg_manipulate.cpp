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
    using namespace CPU_Enum ;
    CpuMode oldMode = static_cast<CpuMode> (_regs._cpsr & cpuModeMask) ;
    CpuMode newMode = static_cast<CpuMode> (newCpsr & cpuModeMask) ;
    unsigned* currentCpsr = _regs.GetBankRegDataPtr(oldMode),
            * targetCpsr  = _regs.GetBankRegDataPtr(newMode);

    if (oldMode != newMode) {
        const int cpStart_old = (oldMode == FIQ) ? r8 : sp ;
        const int cpStart_new = (newMode == FIQ) ? r8 : sp ;
        const unsigned cpSize_old = lr - cpStart_old + 1 ;
        const unsigned cpSize_new = lr - cpStart_new + 1 ;
        // Store back current content to reg bank
        memcpy(currentCpsr, _regs.contents.data() + cpStart_old, sizeof(unsigned) * cpSize_old ) ;
        if (cpStart_old - cpStart_new < 0 && newMode == CpuMode::FIQ) {
            // switch from a bank which is smaller than current mode's bank
            // r8~r12 need to restored from usersys bank
            memcpy(_regs.contents.data() + r8, _regs._registers_usrsys.data() + r8, sizeof(unsigned) * 5 ) ;
        } // if

        // Load banked register from new mode's reg bank
        memcpy( _regs.contents.data() + cpStart_new, targetCpsr, sizeof(unsigned) * cpSize_new ) ;
    } // if

    _regs._cpsr = newCpsr;
}

void Components::CPU::WriteReg(RegName reg, unsigned int val) {
    _regs.contents[reg] = val;
    if (reg == RegName::pc)
        FillPipeline() ;
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






