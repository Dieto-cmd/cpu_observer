#include "cpu_load_calculator.h"
#include <numeric>
#include<thread>
#include<mutex>



double calculateCpuLoad(unsigned long long idleTime, unsigned long long totalTime){
    if (totalTime == 0){
        return -1;
    }
    
    return (static_cast<double>(totalTime - idleTime)/totalTime * 100); 
}

void cpuLoadCalculatorThread(SharedData& data){
    unsigned long long prevIdleTime = 0;
    unsigned long long prevTotalTime = 0;
    unsigned long long idleTime;
    unsigned long long totalTime;

    while(true){
    
        bool dataAquired = false;
    {
        std::lock_guard<std::mutex> lock(data.mtx);
        if(!data.jiffies.empty()){
            idleTime = data.jiffies[3] + data.jiffies[4]; //jiffies[3] - idle time, jiffies[4] - iowait time
            totalTime = std::accumulate(data.jiffies.begin(), data.jiffies.end(), 0);
            dataAquired = true;
        }
        
    }
    
    if(dataAquired){
        if(prevIdleTime != 0 && prevTotalTime != 0){

        unsigned long long idleDelta = idleTime - prevIdleTime; //how much time since last check was spent in idle state
        unsigned long long totalDelta = totalTime - prevTotalTime; //how much time sinc last check has passed
        double cpuLoad = calculateCpuLoad(idleDelta, totalDelta); //Calculating how much time was cpu occpied in %
        std::lock_guard<std::mutex> lock(data.mtx);
        data.percent = cpuLoad;
    }

    prevIdleTime = idleTime;
    prevTotalTime = totalTime;
    }

    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}