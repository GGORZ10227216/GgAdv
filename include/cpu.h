//
// Created by orzgg on 2020-06-25.
//
#include <iostream>
#include <vector>
#include <string>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <system_enum.h>
#include <component_type.h>
#include <system_literals.h>

#ifndef CPU_CPU_H
#define CPU_CPU_H

namespace Components {
    class CPU : public Component_t {
    public :
        CPU() : _regs(this) {
            ChangeCPUMode(ModeEnum::USR) ;
        } // CPU()

        std::string ToString() override {
            return _regs.ToString();
        } // ToString()

        void ChangeCPUMode(CpuMode newMode) {
            _regs._cpsr = (_regs._cpsr >> 5) << 5 ;
            _regs._cpsr |= newMode ;
        } // ChangeCPUMode()

    private :
        class Registers : private ChildComponent_t<CPU> {
        public :
            friend CPU ;
            explicit Registers(CPU* parent) : ChildComponent_t(parent) {}

            unsigned ReadReg(RegName regNum) ;
            unsigned ReadCpsr() ;
            unsigned ReadSpsr() ;
            CpuMode ReadCPUMode() ;
            bool TestFlag( CPU_Enum::E_PSRBit bitName ) {
                return Utility::TestBit( _cpsr, bitName ) ;
            }

            void WriteCpsr(unsigned newCpsr) ;
            void WriteReg(CPU_Enum::E_RegName reg, unsigned val) ;

            std::string ToString() override ;

            template<size_t... Idx>
            std::string PrintGeneralReg( std::integer_sequence<size_t, Idx...> ) ;

            std::string PrintStatus() ;
        private :
            std::array<unsigned, 16> _registers_usersys{};
            std::array<unsigned, 7> _registers_fiq{};
            std::array<unsigned, 2> _registers_svp{};
            std::array<unsigned, 2> _registers_abt{};
            std::array<unsigned, 2> _registers_irq{};
            std::array<unsigned, 2> _registers_und{};

            unsigned _cpsr ;
            unsigned _spsr_fiq, _spsr_svc, _spsr_abt, _spsr_irq, _spsr_und ;
            bool IsVisible( bool inThumb, size_t regNum ) ;
            unsigned& GetRegRef(RegName reg) ;
        };

        Registers _regs ;
    };
}
#endif //CPU_CPU_H