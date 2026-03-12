#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<mutex>
#include "cpu_reader.h"
#include<thread>
#include<map>

std::map<std::string, std::vector<unsigned long long>> parseCpuData(std::istream& input_stream) {
    std::string line;
    std::map<std::string, std::vector<unsigned long long>> map;

    while(getline(input_stream, line)){
        std::istringstream iss(line);
        std::string cpuLabel;
        iss >> cpuLabel; //First element of a string stream is "cpu"

        if (cpuLabel.substr(0,3) != "cpu") break;

        unsigned long long value;

        while(iss >> value){
            map[cpuLabel].push_back(value);
        }
    }
    return map;

}


void cpuReaderThread(SharedData& data) {
    for (; ;){
    std::ifstream file("/proc/stat");

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open /proc/stat!" << std::endl;
        return;
    }

    std::map<std::string, std::vector<unsigned long long>> newLabeledJiffies = parseCpuData(file);
    if(!newLabeledJiffies.empty()){
        std::lock_guard<std::mutex> lock(data.mtx);
        data.labeledJiffies = newLabeledJiffies;
    }

    file.close();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}
