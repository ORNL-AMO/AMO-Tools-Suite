#include "catch.hpp"
#include <calculator/furnace/EfficiencyImprovement.h>

TEST_CASE( "Calculate the Current Excess Air", "[Current Excess Air][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getCurrentExcessAir() == Approx(35.80));
}

TEST_CASE( "Calculate the New Excess Air", "[New Excess Air][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewExcessAir() == Approx(9.4210532075));
}

TEST_CASE( "Calculate the Current Available Heat", "[Current Avaiable Heat][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getCurrentAvailableHeat() == Approx(46.6298023469));
}

TEST_CASE( "Calculate the New Available Heat", "[New Avaiable Heat][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewAvailableHeat() == Approx(78.9720318524));
}

TEST_CASE( "Calculate the New Fuel Savings", "[New Fuel Savings][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewFuelSavings() == Approx(40.9540298596));
}

TEST_CASE( "Calculate the New Energy Input", "[New Energy Input][EfficiencyImprovement][Calculator]") {
    CHECK( EfficiencyImprovement(6, 2, 1600, 1200, 80, 750, 10).getNewEnergyInput() == Approx(5.904597014));
}