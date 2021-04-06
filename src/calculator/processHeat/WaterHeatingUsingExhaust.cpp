/**
 * @file
 * @brief Calculate energy savings from using exhaust gas (waste) heat to provide energy for an absorption chiller in place of a compressor.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#include "calculator/processHeat/WaterHeatingUsingExhaust.h"

WaterHeatingUsingExhaust::Output WaterHeatingUsingExhaust::calculate(const double availableHeat, const double heatInput, const double hxEfficiency,
                                           const double chillerInTemperature, const double chillerOutTemperature,
                                           const double copChiller, const double chillerEfficiency, const double copCompressor)
{
    const double recoveredHeat = (1-availableHeat)*heatInput*hxEfficiency;
    const double hotWaterFlow = recoveredHeat / ((chillerInTemperature - chillerOutTemperature) * 8.335);
    const double tonsRefrigeration = recoveredHeat * copChiller/12000;
    const double capacityChiller = tonsRefrigeration * chillerEfficiency;
    const double electricalEnergy = recoveredHeat * copChiller * chillerEfficiency/(copCompressor);

    return Output(recoveredHeat, hotWaterFlow, tonsRefrigeration, capacityChiller, electricalEnergy);
}
