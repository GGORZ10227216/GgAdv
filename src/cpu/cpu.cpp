//
// Created by orzgg on 2020-06-25.
//
#include <cpu.h>
#include <arm_decoder.h>
#include <arm_info.h>
#include <arm_table.h>
#include <thumb_decoder.h>
#include <cycle_tools.h>
#include <bit_manipulate.h>

#include <utility>
#include <exception>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum;

Components::CPU::CPU(Components::System* parentPtr) :
    ClkDrivenComponent_t(parentPtr)
{
    WriteCpsr(0xd3);
    WriteReg(r0, 0x00000ca5);
    WriteReg(sp, 0x03007f00);
    // WriteReg(pc, 0x0);
}

void Components::CPU::FillPipeline() {
    unsigned pcOffset = CurrentDecodeMode() == DecodeMode::ARM ? 4 : 2;
    unsigned pcBase = 0 ;

    const unsigned Sclk = CLK_CONT.S(ProgramCounter()) ;
    const unsigned Nclk = CLK_CONT.N(ProgramCounter()) ;

    EMU_CLK += Sclk + Nclk ;
    for (int i = 0 ; i < fetchedBuffer.size(); ++i) {
        pcBase = _regs._registers_usersys[pc] + pcOffset*i ;
        if (pcOffset == 4)
            fetchedBuffer[i] = EMU_MEM.Read32(pcBase);
        else
            fetchedBuffer[i] = EMU_MEM.Read16(pcBase);
    } // for

    _regs._registers_usersys[ pc ] = pcBase ;
    stageCounter = 0 ;
    pipelineFlushed = true ;
}

void Components::CPU::Fetch() {
    unsigned pcOffset = CurrentDecodeMode() == DecodeMode::ARM ? 4 : 2;
    _regs._registers_usersys[pc] += pcOffset;
    if (pcOffset == 4)
        fetchedBuffer[ stageCounter ] = EMU_MEM.Read32(ProgramCounter());
    else
        fetchedBuffer[ stageCounter ] = EMU_MEM.Read16(ProgramCounter());
    stageCounter = (stageCounter + 1) % fetchedBuffer.size();
}

void Components::CPU::Tick() {
    if (EMU_CLK == 0) {
        // CPU is ready to process next instruction
        Execute();
        if ( !pipelineFlushed )
            Fetch();
        else
            pipelineFlushed = false ;
    } // if
    else
        CheckInterrupt();
}

void Components::CPU::Execute() {
    if (CurrentDecodeMode() == ARM)
        ExecuteArm();
    /// TODO: Thumb function implement.
//    else
//        type = thumb_decoder::Type(fetched);
}

void Components::CPU::ExecuteArm() {
    if (ConditionCheck(Instruction() >> 28))
        ArmHandlerTable[ arm_decoder::hash(Instruction()) ](emuInstance) ;
}

void Components::CPU::ExecuteThumb() {

}

void Components::CPU::CheckInterrupt() {

}

bool Components::CPU::ConditionCheck(const unsigned condCode) {
    using namespace Utility;
    auto Test = [&](E_PSRBit bit) { return TestBit(_regs._cpsr, bit); };
    switch (condCode) {
        case EQ :
            return Test(Z);
        case NE :
            return !Test(Z);
        case CS :
            return Test(C);
        case CC :
            return !Test(C);
        case MI :
            return Test(N);
        case PL :
            return !Test(N);
        case VS :
            return Test(V);
        case VC :
            return !Test(V);
        case HI :
            return Test(C) && !Test(Z);
        case LS :
            return !Test(C) && Test(Z);
        case GE :
            return Test(N) == Test(V);
        case LT :
            return Test(N) != Test(V);
        case GT :
            return !Test(Z) && (Test(N) == Test(V));
        case LE :
            return Test(Z) && (Test(N) != Test(V));
        case AL :
            return true;
        default :
            throw std::logic_error("unknown condition code");
    }
}

unsigned Components::CPU::ProgramCounter() {
    return _regs._registers_usersys[RegName::pc];
}

unsigned Components::CPU::R15() {
    unsigned offset = (CurrentDecodeMode() == DecodeMode::ARM) ? 4 : 2;
    return _regs._registers_usersys[ RegName::pc ] - offset*2 ;
}







