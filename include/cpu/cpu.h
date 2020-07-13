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

        unsigned ReadReg(RegName regNum);

        unsigned ReadCpsr();

        void RestoreCpsr(CpuMode mode);

        CpuMode CurrentCPUMode();

        bool TestPSRFlag(CPU_Enum::E_PSRBit bitName);

        DecodeMode CurrentDecodeMode();

        void WriteCpsr(unsigned newCpsr);

        void WriteReg(CPU_Enum::E_RegName reg, unsigned val);

        void SetFlag(PSRBit bitName);

        void ClearFlag(PSRBit bitName);

        unsigned ProgramCounter();

        unsigned R15() {
            unsigned offset = (CurrentDecodeMode() == DecodeMode::ARM) ? 4 : 2;
            return _regs._registers_usersys[ RegName::pc ] - offset*2 ;
        }

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

        unsigned &GetRegRef(RegName reg);

        bool ConditionCheck(const unsigned condCode);

        Registers _regs;
        unsigned stageCounter = 0;
        bool pipelineFlushed = true ;
        std::array<unsigned, 3> fetchedBuffer;
    };
}
#endif //CPU_CPU_H