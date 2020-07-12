//
// Created by orzgg on 2020-05-23.
//

#include <system_components.h>
#include <system_enum.h>
#include <cpu_decode.h>
#include <disassemble/decoder/arm/arm_handler.h>
#include <arm_info.h>
#include <instruction.h>

#include <sstream>

using namespace bit_mask ;
using namespace disassemble ;

void ProcessPSRTransfer( const ArmInstruction& self, std::stringstream& ss ) {
    using info = instruction_info<DecodeMode::ARM, 0> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };

    if ( GetBit( Get( info::op ), 0 ) ) {
        ss << "msr" << cpu_decode::condition_name[ Get( info::condition ) ] << " " ;
        if ( GetBit( Get( info::op ), 1 ) ) {
            ss << "spsr, " ; // %s for mode name
        } // if
        else {
            ss << "cpsr, " ;
        } // else

        ss << cpu_decode::register_name[ Get( info::Rm ) ] ;
    } // if
    else {
        ss << "mrs " << cpu_decode::register_name[ Get( info::Rd ) ] << ", " ;
        if ( GetBit( Get( info::op ), 1 ) ) {
            ss << "spsr" ; // %s for mode name
        } // if
        else {
            ss << "cpsr" ;
        } // else
    } // else
}

template<typename T>
void DecodeOperand2(const ArmInstruction& self, std::stringstream& ss) {
    auto Get = [&] (unsigned idx) { return T::access[idx](self) ; };
    
    if ( Get( T::I ) )
        ss << "#" << cpu_decode::HexStr( bit_mask::rotr( Get( T::imm ), Get( T::rotate ) * 2 ) ) ;
    else {
        if ( Get( T::RsMark ) ) {
            ss  << cpu_decode::register_name[ Get( T::Rm ) ] << ", " << cpu_decode::shift_type_name[ Get( T::shType ) ]
                << " " << cpu_decode::register_name[ Get( T::Rs ) ] ;
        } // if
        else {
            ss  << cpu_decode::register_name[ Get( T::Rm ) ] ;
            if ( Get( T::shAmount ) != 0 )
                ss << ", " << cpu_decode::shift_type_name[ Get( T::shType ) ]
                   << " #" << Get( T::shAmount ) ;
            else if ( Get( T::shType ) != cpu_decode::LSL ) {
                if ( Get( T::shType ) == cpu_decode::ROR )
                    ss << ", rrx" ;
                else
                    ss << ", " << cpu_decode::shift_type_name[ Get( T::shType ) ] << " #32" ;
            } // else if
        } // else
    } // else
}

std::string disassemble::DP_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 0> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };

    std::stringstream ss ;
    switch ( Get( info::op ) ) {
        case cpu_decode::DP_OPCODE::Mov :
            if ( !Get( info::I ) && ( Get( info::RsMark ) || ( Get( info::shType ) != cpu_decode::LSL || Get( info::shAmount ) != 0 ) ) ) {
                ss << cpu_decode::shift_type_name[ Get( info::shType ) ]
                   << ( Get( info::S ) ? "s" : "" ) << " "
                   << cpu_decode::register_name[ Get( info::Rd ) ] << ", "
                   << cpu_decode::register_name[ Get( info::Rm ) ] << ", "  ;

                if ( Get( info::RsMark ) ) {
                    ss << cpu_decode::register_name[ Get( info::Rs ) ] ;
                } // if
                else {
                    if ( Get( info::shType ) != cpu_decode::LSL && Get( info::shAmount ) == 0 ) {
                        if ( Get( info::shType ) == cpu_decode::ROR ) {
                            ss.str( "" ) ;
                            ss << "rrx" << ( Get( info::S ) ? "s" : "" ) << " "
                               << cpu_decode::register_name[ Get( info::Rd ) ] << ", "
                               << cpu_decode::register_name[ Get( info::Rm ) ] ;
                        } // if
                        else
                            ss << "#32" ;
                    } // if

                    else
                        ss << "#" << cpu_decode::HexStr( Get( info::shAmount ) ) ; // Get( info::shAmount ) is no need to hex
                } // else

                return ss.str() ;
            } // if
            else {
                ss << cpu_decode::data_processing_opcode[ Get( info::op ) ]
                   << ( Get( info::S ) ? "s" : "" )
                   << cpu_decode::condition_name[ Get( info::condition ) ] << " "
                   << cpu_decode::register_name[ Get( info::Rd ) ] << ", " ;
            } // else
            break ;
        case cpu_decode::DP_OPCODE::Mvn :
            ss << cpu_decode::data_processing_opcode[ Get( info::op ) ]
               << ( Get( info::S ) ? "s" : "" )
               << cpu_decode::condition_name[ Get( info::condition ) ] << " "
               << cpu_decode::register_name[ Get( info::Rd ) ] << ", " ;
            break ;
        case cpu_decode::DP_OPCODE::Cmp : case cpu_decode::DP_OPCODE::Cmn : case cpu_decode::DP_OPCODE::Teq : case cpu_decode::DP_OPCODE::Tst :
            if ( !Get( info::S ) ) {
                ProcessPSRTransfer( self, ss ) ;
                return ss.str() ;
            } // if
            else {
                ss << cpu_decode::data_processing_opcode[ Get( info::op ) ]
                   << cpu_decode::condition_name[ Get( info::condition ) ] << " "
                   << cpu_decode::register_name[ Get( info::Rn ) ] << ", " ;
            } // else
            break ;
        default :
            ss << cpu_decode::data_processing_opcode[ Get( info::op ) ]
               << ( Get( info::S ) ? "s" : "" )
               << cpu_decode::condition_name[ Get( info::condition ) ] << " "
               << cpu_decode::register_name[ Get( info::Rd ) ] << ", "
               << cpu_decode::register_name[ Get( info::Rn ) ] << ", " ;
    } // switch

    DecodeOperand2<instruction_info<DecodeMode::ARM,0>>( self, ss ) ;
    return ss.str() ;
}

std::string disassemble::MUL_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 1> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };
    
    std::stringstream ss ;
    ss << ( Get( info::A ) ? "mla" : "mul" )
       << ( Get( info::S ) ? "s" : "" )
       << cpu_decode::condition_name[ Get( info::condition ) ] << " "
       << cpu_decode::register_name[ Get( info::Rd ) ] << ", "
       << cpu_decode::register_name[ Get( info::Rm ) ] << ", "
       << cpu_decode::register_name[ Get( info::Rs ) ] ;

    if ( Get( info::A ) )
        ss << ", " << cpu_decode::register_name[ Get( info::Rn ) ] ;

    return ss.str() ;
}

std::string disassemble::MULL_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 2> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };
    std::stringstream ss ;
    ss << (Get( info::U ) ? "s" : "u")
       << (Get( info::A ) ? "mlal" : "mull")
       << (Get( info::S ) ? "s" : "")
       << cpu_decode::condition_name[ Get( info::condition ) ] << " "
       << cpu_decode::register_name[ Get( info::RdLo ) ] << ", "
       << cpu_decode::register_name[ Get( info::RdHi ) ] << ", "
       << cpu_decode::register_name[ Get( info::Rm ) ] << ", "
       << cpu_decode::register_name[ Get( info::Rs ) ] ;

    return ss.str() ;
}

std::string disassemble::SWP_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 3> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };

    std::stringstream ss ;
    ss << "swp" << ( Get( info::B ) ? "b" : "" )
       << cpu_decode::condition_name[ Get( info::condition ) ] << " "
       << cpu_decode::register_name[ Get( info::Rd ) ] << ", "
       << cpu_decode::register_name[ Get( info::Rm ) ] << ", "
       << "[" << cpu_decode::register_name[ Get( info::Rn ) ] << "]" ;
    return ss.str() ;
}

std::string disassemble::BX_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 4> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };

    std::stringstream ss ;
    ss << "bx" << cpu_decode::condition_name[ Get( info::condition ) ] << " "
       << cpu_decode::register_name[ Get( info::Rn ) ] ;

    return ss.str() ;
}

std::string disassemble::HDT_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 5> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };
    
    std::stringstream ss ;
    ss << ( Get( info::L ) ? "ldr" : "str" ) ;

    const int shFlags = ( Get( info::S ) << 1 ) | Get( info::H ) ;
    switch ( shFlags ) {
        case 0b00 :
            // SWP instruction, should not be here.
            break;
        case 0b01 :
            ss << "h" ;
            break ;
        case 0b10 :
            ss << "sb" ;
            break ;
        case 0b11 :
            ss << "sh" ;
            break ;
    } // switch

    ss << cpu_decode::condition_name[ Get( info::condition ) ] << " " << cpu_decode::register_name[ Get( info::Rd ) ] << ", " ;
    if ( Get( info::P ) ) {
        // pre indexing
        ss << "[" << cpu_decode::register_name[ Get( info::Rn ) ] ;
        if ( Get( info::I ) ) {
            if ( Get( info::offset ) != 0 || Get( info::W ) || !Get( info::U ) ) {
                ss << ", #" << ( Get( info::U ) ? "" : "-" )
                   << cpu_decode::HexStr( Get( info::offset ) ) << "]" ;
            } // if
            else
                ss << "]" ;
        } // if
        else {
            ss << ", " << ( Get( info::U ) ? "" : "-" )
               << cpu_decode::register_name[ Get( info::Rm ) ] << "]" ;
        } // else

        ss << ( Get( info::W ) ? "!" : "" ) ;
    } // if
    else {
        // post indexing
        ss << "[" << cpu_decode::register_name[ Get( info::Rn ) ] ;
        if ( Get( info::I ) ) {
            ss << "], #" << ( Get( info::U ) ? "" : "-" )
               << cpu_decode::HexStr( Get( info::offset ) ) ;
        } // if
        else {
            ss << "], " << ( Get( info::U ) ? "" : "-" )
               << cpu_decode::register_name[ Get( info::Rm ) ] ;
        } // else
    } // else

    return ss.str() ;
}

std::string disassemble::DT_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 6> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };

    std::stringstream ss ;
    ss << ( Get( info::L ) ? "ldr" : "str" )
       << ( Get( info::B ) ? "b" : "" )
       << ( Get( info::W ) && !Get( info::P ) ? "t" : "" )
       << cpu_decode::condition_name[ Get( info::condition ) ] << " "
       << cpu_decode::register_name[ Get( info::Rd ) ] << ", " ;

    ss << "[" << cpu_decode::register_name[ Get( info::Rn ) ] ;
    if ( Get( info::P ) ) {
        // pre indexing
        if ( Get( info::I ) ) {
            ss << ", " << ( Get( info::U ) ? "" : "-" )
               << cpu_decode::register_name[ Get( info::Rm ) ] ;
            if ( Get( info::shAmount ) == 0 )
                ss << "]" ;
            else {
                ss << ", " << cpu_decode::shift_type_name[ Get( info::shType ) ]
                   << " #" << Get( info::shAmount ) << "]" ;
            } // else
        } // if
        else {
            if ( Get( info::imm ) != 0 || Get( info::W ) || !Get( info::U ) )
                ss << ", #" << ( Get( info::U ) ? "" : "-" ) << cpu_decode::HexStr( Get( info::imm ) ) << "]" ;
            else
                ss << "]" ;
        } // else

        ss << ( Get( info::W ) ? "!" : "" ) ;
    } // if
    else {
        // post indexing
        ss << "]" ;
        if ( Get( info::I ) ) {
            ss << ", " << ( Get( info::U ) ? "" : "-" )
               << cpu_decode::register_name[ Get( info::Rm ) ] ;
            if ( Get( info::shAmount ) != 0 )
                ss << ", " << cpu_decode::shift_type_name[ Get( info::shType ) ]
                   << " #" << Get( info::shAmount ) ;
        } // if
        else {
            if ( Get( info::imm ) == 4 &&
            !Get( info::B ) && Get( info::U ) && Get( info::L ) && (!Get( info::W ) || Get( info::P )) && Get( info::Rn ) == cpu_decode::sp ) {
                ss.str( "" ) ;
                ss << "pop {" << cpu_decode::register_name[ Get( info::Rd ) ] << "}" ;
            } // if
            else
                ss << ", #" << ( Get( info::U ) ? "" : "-" ) << cpu_decode::HexStr( Get( info::imm ) ) ;
        } // else
    } // else

    return ss.str() ;
}

std::string disassemble::UDF_ToString(const ArmInstruction& self) {
    return "Unknown instruction, IGNORED!";
}

std::string disassemble::MDT_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 8> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };
    
    std::stringstream ss ;
    int LPU_value = (Get( info::L ) << 2) | (Get( info::P ) << 1) | Get( info::U ) ;
    bool isPushPop = false ;
    switch ( LPU_value ) {
        case 0b000 :
            ss << "stmda" ;
            break ;
        case 0b010 :
            isPushPop = Get( info::Rn ) == 13 && Get( info::W ) ;
            ss << ( isPushPop ? "push" : "stmdb" ) ;
            break ;
        case 0b001 :
            ss << "stm" ;
            break ;
        case 0b011 :
            ss << "stmib" ;
            break ;
        case 0b100 :
            ss << "ldmda" ;
            break ;
        case 0b110 :
            ss << "ldmdb" ;
            break ;
        case 0b101 :
            isPushPop = Get( info::Rn ) == 13 && Get( info::W ) ;
            ss << ( isPushPop ? "pop" : "ldm" ) ;
            break ;
        case 0b111 :
            ss << "ldmib" ;
            break ;
    } // switch()

    if ( !isPushPop )
        ss << cpu_decode::condition_name[ Get( info::condition ) ] << " " << cpu_decode::register_name[ Get( info::Rn ) ] << ( Get( info::W ) ? "!" : "" ) << ", {" ;
    else
        ss << cpu_decode::condition_name[ Get( info::condition ) ] << " {" ;

    for ( int i = 0, j = 0 ; i < 16 ; ++i ) {
        if ( Get( info::rList ) & _BV( i ) ) {
            if ( j++ != 0 )
                ss << ", " ;
            ss << cpu_decode::register_name[ i ] ;
        } // if
    } // for

    ss << "}" << ( Get( info::S ) ? " ^" : "" ) ;
    return ss.str() ;
}

std::string disassemble::B_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 9> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };

    std::stringstream ss ;

    int32_t realAddr = Get( info::offset ) << 2 ;
    if ( GetBit(realAddr, 25) )
        realAddr |= 0xfc000000 ;

    realAddr += 8 ;
    ss << "b" << ( Get( info::L ) ? "l" : "" )
       << cpu_decode::condition_name[ Get( info::condition ) ] << " #"
       << cpu_decode::HexStr( realAddr + EMU_CPU.ReadReg( RegName::pc ) ) ;

    return ss.str() ;
}

std::string disassemble::CDT_ToString(const ArmInstruction& self) {
    return "Co-processor data transfer, IGNORED!" ;
}

std::string disassemble::CDP_ToString(const ArmInstruction& self) {
    return "Co-processor data processing, IGNORED!";
}

std::string disassemble::CRT_ToString(const ArmInstruction& self) {
    return "Co-processor register transfer, IGNORED!";
}

std::string disassemble::SWI_ToString(const ArmInstruction& self) {
    using info = instruction_info<DecodeMode::ARM, 13> ;
    auto Get = [&] (unsigned idx) { return info::access[idx](self) ; };

    std::stringstream ss ;
    ss << "svp" << cpu_decode::condition_name[ Get( info::condition ) ]
       << " #" << cpu_decode::HexStr( Get( info::interruptNumber ) ) ;
    return ss.str() ;
}