//
// Created by orzgg on 2020-05-04.
//

#ifndef DECODER_BIT_MASK_H
#define DECODER_BIT_MASK_H

#include <tuple>

using BitMask = const std::tuple<unsigned int, unsigned int> ;

namespace bit_mask {
    constexpr BitMask mask_condition        = { 0xf0000000, 28 } ;
    constexpr BitMask mask_16_19            = { 0x000f0000, 16 } ;
    constexpr BitMask mask_12_15            = { 0x0000f000, 12 } ;
    constexpr BitMask mask_08_11            = { 0x00000f00, 8 } ;
    constexpr BitMask mask_04_07            = { 0x000000f0, 4 } ;
    constexpr BitMask mask_00_03            = { 0x0000000f, 0 } ;
    constexpr BitMask mask_shift_type       = { 0x00000060, 5 } ;
    constexpr BitMask mask_reg_shift_amount = { 0x00000f80, 7 } ;
    constexpr BitMask mask_dp_opcode        = { 0x01e00000, 21 } ;
    constexpr BitMask mask_operand2_imm     = { 0x000000ff, 0 } ;
    constexpr BitMask mask_operand2_rot     = { 0x00000f00, 8 } ;
    constexpr BitMask mask_reg_list         = { 0x0000ffff, 0 } ;

    constexpr unsigned int _BV(const int shift) {
        return 0x1 << shift ;
    } // BitMask()

    constexpr int MASK32( const int width, const int offset ) { return ( 0xffffffff >> ( 32 - width ) ) << offset ; }

    constexpr unsigned int FlagMask(const char flagName) {
        return flagName - 'A' ;
    } // BitMask()

    constexpr bool GetBit(const uint32_t instruction, const uint bitNo) {
        return instruction & _BV(bitNo) ;
    }

    constexpr int RealMaskedValue(const uint32_t instruction, const BitMask& bitMask) {
        return ( instruction & std::get<0>(bitMask) ) >> std::get<1>(bitMask) ;
    }

    constexpr uint32_t rotr (uint32_t x, unsigned int n) {
        enum { CHAR_BIT = 8 };
        n %= 32 ;
        const int shinfAmount = CHAR_BIT*sizeof(x) - n ;
        if ( shinfAmount == 32 )
            return x >> n ;
        else
            return (x>>n) | (x<< shinfAmount);
    }

    template<typename Arg>
    constexpr unsigned Type(Arg f) {
        return _BV( f ) ;
    } // MakeFieldFlag()

    template<typename Arg, typename... Args>
    constexpr unsigned Type(Arg f, Args... fn) {
        return Type( fn... ) | _BV( f ) ;
    } // MakeFieldFlag()

    constexpr uint32_t Count(uint32_t i) {
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        uint32_t result = (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24 ;

        return result;
    }

    constexpr uint32_t Count( uint32_t i, uint32_t f) {
        bool PostNotation = (f == 5 || f == 6 )
                            && (i & _BV( 11 )) ;

        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        uint32_t result = (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24 ;

        return ( PostNotation ? result - 1 : result );
    }
}

#endif //DECODER_BIT_MASK_H
