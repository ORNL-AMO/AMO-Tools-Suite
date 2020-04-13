
#include "results/Results.h"
#include "results/InputData.h"
#include "fans/Fan203.h"
#include "fans/CompressibilityFactor.h"
#include <emscripten/bind.h>
using namespace emscripten;

//fanResultsExisting / fanResultsModified
EMSCRIPTEN_BINDINGS(fsat_results)
{
    //fan input
    class_<Fan::Input>("FanInput")
        .constructor<double, double, Motor::Drive, double>();

    //field data basleline
    class_<Fan::FieldDataBaseline>("FieldDataBaseline")
        .constructor<double, double, double, double, double, double, double, Motor::LoadEstimationMethod>();

    //field data modified
    class_<Fan::FieldDataModified>("FieldDataModified")
        .constructor<double, double, double, double, double, double>();

    //fan result
    class_<FanResult>("FanResult")
        .constructor<Fan::Input, Motor, double, double>()
        .function("calculateExisting", &FanResult::calculateExisting)
        .function("calculateModified", &FanResult::calculateModified);
}

EMSCRIPTEN_BINDINGS(fsat_output)
{
    class_<FanResult::Output>("FanOutput")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double, double, double>()
        .property("fanEfficiency", &FanResult::Output::fanEfficiency)
        .property("motorRatedPower", &FanResult::Output::motorRatedPower)
        .property("motorShaftPower", &FanResult::Output::motorShaftPower)
        .property("fanShaftPower", &FanResult::Output::fanShaftPower)
        .property("motorEfficiency", &FanResult::Output::motorEfficiency)
        .property("motorPowerFactor", &FanResult::Output::motorPowerFactor)
        .property("motorCurrent", &FanResult::Output::motorCurrent)
        .property("motorPower", &FanResult::Output::motorPower)
        .property("annualEnergy", &FanResult::Output::annualEnergy)
        .property("annualCost", &FanResult::Output::annualCost)
        .property("fanEnergyIndex", &FanResult::Output::fanEnergyIndex)
        .property("loadFactor", &FanResult::Output::loadFactor)
        .property("driveEfficiency", &FanResult::Output::driveEfficiency)
        .property("estimatedFLA", &FanResult::Output::estimatedFLA);
}
//fan203
EMSCRIPTEN_BINDINGS(fan_203)
{
    //fan rated info
    class_<FanRatedInfo>("FanRatedInfo")
        .constructor<double, double, double, double, double>();
    //plane data
    class_<PlaneData>("PlaneData")
        .constructor<FlangePlane, FlangePlane, TraversePlane, std::vector<TraversePlane>, MstPlane, MstPlane, double, double, bool>();
    //FlangePlane
    class_<FlangePlane>("FlangePlane")
        .constructor<double, double, double>();
    //TraversePlane
    class_<TraversePlane>("TraversePlane")
        .constructor<double, double, double, double, double, std::vector<std::vector<double>>>();
    //MstPlane
    class_<MstPlane>("MstPlane")
        .constructor<double, double, double, double>();
    //fan shaft power
    class_<FanShaftPower>("FanShaftPower")
        .constructor<double, double, double, double, double>();
    //fan203
    class_<Fan203>("Fan203")
        .constructor<FanRatedInfo, PlaneData, BaseGasDensity, FanShaftPower>()
        .function("calculate", &Fan203::calculate);
    class_<Fan203::Output>("Fsat203Output")
        .constructor<double, double, double, Fan203::Results, Fan203::Results>();

    // register_vector<TraversePlane>("TraversePlaneVector");
    register_vector<double>("DoubleVector");
}


//getBaseGasDensityRelativeHumidity
//getBaseGasDensityDewPoint
//getBaseGasDensityWetBulb
EMSCRIPTEN_BINDINGS(base_gas_density)
{
    class_<BaseGasDensity>("BaseGasDensity")
        .constructor<double, double, double, double, BaseGasDensity::GasType>()
        .constructor<double, double, double, double, BaseGasDensity::GasType, BaseGasDensity::InputType, double>()
        .constructor<double, double, double, double, BaseGasDensity::GasType, BaseGasDensity::InputType, double, double>()
        .function("getGasDensity", &BaseGasDensity::getGasDensity);
}

//getVelocityPressureData

//getPlaneResults

//fanCurve

//optimalFanEfficiency

//compressibilityFactor
EMSCRIPTEN_BINDINGS(compressibility_factor)
{
    class_<CompressibilityFactor>("CompressibilityFactor")
        .constructor<double, double, double, double, double, double>()
        .function("calculate", &CompressibilityFactor::calculate);
}