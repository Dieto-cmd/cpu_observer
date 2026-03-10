#pragma once
#include <vector>
#include <shared_data.h>

double calculateCpuLoad(unsigned long long idleTime, unsigned long long totalTime);
void cpuLoadCalculatorThread(SharedData& data);