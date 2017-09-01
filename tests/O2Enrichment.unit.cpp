#include "catch.hpp"
#include <calculator/furnace/O2Enrichment.h>

TEST_CASE( "Calculate the Available Heat with Air", "[Available Heat][O2Enrichment][Calculator]") {
CHECK( O2Enrichment(21, 100, 1800, 1900, 5, 1, 900, 80, 10).getAvailableHeat() == Approx(61.97));
}

TEST_CASE( "Calculate the Available Heat with Oxygen Enriched Air", "[Available Heat Enriched][O2Enrichment][Calculator]") {
    CHECK( O2Enrichment(21, 100, 1800, 1900, 5, 1, 900, 80, 10).getAvailableHeatEnriched() == Approx(74.2210855231));
}

TEST_CASE( "Calculate the Fuel Savings with Oxygen Enriched Air", "[Fuel Savings Enriched][O2Enrichment][Calculator]") {
    CHECK( O2Enrichment(21, 100, 1800, 1900, 5, 1, 900, 80, 10).getFuelSavingsEnriched() == Approx(16.5058213035));
}

TEST_CASE( "Calculate the Fuel Consumption with Oxygen Enriched Air", "[Fuel Consumption Enriched][O2Enrichment][Calculator]") {
    CHECK( O2Enrichment(21, 100, 1800, 1900, 5, 1, 900, 80, 10).getFuelConsumptionEnriched() == Approx(8.3494178697));
}
