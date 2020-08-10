#include "fans/Fan203.h"
#include "fans/OptimalFanEfficiency.h"
#include "fans/FanCurve.h"
#include "fans/Planar.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(fan_enums)
{
    enum_<BaseGasDensity::GasType>("GasType")
        .value("AIR", BaseGasDensity::GasType::AIR)
        .value("STANDARDAIR", BaseGasDensity::GasType::STANDARDAIR)
        .value("OTHERGAS", BaseGasDensity::GasType::OTHERGAS);

    enum_<BaseGasDensity::InputType>("BaseGasDensityInputType")
        .value("DewPoint", BaseGasDensity::InputType::DewPoint)
        .value("RelativeHumidity", BaseGasDensity::InputType::RelativeHumidity)
        .value("WetBulbTemp", BaseGasDensity::InputType::WetBulbTemp);

    enum_<OptimalFanEfficiency::FanType>("FanType")
        .value("AirfoilSISW", OptimalFanEfficiency::FanType::AirfoilSISW)
        .value("BackwardCurvedSISW", OptimalFanEfficiency::FanType::BackwardCurvedSISW)
        .value("RadialSISW", OptimalFanEfficiency::FanType::RadialSISW)
        .value("RadialTipSISW", OptimalFanEfficiency::FanType::RadialTipSISW)
        .value("BackwardInclinedSISW", OptimalFanEfficiency::FanType::BackwardInclinedSISW)
        .value("AirfoilDIDW", OptimalFanEfficiency::FanType::AirfoilDIDW)
        .value("BackwardCurvedDIDW", OptimalFanEfficiency::FanType::BackwardCurvedDIDW)
        .value("BackwardInclinedDIDW", OptimalFanEfficiency::FanType::BackwardInclinedDIDW)
        .value("VaneAxial", OptimalFanEfficiency::FanType::VaneAxial)
        .value("AirHandling", OptimalFanEfficiency::FanType::AirHandling)
        .value("MaterialHandling", OptimalFanEfficiency::FanType::MaterialHandling)
        .value("LongShavings", OptimalFanEfficiency::FanType::LongShavings);

    enum_<FanCurveData::CalculationType>("FanCurveDataCalculationType")
        .value("BaseCurve", FanCurveData::CalculationType::BaseCurve)
        .value("RatedPoint", FanCurveData::CalculationType::RatedPoint)
        .value("BaseOperatingPoint", FanCurveData::CalculationType::BaseOperatingPoint);

    enum_<FanCurveType>("FanCurveType")
        .value("FanStaticPressure", FanCurveType::FanStaticPressure)
        .value("FanTotalPressure", FanCurveType::FanTotalPressure)
        .value("StaticPressureRise", FanCurveType::StaticPressureRise);
}
