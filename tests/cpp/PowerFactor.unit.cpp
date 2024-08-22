#include "catch.hpp"
#include "electrical/PowerFactor.h"

auto validate = [](PowerFactor::Output const & results, PowerFactor::Output expected) {
    CHECK(Approx(results.realDemand) == expected.realDemand);
    CHECK(Approx(results.demandPenalty) == expected.demandPenalty);
    CHECK(Approx(results.reactivePower) == expected.reactivePower);
    CHECK(Approx(results.proposedReactivePower) == expected.proposedReactivePower);
    CHECK(Approx(results.proposedCapacitance) == expected.proposedCapacitance);
};

TEST_CASE("Calculate Apparent Power, Real Power, Reactive Power, Phase Angle, Power Factor and Capacitance based on inputs, 9 combinations:", "[powerFactor]") {
    INFO("Powers as inputs, 3 combinations: ");
    INFO("ApparentPower + RealPower as inputs: Test# 1");
    validate(PowerFactor().calculate(PowerFactor::Mode::ApparentPower_RealPower, 100, 87, 0.95), 
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("ApparentPower + ReactivePower as inputs: Test# 2");
    validate(PowerFactor().calculate(PowerFactor::Mode::ApparentPower_ReactivePower, 100, 49.3052, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("RealPower + ReactivePower as inputs: Test# 3");
    validate(PowerFactor().calculate(PowerFactor::Mode::RealPower_ReactivePower, 87, 49.3052, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("Power and Phase Angle as inputs, 3 combinations: ");
    INFO("ApparentPower + PhaseAngle as inputs: Test# 1");
    validate(PowerFactor().calculate(PowerFactor::Mode::ApparentPower_PhaseAngle, 100, 29.5413605, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("RealPower + PhaseAngle as inputs: Test# 2");
    validate(PowerFactor().calculate(PowerFactor::Mode::RealPower_PhaseAngle, 87, 29.5413605, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("ReactivePower + PhaseAngle as inputs: Test# 3");
    validate(PowerFactor().calculate(PowerFactor::Mode::ReactivePower_PhaseAngle, 49.3052, 29.5413605, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("Power and Power Factor as inputs, 3 combinations: ");
    INFO("ApparentPower + PowerFactor as inputs: Test# 1");
    validate(PowerFactor().calculate(PowerFactor::Mode::ApparentPower_PowerFactor, 100, 0.87, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("RealPower + PowerFactor as inputs: Test# 2");
    validate(PowerFactor().calculate(PowerFactor::Mode::RealPower_PowerFactor, 87, 0.87, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");

    INFO("ReactivePower + PowerFactor as inputs: Test# 3");
    validate(PowerFactor().calculate(PowerFactor::Mode::ReactivePower_PowerFactor, 49.3052, 0.87, 0.95),  
             {87, 49.3052, 100, 0.87, 29.54, 91.5789, 8.4211, 28.5955, 20.7097});
    INFO("Passed");
}