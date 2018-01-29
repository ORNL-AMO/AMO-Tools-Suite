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
     * @param fieldPower double, power from field data in hp
     * @param operatingFraction double, perating fraction(%).
     */
    AnnualEnergy(
        double fieldPower,
        double operatingFraction
    ) :
        fieldPower(fieldPower),
        operatingFraction(operatingFraction)
    {}

    /**
     * Calculates annual energy
     * @return double, annual energy in MWh/year
     */
    double calculate();

    /**
     * Getter for field power
     * @return double, power from field data in hp
     */
    double getFieldPower() const {
        return fieldPower;
    }

    /**
     * Setter for field power
     * @param fieldPower double, power from field data in hp
     */
    void setFieldPower(double fieldPower) {
        this->fieldPower = fieldPower;
    }

    /**
     * Getter for operating fraction
     * @return double, operating fraction as %
     */
    double getOperatingFraction() const {
        return operatingFraction;
    }

    /**
     * Setter for operating fraction
     *
     * @param operatingFraction double, operating fraction as %
     *
     */
    void setOperatingFraction(double operatingFraction) {
        this->operatingFraction = operatingFraction;
    }

private:
    /**
     * Power from field data in kWe: kilo Watts electrical
     */
    double fieldPower;
    /**
     * Operating fraction
     */
    double operatingFraction;
    /**
     * Annual energy in MWh/year
     */
    double annualEnergy;
};


#endif //AMO_LIBRARY_ANNUALENERGY_H
