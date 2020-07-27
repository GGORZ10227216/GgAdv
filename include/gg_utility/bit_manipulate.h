//
// Created by orzgg on 2020-06-25.
//

#ifndef CPU_UTILITY_H
#define CPU_UTILITY_H

namespace Utility {
    constexpr unsigned _BV(size_t bitNo) {
        return 0x1 << bitNo ;
    } // _BV()

    template<typename T>
    constexpr bool TestBit( T bin, size_t bitNo ) {
        return bin & _BV( bitNo ) ;
    } // TestBit()

    constexpr uint32_t rotr (uint32_t x, unsigned int n) {
        enum { CHAR_BIT = 8 };
        n %= 32 ;
        const int shinfAmount = CHAR_BIT*sizeof(x) - n ;
        if ( shinfAmount == 32 )
            return x >> n ;
        else
            return (x>>n) | (x<< shinfAmount);
    }
}

#endif //CPU_UTILITY_H
