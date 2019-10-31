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
     * @param operatingHours double, hours per year equipment is at conditions.
     */
    AnnualEnergy(
        double fieldPower,
        double operatingHours
    ) :
        fieldPower(fieldPower),
        operatingHours(operatingHours)
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
     * @return double, operating hours as hour/year
     */
    double getoperatingHours() const {
        return operatingHours;
    }

    /**
     * Setter for operating fraction
     *
     * @param operatingHours double, operating hours as hour/year
     *
     */
    void setoperatingHours(double operatingHours) {
        this->operatingHours = operatingHours;
    }

private:
    /**
     * Power from field data in kWe: kilo Watts electrical
     */
    double fieldPower;
    /**
     * Operating fraction
     */
    double operatingHours;
    /**
     * Annual energy in MWh/year
     */
    double annualEnergy;
};


#endif //AMO_LIBRARY_ANNUALENERGY_H
