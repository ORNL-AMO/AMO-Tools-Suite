/**
 * @file
 * @brief Calculator for total energy loss for gas, including air
 *
 * This contains the inputs for calculating energy loss due to air or gas
 * total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_GASCOOLINGLOSSES_H
#define AMO_SUITE_GASCOOLINGLOSSES_H

/**
 * Gas Cooling Losses class
 * Contains all of the properties of a cooling system and its gas media.
 * Used to calculate how much heat loss is caused by the cooling components and their cooling media (a gas).
 */
class GasCoolingLosses {
public:
    /**
     * Constructor for the gas cooling losses (including air) with all inputs specified
     *
     * @param flowRate double, Air or gas volumetric flow rate in SCFM (ft³/min)
     * @param initialTemperature double, Inlet temperature of air or gas in °F
     * @param finalTemperature double, Outlet temperature of air or gas in °F
     * @param specificHeat double, Specific heat of gas or air at average air temperature in Btu/(scf*°F)
     * @param correctionFactor double, Correction factor - unitless
     *
     * */


    GasCoolingLosses(const double flowRate, const double initialTemperature, const double finalTemperature,
                     const double specificHeat, const double correctionFactor, const double gasDensity)
            : flowRate(flowRate),
              initialTemperature(initialTemperature),
              finalTemperature(finalTemperature),
              specificHeat(specificHeat),
              correctionFactor(correctionFactor),
              gasDensity(gasDensity) {}

    /**
     * Gets the total heat loss
     * @return double, heat loss in btu/hr
     */
    double getHeatLoss() const;

private:
    const double flowRate, initialTemperature, finalTemperature, specificHeat, correctionFactor, gasDensity;
};
#endif //AMO_SUITE_GASCOOLINGLOSSES_H
