/**
 * @file
 * @brief Function prototypes for the Annual Energy
 *
 * This contains the prototypes for the Annual Energy
 * including getters and setters for the important fields.
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

    AnnualEnergy(double fieldPower, double operatingFraction) : fieldPower_(fieldPower),
                                                                operatingFraction_(operatingFraction) {}

    double calculate();

    double getFieldPower() const {
        return fieldPower_;
    }

    void setFieldPower(double fieldPower) {
        fieldPower_ = fieldPower;
    }

    double getOperatingFraction() const {
        return operatingFraction_;
    }

    void setOperatingFraction(double operatingFraction) {
        operatingFraction_ = operatingFraction;
    }

private:
    double fieldPower_; // in kWe - kilo Watts electrical
    double operatingFraction_;
    double annualEnergy_; // in MWh/year
};


#endif //AMO_LIBRARY_ANNUALENERGY_H
