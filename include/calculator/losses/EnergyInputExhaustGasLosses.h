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
     * @return nothing
     *
     * */
    EnergyInputExhaustGasLosses(const double totalHeatInput,
            const double electricalPowerInput,
            double availableHeat,
            double otherLosses)
            : totalHeatInput_(totalHeatInput),
              electricalPowerInput_(electricalPowerInput),
              availableHeat_(availableHeat),
              otherLosses_(otherLosses),
              heatDelivered_(totalHeatInput * availableHeat / 100),
              exhaustGasLosses(this->heatDelivered_ * (100 - availableHeat_) / availableHeat_)
    {}

    double getHeatDelivered() const { return heatDelivered_; };

    double getExhaustGasLosses() const { return exhaustGasLosses; };

private:
    const double totalHeatInput_, electricalPowerInput_, availableHeat_, otherLosses_ = 0.0;

    const double heatDelivered_;
    double exhaustGasLosses;
};

#endif //AMO_TOOLS_SUITE_ENERGYINPUTEXHAUSTGASLOSSES_H
