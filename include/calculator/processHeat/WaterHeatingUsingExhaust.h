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
     * @param availableHeat double, units percentage / fraction
     * @param heatInput double, units Btu/hr
     * @param hxEfficiency double, units percentage / fraction
     * @param chillerInTemperature double, units F
     * @param chillerOutTemperature double, units F
     * @param copChiller double, units percentage / fraction
     * @param chillerEfficiency double, units percentage / fraction
     * @param copCompressor double, units percentage / fraction
     * @return Output
     * @param recoveredHeat, units btu/hr
     * @param hotWaterFlow, units gal/hr
     * @param tonsRefrigeration, units Tons
     * @param capacityChiller, units Tons
     * @param electricalEnergy, units btu/hr
     *
     */
    Output calculate(const double availableHeat, const double heatInput, const double hxEfficiency,
                                               const double chillerInTemperature, const double chillerOutTemperature,
                                               const double copChiller, const double chillerEfficiency, const double copCompressor);
};

#endif //AMO_TOOLS_SUITE_WATERHEATINGUSINGEXHAUST_H
