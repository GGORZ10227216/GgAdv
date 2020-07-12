//
// Created by orzgg on 2020-06-27.
//

#include <tuple>
#include <array>

#ifndef CPU_ARRAY_TOOL_H
#define CPU_ARRAY_TOOL_H

namespace Utility {
    template <typename... Ts>
    constexpr auto MakeArray( Ts... args ) {
        auto tmp = std::get<0>(std::make_tuple( args... )) ;
        return std::array<decltype(tmp), sizeof...(args)> { args... } ;
    } // MakeArray()
}

#endif //CPU_ARRAY_TOOL_H
