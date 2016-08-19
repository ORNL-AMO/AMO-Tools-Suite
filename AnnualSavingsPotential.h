//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_ANNUALSAVINGSPOTENTIAL_H
#define AMO_LIBRARY_ANNUALSAVINGSPOTENTIAL_H


class AnnualSavingsPotential {
public:

    AnnualSavingsPotential(double existingAnnualCost, double optimalAnnualCost) : existingAnnualCost_(
            existingAnnualCost), optimalAnnualCost_(optimalAnnualCost) {}

    double calculate();

    double getExistingAnnualCost() const {
        return existingAnnualCost_;
    }

    void setExistingAnnualCost(double existingAnnualCost) {
        existingAnnualCost_ = existingAnnualCost;
    }

    double getOptimalAnnualCost() const {
        return optimalAnnualCost_;
    }

    void setOptimalAnnualCost(double optimalAnnualCost) {
        optimalAnnualCost_ = optimalAnnualCost;
    }


private:
    double existingAnnualCost_;
    double optimalAnnualCost_;
};


#endif //AMO_LIBRARY_ANNUALSAVINGSPOTENTIAL_H
