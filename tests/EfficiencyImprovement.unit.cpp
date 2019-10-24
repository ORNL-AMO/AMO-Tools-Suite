#include "catch.hpp"
#include <calculator/furnace/EfficiencyImprovement.h>

TEST_CASE( "Calculate the Current Excess Air", "[Current Excess Air][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getCurrentExcessAir() == Approx(35.80));
}

TEST_CASE( "Calculate the New Excess Air", "[New Excess Air][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewExcessAir() == Approx(9.4210532075));
}

TEST_CASE( "Calculate the Current Available Heat", "[Current Available Heat][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getCurrentAvailableHeat() == Approx(45.5508888775));
}

TEST_CASE( "Calculate the New Available Heat", "[New Available Heat][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewAvailableHeat() == Approx(77.8931185299));
}

TEST_CASE( "Calculate the New Fuel Savings", "[New Fuel Savings][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewFuelSavings() == Approx(41.5212925902));
}

TEST_CASE( "Calculate the New Energy Input", "[New Energy Input][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewEnergyInput() == Approx(5.847870741));
}