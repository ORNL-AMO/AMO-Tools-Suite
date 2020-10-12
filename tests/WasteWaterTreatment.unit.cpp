#include "catch.hpp"
#include <wasteWater/WasteWaterTreatment.h>

TEST_CASE("Waste Water Treatment", "[Test 1]")
{
    WasteWaterTreatment wasteWaterTreatment(20, 200, 1, 1, 40, 35, 0.85, 200, 20, 8, 10000, 3000, 0.1, 0.6, 60, 0.1, 8, 72, 2,4.5, 0.84, 0.92, 2.7, 150, 200, 24, 1, 100, 0.09);
    WasteWaterTreatment::Output output = wasteWaterTreatment.calculate();

    REQUIRE(output.TotalAverageDailyFlowRate == Approx(1.00));
    REQUIRE(output.VolumeInService == Approx(1.00));
    REQUIRE(output.InfluentBOD5Concentration == Approx(200.00));
    REQUIRE(output.InfluentBOD5MassLoading == Approx(1668.00));
    REQUIRE(output.SecWWOxidNLoad == Approx(291.90));
    REQUIRE(output.SecWWTSSLoad == Approx(1668.00));
    REQUIRE(output.FM_ratio == Approx(0.09));
    REQUIRE(output.SolidsRetentionTime == Approx(29.00));
    REQUIRE(output.MLSS == Approx(3082.50));
    REQUIRE(output.MLVSS == Approx(2301.12));
    REQUIRE(output.TSSSludgeProduction == Approx(819.76));
    REQUIRE(output.TSSInActivatedSludgeEffluent == Approx(66.72));
    REQUIRE(output.TotalOxygenRequirements == Approx(3135.09));
    REQUIRE(output.TotalOxygenReqWDenit == Approx(2698.14));
    REQUIRE(output.TotalOxygenSupplied == Approx(3394.16));
    REQUIRE(output.MixingIntensityInReactor == Approx(150.00));
    REQUIRE(output.RASFlowRate == Approx(0.45));
    REQUIRE(output.RASRecyclePercentage == Approx(44.56));
    REQUIRE(output.WASFlowRate == Approx(0.01));
    REQUIRE(output.RASTSSConcentration == Approx(10000.00));
    REQUIRE(output.TotalSludgeProduction == Approx(886.48));
    REQUIRE(output.ReactorDetentionTime == Approx(24.00));
    REQUIRE(output.VOLR == Approx(12.48));
    REQUIRE(output.EffluentCBOD5 == Approx(3.95));
    REQUIRE(output.EffluentTSS == Approx(8.00));
    REQUIRE(output.EffluentAmmonia_N == Approx(0.35));
    REQUIRE(output.EffluentNO3_N == Approx(26.17));
    REQUIRE(output.EffluentNO3_N_W_Denit == Approx(7.85));
    REQUIRE(output.FieldOTR == Approx(0.94));
    REQUIRE(output.AeEnergy == Approx(70200));
    REQUIRE(output.AeCost == Approx(6318));
}