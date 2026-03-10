#include <catch2/catch_test_macros.hpp>
#include "cpu_reader.h"
#include <sstream>
#include <vector>

TEST_CASE("Cpu reader parsing", "[Reader]") {
    
    SECTION("Parsing normal data input") {
        std::istringstream test_stream("cpu 31 3214 321432 2312 2 0 0\n");
        std::vector<unsigned long long> desired_output = {31, 3214, 321432, 2312, 2, 0 , 0};
        std::vector<unsigned long long> real_output = parseCpuData(test_stream);
        REQUIRE( real_output == desired_output);
    }
    SECTION("Parsing empty data input") {
        std::istringstream test_stream("");
        std::vector<unsigned long long> real_output = parseCpuData(test_stream);
        REQUIRE( real_output.empty() == true);
    }
}