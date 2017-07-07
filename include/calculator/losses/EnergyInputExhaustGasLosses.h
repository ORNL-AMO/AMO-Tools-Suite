/**
 * @file
 * @brief Calculator for energy input - exhaust gas losses for a non-EAF electric furnace
 *
 * This contains the inputs for calculating energy input - exhaust gas losses in non-EAF electric furnaces.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#ifndef AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H
#define AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H

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
     * @return nothing
     *
     * */
    AvailableHeat(
            double excessAir,
            double combustionAirTemp,
            double exhaustGasTemp)
            :  excessAir_(excessAir),
               combustionAirTemp_(combustionAirTemp),
               exhaustGasTemp_(exhaustGasTemp)

    {
        heat_ = 0.0;
        specificHeatAir_ = 0.0;
        airCorrection_ = 0.0;
        combustionAirCorrection_ = 0.0;
        availableHeat_ = 0.0;

    }

    AvailableHeat() = default;

    /**
     * Gets the excess air
     *
     * @return double, excess air as %
     */
    double getExcessAir() const {
        return excessAir_;
    }

    /**
     * Sets the excess air
     *
     * @param excessAir double, excess air as %
     *
     * @return nothing
     */
    void setExcessAir(double excessAir) {
        excessAir_ = excessAir;
    }

    /**
     * Gets the temperature of combustion air
     *
     * @return double, temperature of combustion air in °F
     */
    double getCombustionAirTemp() const {
        return combustionAirTemp_;
    }

    /**
     * Sets the temperature of combustion air
     *
     * @param combustionAirTemp double, temperature of combustion air in °F
     *
     * @return nothing
     */
    void setCombustionAirTemp(double combustionAirTemp) {
        combustionAirTemp_ = combustionAirTemp;
    }

    /**
     * Gets the temperature of exhaust gas
     *
     * @return double, temperature of exhaust gas in °F
     */
    double getExhaustGasTemp() const {
        return exhaustGasTemp_;
    }

    /**
     * Sets the temperature of exhaust gas
     *
     * @param exhaustGasTemp double, temperature of exhaust gas in °F
     *
     * @return nothing
     */
    void setExhaustGasTemp(double exhaustGasTemp) {
        exhaustGasTemp_ = exhaustGasTemp;
    }

    /**
     * Gets the heat input
     *
     * @return double, heat input in °F
     */
    double getHeat();

    /**
     * Gets the specific heat of air
     *
     * @return double, specific heat of air in Btu/(lb*°F)
     */
    double getSpecificHeatAir();

    /**
     * Gets the air correction
     *
     * @return double, air correction in btu
     */
    double getAirCorrection();

    /**
     * Gets the combustion air correction
     *
     * @return double, combustion air correction in btu
     */
    double getCombustionAirCorrection();

    /**
     * Gets the calculated available heat
     *
     * @return double, calculated available heat as %
     */
    double getAvailableHeat();

private:
    // In values
    double excessAir_ = 0.0;
    double combustionAirTemp_ = 0.0;
    double exhaustGasTemp_ = 0.0;

    //In-Out values
    double heat_;
    double specificHeatAir_;
    double airCorrection_;
    double combustionAirCorrection_;

    // Out values
    double availableHeat_;
};

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
     * @return nothing
     *
     * */
    EnergyInputExhaustGasLosses(
            double totalHeatInput,
            double electricalPowerInput,
            double availableHeat,
            double otherLosses)
            : totalHeatInput_(totalHeatInput),
              electricalPowerInput_(electricalPowerInput),
              availableHeat_(availableHeat),
              otherLosses_(otherLosses)

    {
        heatDelivered_ = 0.0;
        heatDeliveredInKw_ = 0.0;
    }

    EnergyInputExhaustGasLosses() = default;

    /**
     * Gets the total heat input
     *
     * @return double, total heat input in Btu/hr
     */
    double getTotalHeatInput() const {
        return totalHeatInput_;
    }

    /**
     * Sets the total heat input
     *
     * @param totalHeatInput double, total heat input in Btu/hr
     *
     * @return nothing
     */
    void setTotalHeatInput(double totalHeatInput) {
        totalHeatInput_ = totalHeatInput;
    }



    /**
     * Gets the electrical power input
     *
     * @return double, electrical power input in kW
     */
    double getElectricalPowerInput() const {
        return electricalPowerInput_;
    }

    /**
     * Sets the electrical power input
     *
     * @param electricalPowerInput double, electrical power input in kW
     *
     * @return nothing
     */
    void setElectricalPowerInput(double electricalPowerInput) {
        electricalPowerInput_ = electricalPowerInput;
    }

    /**
     * Gets the available heat
     *
     * @return double, available heat as %
     */
    double getAvailableHeat() const {
        return availableHeat_;
    }

    /**
     * Sets the available heat
     *
     * @param userAvailableHeat double, available heat as %
     *
     * @return nothing
     */
    void setAvailableHeat(double availableHeat) {
        availableHeat_ = availableHeat;
    }

    /**
     * Gets the other losses
     *
     * @return double, other losses in Btu/hr
     */
    double getOtherLosses() const {
        return otherLosses_;
    }

    /**
     * Sets the other losses
     *
     * @param otherLosses double, other losses in Btu/hr
     *
     * @return nothing
     */
    void setOtherLosses(double otherLosses) {
        otherLosses_ = otherLosses;
    }

    /**
     * Gets the heat delivered to the furnace
     *
     * @return double, heat delivered
     */
    double getHeatDelivered();

    /**
     * Gets the heat delivered to the furnace in kW
     *
     * @return double, heat delivered in kW
     */
    double getHeatDeliveredInKw();

private:
    // In values
    double totalHeatInput_ = 0.0;
    double electricalPowerInput_ = 0.0;
    double availableHeat_ = 0.0;
    double otherLosses_ = 0.0;

    //In-Out values
    double combustionAirCorrection_;
    double heatDelivered_;

    // Out values
    double heatDeliveredInKw_;
};

#endif //AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H
