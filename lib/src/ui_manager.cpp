#include "ui_manager.h"
#include<mutex>
#include<thread>
#include<string>
#include<iostream>
#include<iomanip>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

void drawBar(double percent, std::string& resetPosition) {
    float ratio = percent/100.0;

    auto bar = ftxui::gauge(ratio) | ftxui::border;
    auto barColor = ftxui::Color::Green;
    if (percent > 50) barColor = ftxui::Color::Yellow;
     if (percent > 85) barColor = ftxui::Color::Red;

    auto decoratedBar = ftxui::hbox({
        ftxui::text(" CPU: ") | ftxui::bold | ftxui::vcenter,
        bar | ftxui::color(barColor),
        ftxui::text(" " + std::to_string((int)percent) + "%") | ftxui::color(barColor) | ftxui::vcenter
    });

    auto screen = ftxui::Screen::Create(
        ftxui::Dimension::Fixed(35),       // Width
        ftxui::Dimension::Fit(decoratedBar) //Height
    );

    ftxui::Render(screen, decoratedBar);

    std::cout << resetPosition;

    screen.Print();

    resetPosition = screen.ResetPosition();
    
}

void uiManagerThread(SharedData& data){
    std::string resetPosition = "";

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
            drawBar(percent, resetPosition);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}