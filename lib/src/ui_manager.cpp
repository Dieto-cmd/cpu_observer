#include "ui_manager.h"
#include<mutex>
#include<thread>
#include<string>
#include<iostream>
#include<iomanip>

void drawBar(double percent) {
    const int barWidth = 25;
    int fill = (percent/100.0) * barWidth;
    std::string color = "\033[32m"; // Green by default
    if (percent > 50.0) color = "\033[33m"; // Yellow for medium load
    if (percent > 85.0) color = "\033[31m"; // Red for high load
    std::string colorReset = "\033[0m";

    std::cout << "\rCPU: [";
    for (int i = 0; i < barWidth; i++){
        if (i < fill) std::cout << color << "|" << colorReset;
        else std::cout << " ";
    }
    std::cout << "]" << color << std::fixed << std::setprecision(2) << percent;
    std::cout <<"%" << colorReset << std::flush;

}

void uiManagerThread(SharedData& data){
    while(true){
        bool dataAquired = false;
        double percent;
        {
            std::lock_guard<std::mutex> lock(data.mtx);
            if(data.percent != -1){
                percent = data.percent;
                dataAquired = true;
            }
        }
        if(dataAquired){
            drawBar(percent);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}