#pragma once 
#include <vector>
#include <mutex>

struct SharedData {
    std::vector<int> jiffies; 
    std::mutex mtx;            
};