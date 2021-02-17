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

#ifndef AMO_TOOLS_SUITE_WATERHEATINGUSINGEXHAUST_H
#define AMO_TOOLS_SUITE_WATERHEATINGUSINGEXHAUST_H

class WaterHeatingUsingExhaust {
public:
    struct Output
    {
        Output(double recoveredHeat, double hotWaterFlow, double tonsRefrigeration, double capacityChiller, double electricalEnergy) :
                recoveredHeat(recoveredHeat), hotWaterFlow(hotWaterFlow), tonsRefrigeration(tonsRefrigeration), capacityChiller(capacityChiller), electricalEnergy(electricalEnergy) {}

        Output() = default;
        double recoveredHeat = 0, hotWaterFlow = 0, tonsRefrigeration = 0, capacityChiller = 0, electricalEnergy = 0;
    };

    /**
     * @param no arguments
     */
    WaterHeatingUsingExhaust(){}

    /**
     *
     * @param availableHeat double
     * @param heatInput double
     * @param hxEfficiency double
     * @param chillerInTemperature double
     * @param chillerOutTemperature double
     * @param copChiller double
     * @param chillerEfficiency double
     * @param copCompressor double
     * @return Output
     * @param recoveredHeat
     * @param hotWaterFlow
     * @param tonsRefrigeration
     * @param capacityChiller
     * @param electricalEnergy
     *
     */
    Output calculate(const double availableHeat, const double heatInput, const double hxEfficiency,
                                               const double chillerInTemperature, const double chillerOutTemperature,
                                               const double copChiller, const double chillerEfficiency, const double copCompressor);
};

#endif //AMO_TOOLS_SUITE_WATERHEATINGUSINGEXHAUST_H
