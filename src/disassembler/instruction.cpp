//
// Created by orzgg on 2020-05-04.
//
#include <instruction.h>
#include <disassemble/decoder/arm/arm_decoder.h>
#include <disassemble/decoder/thumb/thumb_decoder.h>

ThumbInstruction::ThumbInstruction( unsigned int rawI ) :
    RawInstruction{ rawI }, type (thumb_decoder::Type( raw.word ) ) {}

uint32_t ThumbInstruction::DecodeBLOffset() const {
    uint16_t hiOffset = raw.half[ 0 ] & 0x7ff, loOffset = raw.half[ 1 ] & 0x7ff ;
    return (hiOffset << 12) | (loOffset << 1) ;
}
