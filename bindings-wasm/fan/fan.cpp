
#include "results/Results.h"
#include "results/InputData.h"
#include "fans/Fan203.h"
#include "fans/CompressibilityFactor.h"
#include "fans/FanCurve.h"
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
        //.register_vector<TraversePlane>("TraversePlaneVector"); ???
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
    //const double fanEfficiencyTotalPressure, fanEfficiencyStaticPressure, fanEfficiencyStaticPressureRise;
	//const Results asTested, converted;
    class_<Fan203::Results>("Fsat203Results")
        .constructor<double, double, double, double, double, double>()
        .property("kpc", &Fan203::Results::kpc)
        .property("power", &Fan203::Results::power)
        .property("flow", &Fan203::Results::flow)
        .property("pressureTotal", &Fan203::Results::pressureTotal)
        .property("pressureStatic", &Fan203::Results::pressureStatic)
        .property("staticPressureRise", &Fan203::Results::staticPressureRise);
    class_<Fan203::Output>("Fsat203Output")
        .constructor<double, double, double, Fan203::Results, Fan203::Results>()
        .property("fanEfficiencyTotalPressure", &Fan203::Output::fanEfficiencyTotalPressure)
        .property("fanEfficiencyStaticPressure", &Fan203::Output::fanEfficiencyStaticPressure)
        .property("fanEfficiencyStaticPressureRise", &Fan203::Output::fanEfficiencyStaticPressureRise)
        .property("asTested", &Fan203::Output::asTested)
        .property("converted", &Fan203::Output::converted);
        /*
        .property("flow", &Fan203::Output::asTested.flow)
        .property("kpc", &Fan203::Output::asTested.kpc)
        .property("power", &Fan203::Output::asTested.power)
        .property("pressureStatic", &Fan203::Output::asTested.pressureStatic)
        .property("pressureTotal", &Fan203::Output::asTested.pressureTotal)
        .property("staticPressureRise", &Fan203::Output::asTested.staticPressureRise)
        .property("flowCorrected", &Fan203::Output::converted.flow)
        .property("kpcCorrected", &Fan203::Output::converted.kpc)
        .property("powerCorrected", &Fan203::Output::converted.power)
        .property("pressureStaticCorrected", &Fan203::Output::converted.pressureStatic)
        .property("pressureTotalCorrected", &Fan203::Output::converted.pressureTotal)
        .property("staticPressureRiseCorrected", &Fan203::Output::converted.staticPressureRise);
        */

    register_vector<double>("DoubleVector");
    register_vector<std::vector<double>>("DoubleVector2D");
    register_vector<TraversePlane>("TraversePlaneVector");
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
/*
FanCurve(const double density, const double densityCorrected, const double speed, const double speedCorrected,
	         const double pressureBarometric, const double pressureBarometricCorrected, const double pt1Factor,
	         const double gamma, const double gammaCorrected, const double area1, const double area2, FanCurveData data)
*/

/*
EMSCRIPTEN_BINDINGS(fan_curve)
{
    class_<FanCurve>("FanCurve")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, FanCurveData>()
        .function("calculate", &FanCurve::calculate);
    class_<FanCurveData>("FanCurveData")
        .constructor<FanCurveType const, std::vector<FanCurveData::BaseCurve>>() //BaseCurve
        .constructor<FanCurveType const, std::vector<FanCurveData::RatedPoint>>() //RatedPoint
        .constructor<FanCurveType const, std::vector<FanCurveData::BaseOperatingPoint>>(); //BaseOperatingPoint
    
    class_<FanCurveData::BaseCurve>("FanCurveDataBaseCurve")
        .constructor<const double, const double, const double>()
        .property("flow", &FanCurveData::BaseCurve::flow)
        .property("pressure", &FanCurveData::BaseCurve::pressure)
        .property("power", &FanCurveData::BaseCurve::power);
    class_<FanCurveData::RatedPoint>("FanCurveDataRatedPoint")
        .constructor<const double, const double, const double, const double, const double, const double>()
        //.property("flow", &FanCurveData::RatedPoint::flow)
        //.property("pressure", &FanCurveData::RatedPoint::pressure)
        //.property("power", &FanCurveData::RatedPoint::power)
        .property("density", &FanCurveData::RatedPoint::density)
        .property("speed", &FanCurveData::RatedPoint::speed)
        .property("speedCorrected", &FanCurveData::RatedPoint::speedCorrected);
    class_<FanCurveData::BaseOperatingPoint>("FanCurveDataBaseOperatingPoint")
        .constructor<const double, const double, const double, const double, const double, const double, const double, const double, const double>()
        //.property("flow", &FanCurveData::BaseOperatingPoint::flow)
        //.property("pressure", &FanCurveData::BaseOperatingPoint::pressure)
        //.property("power", &FanCurveData::BaseOperatingPoint::power)
        //.property("density", &FanCurveData::BaseOperatingPoint::density)
        //.property("speed", &FanCurveData::BaseOperatingPoint::speed)
        //.property("speedCorrected", &FanCurveData::BaseOperatingPoint::speedCorrected)
        .property("pressureBarometric", &FanCurveData::BaseOperatingPoint::pressureBarometric)
        .property("usePt1Factor", &FanCurveData::BaseOperatingPoint::usePt1Factor)
        .property("pt1", &FanCurveData::BaseOperatingPoint::pt1);
    

    
    //value_object<FanCurveData::BaseCurve>("BaseCurve")
        //.field("flow", &FanCurveData::BaseCurve::flow)
        //.field("pressure", &FanCurveData::BaseCurve::pressure)
        //.field("power", &FanCurveData::BaseCurve::power);
    //value_object<FanCurveData::RatedPoint>("RatedPoint")
        //.field("flow", &FanCurveData::RatedPoint::flow)
        //.field("pressure", &FanCurveData::RatedPoint::pressure)
        //.field("power", &FanCurveData::RatedPoint::power)
        //.field("density", &FanCurveData::RatedPoint::density)
        //.field("speed", &FanCurveData::RatedPoint::speed)
        //.field("speedCorrected", &FanCurveData::RatedPoint::speedCorrected);
    //value_object<FanCurveData::BaseOperatingPoint>("BaseOperatingPoint")
        //.field("flow", &FanCurveData::BaseOperatingPoint::flow)
        //.field("pressure", &FanCurveData::BaseOperatingPoint::pressure)
        //.field("power", &FanCurveData::BaseOperatingPoint::power)
        //.field("density", &FanCurveData::BaseOperatingPoint::density)
        //.field("speed", &FanCurveData::BaseOperatingPoint::speed)
        //.field("speedCorrected", &FanCurveData::BaseOperatingPoint::speedCorrected)
        //.field("pressureBarometric", &FanCurveData::BaseOperatingPoint::pressureBarometric)
        //.field("usePt1Factor", &FanCurveData::BaseOperatingPoint::usePt1Factor)
        //.field("pt1", &FanCurveData::BaseOperatingPoint::pt1);

    class_<ResultData>("ResultData")
        .constructor<const double, const double, const double, const double>();

    //register_vector<FanCurveData::BaseCurve>("BaseCurveVector");
    //register_vector<FanCurveData::RatedPoint>("RatedPointVector");
    //register_vector<FanCurveData::BaseOperatingPoint>("BaseOperatingPointVector");

}
*/

//optimalFanEfficiency
EMSCRIPTEN_BINDINGS(optimal_fan_efficiency)
{
    class_<OptimalFanEfficiency>("OptimalFanEfficiency")
        .constructor<OptimalFanEfficiency::FanType, double, double, double, double, double>()
        .function("calculate", &OptimalFanEfficiency::calculate);
}

//compressibilityFactor
EMSCRIPTEN_BINDINGS(compressibility_factor)
{
    class_<CompressibilityFactor>("CompressibilityFactor")
        .constructor<double, double, double, double, double, double>()
        .function("calculate", &CompressibilityFactor::calculate);
}