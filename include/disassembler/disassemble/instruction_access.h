//
// Created by orzgg on 2020-06-07.
//

#ifndef TABLE_GEN_INSTRUCTION_ACCESS_H
#define TABLE_GEN_INSTRUCTION_ACCESS_H

#include <disassemble/formatter/arg_formatter.h>
#include <instruction.h>

namespace disassemble {
    template<typename T, uint M>
    constexpr Arg GetField( const uint insn ) {
        constexpr auto& maskPair = T::mask[ M ] ;
        return Arg{ (insn & maskPair.first) >> maskPair.second } ;
    }

    template<typename T, typename T::Field U>
    constexpr Arg Get( const uint insn ) {
        return GetField<T, static_cast<uint>(U)>(insn) ;
    }
} // disassemble

#endif //TABLE_GEN_INSTRUCTION_ACCESS_H
