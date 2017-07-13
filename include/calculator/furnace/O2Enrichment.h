/**
 * @file
 * @brief Calculator for fuel fired furnace
 *
 * This contains the inputs for calculations involving oxygen enrichment for a fuel fired furnace
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_O2ENRICHMENT_H
#define AMO_TOOLS_SUITE_O2ENRICHMENT_H

/**
 * O2 Enrichment calculator class
 * Used to see the potential fuel savings of using O2 enriched fuel.
 */
class O2Enrichment {
public:
    /**
     *
     * Constructor for the O2 enrichment calculator
     *
     * @param o2CombAir double, % of O2 in the combustion air
     * @param o2CombAirEnriched double, % of O2 in the oxygen enriched combustion air
     * @param flueGasTemp double, flue gas temperature in °F
     * @param flueGasTempEnriched double, flue gas temperature with oxygen enriched air in °F
     * @param o2FlueGas double, % of dry O2 in flue gas
     * @param o2FlueGasEnriched double, % of dry O2 in flue gas with oxygen enriched air
     * @param combAirTemp double, combustion air preheat temperature in °F
     * @param combAirTempEnriched double, combustion air preheat temperature with oxygen enriched air in °F
     * @param fuelConsumption double, fuel consumption in MM Btu/hr
     *
     * @return nothing
     *
     * */
    O2Enrichment(
            double o2CombAir,
            double o2CombAirEnriched,
            double flueGasTemp,
            double flueGasTempEnriched,
            double o2FlueGas,
            double o2FlueGasEnriched,
            double combAirTemp,
            double combAirTempEnriched,
            double fuelConsumption)
            : o2CombAir_(o2CombAir),
              o2CombAirEnriched_(o2CombAirEnriched),
              flueGasTemp_(flueGasTemp),
              flueGasTempEnriched_(flueGasTempEnriched),
              o2FlueGas_(o2FlueGas),
              o2FlueGasEnriched_(o2FlueGasEnriched),
              combAirTemp_(combAirTemp),
              combAirTempEnriched_(combAirTempEnriched),
              fuelConsumption_(fuelConsumption)

    {
        excessAir_ = 0.0;
        excessAirEnriched_ = 0.0;
        heatInput_ = 0.0;
        heatInputEnriched_ = 0.0;
        airSpecificHeat_ = 0.0;
        enrichedAirSpecificHeat_ = 0.0;
        airCorrection_ = 0.0;
        enrichedAirCorrection_ = 0.0;
        combustionAirCorrection_ = 0.0;
        combustionAirCorrectionEnriched_ = 0.0;
        stdAvailableHeat_ = 0.0;
        stdAvailableHeatEnriched_ = 0.0;
        availableHeat_ = 0.0;
        availableHeatEnriched_ = 0.0;
        fuelConsumptionEnriched_ = 0.0;
        fuelSavingsEnriched_ = 0.0;

    }

    O2Enrichment() = default;

    /**
     * Gets the O2 in combustion air
     *
     * @return double, % of O2 in combustion air
     */
    double getO2CombAir() const {
        return o2CombAir_;
    }

    /**
     * Sets the percentage of O2 in combustion air
     *
     * @param o2CombAir double, % of O2 in combustion air
     *
     * @return nothing
     */
    void setO2CombAir(double o2CombAir) {
        o2CombAir_ = o2CombAir;
    }

    /**
     * Gets the O2 in combustion air with oxygen enrichment
     *
     * @return double, % of O2 in combustion air with oxygen enrichment
     */
    double getO2CombAirEnriched() const {
        return o2CombAirEnriched_;
    }

    /**
     * Sets the percentage of O2 in combustion air with oxygen enrichment
     *
     * @param o2CombAirEnriched double, % of O2 in combustion air with oxygen enrichment
     *
     * @return nothing
     */
    void setO2CombAirEnriched(double o2CombAirEnriched) {
        o2CombAirEnriched_ = o2CombAirEnriched;
    }

    /**
     * Gets the flue gas temperature
     *
     * @return double, flue gas temperature in °F
     */
    double getFlueGasTemp() const {
        return flueGasTemp_;
    }

    /**
     * Sets the flue gas temperature
     *
     * @param flueGasTemp double, flue gas temperature in °F
     *
     * @return nothing
     */
    void setFlueGasTemp(double flueGasTemp) {
        flueGasTemp_ = flueGasTemp;
    }

    /**
     * Gets the flue gas temperature with oxygen enrichment
     *
     * @return double, flue gas temperature with oxygen enrichment in °F
     */
    double getFlueGasTempEnriched() const {
        return flueGasTempEnriched_;
    }

    /**
     * Sets the flue gas temperature with oxygen enrichment
     *
     * @param flueGasTempEnriched double, flue gas temperature with oxygen enrichment in °F
     *
     * @return nothing
     */
    void setFlueGasTempEnriched(double flueGasTempEnriched) {
        flueGasTempEnriched_ = flueGasTempEnriched;
    }

    /**
     * Gets the dry percentage of O2 in flue gases
     *
     * @return double, dry % of O2 in flue gases
     */
    double getO2FlueGas() const {
        return o2FlueGas_;
    }

    /**
     * Sets the dry percentage of O2 in flue gases
     *
     * @param o2FlueGas double, dry % of O2 in flue gases
     *
     * @return nothing
     */
    void setO2FlueGas(double o2FlueGas) {
        o2FlueGas_ = o2FlueGas;
    }

    /**
     * Gets the dry percentage of O2 in flue gases with oxygen enrichment
     *
     * @return double, dry % of O2 in flue gases with oxygen enrichment
     */
    double getO2FlueGasEnriched() const {
        return o2FlueGasEnriched_;
    }

    /**
     * Sets the dry percentage of O2 in flue gases with oxygen enrichment
     *
     * @param o2FlueGasEnriched double, dry % of O2 in flue gases with oxygen enrichment
     *
     * @return nothing
     */
    void setO2FlueGasEnriched(double o2FlueGasEnriched) {
        o2FlueGasEnriched_ = o2FlueGasEnriched;
    }

    /**
     * Gets the combustion air preheat temperature
     *
     * @return double, combustion air preheat temperature in °F
     */
    double getCombAirTemp() const {
        return combAirTemp_;
    }

    /**
     * Sets the combustion air preheat temperature
     *
     * @param combAirTemp double, combustion air preheat temperature in °F
     *
     * @return nothing
     */
    void setCombAirTemp(double combAirTemp) {
        combAirTemp_ = combAirTemp;
    }

    /**
     * Gets the combustion air preheat temperature with oxygen enrichment
     *
     * @return double, combustion air preheat temperature with oxygen enrichment in °F
     */
    double getCombAirTempEnriched() const {
        return combAirTempEnriched_;
    }

    /**
     * Sets the combustion air preheat temperature with oxygen enrichment
     *
     * @param combAirTempEnriched double, combustion air preheat temperature with oxygen enrichment in °F
     *
     * @return nothing
     */
    void setCombAirTempEnriched(double combAirTempEnriched) {
        combAirTempEnriched_ = combAirTempEnriched;
    }

    /**
     * Gets the fuel consumption
     *
     * @return double, fuel consumption in MM Btu/hr
     */
    double getFuelConsumption() const {
        return fuelConsumption_;
    }

    /**
     * Sets the fuel consumption
     *
     * @param fuelConsumption double, fuel consumption in MM Btu/hr
     *
     * @return nothing
     */
    void setFuelConsumption(double fuelConsumption) {
        fuelConsumption_ = fuelConsumption;
    }

    /**
     * Gets the excess air
     *
     * @return double, excess air as %
     */
    double getExcessAir();

    /**
     * Gets the excess air with oxygen enrichment
     *
     * @return double, excess air with oxygen enrichment as %
     */
    double getExcessAirEnriched();

    /**
     * Gets the heat input
     *
     * @return double, heat input in °F
     */
    double getHeatInput();

    /**
     * Gets the heat input with oxygen enrichment
     *
     * @return double, heat input with oxygen enrichment in °F
     */
    double getHeatInputEnriched();

    /**
     * Gets the specific heat of air
     *
     * @return double, specific heat of air in Btu/(lb*°F)
     */
    double getAirSpecificHeat();

    /**
     * Gets the specific heat of air with oxygen enrichment
     *
     * @return double, specific heat of air with oxygen enrichment in Btu/(lb*°F)
     */
    double getEnrichedAirSpecificHeat();

    /**
     * Gets the air correction
     *
     * @return double, air correction in btu
     */
    double getAirCorrection();

    /**
     * Gets the air correction with oxygen enrichment
     *
     * @return double, air correction with oxygen enrichment in btu
     */
    double getEnrichedAirCorrection();

    /**
     * Gets the combustion air correction
     *
     * @return double, combustion air correction in btu
     */
    double getCombustionAirCorrection();

    /**
     * Gets the combustion air correction with oxygen enrichment
     *
     * @return double, combustion air correction with oxygen enrichment in btu
     */
    double getCombustionAirCorrectionEnriched();

    /**
     * Gets the standard available heat (this does not take % of O2 in combustion air into account)
     *
     * @return double, standard available heat as %
     */
    double getStdAvailableHeat();

    /**
     * Gets the standard available heat with oxygen enrichment (this does not take % of O2 in combustion air into account)
     *
     * @return double, standard available heat with oxygen enrichment as %
     */
    double getStdAvailableHeatEnriched();

    /**
     * Gets the available heat (uses % of O2 in combustion air)
     *
     * @return double, available heat as % of HHV
     */
    double getAvailableHeat();

    /**
     * Gets the available heat with oxygen enrichment (uses % of O2 in combustion air)
     *
     * @return double, available heat with oxygen enrichment as % of HHV
     */
    double getAvailableHeatEnriched();

    /**
     * Gets the fuel consumption with oxygen enrichment
     *
     * @return double, fuel consumption with oxygen enrichment in MM Btu/hr
     */
    double getFuelConsumptionEnriched();

    /**
     * Gets the fuel savings with oxygen enrichment
     *
     * @return double, % of fuel savings
     */
    double getFuelSavingsEnriched();


private:
    // In values
    double o2CombAir_ = 0.0;
    double o2CombAirEnriched_ = 0.0;
    double flueGasTemp_ = 0.0;
    double flueGasTempEnriched_ = 0.0;
    double o2FlueGas_ = 0.0;
    double o2FlueGasEnriched_ = 0.0;
    double combAirTemp_ = 0.0;
    double combAirTempEnriched_ = 0.0;
    double fuelConsumption_ = 0.0;


    // Out values
    double excessAir_;
    double excessAirEnriched_;
    double heatInput_;
    double heatInputEnriched_;
    double airSpecificHeat_;
    double enrichedAirSpecificHeat_;
    double airCorrection_;
    double enrichedAirCorrection_;
    double combustionAirCorrection_;
    double combustionAirCorrectionEnriched_;
    double stdAvailableHeat_;
    double stdAvailableHeatEnriched_;
    double availableHeat_;
    double availableHeatEnriched_;
    double fuelConsumptionEnriched_;
    double fuelSavingsEnriched_;
};

#endif //AMO_TOOLS_SUITE_O2ENRICHMENT_H
