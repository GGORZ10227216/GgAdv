#include <disassemble/formatter/thumb_formatter.h>

using namespace disassemble;
using namespace cpu_decode ;
using namespace std::literals;

void fmt::formatter<ThumbInstruction>::MoveShiftedRegister(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,1> ;
    size_t midx = 0, fidx = 0;
    unsigned int offset = GetField<instruction_info<DecodeMode::THUMB,1>, static_cast<uint>(f::Field::Offset5)>(p) ;
    unsigned int op = GetField<instruction_info<DecodeMode::THUMB,1>, static_cast<uint>(f::Field::Op)>(p) ;

    if ( op == 0 ) {
        if ( offset == 0 ) {
            fidx = f::F_MOV ;
            midx = f::MOV ;
        } // if
        else {
            fidx = f::F_SHIFT ;
            midx = f::LSL ;
        } // else
    } // if
    else {
        fidx = f::F_SHIFT ;
        midx = op ;
    } // else

    to_string_tuple = std::make_pair( f::formats[ fidx ], f::mnemonics[ midx ] ) ;
}

void fmt::formatter<ThumbInstruction>::AddAndSubstract(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,2> ;
    auto formatString = f::formats[ GetField<instruction_info<DecodeMode::THUMB,2>, static_cast<uint>(f::Field::I)>(p) ];
    auto mnemonic = f::mnemonics[ GetField<instruction_info<DecodeMode::THUMB,2>, static_cast<uint>(f::Field::Op)>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::ImmeOperations(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,3> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    auto mnemonic = f::mnemonics[ GetField<instruction_info<DecodeMode::THUMB,3>, static_cast<uint>(f::Field::Op)>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::ALUOperations(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,4> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    auto mnemonic = f::mnemonics[ GetField<f, static_cast<uint>(f::Field::Op)>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::HiRegAndBx(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,5> ;
    size_t fidx = 0, midx = 0 ;
    if ( GetField<f, static_cast<uint>(f::Field::Op)>(p) == 0b11 )
        fidx = GetField<f, static_cast<uint>(f::Field::H2)>(p) + 3 ;
    else
        fidx = ( (GetField<f, static_cast<uint>(f::Field::H1)>(p) << 1) |
                GetField<f, static_cast<uint>(f::Field::H2)>(p) ) - 1;

    midx = GetField<f, static_cast<uint>(f::Field::Op)>(p) ;
    auto formatString = f::formats[ fidx ] ;
    auto mnemonic = f::mnemonics[ midx ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::PCBaseLoad() {
    using f = instruction_info<DecodeMode::THUMB,6> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    constexpr auto mnemonic = f::mnemonics[ 0 ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::LoadStoreRegOffset(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,7> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    auto mnemonic = f::mnemonics[ (Get<f, f::Field::L>(p) << 1) | Get<f, f::Field::B>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::LoadStoreByteHalfWord(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,8> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    auto mnemonic = f::mnemonics[ (Get<f, f::Field::S>(p) << 1) | Get<f, f::Field::H>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::LoadStoreImmOffset(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,9> ;
    unsigned int fidx ;
    auto mnemonic = f::mnemonics[ (Get<f, f::Field::B>(p) << 1) | Get<f, f::Field::L>(p) ] ;

    if ( Get<f, f::Field::Offset5>( p ) == 0 )
        fidx = 0 ;
    else
        fidx = Get<f, f::Field::B>( p ) + 1 ;

    to_string_tuple = std::make_pair( f::formats[ fidx ],mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::LoadStoreHalfWord(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,10> ;
    auto formatString = f::formats[ (Get<f, f::Field::Offset5>( p ) != 0) ] ;
    auto mnemonic = f::mnemonics[ Get<f, f::Field::L>(p)] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::SPBaseLoadStore(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,11> ;
    auto formatString = f::formats[ (Get<f, f::Field::Word8>( p ) != 0) ] ;
    int dbg = Get<f, f::Field::L>(p) ;
    auto mnemonic = f::mnemonics[ Get<f, f::Field::L>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::LoadAddress(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,12> ;
    auto formatString = f::formats[ Get<f, f::Field::SP>(p) ] ;
    auto mnemonic = f::mnemonics[ Get<f, f::Field::SP>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::AddOffsetToStackPtr(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,13> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    auto mnemonic = f::mnemonics[ Get<f, f::Field::S>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::PushPopReg(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,14> ;
    size_t fidx, midx ;
    switch ( (Get<f, f::Field::L>(p) << 1) | Get<f, f::Field::R>(p) ) {
        case 0b00 :
            fidx = 0 ;
            midx = 0 ;
            break ;
        case 0b01 :
            fidx = 1 ;
            midx = 0 ;
            break ;
        case 0b10 :
            fidx = 0 ;
            midx = 1 ;
            break ;
        case 0b11 :
            fidx = 2 ;
            midx = 1 ;
            break ;
    } // switch

    to_string_tuple = std::make_pair( f::formats[ fidx ] , f::mnemonics[ midx ] ) ;
}

void fmt::formatter<ThumbInstruction>::MultipleLoadStore(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,15> ;
    auto formatString = f::formats[ 0 ] ;
    auto mnemonic = f::mnemonics[ Get<f, f::Field::L>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::ConditionalBranch(const uint p) {
    using f = instruction_info<DecodeMode::THUMB,16> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    auto mnemonic = f::mnemonics[ Get<f, f::Field::Cond>(p) ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::SoftwareInterrupt() {
    using f = instruction_info<DecodeMode::THUMB,17> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    constexpr auto mnemonic = f::mnemonics[ 0 ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::UnconditionalBranch() {
    using f = instruction_info<DecodeMode::THUMB,18> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    constexpr auto mnemonic = f::mnemonics[ 0 ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

void fmt::formatter<ThumbInstruction>::LongBranchWithLink() {
    using f = instruction_info<DecodeMode::THUMB,19> ;
    constexpr auto formatString = f::formats[ 0 ] ;
    constexpr auto mnemonic = f::mnemonics[ 0 ] ;
    to_string_tuple = std::make_pair(formatString,mnemonic) ;
}

