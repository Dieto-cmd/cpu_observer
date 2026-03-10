#pragma once
#include <vector>
#include <shared_data.h>

double calculateCpuLoad(int idleTime, int totalTime);
void cpuLoadCalculatorThread(SharedData& data);