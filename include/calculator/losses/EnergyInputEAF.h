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
     * @param electrodeUse delectrode use measured in lbs/cycle
     * @param electrodeHeatingValue electrode heating value measured in btu/lb
     * @param otherFuels heat supplied from other sources, if any, measured in mm btu/cycle
     * @param electricityInput total electric power supplied for the cycle measured in kwh/cycle
     *
     * @return nothing
     *
     * */
    EnergyInputEAF(
            double naturalGasHeatInput,
            double naturalGasFlow,
            double measuredOxygenFlow,
            double coalCarbonInjection,
            double coalHeatingValue,
            double electrodeUse,
            double electrodeHeatingValue,
            double otherFuels,
            double electricityInput)
            : naturalGasHeatInput_(naturalGasHeatInput),
              naturalGasFlow_(naturalGasFlow),
              measuredOxygenFlow_(measuredOxygenFlow),
              coalCarbonInjection_(coalCarbonInjection),
              coalHeatingValue_(coalHeatingValue),
              electrodeUse_(electrodeUse),
              electrodeHeatingValue_(electrodeHeatingValue),
              otherFuels_(otherFuels),
              electricityInput_(electricityInput)

    {
        naturalGasHeat_ = 0.0;
        coalHeatContent_ = 0.0;
        electrodeHeatContent_ = 0.0;
        totalChemicalEnergyInput_ = 0.0;
        kwhCycle_ = 0.0;
        heatDelivered_ = 0.0;
        totalKwhPerCycle_ = 0.0;
    }

    EnergyInputEAF() = default;

    /**
     * Getter for the measured natural gas heat input
     *
     * @return double, measured natural gas heat input in mm btu/cycle
     */
    double getNaturalGasHeatInput() const {
        return naturalGasHeatInput_;
    }

    /**
     * Sets the measured natural gas heat input
     *
     * @param naturalGasHeatInput double, natural gas heat input in mm btu/cycle
     *
     * @return nothing
     */
    void setNaturalGasHeatInput(double naturalGasHeatInput) {
        naturalGasHeatInput_ = naturalGasHeatInput;
    }

    /**
     * Getter for the natural gas flow
     *
     * @return double, natural gas flow in cu.ft/cycle
     */
    double getNaturalGasFlow() const {
        return naturalGasFlow_;
    }

    /**
     * Sets the natural gas flow
     *
     * @param naturalGasFlow double, natural gas flow in cu.ft/cycle
     *
     * @return nothing
     */
    void setNaturalGasFlow(double naturalGasFlow) {
        naturalGasFlow_ = naturalGasFlow;
    }

    /**
     * Getter for the measured oxygen flow
     *
     * @return double, measured oxygen flow in scfh
     */
    double getMeasuredOxygenFlow() const {
        return measuredOxygenFlow_;
    }

    /**
     * Sets the measured oxygen flow
     *
     * @param measuredOxygenFlow double, oxygen flow in scfh
     *
     * @return nothing
     */
    void setMeasuredOxygenFlow(double measuredOxygenFlow) {
        measuredOxygenFlow_ = measuredOxygenFlow;
    }

    /**
     * Getter for the  coal-carbon injection for the cycle
     *
     * @return double, coal-carbon injection in lbs/cycle
     */
    double getCoalCarbonInjection() const {
        return coalCarbonInjection_;
    }

    /**
     * Sets the coal-carbon injection for the cycle
     *
     * @param coalCarbonInjection double, coal-carbon injection in lbs/cycle
     *
     * @return nothing
     */
    void setCoalCarbonInjection(double coalCarbonInjection) {
        coalCarbonInjection_ = coalCarbonInjection;
    }

    /**
     * Getter for the heating value of coal
     *
     * @return double, heating value of coal
     */
    double getCoalHeatingValue() const {
        return coalHeatingValue_;
    }

    /**
     * Sets the heating value of coal
     *
     * @param coalHeatingValue heating value of coal in btu/lb
     *
     * @return nothing
     */
    void setCoalHeatingValue(double coalHeatingValue) {
        coalHeatingValue_ = coalHeatingValue;
    }

    /**
     * Getter for the electrode use for the cycle
     *
     * @return double, electrode use for the cycle in lbs/cycle
     */
    double getElectrodeUse() const {
        return electrodeUse_;
    }

    /**
     * Sets the electrode use
     *
     * @param electrodeUse double, electrode use in lbs/cycle
     *
     * @return nothing
     */
    void setElectrodeUse(double electrodeUse) {
        electrodeUse_ = electrodeUse;
    }

    /**
     * Getter for the electrode heating value
     *
     * @return double, electrode heating value in btu/lb
     */
    double getElectrodeHeatingValue() const {
        return electrodeHeatingValue_;
    }

    /**
     * Sets the electrode heating value
     *
     * @param electrodeHeatingValue double, electrode heating value in btu/lb
     *
     * @return nothing
     */
    void setElectrodeHeatingValue(double electrodeHeatingValue) {
        electrodeHeatingValue_ = electrodeHeatingValue;
    }

    /**
     * Getter for the other fuels or energy used
     *
     * @return double, other fuels or energy used in mm btu/cycle
     */
    double getOtherFuels() const {
        return otherFuels_;
    }

    /**
     * Sets the other fuels/energy used
     *
     * @param otherFuels double, other fuels/energy use in mm btu/cycle
     *
     * @return nothing
     */
    void setOtherFuels(double otherFuels) {
        otherFuels_ = otherFuels;
    }

    /**
     * Getter for the electricity input
     *
     * @return double, electricity input in kwh/cycle
     */
    double getElectricityInput() const {
        return electricityInput_;
    }

    /**
     * Sets the electricity input
     *
     * @param electricityInput double, electricity input in kwh/cycle
     *
     * @return nothing
     */
    void setElectricityInput(double electricityInput) {
        electricityInput_ = electricityInput;
    }



    /**
     * Calculates the natural gas heat
     *
     * @return double, natural gas heat in mm btu/cycle
     */
    double getNaturalGasHeat();


    /**
     * Calculates the coal heat content
     *
     * @return double, coal heat content in mm btu/cycle
     */
    double getCoalHeatContent();


    /**
     * Calculates the electrode heat content
     *
     * @return double, mm btu/cycle electrode heat content
     */
    double getElectrodeHeatContent();


    /**
     * Calculates the total chemical energy input
     *
     * @return double, total chemical energy input in mm btu/cycle
     */
    double getTotalChemicalEnergyInput();


    /**
     * Gets the kwh per cycle
     *
     * @return double, kwh per cycle
     */
    double getKwhCycle();


    /**
     * Calculates the heat delivered to the EAF
     *
     * @return double, heat delivered to the EAF in btu/cycle
     */
    double getHeatDelivered();


    /**
     * Calculates the total kwh per cycle
     *
     * @return double, kwh per cycle
     */
    double getTotalKwhPerCycle();

private:
    // In values
    double naturalGasHeatInput_ = 0.0;
    double naturalGasFlow_ = 0.0;
    double measuredOxygenFlow_ = 0.0;
    double coalCarbonInjection_ = 0.0;
    double coalHeatingValue_ = 0.0;
    double electrodeUse_ = 0.0;
    double electrodeHeatingValue_ = 0.0;
    double otherFuels_ = 0.0;
    double electricityInput_ = 0.0;


    // Out values
    /// natural gas heat
    double naturalGasHeat_;
    /// coal heat content
    double coalHeatContent_;
    /// electrode heat content
    double electrodeHeatContent_;
    /// total chemical energy input specifically in mm btu/cycle
    double totalChemicalEnergyInput_;
    /// total chemical energy input specifically in kwh/cycle
    double kwhCycle_;
    /// heat delivered to EAF
    double heatDelivered_;
    // total kwh per cycle
    double totalKwhPerCycle_;
};
#endif //AMO_TOOLS_SUITE_ENERGYINPUTEAF_H
