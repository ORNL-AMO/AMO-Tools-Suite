/**
 * @brief Function prototypes for the Annual Energy
 *
 * This contains the prototypes for the Annual Energy calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_ANNUALENERGY_H
#define AMO_LIBRARY_ANNUALENERGY_H


class AnnualEnergy {
public:
    /**
     * Constructor
     * @param fieldPower Power from field data in hp kW.
     * @param operatingFraction Operating fraction(%).
     * @return nothing
     */
    AnnualEnergy(
        double fieldPower,
        double operatingFraction
    ) :
        fieldPower_(fieldPower),
        operatingFraction_(operatingFraction)
    {}

    /**
     * Calculates annual energy
     * @return annual energy
     */
    double calculate();

    /**
     * Getter for field power
     * @return power from field data
     */
    double getFieldPower() const {
        return fieldPower_;
    }

    /**
     * Setter for field power
     * @param fieldPower
     */
    void setFieldPower(double fieldPower) {
        fieldPower_ = fieldPower;
    }

    /**
     * Getter for operating fraction
     * @return operating fraction
     */
    double getOperatingFraction() const {
        return operatingFraction_;
    }

    /**
     * Setter for operating fraction
     * @param operatingFraction
     */
    void setOperatingFraction(double operatingFraction) {
        operatingFraction_ = operatingFraction;
    }

private:
    /**
     * Power from field data in kWe: kilo Watts electrical
     */
    double fieldPower_;
    /**
     * Operating fraction
     */
    double operatingFraction_;
    /**
     * Annual energy in MWh/year
     */
    double annualEnergy_;
};


#endif //AMO_LIBRARY_ANNUALENERGY_H
