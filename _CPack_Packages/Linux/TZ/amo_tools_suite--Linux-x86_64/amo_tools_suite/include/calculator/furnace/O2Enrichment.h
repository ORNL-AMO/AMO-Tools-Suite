/**
 * @file
 * @brief Calculator for fuel fired furnace
 *
 * This contains the inputs for calculations involving oxygen enrichment for a fuel fired furnace
 *
 * @author Autumn Ferree (ferreeak) & Preston Shires (pshires)
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
	 * Constructor for the O2 enrichment calculator
	 * @param o2CombAir double, % of O2 in the combustion air
	 * @param o2CombAirEnriched double, % of O2 in the oxygen enriched combustion air
	 * @param flueGasTemp double, flue gas temperature in °F
	 * @param flueGasTempEnriched double, flue gas temperature with oxygen enriched air in °F
	 * @param o2FlueGas double, % of dry O2 in flue gas
	 * @param o2FlueGasEnriched double, % of dry O2 in flue gas with oxygen enriched air
	 * @param combAirTemp double, combustion air preheat temperature in °F
	 * @param combAirTempEnriched double, combustion air preheat temperature with oxygen enriched air in °F
	 * @param fuelConsumption double, fuel consumption in MM Btu/hr
	 * */
    O2Enrichment(const double o2CombAir, const double o2CombAirEnriched, const double flueGasTemp,
                 const double flueGasTempEnriched, const double o2FlueGas, const double o2FlueGasEnriched,
                 const double combAirTemp, const double combAirTempEnriched, const double fuelConsumption)
            : o2CombAir(o2CombAir / 100), o2CombAirEnriched(o2CombAirEnriched / 100), flueGasTemp(flueGasTemp),
              flueGasTempEnriched(flueGasTempEnriched), o2FlueGas(o2FlueGas / 100),
              o2FlueGasEnriched(o2FlueGasEnriched / 100), combAirTemp(combAirTemp),
              combAirTempEnriched(combAirTempEnriched), fuelConsumption(fuelConsumption)
    {
        calculate();
    }

    O2Enrichment() = default;

    /**
     * Gets the O2 in combustion air
     * @return double, % of O2 in combustion air
     */
    double getO2CombAir() const { return o2CombAir; }

    /**
     * Sets the percentage of O2 in combustion air
     * @param o2CombAir double, % of O2 in combustion air
     */
    void setO2CombAir(const double o2CombAir) {
        this->o2CombAir = o2CombAir / 100;
        calculate();
    }

    /**
     * Gets the O2 in combustion air with oxygen enrichment
     * @return double, % of O2 in combustion air with oxygen enrichment
     */
    double getO2CombAirEnriched() const { return o2CombAirEnriched; }

    /**
     * Sets the percentage of O2 in combustion air with oxygen enrichment
     * @param o2CombAirEnriched double, % of O2 in combustion air with oxygen enrichment
     */
    void setO2CombAirEnriched(double o2CombAirEnriched) {
        this->o2CombAirEnriched = o2CombAirEnriched / 100;
        calculate();
    }

    /**
     * Gets the flue gas temperature
     * @return double, flue gas temperature in °F
     */
    double getFlueGasTemp() const { return flueGasTemp; }

    /**
     * Sets the flue gas temperature
     * @param flueGasTemp double, flue gas temperature in °F
     */
    void setFlueGasTemp(double flueGasTemp) {
        this->flueGasTemp = flueGasTemp;
        calculate();
    }

    /**
     * Gets the flue gas temperature with oxygen enrichment
     * @return double, flue gas temperature with oxygen enrichment in °F
     */
    double getFlueGasTempEnriched() const { return flueGasTempEnriched; }

    /**
     * Sets the flue gas temperature with oxygen enrichment
     * @param flueGasTempEnriched double, flue gas temperature with oxygen enrichment in °F
     */
    void setFlueGasTempEnriched(double flueGasTempEnriched) {
        this->flueGasTempEnriched = flueGasTempEnriched;
        calculate();
    }

    /**
     * Gets the dry percentage of O2 in flue gases
     * @return double, dry % of O2 in flue gases
     */
    double getO2FlueGas() const { return o2FlueGas; }

    /**
     * Sets the dry percentage of O2 in flue gases
     * @param o2FlueGas double, dry % of O2 in flue gases
     */
    void setO2FlueGas(double o2FlueGas) {
        this->o2FlueGas = o2FlueGas / 100;
        calculate();
    }

    /**
     * Gets the dry percentage of O2 in flue gases with oxygen enrichment
     * @return double, dry % of O2 in flue gases with oxygen enrichment
     */
    double getO2FlueGasEnriched() const { return o2FlueGasEnriched; }

    /**
     * Sets the dry percentage of O2 in flue gases with oxygen enrichment
     * @param o2FlueGasEnriched double, dry % of O2 in flue gases with oxygen enrichment
     */
    void setO2FlueGasEnriched(double o2FlueGasEnriched) {
        this->o2FlueGasEnriched = o2FlueGasEnriched / 100;
        calculate();
    }

    /**
     * Gets the combustion air preheat temperature
     * @return double, combustion air preheat temperature in °F
     */
    double getCombAirTemp() const { return combAirTemp; }

    /**
     * Sets the combustion air preheat temperature
     * @param combAirTemp double, combustion air preheat temperature in °F
     */
    void setCombAirTemp(double combAirTemp) {
        this->combAirTemp = combAirTemp;
        calculate();
    }

    /**
     * Gets the combustion air preheat temperature with oxygen enrichment
     * @return double, combustion air preheat temperature with oxygen enrichment in °F
     */
    double getCombAirTempEnriched() const { return combAirTempEnriched; }

    /**
     * Sets the combustion air preheat temperature with oxygen enrichment
     * @param combAirTempEnriched double, combustion air preheat temperature with oxygen enrichment in °F
     */
    void setCombAirTempEnriched(double combAirTempEnriched) {
        this->combAirTempEnriched = combAirTempEnriched;
        calculate();
    }

    /**
     * Gets the fuel consumption
     * @return double, fuel consumption in MM Btu/hr
     */
    double getFuelConsumption() const { return fuelConsumption; }

    /**
     * Sets the fuel consumption
     * @param fuelConsumption double, fuel consumption in MM Btu/hr
     */
    void setFuelConsumption(double fuelConsumption) {
        this->fuelConsumption = fuelConsumption;
        calculate();
    }

    /**
     * Gets the excess air
     * @return double, excess air as %
     */
    double getExcessAir() { return excessAir; };

    /**
     * Gets the excess air with oxygen enrichment
     * @return double, excess air with oxygen enrichment as %
     */
    double getExcessAirEnriched() { return excessAirEnriched; };

    /**
     * Gets the heat input
     * @return double, heat input in °F
     */
    double getHeatInput() { return heatInput; };

    /**
     * Gets the heat input with oxygen enrichment
     * @return double, heat input with oxygen enrichment in °F
     */
    double getHeatInputEnriched() { return heatInputEnriched; };

    /**
     * Gets the specific heat of air
     * @return double, specific heat of air in Btu/(lb*°F)
     */
    double getAirSpecificHeat() { return airSpecificHeat; };

    /**
     * Gets the specific heat of air with oxygen enrichment
     * @return double, specific heat of air with oxygen enrichment in Btu/(lb*°F)
     */
    double getEnrichedAirSpecificHeat() { return enrichedAirSpecificHeat; };

    /**
     * Gets the air correction
     * @return double, air correction in btu
     */
    double getAirCorrection() { return airCorrection; };

    /**
     * Gets the air correction with oxygen enrichment
     * @return double, air correction with oxygen enrichment in btu
     */
    double getEnrichedAirCorrection() { return enrichedAirCorrection; };

    /**
     * Gets the combustion air correction
     * @return double, combustion air correction in btu
     */
    double getCombustionAirCorrection() { return combustionAirCorrection; };

    /**
     * Gets the combustion air correction with oxygen enrichment
     * @return double, combustion air correction with oxygen enrichment in btu
     */
    double getCombustionAirCorrectionEnriched() { return combustionAirCorrectionEnriched; };

    /**
     * Gets the standard available heat (this does not take % of O2 in combustion air into account)
     * @return double, standard available heat as %
     */
    double getStdAvailableHeat() { return stdAvailableHeat; };

    /**
     * Gets the standard available heat with oxygen enrichment (this does not take % of O2 in combustion air into account)
     * @return double, standard available heat with oxygen enrichment as %
     */
    double getStdAvailableHeatEnriched() { return stdAvailableHeatEnriched; };

    /**
     * Gets the available heat (uses % of O2 in combustion air)
     * @return double, available heat as % of HHV
     */
    double getAvailableHeat() { return availableHeat; };

    /**
     * Gets the available heat with oxygen enrichment (uses % of O2 in combustion air)
     * @return double, available heat with oxygen enrichment as % of HHV
     */
    double getAvailableHeatEnriched() { return availableHeatEnriched; };

    /**
     * Gets the fuel consumption with oxygen enrichment
     * @return double, fuel consumption with oxygen enrichment in MM Btu/hr
     */
    double getFuelConsumptionEnriched() { return fuelConsumptionEnriched; };

    /**
     * Gets the fuel savings with oxygen enrichment
     * @return double, % of fuel savings
     */
    double getFuelSavingsEnriched() { return fuelSavingsEnriched; };

    /**
     * Calculates available heat, available heat enriched, fuel consumption enriched, and fuel saving enriched
     * @return double, available heat as % of HHV
     */
    void calculate();


private:
    // In values
    double o2CombAir, o2CombAirEnriched, flueGasTemp, flueGasTempEnriched, o2FlueGas, o2FlueGasEnriched, combAirTemp;
    double combAirTempEnriched, fuelConsumption;

    // Out values
    double excessAir, excessAirEnriched, heatInput, heatInputEnriched, airSpecificHeat, enrichedAirSpecificHeat;
    double airCorrection, enrichedAirCorrection, combustionAirCorrection, combustionAirCorrectionEnriched;
    double stdAvailableHeat, stdAvailableHeatEnriched, availableHeat, availableHeatEnriched;
    double fuelConsumptionEnriched, fuelSavingsEnriched;
};

#endif //AMO_TOOLS_SUITE_O2ENRICHMENT_H
