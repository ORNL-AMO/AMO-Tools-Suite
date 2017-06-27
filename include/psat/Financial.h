/**
 * @file
 * @brief Function prototypes for the Financial fields
 *
 * This contains the prototypes for the Financial structure
 * including getters and setters for the important fields. Primary
 * importance are methods for setting and getting data dealing with
 * financial information.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_FINANCIALS_H
#define AMO_LIBRARY_FINANCIALS_H


class Financial {
public:

    /**
     * Constructor
     * @param operatingFraction double, fraction(%) of calender hours the equipment is operating
     * @param unitCost double, per unit energy cost of electricity in $/kwh
     * @return nothing
     */

    Financial(
        double operatingFraction,
        double unitCost
    ) :
        operatingFraction_(operatingFraction),
        unitCost_(unitCost)
    {}

    Financial() = default;

    /**
    * Gets the percentage of calendar hours the equipment is operating
    *
    * @return double, fraction of calendar hours the equipment is operating as %
    */
    double getOperatingFraction() const {
        return operatingFraction_;
    }

    /**
   * Sets the percentage of calendar hours the equipment is operating
   *
   * @param operatingFraction double, fraction of calendar hours the equipment is operating as %
   *
   * @return nothing
   */
    void setOperatingFraction(double operatingFraction) {
        operatingFraction_ = operatingFraction;
    }

    /**
   * Gets the cost of electricity per unit energy
   *
   * @return double, cost of electricity per unit energy in $/kwh
   */
    double getUnitCost() const {
        return unitCost_;
    }

    /**
   * Sets the cost of electricity per unit energy
   *
   * @param unitCost double, cost of electricity per unit in $/kwh
   *
   * @return nothing
   */
    void setUnitCost(double unitCost) {
        unitCost_ = unitCost;
    }

private:
    // 1.0 is 100%
    double operatingFraction_;
    // All units kWhr
    double unitCost_;
};


#endif //AMO_LIBRARY_FINANCIALS_H
