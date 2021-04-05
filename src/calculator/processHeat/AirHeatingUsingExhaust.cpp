/**
 * @file
 * @brief Estimate maximum air flow that can be heated by using exhaust gas heat of flue gases from a furnace or oven or a boiler.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#include <algorithm>
#include "calculator/processHeat/AirHeatingUsingExhaust.h"

AirHeatingUsingExhaust::Output AirHeatingUsingExhaust::calculate(const double flueTemperature, const double excessAir, const double fireRate,
                                                                 const double airflow, const double inletTemperature,
                                                                 const double heaterEfficiency, const double hxEfficiency, const double operatingHours) {
    const double heatCapacityFlue = (fireRate * 1000000 * ((1+ excessAir)* stoichAir/32 +1)* flueTemperature/ fuelHeatingValue/ 1000) * 0.021;
    const double heatCapacityAir = 0.0186 * airflow * 60;
    const double hxColdAir = hxEfficiency * std::min(heatCapacityAir, heatCapacityFlue) * (flueTemperature - inletTemperature);
    const double hxOutletExhaust = flueTemperature - hxColdAir/heatCapacityFlue;
    const double energySavings = operatingHours * hxColdAir/heaterEfficiency/1000000;

    return Output(hxColdAir, hxOutletExhaust, energySavings, heatCapacityFlue, heatCapacityAir);
}