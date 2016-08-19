//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_ANNUALCOST_H
#define AMO_LIBRARY_ANNUALCOST_H

class AnnualCost {
public:
    AnnualCost(double annualEnergy, double kwhRate) : annualEnergy_(annualEnergy), kwhRate_(kwhRate) {}

    double calculate();

    double getAnnualEnergy() const {
        return annualEnergy_;
    }

    void setAnnualEnergy(double annualEnergy) {
        annualEnergy_ = annualEnergy;
    }

    double getKwhRate() const {
        return kwhRate_;
    }

    void setKwhRate(double kwhRate) {
        kwhRate_ = kwhRate;
    }

private:
    double annualEnergy_;
    double kwhRate_;
};

#endif //AMO_LIBRARY_ANNUALCOST_H
