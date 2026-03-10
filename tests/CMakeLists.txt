include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.11.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests test_calculator.cpp test_reader.cpp)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain cpu_logic)

include(Catch)
catch_discover_tests(unit_tests)