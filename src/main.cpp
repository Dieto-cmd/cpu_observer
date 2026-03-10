#include <iostream>
#include <thread>
#include "cpu_reader.h"

int main() {
    SharedData sharedData;
    std::thread cpuReader(cpuReaderThread, std::ref(sharedData));

    cpuReader.join();
}