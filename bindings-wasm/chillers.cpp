#include "chillers/CoolingTower.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(chillers_class)
{
    enum_<CoolingTower::FanControlSpeedType>("FanControlSpeedType")
        .value("One", CoolingTower::FanControlSpeedType::One)
        .value("Two", CoolingTower::FanControlSpeedType::Two)
        .value("Variable", CoolingTower::FanControlSpeedType::Variable);

    enum_<ChillerEfficiency::ChillerType>("ChillerType")
        .value("Centrifugal", ChillerEfficiency::ChillerType::Centrifugal)
        .value("Screw", ChillerEfficiency::ChillerType::Screw);

    enum_<ChillerEfficiency::CondenserCoolingType>("CondenserCoolingType")
        .value("Water", ChillerEfficiency::CondenserCoolingType::Water)
        .value("Air", ChillerEfficiency::CondenserCoolingType::Air);

    enum_<ChillerEfficiency::CompressorConfigType>("CompressorConfigType")
        .value("NoVFD", ChillerEfficiency::CompressorConfigType::NoVFD)
        .value("VFD", ChillerEfficiency::CompressorConfigType::VFD)
        .value("MagneticBearing", ChillerEfficiency::CompressorConfigType::MagneticBearing);

    class_<CoolingTowerMakeupWaterCalculator::Output>("CoolingTowerMakeupWaterCalculatorOutput")
        .property("wcBaseline", &CoolingTowerMakeupWaterCalculator::Output::wcBaseline)
        .property("wcModification", &CoolingTowerMakeupWaterCalculator::Output::wcModification)
        .property("waterSavings", &CoolingTowerMakeupWaterCalculator::Output::waterSavings);

    class_<CoolingTower::PowerEnergyConsumptionOutput>("PowerEnergyConsumptionOutput")
        .property("baselinePower", &CoolingTower::PowerEnergyConsumptionOutput::baselinePower)
        .property("baselineEnergy", &CoolingTower::PowerEnergyConsumptionOutput::baselineEnergy)
        .property("modPower", &CoolingTower::PowerEnergyConsumptionOutput::modPower)
        .property("modEnergy", &CoolingTower::PowerEnergyConsumptionOutput::modEnergy)
        .property("savingsEnergy", &CoolingTower::PowerEnergyConsumptionOutput::savingsEnergy);

    class_<ChillerEfficiency::StagingPowerConsumptionOutput>("StagingPowerConsumptionOutput")
        .property("baselinePowerList", &ChillerEfficiency::StagingPowerConsumptionOutput::baselinePowerList)
        .property("modPowerList", &ChillerEfficiency::StagingPowerConsumptionOutput::modPowerList)
        .property("baselineTotalPower", &ChillerEfficiency::StagingPowerConsumptionOutput::baselineTotalPower)
        .property("baselineTotalEnergy", &ChillerEfficiency::StagingPowerConsumptionOutput::baselineTotalEnergy)
        .property("modTotalPower", &ChillerEfficiency::StagingPowerConsumptionOutput::modTotalPower)
        .property("modTotalEnergy", &ChillerEfficiency::StagingPowerConsumptionOutput::modTotalEnergy)
        .property("savingsEnergy", &ChillerEfficiency::StagingPowerConsumptionOutput::savingsEnergy);

    class_<ChillerEfficiency::CapacityPowerEnergyConsumptionOutput>("CapacityPowerEnergyConsumptionOutput")
        .property("baselineActualCapacity", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::baselineActualCapacity)
        .property("baselineActualEfficiency", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::baselineActualEfficiency)
        .property("baselinePower", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::baselinePower)
        .property("baselineEnergy", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::baselineEnergy)
        .property("modActualCapacity", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::modActualCapacity)
        .property("modActualEfficiency", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::modActualEfficiency)
        .property("modPower", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::modPower)
        .property("modEnergy", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::modEnergy)
        .property("savingsEnergy", &ChillerEfficiency::CapacityPowerEnergyConsumptionOutput::savingsEnergy);

    class_<CoolingTowerWaterConservationData>("CoolingTowerWaterConservationData")
        .constructor<int, double>();

    class_<CoolingTowerOperatingConditionsData>("CoolingTowerOperatingConditionsData")
        .constructor<double, double, int, double>();

    class_<CoolingTowerMakeupWaterCalculator>("CoolingTowerMakeupWaterCalculator")
        .constructor<CoolingTowerOperatingConditionsData, CoolingTowerWaterConservationData, CoolingTowerWaterConservationData>()
        .function("calculate", &CoolingTowerMakeupWaterCalculator::calculate);

    function("BasinHeaterEnergyConsumption", &CoolingTower::BasinHeaterEnergyConsumption);
    function("FanEnergyConsumption", &CoolingTower::FanEnergyConsumption);

    function("ChillerCapacityEfficiency", &ChillerEfficiency::ChillerCapacityEfficiency);
    function("ChillerStagingEfficiency", &ChillerEfficiency::ChillerStagingEfficiency);
}
