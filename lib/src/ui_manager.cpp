#include "ui_manager.h"
#include<mutex>
#include<thread>
#include<string>
#include<iostream>
#include<iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <map>

void drawBars(std::map<std::string, double> labeledPercentages, std::string& resetPosition) {

    std::vector<ftxui::Element> barList;

    std::vector<std::pair<std::string, double>> sortedLabels(labeledPercentages.begin(),labeledPercentages.end());


    std::sort(sortedLabels.begin(), sortedLabels.end(), [](const auto& a, const auto& b){
        if (a.first == "cpu") return true;
        if (b.first == "cpu") return false;

        int numA = std::stoi(a.first.substr(3));
        int numB = std::stoi(b.first.substr(3));

        return numA < numB;
    });


    for (auto element : sortedLabels){
        double percent = element.second;
        std::string cpuLabel = element.first;

        if(cpuLabel == "cpu"){
            std::transform(cpuLabel.begin(), cpuLabel.end(), cpuLabel.begin(), ::toupper);
        }

        float ratio = percent/100.0;

    auto bar = ftxui::gauge(ratio) | ftxui::border;
    auto barColor = ftxui::Color::Green;
    if (percent > 50) barColor = ftxui::Color::Yellow;
     if (percent > 85) barColor = ftxui::Color::Red;

    auto decoratedBar = ftxui::hbox({
        ftxui::text(" " + cpuLabel + ": ") | ftxui::bold | ftxui::vcenter,
        bar | ftxui::color(barColor),
        ftxui::text(" " + std::to_string((int)percent) + "%") | ftxui::color(barColor) | ftxui::vcenter
    });

    barList.push_back(decoratedBar);
    }

    auto allBars = ftxui::vbox(barList);

    auto screen = ftxui::Screen::Create(
        ftxui::Dimension::Fixed(35),       // Width
        ftxui::Dimension::Fit(allBars) //Height
    );

    ftxui::Render(screen, allBars);

    std::cout << resetPosition;

    screen.Print();

    resetPosition = screen.ResetPosition();
    
    
}

void uiManagerThread(SharedData& data){
    std::string resetPosition = "";
    std::map<std::string, double> labeledPercentages;

    while(true){
        bool dataAquired = false;
        {
            int i = 0;
            std::lock_guard<std::mutex> lock(data.mtx);
                for (auto jiffie : data.labeledJiffies){
                    if(data.percent.at(i) != -1){
                    labeledPercentages[jiffie.first] = data.percent.at(i);
                    i++;
                }
            }
            dataAquired = true;
            
        }
        if(dataAquired){
            drawBars(labeledPercentages, resetPosition);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}