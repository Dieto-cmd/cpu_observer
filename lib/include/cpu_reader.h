#pragma once
#include<vector>
#include<mutex>
#include "shared_data.h"
#include <istream>



void cpuReaderThread(SharedData& data);

std::map<std::string, std::vector<unsigned long long>> parseCpuData(std::istream& input_stream);