//
// Created by orzgg on 2020-07-04.
//

#include <array>
#include <string>

#include <component_type.h>

#ifndef TEST_REGISTER_H
#define TEST_REGISTER_H

namespace Components {
    class Registers : public Component_t {
    public :
        friend class CPU ;
        std::string ToString() override ;

    private :
        std::array<unsigned, 16> _registers_usersys{};
        std::array<unsigned, 7> _registers_fiq{};
        std::array<unsigned, 2> _registers_svc{};
        std::array<unsigned, 2> _registers_abt{};
        std::array<unsigned, 2> _registers_irq{};
        std::array<unsigned, 2> _registers_und{};

        unsigned _cpsr ;
        unsigned _spsr_fiq, _spsr_svc, _spsr_abt, _spsr_irq, _spsr_und ;
    };
}

#endif //TEST_REGISTER_H
