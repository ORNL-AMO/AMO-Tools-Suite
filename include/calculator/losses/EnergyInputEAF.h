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


class EnergyInputEAF {
    public:
    /**
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

    double getNaturalGasHeatInput() const {
        return naturalGasHeatInput_;
    }

    void setNaturalGasHeatInput(double naturalGasHeatInput) {
        naturalGasHeatInput_ = naturalGasHeatInput;
    }

    double getNaturalGasFlow() const {
        return naturalGasFlow_;
    }

    void setNaturalGasFlow(double naturalGasFlow) {
        naturalGasFlow_ = naturalGasFlow;
    }

    double getMeasuredOxygenFlow() const {
        return measuredOxygenFlow_;
    }

    void setMeasuredOxygenFlow(double measuredOxygenFlow) {
        measuredOxygenFlow_ = measuredOxygenFlow;
    }

    double getCoalCarbonInjection() const {
        return coalCarbonInjection_;
    }

    void setCoalCarbonInjection(double coalCarbonInjection) {
        coalCarbonInjection_ = coalCarbonInjection;
    }

    double getCoalHeatingValue() const {
        return coalHeatingValue_;
    }

    void setCoalHeatingValue(double coalHeatingValue) {
        coalHeatingValue_ = coalHeatingValue;
    }

    double getElectrodeUse() const {
        return electrodeUse_;
    }

    void setElectrodeUse(double electrodeUse) {
        electrodeUse_ = electrodeUse;
    }

    double getElectrodeHeatingValue() const {
        return electrodeHeatingValue_;
    }

    void setElectrodeHeatingValue(double electrodeHeatingValue) {
        electrodeHeatingValue_ = electrodeHeatingValue;
    }

    double getOtherFuels() const {
        return otherFuels_;
    }

    void setOtherFuels(double otherFuels) {
        otherFuels_ = otherFuels;
    }

    double getElectricityInput() const {
        return electricityInput_;
    }

    void setElectricityInput(double electricityInput) {
        electricityInput_ = electricityInput;
    }


    void setNaturalGasHeat(double naturalGasHeat) {
        naturalGasHeat_ = naturalGasHeat;
    }

    double getNaturalGasHeat();

    void setoalHeatContent(double coalHeatContent) {
        coalHeatContent_ = coalHeatContent;
    }

    double getCoalHeatContent();

    void setElectrodeHeatContent(double electrodeHeatContent) {
        electrodeHeatContent_ = electrodeHeatContent;
    }

    double getElectrodeHeatContent();

    void setTotalChemicalEnergyInput(double totalChemicalEnergyInput) {
        totalChemicalEnergyInput_ = totalChemicalEnergyInput;
    }

    double getTotalChemicalEnergyInput();

    void setKwhCycle(double kwhCycle) {
        kwhCycle_ = kwhCycle;
    }

    double getKwhCycle();

    void setHeatDelivered(double heatDelivered) {
        heatDelivered_ = heatDelivered;
    }

    double getHeatDelivered();

    void setTotalKwhPerCycle(double totalKwhPerCycle) {
        totalKwhPerCycle_ = totalKwhPerCycle;
    }

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
    double naturalGasHeat_;
    double coalHeatContent_;
    double electrodeHeatContent_;
    double totalChemicalEnergyInput_;
    double kwhCycle_;
    double heatDelivered_;
    double totalKwhPerCycle_;
};
#endif //AMO_TOOLS_SUITE_ENERGYINPUTEAF_H
