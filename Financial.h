//
// Created by Accawi, Gina K. on 6/15/16.
//

#ifndef AMO_LIBRARY_FINANCIALS_H
#define AMO_LIBRARY_FINANCIALS_H


class Financial {
public:
    Financial();
    Financial(double operatingFraction, double unitCost);
    void setOperatingFraction(double operatingFraction);
    void setUnitCost(double unitCost);
    double getOperatingFraction(void);
    double getUnitCost(void);

private:
    // 1.0 is 100%
    double operatingFraction_;
    // All units kWhr
    double unitCost_;
};


#endif //AMO_LIBRARY_FINANCIALS_H
