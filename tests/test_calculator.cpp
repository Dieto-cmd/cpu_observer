#include <catch2/catch_test_macros.hpp>
#include "cpu_load_calculator.h"

TEST_CASE("Computing CPU usage", "[Calculator]") {
    
    SECTION("1") {
        long totalDelta = 1000;
        long idleDelta = 1000;
        REQUIRE(calculateCpuLoad(idleDelta, totalDelta) == 0.0);
    }

    SECTION("2") {
        long totalDelta = 1000;
        long idleDelta = 500;
        REQUIRE(calculateCpuLoad(idleDelta, totalDelta) == 50.0);
    }

    SECTION("3") {
        long totalDelta = 1000;
        long idleDelta = 0;
        REQUIRE(calculateCpuLoad(idleDelta, totalDelta) == 100.0);
    }
    SECTION("4") {
        long totalDelta = 1000;
        long idleDelta = 254;
        REQUIRE(calculateCpuLoad(idleDelta, totalDelta) == 74.6);
    }
}