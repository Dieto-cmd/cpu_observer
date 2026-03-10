#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<mutex>
#include "cpu_reader.h"
#include<thread>


std::vector<unsigned long long> parseCpuData(std::istream& input_stream) {
    std::string line;
    std::vector<unsigned long long> jiffies;

    if(getline(input_stream, line)){
        std::istringstream iss(line);
        std::string cpuLabel;
        iss >> cpuLabel; //First element of a string stream is "cpu"

        unsigned long long value;

        while(iss >> value){
            jiffies.push_back(value);
        }
    }
    return jiffies;

}


void cpuReaderThread(SharedData& data) {
    for (; ;){
    std::ifstream file("/proc/stat");

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open /proc/stat!" << std::endl;
        return;
    }

    std::vector<unsigned long long> newJiffies = parseCpuData(file);
    if(!newJiffies.empty()){
        std::lock_guard<std::mutex> lock(data.mtx);
        data.jiffies = newJiffies;
    }

    file.close();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}
