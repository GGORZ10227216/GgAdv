#include <optional>
#include <iostream>
#include <thread>
#include <memory>
#include <benchmark/benchmark.h>
#include <system_components.h>

int main() {
    Components::System emulator;
    emulator.Start(std::nullopt);
    return 0;
}
