#include "cpu_load_calculator.h"
#include <numeric>
#include<iostream>
#include<thread>
#include<mutex>
#include<iomanip>


double calculateCpuLoad(int idleTime, int totalTime){
    if (totalTime == 0){
        return -1;
    }
    
    return (static_cast<double>(totalTime - idleTime)/totalTime * 100); //Calculating how much time was cpu occpied in %
}

void cpuLoadCalculatorThread(SharedData& data){
    int prevIdleTime = 0;
    int prevTotalTime = 0;
    int idleTime;
    int totalTime;

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

        int idleDelta = idleTime - prevIdleTime; //how much time since last check was spent in idle state
        int totalDelta = totalTime - prevTotalTime; //how much time sinc last check has passed
        double cpuLoad = calculateCpuLoad(idleDelta, totalDelta);
        if (cpuLoad != -1){
            std::cout << "Printing cpu load: " << std::fixed << std::setprecision(2) << cpuLoad << "%";
        std::cout << "\n";
        } else {
            std::cout << "Couldn't get cpu load data" << "\n";
        }
        
    }

    prevIdleTime = idleTime;
    prevTotalTime = totalTime;
    }

    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}