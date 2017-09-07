/**
 * @file
 * @brief Calculator for heat loss in an Electric Arc Furnace (EAF)
 *
 * This contains the inputs for calculating the heat loss for an Electric Arc
 * Furnace (EAF)
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_ENERGYINPUTEAF_H
#define AMO_TOOLS_SUITE_ENERGYINPUTEAF_H

/**
 * Energy Input for an Electric Arc Furnace class
 * Used to calculate the heat that is being supplied to an electric arc furnace.
 */
class EnergyInputEAF {
    public:
    /**
     *
     * Constructor for the energy input EAF heat loss with all inputs specified
     *
     * @param naturalGasHeatInput value of total heat input to the heating system (furnace/oven) from all
     *                              sources of heat supplied (natural gas, carbon, fuel oil, etc.)
     *                              measured in mm btu/cycle
     * @param naturalGasFlow natural gas flow measured in cu.ft/cycle
     * @param measuredOxygenFlow oxygen flow to the furnace measured in scfh
     * @param coalCarbonInjection mass of coal or carbon injection for the cycle measured in lbs/cycle
     * @param coalHeatingValue heating value for the coal or carbon injected measured in btu/lb
     * @param electrodeUse electrode use measured in lbs/cycle
     * @param electrodeHeatingValue electrode heating value measured in btu/lb
     * @param otherFuels heat supplied from other sources, if any, measured in mm btu/cycle
     * @param electricityInput total electric power supplied for the cycle measured in kwh/cycle
     *
     * @return nothing
     * **/

    EnergyInputEAF(const double naturalGasHeatInput, const double measuredOxygenFlow, const double coalCarbonInjection, const double coalHeatingValue,
                   const double electrodeUse, const double electrodeHeatingValue, const double otherFuels, const double electricityInput)
            : naturalGasHeatInput_(naturalGasHeatInput), measuredOxygenFlow_(measuredOxygenFlow),
              coalCarbonInjection_(coalCarbonInjection), coalHeatingValue_(coalHeatingValue),
              electrodeUse_(electrodeUse), electrodeHeatingValue_(electrodeHeatingValue),
              otherFuels_(otherFuels), electricityInput_(electricityInput)
    {}

    /**
     * Calculates the total chemical energy input
     *
     * @return double, total chemical energy input in mm btu/cycle
     */
    double getTotalChemicalEnergyInput();

    /**
     * Calculates the heat delivered to the EAF
     *
     * @return double, heat delivered to the EAF in btu/cycle
     */
    double getHeatDelivered();

private:
    const double naturalGasHeatInput_, measuredOxygenFlow_, coalCarbonInjection_, coalHeatingValue_, electrodeUse_;
    const double electrodeHeatingValue_, otherFuels_, electricityInput_;
};
#endif //AMO_TOOLS_SUITE_ENERGYINPUTEAF_H
