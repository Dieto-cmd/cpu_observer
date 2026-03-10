#include <iostream>
#include <thread>
#include "cpu_reader.h"
#include "cpu_load_calculator.h"

int main() {
    SharedData sharedData;
    std::thread cpuReader(cpuReaderThread, std::ref(sharedData));
    std::thread cpuCalculator(cpuLoadCalculatorThread, std::ref(sharedData));


    cpuReader.join();
    cpuCalculator.join();
}