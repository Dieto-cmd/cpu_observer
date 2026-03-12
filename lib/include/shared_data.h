#pragma once 
#include <vector>
#include <mutex>
#include<map>
#include<string>

struct SharedData {
    std::map<std::string, std::vector<unsigned long long>> labeledJiffies; 
    std::vector<double> percent = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //default values
    std::mutex mtx;
};