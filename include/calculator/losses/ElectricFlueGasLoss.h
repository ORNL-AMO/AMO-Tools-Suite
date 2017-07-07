/**
 * @file
 * @brief Calculator for flue gas loss in electric furnaces
 *
 * This contains the inputs for calculating a flue gas loss in electric furnaces.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#ifndef AMO_TOOLS_SUITE_ELECTRICFLUEGASLOSS_H
#define AMO_TOOLS_SUITE_ELECTRICFLUEGASLOSS_H

class ElectricFlueGasLoss {
public:
    /**
     *
     * Constructor for the electric flue gas loss with all inputs specified
     *
     * @param furnaceTemperature double, temperature of the furnace in °F
     * @param heatingSystemEfficiency double, electrical heating system efficiency as %
     *
     * @return nothing
     *
     * */
    ElectricFlueGasLoss(
            double furnaceTemperature,
            double heatingSystemEfficiency)
            : furnaceTemperature_(furnaceTemperature),
              heatingSystemEfficiency_(heatingSystemEfficiency)

    {
        grossHeat_ = 0.0;
        requiredPower_ = 0.0;
    }

    ElectricFlueGasLoss() = default;

    /**
     * Getter for the furnace temperature
     *
     * @return double, furnace temperature in °F
     */
    double getFurnaceTemperature() const {
        return furnaceTemperature_;
    }

    /**
     * Sets the furnace temperature
     *
     * @param furnaceTemperature double, temperature of furnace in °F
     *
     * @return nothing
     */
    void setFurnaceTemperature(double furnaceTemperature) {
        furnaceTemperature_ = furnaceTemperature;
    }

    /**
     * Getter for the electrical heating system efficiency
     *
     * @return double, electrical heating system efficiency as %
     */
    double getHeatingSystemEfficiency() const {
        return heatingSystemEfficiency_;
    }

    /**
     * Sets the electrical heating system efficiency
     *
     * @param heatingSystemEfficiency double, electrical heating system efficiency as %
     *
     * @return nothing
     */
    void setHeatingSystemEfficiency(double heatingSystemEfficiency) {
        heatingSystemEfficiency_ = heatingSystemEfficiency;
    }

    /**
     * Gets the gross heat
     *
     * @return double, gross heat in Btu/hr
     */
    double getGrossHeat();


    /**
     * Gets the gross electrical power required
     *
     * @return double, gross electrical power required in kW
     */
    double getRequiredPower();

private:
    // In values
    double furnaceTemperature_ = 0.0;
    double heatingSystemEfficiency_ = 0.0;


    // Out values
    double grossHeat_;
    double requiredPower_;
};

#endif //AMO_TOOLS_SUITE_ELECTRICFLUEGASLOSS_H
