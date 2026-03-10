#pragma once 
#include <vector>
#include <mutex>

struct SharedData {
    std::vector<unsigned long long> jiffies; 
    double percent = -1;
    std::mutex mtx;
};