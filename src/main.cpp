#include <iostream>
#include <thread>
#include "cpu_reader.h"
#include "cpu_load_calculator.h"
#include "ui_manager.h"

int main() {
    SharedData sharedData;
    std::thread cpuReader(cpuReaderThread, std::ref(sharedData));
    std::thread cpuCalculator(cpuLoadCalculatorThread, std::ref(sharedData));
    std::thread uiManager(uiManagerThread, std::ref(sharedData));


    cpuReader.join();
    cpuCalculator.join();
    uiManager.join();
}