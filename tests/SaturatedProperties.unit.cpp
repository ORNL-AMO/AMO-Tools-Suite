#include "catch.hpp"
#include <ssmt/SaturatedProperties.h>

#include <ssmt/SteamSystemModelerTool.h>

TEST_CASE( "Calculate the Saturated Temperature from Pressure", "[Saturated Temperature][ssmt][Calculator]") {
    CHECK( SaturatedTemperature(20).calculate() == Approx(638.8959115457));
}

TEST_CASE( "Calculate the Saturated Pressure from Temperature", "[Saturated Pressure][ssmt][Calculator]") {
    CHECK( SaturatedPressure(300).calculate() == Approx(0.0035365894));
}

TEST_CASE( "Calculate the Saturated Gas Specific Enthalpy", "[Gas Enthalpy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20, 638.8959115457);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["gasSpecificEnthalpy"] == Approx(2421.6805426877));
}

TEST_CASE( "Calculate the Saturated Gas Specific Entropy", "[Gas Entropy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20, 638.8959115457);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["gasSpecificEntropy"] == Approx(4.946));
}

TEST_CASE( "Calculate the Saturated Gas Specific Volume", "[Gas Volume][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20, 638.8959115457);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["gasSpecificVolume"] == Approx(0.0059368541));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Enthalpy (Region 1)", "[Liquid Enthalpy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["liquidSpecificEnthalpy"] == Approx(112.5749908124));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Entropy (Region 1)", "[Liquid Entropy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["liquidSpecificEntropy"] == Approx(0.3931236015));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Volume (Region 1)", "[Liquid Volume][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["liquidSpecificVolume"] == Approx(0.001));
}

TEST_CASE( "Calculate the Evaporation Specific Volume", "[Evaporation Volume][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["evaporationSpecificVolume"] == Approx(39.081));
}

TEST_CASE( "Calculate the Evaporation Specific Enthalpy", "[Evaporation Enthalpy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["evaporationSpecificEnthalpy"] == Approx(2437.3));
}

TEST_CASE( "Calculate the Evaporation Specific Entropy", "[Evaporation Entropy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(0.0035365894, 300);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["evaporationSpecificEntropy"] == Approx(8.1244130853));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Volume (Region 3)", "[Liquid Volume][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20.2659, 640);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["liquidSpecificVolume"] == Approx(0.0020763677));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Enthalpy (Region 3)", "[Liquid Enthalpy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20.2659, 640);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["liquidSpecificEnthalpy"] == Approx(1841.9862103902));
}

TEST_CASE( "Calculate the Saturated Liquid Specific Entropy (Region 3)", "[Liquid Entropy][ssmt][Calculator]") {
    SaturatedProperties sp = SaturatedProperties(20.2659, 640);
    std::unordered_map <std::string, double> props = sp.calculate();
    CHECK( props["liquidSpecificEntropy"] == Approx(4.0378047547));
}

