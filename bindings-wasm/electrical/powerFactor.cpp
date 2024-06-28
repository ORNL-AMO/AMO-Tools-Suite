#include "electrical/PowerFactor.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(powerFactor_class)
{
    enum_<PowerFactor::Mode>("PowerFactorModeType")
            .value("ApparentPower_RealPower", PowerFactor::Mode::ApparentPower_RealPower)
            .value("ApparentPower_ReactivePower", PowerFactor::Mode::ApparentPower_ReactivePower)
            .value("ApparentPower_PhaseAngle", PowerFactor::Mode::ApparentPower_PhaseAngle)
            .value("ApparentPower_PowerFactor", PowerFactor::Mode::ApparentPower_PowerFactor)
            .value("RealPower_ReactivePower", PowerFactor::Mode::RealPower_ReactivePower)
            .value("RealPower_PhaseAngle", PowerFactor::Mode::RealPower_PhaseAngle)
            .value("RealPower_PowerFactor", PowerFactor::Mode::RealPower_PowerFactor)
            .value("ReactivePower_PhaseAngle", PowerFactor::Mode::ReactivePower_PhaseAngle)
            .value("ReactivePower_PowerFactor", PowerFactor::Mode::ReactivePower_PowerFactor);

    class_<PowerFactor::Output>("PowerFactorOutput")
        .property("realDemand", &PowerFactor::Output::realDemand)
        .property("demandPenalty", &PowerFactor::Output::demandPenalty)
        .property("reactivePower", &PowerFactor::Output::reactivePower)
        .property("proposedReactivePower", &PowerFactor::Output::proposedReactivePower)
        .property("proposedCapacitance", &PowerFactor::Output::proposedCapacitance);

    class_<PowerFactor>("PowerFactor")
        .constructor<>()
        .function("calculate", &PowerFactor::calculate);
}