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
        .constructor<string, double, double, double, double, double, double, double, double, double, double, double>()
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
        .function("getHeatLoss", &SolidLiquidFlueGasMaterial::getHeatLoss)
        .function("calculateHeatingValueFuel", &SolidLiquidFlueGasMaterial::calculateHeatingValueFuel)
        .function("calculateFlueGasO2", &SolidLiquidFlueGasMaterial::calculateFlueGasO2)
        .function("calculateExcessAirFromFlueGasO2", &&SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2);
}

// gasCoolingLosses
EMSCRIPTEN_BINDINGS(gasCoolingLosses)
{
    class_<GasCoolingLosses>("GasCoolingLosses")
        .constructor<double, double, double, double, double>()
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
        .function("getTotalHeat", &LiquidCoolingLosses::getTotalHeat);
}
// openingLossesCircular
// openingLossesQuad
// viewFactorCalculation
EMSCRIPTEN_BINDINGS(openingLosses)
{
    class_<OpeningLosses>("OpeningLosses")
        .constructor<double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double>()
        .function("getHeatLoss", &OpeningLosses::getHeatLoss)
        .function("calculateViewFactor", &OpeningLosses::calculateViewFactor);
}
// slagOtherMaterialLosses
// solidLoadChargeMaterial
// wallLosses
// waterCoolingLosses
// efficiencyImprovement
// energyEquivalencyElectric
// energyEquivalencyFuel
// flowCalculations
// o2Enrichment
// humidityRatio
