#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <vector>
#include "cpu_reader.h"
#include <map>

TEST_CASE("Cpu reader parsing", "[Reader]") {
    
    SECTION("Parsing normal data input") {
        std::istringstream test_stream("cpu 31 3214 321432 2312 2 0 0\ncpu1 2 6 7 8");
                                        
        std::map<std::string, std::vector<unsigned long long>> desired_output = {
                                                                        {"cpu",{31,3214,321432,2312,2,0,0}},
                                                                         {"cpu1", {2,6,7,8}}};
        auto  real_output = parseCpuData(test_stream);
        REQUIRE( real_output == desired_output);
    }
    SECTION("Parsing empty data input") {
        std::istringstream test_stream("");
        auto real_output = parseCpuData(test_stream);
        REQUIRE( real_output.empty() == true);
    }
    SECTION("Parsing invalid data input") {
        std::istringstream test_stream("cpu 1 2 4 5\ncsdadfsaf 2 5 2 2 3");
        std::map<std::string, std::vector<unsigned long long>> desired_output = {
                                                                        {"cpu",{1,2,4,5}}};
        auto  real_output = parseCpuData(test_stream);
        REQUIRE( real_output == desired_output);
    }
}