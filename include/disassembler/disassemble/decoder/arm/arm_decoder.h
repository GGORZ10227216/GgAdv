//
// Created by orzgg on 2020-05-04.
//

#ifndef DECODER_ARM_DECODER_H
#define DECODER_ARM_DECODER_H

#include <cpu_decode.h>
#include <disassemble/decoder/arm/arm_type_table.h>

struct arm_decoder {
    static constexpr uint Type(const uint fetched) {
        return cpu_decode::armTable[ hash( fetched ) ] ;
    } // Type

    static constexpr uint32_t hash(const uint32_t fetched) {
        return ( ( fetched & 0x0ff00000 ) >> 16 ) | ( (fetched & 0xf0) >> 4 ) ;
    } // hash()
};


#endif //DECODER_ARM_DECODER_H
