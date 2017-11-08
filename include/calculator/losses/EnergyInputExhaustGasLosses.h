/**
 * @file
 * @brief Calculator for energy input - exhaust gas losses for a non-EAF electric furnace
 *
 * This contains the inputs for calculating energy input - exhaust gas losses in non-EAF electric furnaces.
 *
 * @author Autumn Ferree (ferreeak) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */
#ifndef AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H
#define AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H

/**
 * Available Heat class
 * Used to calculate the available heat
 */
class AvailableHeat {
public:
    /**
     *
     * Constructor for the available heat with all inputs specified
     *
     * @param excessAir double, excess air as %
     * @param combustionAirTemp double, temperature of combustion air in °F
     * @param exhaustGasTemp double, temperature of exhaust gas in °F
     *
     *
     * */
    AvailableHeat(double excessAir, double combustionAirTemp, double exhaustGasTemp);

    double getAvailableHeat() const { return availableHeat; };

private:
    const double excessAir;

    const double heat, specificHeatAir, airCorrection, combustionAirCorrection;

    // Out values
    const double availableHeat;
};

/**
 * Energy Input Exhaust Gas Losses
 * Used to calculate the fuel heat that is delivered to the oven/furnace
 */
class EnergyInputExhaustGasLosses {
public:
    /**
     *
     * Constructor for the energy input - exhaust gas losses with all inputs specified
     *
     * @param totalHeatInput double, total heat input from all sources of heat supplied in Btu/hr
     * @param electricalPowerInput double, electrical power input in kW
     * @param userAvailableHeat double, user defined available heat as %
     * @param otherLosses double, other losses in Btu/hr
     *
     *
     * */
    EnergyInputExhaustGasLosses(double totalHeatInput, double electricalPowerInput, double availableHeat,
                                double otherLosses);

    double getHeatDelivered() const { return heatDelivered; };

    double getExhaustGasLosses() const { return exhaustGasLosses; };

private:
    const double heatDelivered, exhaustGasLosses;
};

#endif //AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H
