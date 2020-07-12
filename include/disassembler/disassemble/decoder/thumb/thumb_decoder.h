//
// Created by orzgg on 2020-06-07.
//

#ifndef TABLE_GEN_THUMB_DECODER_H
#define TABLE_GEN_THUMB_DECODER_H

#include <cstdint>
#include <disassemble/decoder/thumb/thumb_type_table.h>

struct thumb_decoder {
    static constexpr uint Type(const uint fetched) {
        return cpu_decode::thumbTable[ hash( fetched ) ] ;
    } // Type

    static constexpr uint16_t hash(const uint32_t fetched) {
        return ( fetched & 0xffc0 ) >> 6 ;
    } // hash()
};

#endif //TABLE_GEN_THUMB_DECODER_H
