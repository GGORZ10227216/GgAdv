//
// Created by orzgg on 2020-06-23.
//

#include <component_type.h>
#include <capstone/capstone.h>

#ifndef TABLE_GEN_DECODER_H
#define TABLE_GEN_DECODER_H

namespace Components {
    class Disassembler : public Component_t<Components::System> {
    public :
        Disassembler(Components::System* parentPtr) ;
        ~Disassembler() ;
        std::string Disassemble(unsigned binary) ;
        std::string ToString() override {
            return "Huh?" ;
        }

    private :
        csh armHandle, thumbHandle;
        cs_insn *insn;
        size_t count;
    };
}


#endif //TABLE_GEN_DECODER_H
