//
// Created by orzgg on 2020-06-23.
//


#ifndef TABLE_GEN_DECODER_H
#define TABLE_GEN_DECODER_H

#include <arm_formatter.h>
#include <thumb_formatter.h>

class Disassembler {
public :
    std::string Disassemble(unsigned binary) ;
};

#endif //TABLE_GEN_DECODER_H
