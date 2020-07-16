//
// Created by orzgg on 2020-07-01.
//

#include <system_components.h>
#include <disassembler.h>
#include <system_enum.h>
#include <cpu.h>

std::string Components::Disassembler::Disassemble(unsigned binary) {
    if ( EMU_CPU.CurrentDecodeMode() == ModeEnum::ARM ) {
        count = cs_disasm(armHandle, reinterpret_cast<uint8_t*>(&binary), 4, emuInstance.cpu.R15(), 0, &insn);
        auto result = fmt::format( "{} {}", insn[0].mnemonic, insn[0].op_str ) ;
        cs_free(insn, count) ;
        return result ;
    } // if
    else {
        count = cs_disasm(thumbHandle, reinterpret_cast<uint8_t*>(&binary), 2, emuInstance.cpu.R15(), 0, &insn);
        auto result = fmt::format( "{} {}", insn[0].mnemonic, insn[0].op_str ) ;
        cs_free(insn, count) ;
        return result ;
    } // else

    return std::string() ;
}

Components::Disassembler::Disassembler(Components::System* parentPtr) :
    Component_t(parentPtr)
{
    if (cs_open(CS_ARCH_ARM, CS_MODE_ARM, &armHandle) != CS_ERR_OK)
        exit(-1);
    if (cs_open(CS_ARCH_ARM, CS_MODE_THUMB, &thumbHandle) != CS_ERR_OK)
        exit(-1);
}
