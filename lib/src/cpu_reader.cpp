#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<mutex>
#include "cpu_reader.h"
#include<thread>



void cpuReaderThread(SharedData& data) {
    for (int i = 0; i < 2; i++){
    std::ifstream file("/proc/stat");

    if (!file.is_open()) {
        std::cerr << "Error: Couldn't open /proc/stat!" << std::endl;
        return;
    }

    std::string line;

    if(getline(file,line)){
        std::istringstream iss(line);
        std::string cpuLabel;
        iss >> cpuLabel; //First element of a string stream is "cpu"

        int value;

        std::vector<int> jiffies;
        while(iss >> value){
            jiffies.push_back(value);
        }
        std::cout << "\nPrinting parameteres obtained from /proc/stat:\n";
        std::cout << cpuLabel << " ";
        for (auto item : jiffies) {
            std::cout << item << " ";
        }
    }

    file.close();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}
