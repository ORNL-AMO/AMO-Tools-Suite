#include "calculator/losses/WaterAssessment.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(waterAssessment_class)
{
    class_<WaterAssessment::ProcessWaterUseOutput>("ProcessWaterUseOutput")
        .property("recirculatedWater", &WaterAssessment::ProcessWaterUseOutput::recirculatedWater)
        .property("incomingWater", &WaterAssessment::ProcessWaterUseOutput::incomingWater)
        .property("wasteDischargedAndRecycledOther", &WaterAssessment::ProcessWaterUseOutput::wasteDischargedAndRecycledOther);

    class_<WaterAssessment::CoolingTowerLossOutput>("CoolingTowerLossOutput")
        .property("grossWaterUse", &WaterAssessment::CoolingTowerLossOutput::grossWaterUse)
        .property("evaporationLoss", &WaterAssessment::CoolingTowerLossOutput::evaporationLoss)
        .property("cycleOfConcentration", &WaterAssessment::CoolingTowerLossOutput::cycleOfConcentration)
        .property("makeupWater", &WaterAssessment::CoolingTowerLossOutput::makeupWater)
        .property("blowdownLoss", &WaterAssessment::CoolingTowerLossOutput::blowdownLoss);

    class_<WaterAssessment::BoilerWaterLossOutput>("BoilerWaterLossOutput")
        .property("cycleOfConcentration", &WaterAssessment::BoilerWaterLossOutput::cycleOfConcentration)
        .property("grossWaterUse", &WaterAssessment::BoilerWaterLossOutput::grossWaterUse)
        .property("makeupWater", &WaterAssessment::BoilerWaterLossOutput::makeupWater)
        .property("steamLoss", &WaterAssessment::BoilerWaterLossOutput::steamLoss)
        .property("blowdownLoss", &WaterAssessment::BoilerWaterLossOutput::blowdownLoss)
        .property("condensateReturn", &WaterAssessment::BoilerWaterLossOutput::condensateReturn)
        .property("rateOfRecirculation", &WaterAssessment::BoilerWaterLossOutput::rateOfRecirculation);

    class_<WaterAssessment>("WaterAssessment")
        .constructor<>()
        .function("calculateProcessWaterUse", &WaterAssessment::calculateProcessWaterUse)
        .function("calculateCoolingTowerLoss", &WaterAssessment::calculateCoolingTowerLoss)
        .function("calculateBoilerWaterLosses", &WaterAssessment::calculateBoilerWaterLosses)
        .function("calculateKitchenRestroomGrossWaterUse", &WaterAssessment::calculateKitchenRestroomGrossWaterUse)
        .function("calculateLandscapingGrossWaterUse", &WaterAssessment::calculateLandscapingGrossWaterUse)
        .function("calculateHeatEnergyInDischarge", &WaterAssessment::calculateHeatEnergyInDischarge)
        .function("calculateAddedMotorEnergyUse", &WaterAssessment::calculateAddedMotorEnergyUse);
}