

add_library(cpu_logic src/cpu_reader.cpp src/cpu_load_calculator.cpp)

target_include_directories(cpu_logic PUBLIC include)
find_package(Threads REQUIRED)
target_link_libraries(cpu_logic PRIVATE Threads::Threads)