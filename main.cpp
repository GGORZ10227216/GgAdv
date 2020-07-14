#include <optional>
#include <iostream>
#include <thread>
#include <memory>
#include <benchmark/benchmark.h>
#include <system_components.h>

void BenchmarkEmulator(benchmark::State& state) {
    Components::System emulator;
    for (auto _ : state) {
        emulator.BenchmarkStart(std::nullopt) ;
    } // for
}

BENCHMARK(BenchmarkEmulator) ;
BENCHMARK_MAIN() ;

//int main() {
//    Components::System emulator;
//    emulator.Start(std::nullopt);
//    return 0;
//}
