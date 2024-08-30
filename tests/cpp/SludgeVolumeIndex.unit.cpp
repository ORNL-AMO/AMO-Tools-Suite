#include "catch.hpp"
#include <iostream>
#include <calculator/util/SludgeVolumeIndex.h>

TEST_CASE( "State Point Analysis", "SVIXX/VoK" ) {
    auto res = SludgeVolumeIndex(SludgeVolumeIndex::SVIGN, 0.150000, 1, 930, 0.0025, 1892705, 788627, 1).calculate();
    CHECK(res.TotalAreaClarifier == Approx(930));
    CHECK(res.SurfaceOverflow == Approx(2035.17));
    CHECK(res.AppliedSolidsLoading == Approx(7.20788));
    CHECK(res.RasConcentration == Approx(0.0085));
    CHECK(res.UnderFlowRateX2 == Approx(8.5000006));
    CHECK(res.UnderFlowRateY1 == Approx(7.20788));
    CHECK(res.OverFlowRateX2 == Approx(3.8057908));
    CHECK(res.OverFlowRateY2 == Approx(7.7454186));
    CHECK(res.StatePointX == Approx(2.5000));
    CHECK(res.StatePointY == Approx(5.0879167));
    CHECK(res.GraphData[39].SolidsConcentration == Approx(3.9));
    CHECK(res.GraphData[39].SolidsFlux == Approx(5.21));
    CHECK(res.GraphData[150].SolidsConcentration == Approx(15));
    CHECK(res.GraphData[150].SolidsFlux == Approx(0.16));

    std::cout << "Begin Graph Data Points" << std::endl;
    for(int i = 0; i < 151; i++) std::cout << i+1 << " : (" << res.GraphData[i].SolidsConcentration << ", " << res.GraphData[i].SolidsFlux << ")" << std::endl;
    std::cout << "End Graph Data Points" << std::endl;

    res = SludgeVolumeIndex(SludgeVolumeIndex::VoK, 0.6000, 2, 84.3486, 0.0025, 157725, 110408, 8.998).calculate();
    CHECK(res.TotalAreaClarifier == Approx(168.6971));
    CHECK(res.SurfaceOverflow == Approx(934.9626));
    CHECK(res.AppliedSolidsLoading == Approx(3.973591));
    CHECK(res.RasConcentration == Approx(0.006071));
    CHECK(res.UnderFlowRateX2 == Approx(6.07142857));
    CHECK(res.UnderFlowRateY1 == Approx(3.97359117));
    CHECK(res.OverFlowRateX2 == Approx(7.37591695));
    CHECK(res.OverFlowRateY2 == Approx(6.89620669));
    CHECK(res.StatePointX == Approx(2.5000));
    CHECK(res.StatePointY == Approx(2.33740657));
    CHECK(res.GraphData[39].SolidsConcentration == Approx(3.9));
    CHECK(res.GraphData[39].SolidsFlux == Approx(3.38));
    CHECK(res.GraphData[150].SolidsConcentration == Approx(15));
    CHECK(res.GraphData[150].SolidsFlux == Approx(0.02));

    std::cout << "Begin Graph Data Points" << std::endl;
    for(int i = 0; i < 151; i++) std::cout << i+1 << " : (" << res.GraphData[i].SolidsConcentration << ", " << res.GraphData[i].SolidsFlux << ")" << std::endl;
    std::cout << "End Graph Data Points" << std::endl;
}