#include <catch2/catch_test_macros.hpp>

double calculateCpuUsage(long totalDelta, long idleDelta) {
    return (static_cast<double>(totalDelta- idleDelta)/ totalDelta) * 100;
}

TEST_CASE("Computing CPU usage", "[Calculator]") {
    
    SECTION("When CPU is idle (0% load)") {
        long totalDelta = 1000;
        long idleDelta = 1000;
        REQUIRE(calculateCpuUsage(totalDelta, idleDelta) == 0.0);
    }

    SECTION("When CPU is working half loaded (50% load)") {
        long totalDelta = 1000;
        long idleDelta = 500;
        REQUIRE(calculateCpuUsage(totalDelta, idleDelta) == 50.0);
    }

    SECTION("When CPU is loaded to it's maximum capabilities (100% usage)") {
        long totalDelta = 1000;
        long idleDelta = 0;
        REQUIRE(calculateCpuUsage(totalDelta, idleDelta) == 100.0);
    }
}