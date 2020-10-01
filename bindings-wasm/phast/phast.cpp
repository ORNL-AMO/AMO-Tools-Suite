#include "calculator/losses/Atmosphere.h"
#include "calculator/losses/AuxiliaryPower.h"
#include "calculator/losses/FixtureLosses.h"
#include "calculator/losses/EnergyInputEAF.h"
#include "calculator/losses/EnergyInputExhaustGasLosses.h"
#include "calculator/losses/ExhaustGasEAF.h"
#include "calculator/losses/GasFlueGasMaterial.h"
#include "calculator/losses/SolidLiquidFlueGasMaterial.h"
#include "calculator/losses/GasCoolingLosses.h"
#include "calculator/losses/GasLoadChargeMaterial.h"
#include "calculator/losses/LoadChargeMaterial.h"
#include "calculator/losses/LeakageLosses.h"
#include "calculator/losses/LiquidCoolingLosses.h"
#include "calculator/losses/LiquidLoadChargeMaterial.h"
#include "calculator/losses/OpeningLosses.h"
#include "calculator/losses/SlagOtherMaterialLosses.h"
#include "calculator/losses/SolidLoadChargeMaterial.h"
#include "calculator/losses/WallLosses.h"
#include "calculator/losses/WaterCoolingLosses.h"
#include "calculator/furnace/EfficiencyImprovement.h"
#include "calculator/furnace/EnergyEquivalency.h"
#include "calculator/furnace/FlowCalculationsEnergyUse.h"
#include "calculator/furnace/O2Enrichment.h"
#include "calculator/furnace/HumidityRatio.h"
#include <emscripten/bind.h>
using namespace emscripten;

//atmosphere
//getTotalHeat()
EMSCRIPTEN_BINDINGS(atmosphere)
{
    class_<Atmosphere>("Atmosphere")
        .constructor<double, double, double, double, double>()
        .function("getTotalHeat", &Atmosphere::getTotalHeat);
}
//auxiliaryPowerLoss
//getPowerUsed()
EMSCRIPTEN_BINDINGS(auxiliaryPowerLoss)
{
    // motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime
    class_<AuxiliaryPower>("AuxiliaryPower")
        .constructor<double, double, double, double, double>()
        .function("getPowerUsed", &AuxiliaryPower::getPowerUsed);
}
// fixtureLosses
// getHeatLoss()
EMSCRIPTEN_BINDINGS(fixtureLosses)
{
    // specificHeat, feedRate, initialTemperature, finalTemperature, correctionFactor
    class_<FixtureLosses>("FixtureLosses")
        .constructor<double, double, double, double, double>()
        .function("getHeatLoss", &FixtureLosses::getHeatLoss);
}
// energyInputEAF
EMSCRIPTEN_BINDINGS(energyInputEAF)
{
    // naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse,
    //    electrodeHeatingValue, otherFuels, electricityInput
    class_<EnergyInputEAF>("EnergyInputEAF")
        .constructor<double, double, double, double, double, double, double>()
        .function("getTotalChemicalEnergyInput", &EnergyInputEAF::getTotalChemicalEnergyInput)
        .function("getHeatDelivered", &EnergyInputEAF::getHeatDelivered);
}
// energyInputExhaustGasLosses
EMSCRIPTEN_BINDINGS(energyInputExhaustGasLosses)
{
    class_<EnergyInputExhaustGasLosses>("EnergyInputExhaustGasLosses")
        .constructor<double, double, double, double>()
        .function("getHeatDelivered", &EnergyInputExhaustGasLosses::getHeatDelivered)
        .function("getExhaustGasLosses", &EnergyInputExhaustGasLosses::getExhaustGasLosses)
        .function("getAvailableHeat", &EnergyInputExhaustGasLosses::getAvailableHeat);
}
// exhaustGasEAF
EMSCRIPTEN_BINDINGS(exhaustGasEAF)
{
    class_<ExhaustGasEAF>("ExhaustGasEAF")
        .constructor<double, double, double, double, double, double>()
        .function("getTotalHeatExhaust", &ExhaustGasEAF::getTotalHeatExhaust);
}
EMSCRIPTEN_BINDINGS(flueGasLosses)
{

    // flueGasByVolumeCalculateHeatingValue
    // flueGasCalculateExcessAir
    // flueGasCalculateO2
    class_<GasCompositions>("GasCompositions")
        .constructor<std::string, double, double, double, double, double, double, double, double, double, double, double>()
        .function("getHeatingValue", &GasCompositions::getHeatingValue)
        .function("getHeatingValueVolume", &GasCompositions::getHeatingValueVolume)
        .function("getSpecificGravity", &GasCompositions::getSpecificGravity)
        .function("calculateExcessAir", &GasCompositions::calculateExcessAir)
        .function("calculateO2", &GasCompositions::calculateO2);

    // flueGasLossesByVolume
    class_<GasFlueGasMaterial>("GasFlueGasMaterial")
        .constructor<double, double, double, GasCompositions, double>()
        .function("getHeatLoss", &GasFlueGasMaterial::getHeatLoss);

    // flueGasLossesByMass
    // flueGasByMassCalculateHeatingValue
    // flueGasByMassCalculateO2
    // flueGasByMassCalculateExcessAir
    class_<SolidLiquidFlueGasMaterial>("SolidLiquidFlueGasMaterial")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double, double, double>()
        .constructor()
        .function("getHeatLoss", &SolidLiquidFlueGasMaterial::getHeatLoss)
        .function("calculateHeatingValueFuel", &SolidLiquidFlueGasMaterial::calculateHeatingValueFuel)
        .function("calculateFlueGasO2", &SolidLiquidFlueGasMaterial::calculateFlueGasO2)
        .function("calculateExcessAirFromFlueGasO2", &SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2);
}

// gasCoolingLosses
EMSCRIPTEN_BINDINGS(gasCoolingLosses)
{
    class_<GasCoolingLosses>("GasCoolingLosses")
        .constructor<double, double, double, double, double, double>()
        .function("getHeatLoss", &GasCoolingLosses::getHeatLoss);
}
// gasLoadChargeMaterial
EMSCRIPTEN_BINDINGS(gasLoadChargeMaterial)
{
    class_<GasLoadChargeMaterial>("GasLoadChargeMaterial")
        .constructor<LoadChargeMaterial::ThermicReactionType, double, double, double, double, double, double, double, double, double>()
        .function("getTotalHeat", &GasLoadChargeMaterial::getTotalHeat);
}
// leakageLosses
EMSCRIPTEN_BINDINGS(leakageLosses)
{
    class_<LeakageLosses>("LeakageLosses")
        .constructor<double, double, double, double, double, double, double>()
        .function("getExfiltratedGasesHeatContent", &LeakageLosses::getExfiltratedGasesHeatContent);
}
// liquidCoolingLosses
EMSCRIPTEN_BINDINGS(liquidCoolingLosses)
{
    class_<LiquidCoolingLosses>("LiquidCoolingLosses")
        .constructor<double, double, double, double, double, double>()
        .function("getHeatLoss", &LiquidCoolingLosses::getHeatLoss);
}
// liquidLoadChargeMaterial
EMSCRIPTEN_BINDINGS(liquidLoadChargeMaterial)
{
    class_<LiquidLoadChargeMaterial>("LiquidLoadChargeMaterial")
        .constructor<LoadChargeMaterial::ThermicReactionType, double, double, double, double, double, double, double, double, double, double, double>()
        .function("getTotalHeat", &LiquidLoadChargeMaterial::getTotalHeat);
}
// openingLossesCircular
// openingLossesQuad
// viewFactorCalculation
EMSCRIPTEN_BINDINGS(openingLosses)
{
    class_<OpeningLosses>("OpeningLosses")
        .constructor<double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double>()
        .constructor()
        .function("getHeatLoss", &OpeningLosses::getHeatLoss)
        .function("calculateViewFactorQuad", select_overload<double(double, double, double)>(&OpeningLosses::calculateViewFactor))
        .function("calculateViewFactorCircular", select_overload<double(double, double)>(&OpeningLosses::calculateViewFactor));
}
// slagOtherMaterialLosses
EMSCRIPTEN_BINDINGS(slagOtherMaterialLosses)
{
    class_<SlagOtherMaterialLosses>("SlagOtherMaterialLosses")
        .constructor<double, double, double, double, double>()
        .function("getHeatLoss", &SlagOtherMaterialLosses::getHeatLoss);
}
// solidLoadChargeMaterial
EMSCRIPTEN_BINDINGS(solidLoadChargeMaterial)
{
    class_<SolidLoadChargeMaterial>("SolidLoadChargeMaterial")
        .constructor<LoadChargeMaterial::ThermicReactionType, double, double, double, double, double, double, double, double, double, double, double, double, double, double>()
        .function("getTotalHeat", &SolidLoadChargeMaterial::getTotalHeat);
}
// wallLosses
EMSCRIPTEN_BINDINGS(wallLosses)
{
    class_<WallLosses>("WallLosses")
        .constructor<double, double, double, double, double, double, double>()
        .function("getHeatLoss", &WallLosses::getHeatLoss);
}
// waterCoolingLosses
EMSCRIPTEN_BINDINGS(waterCoolingLosses)
{
    class_<WaterCoolingLosses>("WaterCoolingLosses")
        .constructor<double, double, double, double>()
        .function("getHeatLoss", &WaterCoolingLosses::getHeatLoss);
}
// efficiencyImprovement
EMSCRIPTEN_BINDINGS(efficiencyImprovement)
{
    class_<EfficiencyImprovement>("EfficiencyImprovement")
        .constructor<double, double, double, double, double, double, double>()
        .function("getCurrentExcessAir", &EfficiencyImprovement::getCurrentExcessAir)
        .function("getNewExcessAir", &EfficiencyImprovement::getNewExcessAir)
        .function("getCurrentAvailableHeat", &EfficiencyImprovement::getCurrentAvailableHeat)
        .function("getNewAvailableHeat", &EfficiencyImprovement::getNewAvailableHeat)
        .function("getNewFuelSavings", &EfficiencyImprovement::getNewFuelSavings)
        .function("getNewEnergyInput", &EfficiencyImprovement::getNewEnergyInput);
}
// energyEquivalencyElectric
EMSCRIPTEN_BINDINGS(energyEquivalencyElectric)
{
    class_<ElectricalEnergyEquivalency>("ElectricalEnergyEquivalency")
        .constructor<double, double, double>()
        .function("getElectricalHeatInput", &ElectricalEnergyEquivalency::getElectricalHeatInput);
}

// energyEquivalencyFuel
EMSCRIPTEN_BINDINGS(energyEquivalencyFuel)
{
    class_<FuelFiredEnergyEquivalency>("FuelFiredEnergyEquivalency")
        .constructor<double, double, double>()
        .function("getFuelFiredHeatInput", &FuelFiredEnergyEquivalency::getFuelFiredHeatInput);
}

// flowCalculations
EMSCRIPTEN_BINDINGS(flowCalculations)
{
    class_<FlowCalculationsEnergyUse>("FlowCalculationsEnergyUse")
        .constructor<FlowCalculationsEnergyUse::Gas, double, double, double, FlowCalculationsEnergyUse::Section, double, double, double, double, double, double>()
        .function("getFlow", &FlowCalculationsEnergyUse::getFlow)
        .function("getHeatInput", &FlowCalculationsEnergyUse::getHeatInput)
        .function("getTotalFlow", &FlowCalculationsEnergyUse::getTotalFlow);
}

// o2Enrichment
EMSCRIPTEN_BINDINGS(o2Enrichment)
{
    class_<O2Enrichment>("O2Enrichment")
        .constructor<double, double, double, double, double, double, double, double, double>()
        .function("getAvailableHeat", &O2Enrichment::getAvailableHeat)
        .function("getAvailableHeatEnriched", &O2Enrichment::getAvailableHeatEnriched)
        .function("getFuelSavingsEnriched", &O2Enrichment::getFuelSavingsEnriched)
        .function("getFuelConsumptionEnriched", &O2Enrichment::getFuelConsumptionEnriched);
}

// humidityRatio
EMSCRIPTEN_BINDINGS(humidityRatio)
{
    class_<HumidityRatio>("HumidityRatio")
        .constructor<double, double, double, double>()
        .function("getHumidityRatioUsingRH", &HumidityRatio::getHumidityRatioUsingRH)
        .function("getHumidityRatioUsingWBT", &HumidityRatio::getHumidityRatioUsingWBT);
}
