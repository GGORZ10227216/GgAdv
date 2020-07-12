//
// Created by orzgg on 2020-07-01.
//

#include <disassembler.h>
#include <system_components.h>
#include <system_enum.h>

std::string Disassembler::Disassemble(unsigned binary) {
    if ( EMU_CPU.CurrentDecodeMode() == ModeEnum::ARM )
        return fmt::format( "{}", ArmInstruction{ binary } ) ;
    else
        return fmt::format( "{}", ThumbInstruction{ binary } ) ;
}
