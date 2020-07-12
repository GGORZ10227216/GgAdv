//
// Created by orzgg on 2020-06-18.
//

#ifndef TABLE_GEN_ARM_FORMATTER_H
#define TABLE_GEN_ARM_FORMATTER_H

#include <tuple>

#include <fmt/core.h>
#include <fmt/format.h>

#include <cpu_decode.h>
#include <disassemble/decoder/arm/arm_decoder.h>
#include <disassemble/information/arm_info.h>
#include <disassemble/decoder/arm/arm_handler.h>

template <>
struct fmt::formatter<ArmInstruction> {
    uint typecode ;
    std::pair<const char*, const char*> to_string_tuple ;

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it++ != '}')
            throw format_error("invalid format");
        return it;
    }

    template <typename FormatContext>
    auto format(const ArmInstruction& p, FormatContext& ctx) {
        using namespace disassemble;
        using namespace cpu_decode ;

        typecode = arm_decoder::Type(p);
        return fmt::format_to( ctx.out(), "{}", handlerTable[ typecode ]( p ) ) ;
    } // format()
} ;
#endif //TABLE_GEN_ARM_FORMATTER_H
