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

/**
 * Financial class
 * Contains the properties relating to the cost of operating equipment.
 */
class Financial {
public:

    /**
     * Constructor
     * @param operatingFraction double, fraction(%) of calender hours the equipment is operating
     * @param unitCost double, per unit energy cost of electricity in $/kwh
     */

    Financial(
        double operatingFraction,
        double unitCost
    ) :
        operatingFraction(operatingFraction),
        unitCost(unitCost)
    {}

    Financial() = default;

    /**
    * Gets the percentage of calendar hours the equipment is operating
    * @return double, fraction of calendar hours the equipment is operating as %
    */
    double getOperatingFraction() const {
        return operatingFraction;
    }

    /**
   * Sets the percentage of calendar hours the equipment is operating
   * @param operatingFraction double, fraction of calendar hours the equipment is operating as %
   */
    void setOperatingFraction(double operatingFraction) {
        this->operatingFraction = operatingFraction;
    }

    /**
   * Gets the cost of electricity per unit energy
   * @return double, cost of electricity per unit energy in $/kwh
   */
    double getUnitCost() const {
        return unitCost;
    }

    /**
   * Sets the cost of electricity per unit energy
   * @param unitCost double, cost of electricity per unit in $/kwh
   */
    void setUnitCost(double unitCost) {
        this->unitCost = unitCost;
    }

private:
    // 1.0 is 100%
    double operatingFraction;
    // All units kWhr
    double unitCost;
};


#endif //AMO_LIBRARY_FINANCIALS_H
