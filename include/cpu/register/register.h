//
// Created by orzgg on 2020-07-04.
//

#include <array>
#include <string>

#include <component_type.h>
#include <system_enum.h>

#ifndef TEST_REGISTER_H
#define TEST_REGISTER_H

namespace Components {
    class Registers {
    public :
        friend class CPU ;
        std::string ToString() ;

        unsigned* GetBankRegDataPtr(CpuMode mode) {
            using namespace ModeEnum ;
            switch (mode) {
                case FIQ :
                    return _registers_fiq.data() ;
                case IRQ :
                    return _registers_irq.data() ;
                case SVC :
                    return _registers_svc.data() ;
                case ABT :
                    return _registers_abt.data() ;
                case UND :
                    return _registers_und.data() ;
                case SYS : case USR :
                    return _registers_usrsys.data() ;
                default:
                    throw std::logic_error("Unknown register bank") ;
            } // switch

            return nullptr ;
        }

    private :
        std::array<unsigned, 16> contents{};
        std::array<unsigned, 7> _registers_usrsys{};
        std::array<unsigned, 7> _registers_fiq{};
        std::array<unsigned, 2> _registers_svc{};
        std::array<unsigned, 2> _registers_abt{};
        std::array<unsigned, 2> _registers_irq{};
        std::array<unsigned, 2> _registers_und{};

        unsigned _cpsr = 0xd3 ;
        unsigned _spsr_fiq = ModeEnum::FIQ,
                 _spsr_svc = ModeEnum::SVC,
                 _spsr_abt = ModeEnum::ABT,
                 _spsr_irq = ModeEnum::IRQ,
                 _spsr_und = ModeEnum::UND ;
    };
}

#endif //TEST_REGISTER_H
