#include "catch.hpp"
#include <calculator/furnace/O2Enrichment.h>

TEST_CASE( "Calculate o2 enrichment", "[Available Heat][O2Enrichment][Calculator]") {
    auto o2Enrichment = O2Enrichment(21, 100, 1800, 1900, 5, 1, 900, 80, 10);
    CHECK( o2Enrichment.getAvailableHeat() == Approx(61.97));
    CHECK( o2Enrichment.getAvailableHeatEnriched() == Approx(74.2210855231));
    CHECK( o2Enrichment.getFuelSavingsEnriched() == Approx(16.5058213035));
    CHECK( o2Enrichment.getFuelConsumptionEnriched() == Approx(8.3494178697));
}

TEST_CASE( "Calculate o2 enrichment 2", "[O2Enrichment][Calculator]") {
    auto o2Enrichment = O2Enrichment(21, 100, 2200, 2300, 5, 1, 900, 80, 10);
    CHECK( o2Enrichment.getAvailableHeat() == Approx(49.7183629149));
    CHECK( o2Enrichment.getAvailableHeatEnriched() == Approx(69.9474376972));
    CHECK( o2Enrichment.getFuelSavingsEnriched() == Approx(28.9203942964));
    CHECK( o2Enrichment.getFuelConsumptionEnriched() == Approx(7.1079605704));
}

TEST_CASE( "Calculate o2 enrichment 3 - set methods", "[O2Enrichment][Calculator]") {
    auto o2Enrichment = O2Enrichment();
	o2Enrichment.setO2CombAir(21);
    o2Enrichment.setO2CombAirEnriched(100);
    o2Enrichment.setFlueGasTemp(2200);
    o2Enrichment.setFlueGasTempEnriched(2300);
    o2Enrichment.setO2FlueGas(8);
    o2Enrichment.setO2FlueGasEnriched(3);
	o2Enrichment.setCombAirTemp(900);
    o2Enrichment.setCombAirTempEnriched(80);
	o2Enrichment.setFuelConsumption(10);
    CHECK( o2Enrichment.getAvailableHeat() == Approx(42.6248055296));
    CHECK( o2Enrichment.getAvailableHeatEnriched() == Approx(65.7672982588));
    CHECK( o2Enrichment.getFuelSavingsEnriched() == Approx(35.1884497948));
    CHECK( o2Enrichment.getFuelConsumptionEnriched() == Approx(6.4811550205));
}

TEST_CASE( "Calculate o2 enrichment 4", "[O2Enrichment][Calculator]") {
    auto o2Enrichment = O2Enrichment(21, 100, 2200, 2300, 8, 3, 1100, 110, 10);
    CHECK( o2Enrichment.getAvailableHeat() == Approx( 49.1204784776));
    CHECK( o2Enrichment.getAvailableHeatEnriched() == Approx(66.3723712295));
    CHECK( o2Enrichment.getFuelSavingsEnriched() == Approx(25.9925816002));
    CHECK( o2Enrichment.getFuelConsumptionEnriched() == Approx(7.40074184));
}
