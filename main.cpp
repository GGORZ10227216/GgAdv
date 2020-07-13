#include <optional>
#include <iostream>
#include <thread>
#include <system_components.h>

int main( ) {
    std::thread emuWorker(
        []() {
            auto emulator = std::make_shared<Components::System>() ;
            emulator->Start(std::nullopt) ;
        }
    ) ;

    emuWorker.join() ;
    return 0;
}
