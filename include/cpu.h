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
        CPU() : _regs(this) {}
        std::string ToString() override {
            return _regs.ToString();
        } // ToString()

    private :
        class Registers : private ChildComponent_t<CPU> {
        public :
            explicit Registers(CPU* parent) : ChildComponent_t(parent) {}

            unsigned ReadReg(DecodeMode dMode, size_t regNum) ;
            unsigned ReadCpsr() ;
            unsigned ReadSpsr() ;
            unsigned ProgramCounter() { return _registers_usersys[15]; }
            std::string ToString() override ;

            template<size_t... Idx>
            std::string PrintGeneralReg( std::integer_sequence<size_t, Idx...> ) ;
        private :
            std::array<unsigned, 16> _registers_usersys{};
            std::array<unsigned, 7> _registers_fiq{};
            std::array<unsigned, 2> _registers_svp{};
            std::array<unsigned, 2> _registers_abt{};
            std::array<unsigned, 2> _registers_irq{};
            std::array<unsigned, 2> _registers_und{};

            unsigned _cpsr ;
            unsigned _spsr_fiq, _spsr_svc, _spsr_abt, _spsr_irq, _spsr_und ;

            bool IsVisible( DecodeMode dMode, size_t regNum ) ;
        };

        Registers _regs ;
        CpuMode _cpuMode ;
    };
}
#endif //CPU_CPU_H