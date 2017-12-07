/**
 * @brief Header file for AnnualCost class
 *
 * This contains the prototypes of AnnualCost calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


#ifndef AMO_LIBRARY_ANNUALCOST_H
#define AMO_LIBRARY_ANNUALCOST_H

class AnnualCost {
public:
    /**
     * Constructor
     * @param annualEnergy double, annual energy consumption in MWh/year
     * @param kwhRate double, rate in $/kWh
     */
    AnnualCost(
        double annualEnergy,
        double kwhRate
    ) :
        annualEnergy_(annualEnergy),
        kwhRate_(kwhRate)
    {}

    /**
     * Calculates the annual energy cost
     * @return double, annual energy cost in $/year
     */
    double calculate();

    /**
     * Getter for annual energy.
     * @return double, annual energy in MWh/year
     */
    double getAnnualEnergy() const {
        return annualEnergy_;
    }

    /**
     * Setter for annual energy
     * @param annualEnergy double, annual energy consumption in MWh/year
     */
    void setAnnualEnergy(double annualEnergy) {
        annualEnergy_ = annualEnergy;
    }

    /**
     * Getter for the rate in $/kWh
     * @return double, rate in $/kWh
     */
    double getKwhRate() const {
        return kwhRate_;
    }

    /**
     * Setter for rate in $/kWh
     * @param kwhRate double, rate in $/kwh
     */
    void setKwhRate(double kwhRate) {
        kwhRate_ = kwhRate;
    }

private:
    /**
     * Annual Energy in MWh/year
     */
    double annualEnergy_;
    /**
     * Rate in $/kWh
     */
    double kwhRate_;
    /**
     * Annual Energy Cost
     */
    double annualEnergyCost_; // in $
};

#endif //AMO_LIBRARY_ANNUALCOST_H
