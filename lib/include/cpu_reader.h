#pragma once
#include<vector>
#include<mutex>
struct SharedData {
    std::vector<long> jiffies; 
    std::mutex mtx;            
};

void cpuReaderThread(SharedData& data);