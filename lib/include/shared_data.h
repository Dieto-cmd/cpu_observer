#pragma once 
#include <vector>
#include <mutex>

struct SharedData {
    std::vector<int> jiffies; 
    double percent = -1;
    std::mutex mtx;
};