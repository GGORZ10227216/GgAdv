//
// Created by orzgg on 2020-06-25.
//
#include <iostream>
#include <vector>
#include <string>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <register.h>
#include <system_enum.h>
#include <component_type.h>
#include <system_literals.h>

#ifndef CPU_CPU_H
#define CPU_CPU_H

namespace Components {
    class CPU : public ClkDrivenComponent_t<Components::System> {
    public :
        CPU(Components::System* parentPtr);

        std::string ToString() override;

        void Tick() override;

        void ChangeCPUMode(CpuMode newMode);

        unsigned ReadReg(RegName reg) {
            return _regs.contents[reg];
        } // ReadReg()

        unsigned ReadCpsr();

        void RestoreCpsr(CpuMode mode);

        CpuMode CurrentCPUMode();

        bool TestPSRFlag(CPU_Enum::E_PSRBit bitName);

        DecodeMode CurrentDecodeMode();

        unsigned ReadSpsr(CpuMode target) {
            return GetSpsr(target) ;
        }

        void WriteCpsr(unsigned newCpsr);

        void WriteSpsr(CpuMode target, unsigned value) {
            GetSpsr(target) = value ;
        }

        void WriteReg(CPU_Enum::E_RegName reg, unsigned val);

        void SetFlag(PSRBit bitName);

        void ClearFlag(PSRBit bitName);

        unsigned ProgramCounter();

        unsigned R15() ;

        unsigned Instruction() { return fetchedBuffer[stageCounter]; }

        void FillPipeline();

    private :

        void Fetch();

        void Execute();

        void ExecuteArm();

        void ExecuteThumb();

        void CheckInterrupt();

        std::string PrintStatus();

        void CheckVisible(bool inThumb, size_t regNum);

//        unsigned &GetRegRef(RegName reg);

        bool ConditionCheck(const unsigned condCode);

        unsigned& GetSpsr(CpuMode target) {
            switch (target) {
                case CpuMode::FIQ :
                    _regs._spsr_fiq ;
                    break ;
                case CpuMode::IRQ :
                    _regs._spsr_irq ;
                    break ;
                case CpuMode::SVC :
                    _regs._spsr_svc ;
                    break ;
                case CpuMode::ABT :
                    _regs._spsr_abt ;
                    break ;
                case CpuMode::UND :
                    _regs._spsr_und ;
                    break ;
                default :
                    throw std::logic_error("write spsr to a non-banked mode") ;
            } // switch
        }

        Registers _regs;
        unsigned stageCounter = 0 ;
        bool pipelineFlushed = true ;
        std::array<unsigned, 3> fetchedBuffer;
    };
}
#endif //CPU_CPU_H