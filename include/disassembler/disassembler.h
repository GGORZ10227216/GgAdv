//
// Created by orzgg on 2020-06-23.
//

#include <component_type.h>
#include <arm_formatter.h>
#include <thumb_formatter.h>

#ifndef TABLE_GEN_DECODER_H
#define TABLE_GEN_DECODER_H

namespace Components {
    class Disassembler : public Component_t<Components::System> {
    public :
        Disassembler(Components::System* parentPtr) :
            Component_t(parentPtr) {}

        std::string Disassemble(unsigned binary) ;
        std::string ToString() override {
            return "Huh?" ;
        }
    };
}


#endif //TABLE_GEN_DECODER_H
