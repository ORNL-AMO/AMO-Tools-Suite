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

WaterHeatingUsingFlue::Output WaterHeatingUsingFlue::calculate(GasCompositions gasCompositions, const double tempFlueGasF, const double percO2, const double tempCombAirF,
                                                               const double moistCombAir, const double ratingBoiler, const double prSteam, const double tempAmbientAirF,
                                                               const double tempSteamF, const double tempFW, const double percBlowDown, const double effHX,
                                                               const double opHours, const double costFuel, const double hhvFuel, const SteamCondition condSteam, const double fuelTempF) {
    //Temp Conversion
    const double tempSteamK = TempFtoK(tempSteamF);
    const double tempFWK = TempFtoK(tempFW);
    const double tempFlueGasK = TempFtoK(tempFlueGasF);

    const auto res = gasCompositions.getProcessHeatProperties(tempFlueGasF, percO2, tempCombAirF, fuelTempF, tempAmbientAirF, moistCombAir);
    const double effBoiler = res.availableHeat;
    const double specificHeatFG = 4.1868 * res.specificHeat;
    const double flowFlueGas = 16.018463 * res.density * ratingBoiler * 1000000 / hhvFuel;

    const double enthalpySteam = condSteam == SteamCondition::Saturated ?
            SteamProperties(prSteam, SteamProperties::ThermodynamicQuantity::QUALITY, 1).calculate().specificEnthalpy :
            SteamProperties(prSteam, SteamProperties::ThermodynamicQuantity::TEMPERATURE, tempSteamK).calculate().specificEnthalpy;
    const double enthalpyFW = SaturatedProperties(prSteam, tempFWK).calculate().liquidSpecificEnthalpy;
    const double specificHeatFW =
            +0.000000000000326658 * pow(tempFWK,6)
            -0.000000000838033377 * pow(tempFWK,5)
            +0.000000883910920876 * pow(tempFWK,4)
            -0.000490348083986228 * pow(tempFWK,3)
            +0.150847712358072 * pow(tempFWK,2)
            -24.3962399473808 * tempFWK
            +1624.65179353148;

    const double flowSteam = (ratingBoiler * 1000000 * effBoiler * (1 - percBlowDown)) / ((enthalpySteam-enthalpyFW));
    const double flowFW = flowSteam * (1 + percBlowDown);
    const double heatCapacityFG  = specificHeatFG * flowFlueGas;
    const double heatCapacityFW = specificHeatFW * flowFW;
    const double heatCapacityMin = heatCapacityFG < heatCapacityFW ? heatCapacityFG : heatCapacityFW;
    const double ratingHeatRecFW = effHX * heatCapacityMin * (tempFlueGasK - tempFWK);
    const double tempFlueGasOut = tempFlueGasK - ratingHeatRecFW / heatCapacityFG;
    const double tempFWOut = tempFWK + ratingHeatRecFW / heatCapacityFW;
    const double energySavingsBoiler = ratingHeatRecFW / effBoiler * opHours / 1000000;

    return Output(flowFlueGas, effBoiler,
                  enthalpySteam, enthalpyFW, flowSteam,
                  flowFW, specificHeatFG, heatCapacityFG, specificHeatFW, heatCapacityFW,
                  heatCapacityMin, ratingHeatRecFW, tempFlueGasOut, tempFWOut,
                  energySavingsBoiler, energySavingsBoiler * costFuel);
}
