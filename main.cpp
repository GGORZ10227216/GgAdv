#include <optional>
#include <iostream>
#include <system_components.h>

Components::System Components::emulator ;

int main( ) {
    using namespace Components ;
    Components::emulator.Start(std::nullopt) ;
    return 0;
}
