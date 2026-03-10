#pragma once
#include<vector>
#include<mutex>


struct SharedData {
    std::vector<int> jiffies; 
    std::mutex mtx;            
};

void cpuReaderThread(SharedData& data);
std::vector<int> parseCpuData(std::istream& input_stream);