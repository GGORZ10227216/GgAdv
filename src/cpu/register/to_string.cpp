//
// Created by orzgg on 2020-06-25.
//

#include <register.h>
#include <utility>
#include <exception>

using namespace ModeEnum;
using namespace ErrorEnum;
using namespace CPU_Enum;
using namespace CPUString;

std::string Components::Registers::ToString() {
    return fmt::format(
            CPUString::UserSysRegFormat_Arm,
            contents[0], contents[1], contents[2],
            contents[3],
            contents[4], contents[5], contents[6],
            contents[7],
            contents[8], contents[9], contents[10],
            contents[11],
            contents[12], contents[13], contents[14],
            contents[15]
    );
}
