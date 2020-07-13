//
// Created by orzgg on 2020-07-01.
//

#include <disassembler.h>
#include <system_components.h>
#include <cpu.h>
#include <system_enum.h>

std::string Components::Disassembler::Disassemble(unsigned binary) {
    if ( emuInstance->cpu->CurrentDecodeMode() == ModeEnum::ARM )
        return fmt::format( "{}", ArmInstruction{ binary } ) ;
    else
        return fmt::format( "{}", ThumbInstruction{ binary } ) ;
    return std::string() ;
}
