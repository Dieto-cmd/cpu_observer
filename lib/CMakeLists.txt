

add_library(cpu_logic src/cpu_reader.cpp src/cpu_load_calculator.cpp src/ui_manager.cpp)
target_include_directories(cpu_logic PUBLIC include)


find_package(Threads REQUIRED)
include(FetchContent)
 
FetchContent_Declare(
    ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9  
)

FetchContent_MakeAvailable(ftxui)

target_link_libraries(cpu_logic 
    PRIVATE Threads::Threads
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
  )