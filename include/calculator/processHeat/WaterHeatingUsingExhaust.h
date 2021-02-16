//
// Created by 7bo on 2/16/2021.
// Calculate energy savings from using exhaust gas (waste) heat to provide energy for an
// absorption chiller in place of a compressor
//

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

    WaterHeatingUsingExhaust(){}

    Output calculate(const double availableHeat, const double heatInput, const double hxEfficiency,
                                               const double chillerInTemperature, const double chillerOutTemperature,
                                               const double copChiller, const double chillerEfficiency, const double copCompressor);
};

#endif //AMO_TOOLS_SUITE_WATERHEATINGUSINGEXHAUST_H
