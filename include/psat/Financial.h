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
     * @param operatingFraction Fraction(%) of calender hours the equipment is operating.
     * @param unitCost Per unit energy cost of electricity in $/kwhr.
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

    double getOperatingFraction() const {
        return operatingFraction_;
    }

    void setOperatingFraction(double operatingFraction) {
        operatingFraction_ = operatingFraction;
    }

    double getUnitCost() const {
        return unitCost_;
    }

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
