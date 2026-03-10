#pragma once
#include<vector>
#include<mutex>
#include "shared_data.h"



void cpuReaderThread(SharedData& data);
std::vector<unsigned long long> parseCpuData(std::istream& input_stream);