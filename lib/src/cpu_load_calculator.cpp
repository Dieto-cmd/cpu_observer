#include "cpu_load_calculator.h"
#include <numeric>
#include<thread>
#include<mutex>
#include<array>



double calculateCpuLoad(unsigned long long idleTime, unsigned long long totalTime){
    if (totalTime == 0){
        return -1;
    }
    
    return (static_cast<double>(totalTime - idleTime)/totalTime * 100); 
}

void cpuLoadCalculatorThread(SharedData& data){
    std::array<unsigned long long, 13> prevIdleTime = {0, 0 ,0 ,0,0, 0 ,0 ,0, 0, 0 ,0 ,0, 0};
    std::array<unsigned long long, 13> prevTotalTime = {0, 0 ,0 ,0,0, 0 ,0 ,0, 0, 0 ,0 ,0, 0};
    std::array<unsigned long long, 13> idleTime;//The length is 13 because there are 12 cpu threads and 
    std::array<unsigned long long, 13> totalTime;//one additional is need for overall statistic

    while(true){
    
        bool dataAquired = false;
    {
        std::lock_guard<std::mutex> lock(data.mtx);
        if(!data.labeledJiffies.empty()){
            int i = 0;
            for (auto jiffies : data.labeledJiffies){ //jiffies.second is a vector containing actual jiffies, jiffies.first is a cpu label e.g "cpu2"
                idleTime.at(i) = jiffies.second[3] + jiffies.second[4]; //jiffies[3] - idle time, jiffies[4] - iowait time
                totalTime.at(i) = std::accumulate(jiffies.second.begin(), jiffies.second.end(), 0);
                i++;
            }
            dataAquired = true;
            
        }
        
    }
    
    if(dataAquired){
        for (int i = 0; i < 13; i++) {
            if(prevIdleTime.at(i) != 0 && prevTotalTime.at(i) != 0){

                //how much time since last check was spent in idle state
                unsigned long long idleDelta = idleTime.at(i) - prevIdleTime.at(i); 

                //how much time sinc last check has passed
                unsigned long long totalDelta = totalTime.at(i) - prevTotalTime.at(i); 

                //Calculating how much time was cpu occpied in %
                double cpuLoad = calculateCpuLoad(idleDelta, totalDelta); 

                std::lock_guard<std::mutex> lock(data.mtx);
                data.percent.at(i) = cpuLoad;
            }
        }
        
        prevIdleTime = idleTime;
        prevTotalTime = totalTime;
    
    }

    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}