//
// Created by orzgg on 2020-06-10.
//

#ifndef TABLE_GEN_ARG_FORMATTER_H
#define TABLE_GEN_ARG_FORMATTER_H

#include <fmt/core.h>
#include <fmt/format.h>
#include <cpu_decode.h>

struct Arg {
    uint val ;
    constexpr bool operator== ( const int& i ) const {
        return i == val ;
    }

    constexpr operator uint() const {
        return val ;
    }
};

template <>
struct fmt::formatter<Arg> {
    char presentation = '\0';
    size_t shAmount = 0, regOffset = 0 ;
    bool signExtend = false, zeroToDec32 = false, skip = false ;
    bool needOffset = false ;
    size_t offset = 0, signBit = 0 ;
    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        bool isvalid = false ;

        if ( it != end ) {
            enum class STATE { NONE, REG, IMM, END } ;
            STATE state = STATE::NONE ;
            for ( auto seek = it ; seek != end ; ++seek ) {
                if ( state == STATE::NONE ) {
                    switch ( *seek ) {
                        case 'r' : case 'l' :
                            presentation = *seek ;
                            state = STATE::REG ;
                            break ;
                        case 'c' :
                            presentation = *seek ;
                            state = STATE::END ;
                            break ;
                        case 'i' :
                            presentation = 'i' ;
                            state = STATE::IMM ;
                            break ;
                        case 'x' :
                            skip = true ;
                            state = STATE::END ;
                            break ;
                        default :
                            throw format_error( "invalid format" ) ;
                    } // switch
                } // if
                else if ( state == STATE::REG ) {
                    if ( *seek == '}' ) {
                        regOffset = 0 ;
                        return seek ;
                    } // if
                    else if ( *seek == 'h' ) {
                        regOffset = 8 ;
                        state = STATE::END ;
                    } // else if
                    else
                        throw format_error( "invalid format" ) ;
                } // else if
                else if ( state == STATE::IMM ) {
                    if ( *seek == '}' ) {
                        return seek ;
                    } // if
                    else if ( *seek == '+' ) {
                        needOffset = true ;
                    } // else if
                    else if ( isdigit(*seek) ) {
                        if ( needOffset ) {
                            offset = *seek - '0' ;
                            needOffset = false ;
                        } // if
                        else if ( signExtend ) {
                            for ( int i = 0 ; *seek != '}' ; seek++ ) {
                                if ( !isdigit( *seek ) )
                                    break ;
                                else
                                    signBit = signBit * 10 + (*seek - '0')  ;
                            } // for

                            signExtend = false ;
                            return seek ;
                        } // else if
                        else
                            shAmount = *seek - '0' ;
                    } // else if
                    else if ( *seek == 'e') {
                        signExtend = true ;
                    } // else if
                    else if ( *seek == 'x' ) {
                        skip = true ;
                    } // else if
                    else if ( *seek == 'z') {
                        zeroToDec32 = true ;
                    } // else if
                    else
                        throw format_error( "invalid format" ) ;
                } // else if
                else if ( state == STATE::END ) {
                    if ( *seek != '}' )
                        throw format_error( "invalid format" ) ;
                    else {
                        it = seek ;
                        isvalid = true ;
                        break ;
                    } // else
                } // else if
            } // for
        } // if

        if ( !isvalid )
            throw format_error( "invalid format" ) ;

        return it;
    }

    template <typename FormatContext>
    auto format(const Arg& p, FormatContext& ctx) {
        if ( skip )
            return format_to(ctx.out(), "" ) ;
        else {
            if ( presentation == 'r' ) {
                return format_to(ctx.out(), "{}", cpu_decode::register_name[ p + regOffset ] ) ;
            } // if
            else if (presentation == 'i') {
                if ( signBit != 0 ) {
                    uint32_t p32 = p << shAmount ;
                    signBit += shAmount ;
                    if ( p32 & bit_mask::_BV( signBit ) )
                        p32 |= (0xffffffff >> (signBit + 1)) << (signBit + 1) ;
                    p32 += offset ; // pipeline preload
                    const char* formatString = ( p32 >= 0 && p32 < 10 ) ? "{:d}" : "{:#x}" ;
                    return format_to(ctx.out(), formatString, p32);
                } // if
                else if ( zeroToDec32 && p == 0 )
                    return format_to(ctx.out(), "{:#x}", 0x20);
                else {
                    unsigned int pShifted = (p << shAmount) + offset ;
                    const char* formatString = ( pShifted >= 0 && pShifted < 10 ) ? "{:d}" : "{:#x}" ;
                    return format_to(ctx.out(), formatString, pShifted );
                } // else
            } // else
            else if (presentation == 'l') {
                std::vector<std::string> regs ;
                for (size_t i = 0 ; i < 8 ; ++i) {
                    if ( p & bit_mask::_BV( i ) )
                        regs.push_back( cpu_decode::register_name[ i ] ) ;
                } // for

                return format_to(ctx.out(), "{}", fmt::join( regs, ", " ) ) ;
            } // else if
            else if ( presentation == 'c' ) {
                return format_to(ctx.out(), "{}", cpu_decode::condition_name[ p ] ) ;
            } // else if
            else
                return format_to(ctx.out(), "{}", p ) ;
        } // else
    } // format()
};

#endif //TABLE_GEN_ARG_FORMATTER_H
