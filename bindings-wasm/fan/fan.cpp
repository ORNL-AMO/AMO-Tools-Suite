
#include "results/Results.h"
#include "results/InputData.h"
#include "fans/Fan203.h"
#include "fans/CompressibilityFactor.h"
#include "fans/FanCurve.h"
#include "fans/Planar.h"
#include "fans/FanShaftPower.h"
#include "fans/OptimalFanEfficiency.h"
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
    class_<TraversePlane, base<VelocityPressureTraverseData>>("TraversePlane") // Also inherits from Planar (multiple inheritance?)
        .constructor<double, double, double, double, double, std::vector<std::vector<double>>>();
        //.function("getPv3Value", &VelocityPressureTraverseData::getPv3Value)
        //.function("get75PercentRule", &VelocityPressureTraverseData::get75percentRule);
    register_vector<TraversePlane>("TraversePlaneVector");
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

    register_vector<double>("DoubleVector");
    register_vector<std::vector<double>>("DoubleVector2D");
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
EMSCRIPTEN_BINDINGS(velocity_pressure_data)
{
    class_<VelocityPressureTraverseData>("VelocityPressureTraverseData")
        .function("getPv3Value", &VelocityPressureTraverseData::getPv3Value)
        .function("get75percentRule", &VelocityPressureTraverseData::get75percentRule);
}

//getPlaneResults
EMSCRIPTEN_BINDINGS(plane_results)
{
    class_<PlaneData::NodeBinding>("PlaneDataNodeBinding")
        .function("calculate", &PlaneData::NodeBinding::calculate);
    function("PlaneDataNodeBindingCalculate", &PlaneData::NodeBinding::calculate);
    class_<PlaneData::NodeBinding::Data>("PlaneDataNodeBindingData")
        .constructor<double, double, double, double, double>()
        .property("gasDensity", &PlaneData::NodeBinding::Data::gasDensity)
        .property("gasVelocity", &PlaneData::NodeBinding::Data::gasVelocity)
        .property("gasVolumeFlowRate", &PlaneData::NodeBinding::Data::gasVolumeFlowRate)
        .property("gasVelocityPressure", &PlaneData::NodeBinding::Data::gasVelocityPressure)
        .property("gasTotalPressure", &PlaneData::NodeBinding::Data::gasTotalPressure);
    register_vector<PlaneData::NodeBinding::Data>("PlaneDataNodeBindingDataVector");
    class_<PlaneData::NodeBinding::DataFlange, base<PlaneData::NodeBinding::Data>>("PlaneDataNodeBindingDataFlange")
        .constructor<double, double, double, double, double, double>()
        .property("staticPressure", &PlaneData::NodeBinding::DataFlange::staticPressure);
    class_<PlaneData::NodeBinding::Output>("PlaneDataNodeBindingOutput")
        .constructor<PlaneData>()
        .property("fanInletFlange", &PlaneData::NodeBinding::Output::fanInletFlange)
        .property("fanOrEvaseOutletFlange", &PlaneData::NodeBinding::Output::fanOrEvaseOutletFlange)
        .property("flowTraverse", &PlaneData::NodeBinding::Output::flowTraverse)
        .property("inletMstPlane", &PlaneData::NodeBinding::Output::inletMstPlane)
        .property("outletMstPlane", &PlaneData::NodeBinding::Output::outletMstPlane)
        .property("addlTravPlanes", &PlaneData::NodeBinding::Output::addlTravPlanes);
}

//fanCurve

class Dummy
{
    public:
        Dummy(int x, double y)
        {
            this->x = x;
            this->y = y;
            this->z = 0;
        }
        Dummy(int x, int z)
        {
            this->x = x;
            this->y = 0.0;
            this->z = 0;
        }

    private:
        int x;
        double y;
        int z;
};

EMSCRIPTEN_BINDINGS(fan_curve)
{
    class_<Dummy>("Dummy")
        .constructor<int, double>();
        //.constructor<int, int>();
    //EMSCRIPTEN_BINDINGS(base_example) 
    //{
        //class_<BaseClass>("BaseClass");
        //class_<DerivedClass, base<BaseClass>>("DerivedClass");
    //}
    class_<FanCurve>("FanCurve")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, FanCurveData>()
        .function("calculate", &FanCurve::calculate);
    class_<FanCurveData>("FanCurveData")
        .constructor<FanCurveType, std::vector<FanCurveData::BaseCurve>>();
    /*
    // Cannot have overloaded constructors with the same number of arguments...
    class_<FanCurveData>("FanCurveData")
        .constructor<FanCurveType, std::vector<FanCurveData::BaseCurve>>()
        .constructor<FanCurveType, std::vector<FanCurveData::RatedPoint>>()
        .constructor<FanCurveType, std::vector<FanCurveData::BaseOperatingPoint>>();
    */
    /*
    // This doesn't work either
    class_<FanCurveData>("FanCurveData_BaseCurve")
        .constructor<FanCurveType, std::vector<FanCurveData::BaseCurve>>();
    class_<FanCurveData>("FanCurveData_RatedPoint")
        .constructor<FanCurveType, std::vector<FanCurveData::RatedPoint>>();
    class_<FanCurveData>("FanCurveData_BaseOperatingPoint")
        .constructor<FanCurveType, std::vector<FanCurveData::BaseOperatingPoint>>();
    */
    
    class_<FanCurveData::BaseCurve>("FanCurveDataBaseCurve")
        .constructor<double, double, double>()
        .property("flow", &FanCurveData::BaseCurve::flow)
        .property("pressure", &FanCurveData::BaseCurve::pressure)
        .property("power", &FanCurveData::BaseCurve::power);
    register_vector<FanCurveData::BaseCurve>("BaseCurveVector");
    class_<FanCurveData::RatedPoint, base<FanCurveData::BaseCurve>>("FanCurveDataRatedPoint")
        .constructor<double, double, double, double, double, double>()
        .property("density", &FanCurveData::RatedPoint::density)
        .property("speed", &FanCurveData::RatedPoint::speed)
        .property("speedCorrected", &FanCurveData::RatedPoint::speedCorrected);
    register_vector<FanCurveData::RatedPoint>("RatedPointVector");
    class_<FanCurveData::BaseOperatingPoint, base<FanCurveData::RatedPoint>>("FanCurveDataBaseOperatingPoint")
        .constructor<double, double, double, double, double, double, double, double, double>()
        .property("pressureBarometric", &FanCurveData::BaseOperatingPoint::pressureBarometric)
        .property("usePt1Factor", &FanCurveData::BaseOperatingPoint::usePt1Factor)
        .property("pt1", &FanCurveData::BaseOperatingPoint::pt1);
    register_vector<FanCurveData::BaseOperatingPoint>("BaseOperatingPointVector");
    class_<ResultData>("ResultData")
        .constructor<double, double, double, double>()
        .property("flow", &ResultData::flow)
        .property("pressure", &ResultData::pressure)
        .property("power", &ResultData::power)
        .property("efficiency", &ResultData::efficiency);
    register_vector<ResultData>("ResultDataVector");
}


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