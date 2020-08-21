#include "calculator/losses/Atmosphere.h"
#include "calculator/losses/AuxiliaryPower.h"
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
// energyInputEAF
// energyInputExhaustGasLosses
// exhaustGasEAF
// flueGasLossesByVolume
// flueGasByVolumeCalculateHeatingValue
// flueGasLossesByMass
// flueGasByMassCalculateHeatingValue
// flueGasCalculateExcessAir
// flueGasCalculateO2
// flueGasByMassCalculateO2
// flueGasByMassCalculateExcessAir
// gasCoolingLosses
// gasLoadChargeMaterial
// leakageLosses
// liquidCoolingLosses
// liquidLoadChargeMaterial
// openingLossesCircular
// openingLossesQuad
// viewFactorCalculation
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

