//
// Created by Accawi, Gina K. on 6/15/16.
//

#ifndef AMO_LIBRARY_FINANCIALS_H
#define AMO_LIBRARY_FINANCIALS_H


class Financial {
public:
    Financial(double operatingFraction, double unitCost) : operatingFraction_(operatingFraction), unitCost_(unitCost) {}

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
