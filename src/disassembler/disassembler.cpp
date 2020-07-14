//
// Created by orzgg on 2020-07-01.
//

#include <system_components.h>
#include <disassembler.h>
#include <system_enum.h>
#include <cpu.h>

std::string Components::Disassembler::Disassemble(unsigned binary) {
    if ( EMU_CPU.CurrentDecodeMode() == ModeEnum::ARM )
        return fmt::format( "{}", ArmInstruction{ binary } ) ;
    else
        return fmt::format( "{}", ThumbInstruction{ binary } ) ;
    return std::string() ;
}

Components::Disassembler::Disassembler(Components::System* parentPtr) :
    Component_t(parentPtr)
{

}
