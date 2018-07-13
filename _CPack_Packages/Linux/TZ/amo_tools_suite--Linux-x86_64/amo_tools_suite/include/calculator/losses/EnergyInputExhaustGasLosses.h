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
 * Energy Input Exhaust Gas Losses
 * Used to calculate the fuel heat that is delivered to the oven/furnace
 */
class EnergyInputExhaustGasLosses {
public:
    /**
     * Constructor for the energy input - exhaust gas losses - Will calculate availableHeat given input parameters
     * and calculate heatDelivered and exhaustGasLosses
     * @param excessAir double, excess air as %
     * @param combustionAirTemp double, temperature of combustion air in °F
     * @param exhaustGasTemp double, temperature of exhaust gas in °F
     * @param totalHeatInput optional double, total heat input from all sources of heat supplied in Btu/hr, if this is zero, available heat will be 100%
     * */
    EnergyInputExhaustGasLosses(const double excessAir, const double combustionAirTemp, const double exhaustGasTemp,
                                const double totalHeatInput = 1)
		    :
		      excessAir(excessAir / 100), heat(95 - 0.025 * exhaustGasTemp),
		      specificHeatAir(0.017828518 + 0.000002556 * combustionAirTemp),
		      airCorrection(-((-1.078913827 + specificHeatAir * exhaustGasTemp) * this->excessAir)),
		      combustionAirCorrection((-1.078913827 + specificHeatAir * combustionAirTemp) * (1 + this->excessAir)),
		      availableHeat((!totalHeatInput) ? 100 : heat + airCorrection + combustionAirCorrection),
		      heatDelivered(totalHeatInput * availableHeat / 100),
		      exhaustGasLosses(heatDelivered * (100 - availableHeat) / availableHeat)
    {}

    double getHeatDelivered() const { return heatDelivered; };

    double getExhaustGasLosses() const { return exhaustGasLosses; };

	double getAvailableHeat() const { return availableHeat; };

private:
    const double excessAir, heat, specificHeatAir, airCorrection;
	const double combustionAirCorrection, availableHeat, heatDelivered, exhaustGasLosses;
};

#endif //AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H
