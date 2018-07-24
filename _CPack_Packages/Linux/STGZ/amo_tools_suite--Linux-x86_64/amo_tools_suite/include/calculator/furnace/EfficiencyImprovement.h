/**
 * @file
 * @brief Calculator for fuel fired furnace
 *
 * This contains the inputs for calculating the efficiency improvement for a fuel fired furnace
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_EFFICIENCYIMPROVEMENT_H
#define AMO_TOOLS_SUITE_EFFICIENCYIMPROVEMENT_H

/**
 * Efficiency Improvement calculator class
 * Used to help calculate potential fuel savings by increasing the efficiency of the furnace.
 */
class EfficiencyImprovement {
public:
    /**
     *
     * Constructor for the efficiency improvement calculator
     *
     * @param currentFlueGasOxygen double, current % dry of flue gas oxygen
     * @param newFlueGasOxygen double, new % dry of flue gas oxygen
     * @param currentFlueGasTemp double, current temperature of flue gas in °F
     * @param newFlueGasTemp double, new temperature of flue gas in °F
     * @param currentCombustionAirTemp double, current temperature of combustion air in °F
     * @param newCombustionAirTemp double, new temperature of combustion air in °F
     * @param currentEnergyInput double, current energy input in MM Btu/hr
     *
     *
     * */
    EfficiencyImprovement(
            double currentFlueGasOxygen,
            double newFlueGasOxygen,
            double currentFlueGasTemp,
            double newFlueGasTemp,
            double currentCombustionAirTemp,
            double newCombustionAirTemp,
            double currentEnergyInput)
            : currentFlueGasOxygen_(currentFlueGasOxygen),
              newFlueGasOxygen_(newFlueGasOxygen),
              currentFlueGasTemp_(currentFlueGasTemp),
              newFlueGasTemp_(newFlueGasTemp),
              currentCombustionAirTemp_(currentCombustionAirTemp),
              newCombustionAirTemp_(newCombustionAirTemp),
              currentEnergyInput_(currentEnergyInput)

    {
        currentExcessAir_ = 0.0;
        newExcessAir_ = 0.0;
        currentHeatInput_ = 0.0;
        newHeatInput_ = 0.0;
        currentAirSpecificHeat_ = 0.0;
        newAirSpecificHeat_ = 0.0;
        currentAirCorrection_ = 0.0;
        newAirCorrection_ = 0.0;
        currentCombustionAirCorrection_ = 0.0;
        newCombustionAirCorrection_ = 0.0;
        currentAvailableHeat_ = 0.0;
        newAvailableHeat_ = 0.0;
        currentFuelSavings_ = 0.0;
        newFuelSavings_ = 0.0;
        newEnergyInput_ = 0.0;

    }

    EfficiencyImprovement() = default;

    /**
     * Gets the current % of dry flue gas oxygen
     *
     * @return double, current % of dry flue gas oxygen
     */
    double getCurrentFlueGasOxygen() const {
        return currentFlueGasOxygen_;
    }

    /**
     * Sets the current % of dry flue gas oxygen
     *
     * @param currentFlueGasOxygen double, current % of dry flue gas oxygen
     *
     */
    void setCurrentFlueGasOxygen(double currentFlueGasOxygen) {
        currentFlueGasOxygen_ = currentFlueGasOxygen;
    }

    /**
     * Gets the new % of dry flue gas oxygen
     *
     * @return double, new % of dry flue gas oxygen
     */
    double getNewFlueGasOxygen() const {
        return newFlueGasOxygen_;
    }

    /**
     * Sets the new % of dry flue gas oxygen
     *
     * @param newFlueGasOxygen double, new % of dry flue gas oxygen
     *
     */
    void setNewFlueGasOxygen(double newFlueGasOxygen) {
        newFlueGasOxygen_ = newFlueGasOxygen;
    }

    /**
     * Gets the current temperature of flue gas
     *
     * @return double, current temperature of flue gas in °F
     */
    double getCurrentFlueGasTemp() const {
        return currentFlueGasTemp_;
    }

    /**
     * Sets the current temperature of flue gas
     *
     * @param currentFlueGasTemp double, current temperature of flue gas in °F
     *
     */
    void setCurrentFlueGasTemp(double currentFlueGasTemp) {
        currentFlueGasTemp_ = currentFlueGasTemp;
    }

    /**
     * Gets the new temperature of flue gas
     *
     * @return double, new temperature of flue gas in °F
     */
    double getNewFlueGasTemp() const {
        return newFlueGasTemp_;
    }

    /**
     * Sets the new temperature of flue gas
     *
     * @param newFlueGasTemp double, new temperature of flue gas in °F
     *
     */
    void setNewFlueGasTemp(double newFlueGasTemp) {
        newFlueGasTemp_ = newFlueGasTemp;
    }

    /**
     * Gets the current temperature of combustion air
     *
     * @return double, current temperature of combustion air in °F
     */
    double getCurrentCombustionAirTemp() const {
        return currentCombustionAirTemp_;
    }

    /**
     * Sets the current temperature of combustion air
     *
     * @param currentCombustionAirTemp double, current temperature of combustion in °F
     *
     */
    void setCurrentCombustionAirTemp(double currentCombustionAirTemp) {
        currentCombustionAirTemp_ = currentCombustionAirTemp;
    }

    /**
     * Gets the new temperature of combustion air
     *
     * @return double, new temperature of combustion air in °F
     */
    double getNewCombustionAirTemp() const {
        return newCombustionAirTemp_;
    }

    /**
     * Sets the new temperature of combustion air
     *
     * @param newCombustionAirTemp double, new temperature of combustion in °F
     *
     */
    void setNewCombustionAirTemp(double newCombustionAirTemp) {
        newCombustionAirTemp_ = newCombustionAirTemp;
    }

    /**
     * Gets the current energy input
     *
     * @return double, current energy input in MM Btu/hr
     */
    double getCurrentEnergyInput() const {
        return currentEnergyInput_;
    }

    /**
     * Sets the current energy input
     *
     * @param currentEnergyInput double, current, current energy input in MM Btu/hr
     *
     */
    void setCurrentEnergyInput(double currentEnergyInput) {
        currentEnergyInput_ = currentEnergyInput;
    }

    /**
     * Gets the current excess air
     *
     * @return double, current excess air as %
     */
    double getCurrentExcessAir();

    /**
     * Gets the new excess air
     *
     * @return double, new excess air as %
     */
    double getNewExcessAir();

    /**
     * Gets the current heat input in °F
     *
     * @return double, current heat input in °F
     */
    double getCurrentHeatInput();

    /**
     * Gets the new heat input in °F
     *
     * @return double, new heat input in °F
     */
    double getNewHeatInput();

    /**
     * Gets the current specific heat of air
     *
     * @return double, current specific heat of air in Btu/(lb*°F)
     */
    double getCurrentAirSpecificHeat();

    /**
     * Gets the new specific heat of air
     *
     * @return double, new specific heat of air in Btu/(lb*°F)
     */
    double getNewAirSpecificHeat();

    /**
     * Gets the current air correction
     *
     * @return double, current air correction in btu
     */
    double getCurrentAirCorrection();

    /**
     * Gets the new air correction
     *
     * @return double, new air correction in btu
     */
    double getNewAirCorrection();

    /**
     * Gets the combustion air correction
     *
     * @return double, combustion air correction in btu
     */
    double getCurrentCombustionAirCorrection();

    /**
     * Gets the combustion air correction
     *
     * @return double, combustion air correction in btu
     */
    double getNewCombustionAirCorrection();

    /**
     * Gets the current available heat
     *
     * @return double, current available heat as % of HHV
     */
    double getCurrentAvailableHeat();

    /**
     * Gets the new available heat
     *
     * @return double, new available heat as % of HHV
     */
    double getNewAvailableHeat();

    /**
     * Gets the new fuel savings
     *
     * @return double, new fuel savings as %
     */
    double getNewFuelSavings();

    /**
     * Gets the current fuel savings
     *
     * @return double, current fuel savings as %
     */
    double getCurrentFuelSavings() {
        return currentFuelSavings_;
    };


    /**
     * Gets the new fuel savings
     *
     * @return double, new fuel savings as %
     */
    double getNewEnergyInput();

private:
    // In values
    double currentFlueGasOxygen_ = 0.0;
    double newFlueGasOxygen_ = 0.0;
    double currentFlueGasTemp_ = 0.0;
    double newFlueGasTemp_ = 0.0;
    double currentCombustionAirTemp_ = 0.0;
    double newCombustionAirTemp_ = 0.0;
    double currentEnergyInput_ = 0.0;


    // Out values
    double currentExcessAir_;
    double newExcessAir_;
    double currentHeatInput_;
    double newHeatInput_;
    double currentAirSpecificHeat_;
    double newAirSpecificHeat_;
    double currentAirCorrection_;
    double newAirCorrection_;
    double currentCombustionAirCorrection_;
    double newCombustionAirCorrection_;
    double currentAvailableHeat_;
    double newAvailableHeat_;
    double currentFuelSavings_;
    double newFuelSavings_;
    double newEnergyInput_;
};
#endif //AMO_TOOLS_SUITE_EFFICIENCYIMPROVEMENT_H
