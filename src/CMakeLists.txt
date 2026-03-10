

add_executable(cpu_observer main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(cpu_observer Threads::Threads)