/**
 * @file
 * @brief Calculator for energy equivalency for electric and fuel-fired furnaces
 *
 * This contains the inputs for calculating the energy equivalency for electric and fuel-fired furnaces.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_ENERGYEQUIVALENCY_H
#define AMO_TOOLS_SUITE_ENERGYEQUIVALENCY_H

/**
 * Electrical Energy Equivalency calculator class
 * Used to calculate the electrical heat input that is equivalent to the fuel-fired heat input.
 */
class ElectricalEnergyEquivalency {
public:
    /**
     *
     * Constructor for the electric energy equivalency calculator
     *
     * @param fuelFiredEfficiency double, fuel-fired equipment efficiency as %
     * @param electricallyHeatedEfficiency double, electrically heated equipment efficiency as %
     * @param fuelFiredHeatInput double, heat input for fuel-fired equipment in MM Btu/hr
     *
     *
     * */
    ElectricalEnergyEquivalency(
            double fuelFiredEfficiency,
            double electricallyHeatedEfficiency,
            double fuelFiredHeatInput)
            : fuelFiredEfficiency_(fuelFiredEfficiency),
              electricallyHeatedEfficiency_(electricallyHeatedEfficiency),
              fuelFiredHeatInput_(fuelFiredHeatInput)

    {
        electricalHeatInput_ = 0.0;

    }

    ElectricalEnergyEquivalency() = default;

    /**
     * Getter for the fuel-fired equipment efficiency
     *
     * @return double, fuel-fired equipment efficiency as %
     */
    double getFuelFiredEfficiency() const {
        return fuelFiredEfficiency_;
    }

    /**
     * Sets the fuel-fired equipment efficiency
     *
     * @param fuelFiredEfficiency double, fuel-fired equipment efficiency as %
     *
     */
    void setFuelFiredEfficiency(double fuelFiredEfficiency) {
        fuelFiredEfficiency_ = fuelFiredEfficiency;
    }

    /**
     * Getter for the electrically heated equipment efficiency
     *
     * @return double, electrically heated equipment efficiency as %
     */
    double getElectricallyHeatedEfficiency() const {
        return electricallyHeatedEfficiency_;
    }

    /**
     * Sets the electrically heated equipment efficiency
     *
     * @param electricallyHeatedEfficiency double, electrically heated equipment efficiency as %
     *
     */
    void setElectricallyHeatedEfficiency(double electricallyHeatedEfficiency) {
        electricallyHeatedEfficiency_ = electricallyHeatedEfficiency;
    }

    /**
     * Getter for the heat input for fuel-fired equipment
     *
     * @return double, heat input for fuel-fired equipment in MM Btu/hr
     */
    double getFuelFiredHeatInput() const {
        return fuelFiredHeatInput_;
    }

    /**
     * Sets the heat input for fuel-fired equipment
     *
     * @param fuelFiredHeatInput double, heat input for fuel-fired equipment in MM Btu/hr
     *
     */
    void setFuelFiredHeatInput(double fuelFiredHeatInput) {
        fuelFiredHeatInput_ = fuelFiredHeatInput;
    }

    /**
     * Gets the equivalent electrical heat input
     * @return double, equivalent electrical heat input in kW
     */
    double getElectricalHeatInput();

private:
    // In values
    double fuelFiredEfficiency_ = 0.0;
    double electricallyHeatedEfficiency_ = 0.0;
    double fuelFiredHeatInput_ = 0.0;


    // Out values
    /// natural gas heat
    double electricalHeatInput_;
};

/**
 * Fuel Fired Energy Equivalency calculator class
 * Used to calculate the fuel-fired heat input that is equivalent to the electric heat input.
 */
class FuelFiredEnergyEquivalency {
public:
    /**
     *
     * Constructor for the fuel-fired equivalency calculator
     *
     * @param electricallyHeatedEfficiency double, electrically heated equipment efficiency as %
     * @param fuelFiredEfficiency double, fuel-fired equipment efficiency as %
     * @param electricalHeatInput double, heat input for electrically heated equipment in kW
     *
     *
     * */
    FuelFiredEnergyEquivalency(
            double electricallyHeatedEfficiency,
            double fuelFiredEfficiency,
            double electricalHeatInput)
            : electricallyHeatedEfficiency_(electricallyHeatedEfficiency),
              fuelFiredEfficiency_(fuelFiredEfficiency),
              electricalHeatInput_(electricalHeatInput)

    {
        fuelFiredHeatInput_ = 0.0;

    }

    FuelFiredEnergyEquivalency() = default;


    /**
     * Getter for the electrically heated equipment efficiency
     *
     * @return double, electrically heated equipment efficiency as %
     */
    double getElectricallyHeatedEfficiency() const {
        return electricallyHeatedEfficiency_;
    }

    /**
     * Sets the electrically heated equipment efficiency
     *
     * @param electricallyHeatedEfficiency double, electrically heated equipment efficiency as %
     *
     */
    void setElectricallyHeatedEfficiency(double electricallyHeatedEfficiency) {
        electricallyHeatedEfficiency_ = electricallyHeatedEfficiency;
    }

    /**
     * Getter for the fuel-fired equipment efficiency
     *
     * @return double, fuel-fired equipment efficiency as %
     */
    double getFuelFiredEfficiency() const {
        return fuelFiredEfficiency_;
    }

    /**
     * Sets the fuel-fired equipment efficiency
     *
     * @param fuelFiredEfficiency double, fuel-fired equipment efficiency as %
     *
     */
    void setFuelFiredEfficiency(double fuelFiredEfficiency) {
        fuelFiredEfficiency_ = fuelFiredEfficiency;
    }

    /**
     * Getter for the heat input for electrically heated equipment
     *
     * @return double, heat input for electrically heated equipment in kW
     */
    double getElectricalHeatInput() const {
        return electricalHeatInput_;
    }

    /**
     * Sets the heat input for electrically heated equipment
     *
     * @param electricalHeatInput double, heat input for electrically heated equipment in kW
     *
     */
    void setElectricalHeatInput(double electricalHeatInput) {
        electricalHeatInput_ = electricalHeatInput;
    }

    /**
     * Gets the equivalent fuel-fired heat input
     * @return double, equivalent fuel-fired heat input in MM Btu/hr
     */
    double getFuelFiredHeatInput();

private:
    // In values
    double electricallyHeatedEfficiency_ = 0.0;
    double fuelFiredEfficiency_ = 0.0;
    double electricalHeatInput_ = 0.0;


    // Out values
    /// natural gas heat
    double fuelFiredHeatInput_;
};
#endif //AMO_TOOLS_SUITE_ENERGYEQUIVALENCY_H
