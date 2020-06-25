//
// Created by orzgg on 2020-06-25.
//

#include <tuple>
#include <array>

#ifndef CPU_UTILITY_H
#define CPU_UTILITY_H

namespace Utility {
    template <typename... Ts>
    constexpr auto MakeArray( Ts... args ) {
        auto tmp = std::get<0>(std::make_tuple( args... )) ;
        return std::array<decltype(tmp), sizeof...(args)> { args... } ;
    } // MakeArray()

    constexpr unsigned _BV(size_t bitNo) {
        return 0x1 << bitNo ;
    } // _BV()

    constexpr bool TestBit( unsigned bin, size_t bitNo ) {
        return bin & _BV( bitNo ) ;
    } // TestBit()
}

#endif //CPU_UTILITY_H
