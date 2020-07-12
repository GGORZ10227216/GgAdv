//
// Created by orzgg on 2020-06-08.
//

#ifndef TABLE_GEN_THUMB_FORMATTER_H
#define TABLE_GEN_THUMB_FORMATTER_H

#include <fmt/core.h>
#include <fmt/format.h>

#include <system_enum.h>
#include <thumb_info.h>
#include <thumb_decoder.h>
#include <instruction_access.h>
#include <instruction.h>

template <>
struct fmt::formatter<ThumbInstruction> {
private :
    void MoveShiftedRegister(uint p) ;
    void AddAndSubstract(uint p) ;
    void ImmeOperations(uint p) ;
    void ALUOperations(uint p) ;
    void HiRegAndBx(uint p) ;
    void PCBaseLoad() ;
    void LoadStoreRegOffset(uint p) ;
    void LoadStoreByteHalfWord(uint p) ;
    void LoadStoreImmOffset(uint p) ;
    void LoadStoreHalfWord(uint p) ;
    void SPBaseLoadStore(uint p) ;
    void LoadAddress(uint p) ;
    void AddOffsetToStackPtr(uint p) ;
    void PushPopReg(uint p) ;
    void MultipleLoadStore(uint p) ;
    void ConditionalBranch(uint p) ;
    void SoftwareInterrupt() ;
    void UnconditionalBranch() ;
    void LongBranchWithLink() ;

    template<typename FormatContext, uint T, uint... seq>
    auto FormatThumb(FormatContext& ctx, uint32_t binary,std::integer_sequence<uint, seq...>  ) {
        using namespace disassemble ;
        using namespace cpu_decode ;
        return fmt::format_to( ctx.out(),
                               to_string_tuple.first,
                               to_string_tuple.second,
                               GetField<disassemble::instruction_info<DecodeMode::THUMB, T>, seq>(binary)...
        ) ;
    }

    std::pair<const char*, const char*> to_string_tuple ;

public :
    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it++ != '}')
            throw format_error("invalid format");
        return it;
    }

    template <typename FormatContext>
    auto format(const ThumbInstruction& p, FormatContext& ctx) {
        using namespace disassemble;
        using namespace cpu_decode ;
        switch ( p.type ) {
            case 0 :
                MoveShiftedRegister(p) ;
                return FormatThumb<FormatContext, 1>(ctx, p, instruction_info<DecodeMode::THUMB,1>::Args);
            case 1 :
                AddAndSubstract(p) ;
                return FormatThumb<FormatContext, 2>(ctx, p, instruction_info<DecodeMode::THUMB,2>::Args);
            case 2 :
                ImmeOperations(p) ;
                return FormatThumb<FormatContext, 3>(ctx, p, instruction_info<DecodeMode::THUMB,3>::Args);
            case 3 :
                ALUOperations(p) ;
                return FormatThumb<FormatContext, 4>(ctx, p, instruction_info<DecodeMode::THUMB,4>::Args);
            case 4 :
                HiRegAndBx(p) ;
                return FormatThumb<FormatContext, 5>(ctx, p, instruction_info<DecodeMode::THUMB,5>::Args);
            case 5 :
                PCBaseLoad() ;
                return FormatThumb<FormatContext, 6>(ctx, p, instruction_info<DecodeMode::THUMB,6>::Args) ;
            case 6 :
                LoadStoreRegOffset(p) ;
                return FormatThumb<FormatContext, 7>(ctx, p, instruction_info<DecodeMode::THUMB,7>::Args);
            case 7 :
                LoadStoreByteHalfWord(p) ;
                return FormatThumb<FormatContext, 8>(ctx, p, instruction_info<DecodeMode::THUMB,8>::Args);
            case 8 :
                LoadStoreImmOffset(p);
                return FormatThumb<FormatContext, 9>(ctx, p, instruction_info<DecodeMode::THUMB,9>::Args);
            case 9 :
                LoadStoreHalfWord(p) ;
                return FormatThumb<FormatContext, 10>(ctx, p, instruction_info<DecodeMode::THUMB,10>::Args);
            case 10 :
                SPBaseLoadStore(p) ;
                return FormatThumb<FormatContext, 11>(ctx, p, instruction_info<DecodeMode::THUMB,11>::Args);
            case 11 :
                LoadAddress(p) ;
                return FormatThumb<FormatContext, 12>(ctx, p, instruction_info<DecodeMode::THUMB,12>::Args) ;
            case 12 :
                AddOffsetToStackPtr(p) ;
                return FormatThumb<FormatContext, 13>(ctx, p, instruction_info<DecodeMode::THUMB,13>::Args);
            case 13 :
                PushPopReg(p) ;
                return FormatThumb<FormatContext, 14>(ctx, p, instruction_info<DecodeMode::THUMB,14>::Args);
            case 14 :
                MultipleLoadStore(p) ;
                return FormatThumb<FormatContext, 15>(ctx, p, instruction_info<DecodeMode::THUMB,15>::Args);
            case 15 :
                ConditionalBranch(p) ;
                return FormatThumb<FormatContext, 16>(ctx, p, instruction_info<DecodeMode::THUMB,16>::Args);
            case 16 :
                SoftwareInterrupt() ;
                return FormatThumb<FormatContext, 17>(ctx, p, instruction_info<DecodeMode::THUMB,17>::Args);
            case 17 :
                UnconditionalBranch() ;
                return FormatThumb<FormatContext, 18>(ctx, p, instruction_info<DecodeMode::THUMB,18>::Args);
            case 18 :
                LongBranchWithLink() ;
                return FormatThumb<FormatContext, 19>(ctx, p.DecodeBLOffset(), instruction_info<DecodeMode::THUMB,19>::Args);
            default :
                return fmt::format_to( ctx.out(),
                                       "Unknown format! raw: {:x}, hash: {:d}",
                                       p, thumb_decoder::hash(p)
                ) ;
        } // switch
    } // format()
};

#endif //TABLE_GEN_THUMB_FORMATTER_H
