#include "calculator/processHeat/AirHeatingUsingExhaust.h"
#include "calculator/processHeat/CascadeHeatHighToLow.h"
#include "calculator/processHeat/WaterHeatingUsingExhaust.h"
#include "calculator/processHeat/WaterHeatingUsingSteam.h"
#include <emscripten/bind.h>
#include <string>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(processHeat_class)
{
    class_<AirHeatingUsingExhaust::Output>("AirHeatingUsingExhaustOutput")
        .property("hxColdAir", &AirHeatingUsingExhaust::Output::hxColdAir)
        .property("hxOutletExhaust", &AirHeatingUsingExhaust::Output::hxOutletExhaust)
        .property("energySavings", &AirHeatingUsingExhaust::Output::energySavings)
        .property("heatCapacityFlue", &AirHeatingUsingExhaust::Output::heatCapacityFlue)
        .property("heatCapacityAir", &AirHeatingUsingExhaust::Output::heatCapacityAir);

    class_<WaterHeatingUsingExhaust::Output>("WaterHeatingUsingExhaustOutput")
        .property("recoveredHeat", &WaterHeatingUsingExhaust::Output::recoveredHeat)
        .property("hotWaterFlow", &WaterHeatingUsingExhaust::Output::hotWaterFlow)
        .property("tonsRefrigeration", &WaterHeatingUsingExhaust::Output::tonsRefrigeration)
        .property("capacityChiller", &WaterHeatingUsingExhaust::Output::capacityChiller)
        .property("electricalEnergy", &WaterHeatingUsingExhaust::Output::electricalEnergy);

    class_<WaterHeatingUsingSteam::Output>("WaterHeatingUsingSteamOutput")
        .property("tempWaterOut", &WaterHeatingUsingSteam::Output::tempWaterOut)
        .property("bpTempWaterOut", &WaterHeatingUsingSteam::Output::bpTempWaterOut)
        .property("bpTempWarningFlag", &WaterHeatingUsingSteam::Output::bpTempWarningFlag)
        .property("flowByPassSteam", &WaterHeatingUsingSteam::Output::flowByPassSteam)
        .property("enthalpySteamIn", &WaterHeatingUsingSteam::Output::enthalpySteamIn)
        .property("enthalpySteamOut", &WaterHeatingUsingSteam::Output::enthalpySteamOut)
        .property("enthalpyMakeUpWater", &WaterHeatingUsingSteam::Output::enthalpyMakeUpWater)
        .property("energySavedDWH", &WaterHeatingUsingSteam::Output::energySavedDWH)
        .property("energySavedBoiler", &WaterHeatingUsingSteam::Output::energySavedBoiler)
        .property("waterSaved", &WaterHeatingUsingSteam::Output::waterSaved)
        .property("heatGainRate", &WaterHeatingUsingSteam::Output::heatGainRate);

    class_<CascadeHeatHighToLow::Output>("CascadeHeatHighToLowOutput")
        .property("priFlueVolume", &CascadeHeatHighToLow::Output::priFlueVolume)
        .property("hxEnergyRate", &CascadeHeatHighToLow::Output::hxEnergyRate)
        .property("eqEnergySupply", &CascadeHeatHighToLow::Output::eqEnergySupply)
        .property("effOpHours", &CascadeHeatHighToLow::Output::effOpHours)
        .property("energySavings", &CascadeHeatHighToLow::Output::energySavings)
        .property("costSavings", &CascadeHeatHighToLow::Output::costSavings)
        .property("hourlySavings", &CascadeHeatHighToLow::Output::hourlySavings);

    class_<AirHeatingUsingExhaust>("AirHeatingUsingExhaust")
        .constructor<GasCompositions>()
        .constructor<SolidLiquidFlueGasMaterial, bool>()
        .function("calculate", &AirHeatingUsingExhaust::calculate);

    class_<WaterHeatingUsingExhaust>("WaterHeatingUsingExhaust")
        .constructor<>()
        .function("calculate", &WaterHeatingUsingExhaust::calculate);

    class_<WaterHeatingUsingSteam>("WaterHeatingUsingSteam")
        .constructor<>()
        .function("calculate", &WaterHeatingUsingSteam::calculate);

    class_<CascadeHeatHighToLow>("CascadeHeatHighToLow")
        .constructor<GasCompositions, double, double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &CascadeHeatHighToLow::calculate);
}
