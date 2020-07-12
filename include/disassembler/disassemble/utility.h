//
// Created by orzgg on 2020-06-13.
//

#ifndef TABLE_GEN_UTILITY_H
#define TABLE_GEN_UTILITY_H

#include <tuple>
#include <initializer_list>
#include <bit_mask.h>

namespace disassemble {
    enum { sig, sig_sh, op, op_sh } ;

    template<size_t T>
    using Op_value_t = std::array<unsigned int, T> ;
    using Op_Shift_t = unsigned int ;
    using Sig_value_t = unsigned int ;
    using Sig_Shift_t = unsigned int ;

    template<unsigned int... Ts>
    constexpr auto MakeOp(std::integer_sequence<unsigned int, Ts...>) {
        return std::array<unsigned int, sizeof...(Ts)> { Ts... } ;
    }

    template<unsigned int SIGNATURE, unsigned int SIG_SHIFT, unsigned int SIG_END, unsigned int OP_SHIFT>
    constexpr auto MakeSignature() {
        constexpr auto Ops = MakeOp( std::make_integer_sequence<unsigned int, SIG_END>{} );
        return std::make_tuple( SIGNATURE, SIG_SHIFT, Ops, OP_SHIFT ) ;
    }

    template<unsigned int SIGNATURE, unsigned int SIG_SHIFT, unsigned int OP_SHIFT, typename... OPs>
    constexpr auto MakeSignature(OPs... ops) {
        return std::make_tuple( SIGNATURE, SIG_SHIFT, Op_value_t<sizeof...(ops)>{ static_cast<unsigned>(ops)... }, OP_SHIFT ) ;
    }

    template<unsigned int SIGNATURE, unsigned int SIG_SHIFT>
    constexpr auto MakeSignature() {
        return std::make_tuple( SIGNATURE, SIG_SHIFT, Op_value_t<1>{ 0 }, 0 ) ;
    }

    template <typename... Ts>
    constexpr auto MakeArray( Ts... args ) {
        auto tmp = std::get<0>(std::make_tuple( args... )) ;
        return std::array<decltype(tmp), sizeof...(args)> { args... } ;
    }

    template<unsigned int... start, unsigned int... width>
    constexpr auto InitInsnType(std::integer_sequence<unsigned int, width...>, std::integer_sequence<unsigned int, start...> ) {
        std::array<std::pair<int,int>, sizeof...(start)> result = {
                std::make_pair( bit_mask::MASK32( width, start ), start )...
        }  ;
        return result ;
    }

    template<unsigned int... start, unsigned int... width>
    constexpr auto GenerateAccessHandler(std::integer_sequence<unsigned int, width...>, std::integer_sequence<unsigned int, start...> ) {
        using returnType = unsigned(*)(unsigned) ;
        constexpr std::array<returnType, sizeof...(start)> result = {
                [](unsigned insn) {
                    using namespace bit_mask ;
                    return (insn & MASK32( width, start ) ) >> start ;
                }...
        } ;

        return result ;
    }

    template<unsigned int... start, unsigned int... width>
    constexpr auto GenerateAccessHandlerList(std::integer_sequence<unsigned int, width...>, std::integer_sequence<unsigned int, start...> ) {
        using returnType = unsigned(*)(unsigned) ;
        constexpr std::initializer_list<returnType> result = {
                [](unsigned insn) {
                    using namespace bit_mask ;
                    return (insn & MASK32( width, start ) ) >> start ;
                }...
        } ;

        return result ;
    }

    template<typename T>
    unsigned int Signature() {
        return std::get<sig>( T::signature ) << std::get<sig_sh>( T::signature ) ;
    }

    template<typename T>
    unsigned int Opcode( const size_t idx ) {
        return std::get<op>( T::signature )[ idx ] << std::get<op_sh>( T::signature ) ;
    }
}

#endif //TABLE_GEN_UTILITY_H
