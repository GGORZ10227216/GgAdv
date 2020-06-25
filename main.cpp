#include <iostream>
#include <system_components.h>

Components::System Components::emulator ;

int main() {
    using namespace Components ;
    std::cout << emulator.cpu.ToString() << std::endl;
    return 0;
}
