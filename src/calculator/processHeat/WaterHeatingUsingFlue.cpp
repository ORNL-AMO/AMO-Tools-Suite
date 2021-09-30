/**
 * @file
 * @brief Calculate energy and cost savings from using flue gas (waste) heat to heat boiler feed water using non-condensing heat exchanger.
 *
 *
 *
 * @author Omer Aziz (omerb)
 *
 */

#include "calculator/processHeat/WaterHeatingUsingFlue.h"
#include "ssmt/SteamProperties.h"
#include "ssmt/SaturatedProperties.h"

WaterHeatingUsingFlue::Output WaterHeatingUsingFlue::calculate(GasCompositions gasCompositions, const double tempFlueGas, const double percO2, const double tempCombAir,
                                                               const double moistCombAir, const double ratingBoiler, const double prSteam, const double tempAmbientAir,
                                                               const double tempSteam, const double tempFW, const double percBlowDown, const double effHX,
                                                               const double opHours, const double costFuel, const double hhvFuel, const SteamCondition condSteam) {
    const auto res = gasCompositions.getProcessHeatProperties(tempFlueGas, percO2, tempCombAir, tempAmbientAir, moistCombAir);
    const double effBoiler = res.availableHeat;
    const double specificHeatFG = res.specificHeat;
    const double flowFlueGas = res.density * ratingBoiler * 1000000 / hhvFuel;

    const double enthalpySteam = condSteam == SteamCondition::Saturated ?
            SteamProperties(prSteam, SteamProperties::ThermodynamicQuantity::QUALITY, 1).calculate().specificEnthalpy :
            SteamProperties(prSteam, SteamProperties::ThermodynamicQuantity::TEMPERATURE, tempSteam).calculate().specificEnthalpy;
    const double enthalpyFW = SaturatedProperties(prSteam, tempFW).calculate().liquidSpecificEnthalpy;
    const double specificHeatFW =
            +0.000000000000326658 * pow(tempFW,6)
            -0.000000000838033377 * pow(tempFW,5)
            +0.000000883910920876 * pow(tempFW,4)
            -0.000490348083986228 * pow(tempFW,3)
            +0.150847712358072 * pow(tempFW,2)
            -24.3962399473808 * tempFW
            +1624.65179353148;

    const double flowSteam = (ratingBoiler * 1000000 * effBoiler * (1 - percBlowDown)) / ((enthalpySteam-enthalpyFW));
    const double flowFW = flowSteam * (1 + percBlowDown);
    const double heatCapacityFG  = specificHeatFG * flowFlueGas;
    const double heatCapacityFW = specificHeatFW * flowFW;
    const double heatCapacityMin = heatCapacityFG < heatCapacityFW ? heatCapacityFG : heatCapacityFW;
    const double ratingHeatRecFW = effHX * heatCapacityMin * (tempFlueGas - tempFW);
    const double tempFlueGasOut = tempFlueGas - ratingHeatRecFW / heatCapacityFG;
    const double tempFWOut = tempFW + ratingHeatRecFW / heatCapacityFW;
    const double energySavingsBoiler = ratingHeatRecFW / effBoiler * opHours / 1000000;

    return Output(flowFlueGas, effBoiler,
                  enthalpySteam, enthalpyFW, flowSteam,
                  flowFW, specificHeatFG, heatCapacityFG, specificHeatFW, heatCapacityFW,
                  heatCapacityMin, ratingHeatRecFW, tempFlueGasOut, tempFWOut,
                  energySavingsBoiler, energySavingsBoiler * costFuel);
}
