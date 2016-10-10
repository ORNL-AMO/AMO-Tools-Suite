//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorEfficiency.h"
#include  <iostream>

double MotorEfficiency::calculate() {



        /*
         * Calculating the 1% interval values based on the load factor
         * 0 - 25
         * 1. Using the 0% and 25% kW loss values, develop a linear table of loss by 1% load
         * Equation: kWloss (X) = kWloss (0) + X * (kWloss(25) - kWloss(0))/25      where X = 0,1,2,3…..25
         * 2. Assemble an array of shaft power from 0 to 25
         * Equation: kW shaft (X) = rated hp *0.746 * (X / 100)
         * Assemble an array of kWe (input electric power
         * Equation: kWe(X) = kWloss(x) + kWshaft(X)
         * Calculate efficiency
         * Equation: Eff(X) = kW shaft (X) / kWe (X)
         */

        /*
         * Setting up kWloss0 and kWloss25
         * Make sure motoEfficiency is in decimal rather %.
         * E.g.: 0.92 is correct, 92 is wrong.
         */


        std::cout << std::endl;
        if(efficiencyClass_==Motor::EfficiencyClass::ENERGY_EFFICIENT) {
            MotorEfficiency25 motorEfficiency25(efficiencyClass_, motorRatedPower_);
            motorEfficiency_ = motorEfficiency25.calculate();
        }
        else if (efficiencyClass_==Motor::EfficiencyClass::STANDARD){
            MotorEfficiency25 motorEfficiency25(efficiencyClass_, motorRatedPower_);
            motorEfficiency_ = motorEfficiency25.calculate();
        }
        else if (efficiencyClass_==Motor::EfficiencyClass::SPECIFIED){

            MotorEfficiency25 eeMotorEfficiency(Motor::EfficiencyClass::ENERGY_EFFICIENT, motorRatedPower_);
            double *motorEfficiencyE_ = eeMotorEfficiency.calculate();
            motorEfficiency_ = eeMotorEfficiency.calculate();
            MotorEfficiency25 seMotorEfficiency(Motor::EfficiencyClass::STANDARD, motorRatedPower_);
            double *motorEfficiencyS_ = seMotorEfficiency.calculate();


            if(fabs(motorEfficiencyE_[3] - specifiedEfficiency_) > fabs(motorEfficiencyS_[3] - specifiedEfficiency_)){
                //SE chosen
                double C = specifiedEfficiency_/motorEfficiencyS_[3];
                for (int i = 0; i < 5; ++i) {
                    motorEfficiency_[i] = motorEfficiencyS_[i]*C;
                }
            }
            else{ // EE chosen
                specifiedEfficiency_ = specifiedEfficiency_/100;
                double C = specifiedEfficiency_/motorEfficiencyE_[3];


                for (int i = 0; i < 5; ++i) {
                    motorEfficiency_[i] = motorEfficiencyE_[i]*C;

                }
            }
        }

        for (int j = 0; j < 5; ++j) {
            std::cout << motorEfficiency_[j] << ":";

        }
        std::cout << std::endl;

        double kWloss25 = ((1 / motorEfficiency_[0]) - 1) * motorRatedPower_ * 0.746 * 0.25;
        double kWloss0 = 0.8 * kWloss25;

        /*
         * Note: Above is for EE or SE. More calculations are required for Specified Efficiency
         */


        if (loadFactor_ <= 0.25) {
            double kWloss_ = kWloss0 + loadFactor_ * (kWloss25 - kWloss0) / 25;
            double kWshaft_ = motorRatedPower_ * 0.746 * (loadFactor_); // Make sure motorRatedPower is in hp
            double kWe_ = kWloss_ + kWshaft_; // Input electric power
            motorEff_ = kWshaft_ / kWe_; //Final efficiency calculation
            std::cout << "In25 lf: " << loadFactor_ << "motoreff: " << motorEff_ << std::endl;
        }
            /*
             * 26 - 125
             * Fitting tabular, 25% interval, motor efficiency data to assemble an overall curve with 1% interval data from 26 to 150%
             * 25% load interval efficiency values come from "Adjusting 25 percent arrays for specified efficiency"
             * Pick the 25,50,75,100,and 125% motor efficiency values and do a 4th order polynomial fit.
             * Use the fit coefficients to popluate, in 1% load intervals, from 26 to 125% load
             */

        else if (loadFactor_ <= 1.25 && loadFactor_ > 0.25) {
            double xCoord_[5] = {.25, .50, .75, 1.00, 1.25};
            double yCoord_[5] = {motorEfficiency_[0], motorEfficiency_[1], motorEfficiency_[2], motorEfficiency_[3],
                                 motorEfficiency_[4]};
            CurveFitVal cfv(5, xCoord_, motorEfficiency_, 4, loadFactor_);
            motorEff_ = cfv.calculate();
            std::cout << "In125 lf: " << loadFactor_ << "motoreff: " << motorEff_ << std::endl;
        }
            /*
             * 126 - 150
             * Pick the 75, 100, and 125% motor efficiency values and do a 2nd order polynomial fit
             * Use the fit coefficients to populate, in 1% load intervals, the current range from 126 to 150% load
             */
        else if (loadFactor_ <= 1.50 && loadFactor_ > 1.25) {
            double xCoord_[3] = {.75, 1.00, 1.25};
            double yCoord_[3] = {motorEfficiency_[2], motorEfficiency_[3], motorEfficiency_[4]};
            CurveFitVal cfv(3, xCoord_, yCoord_, 2, loadFactor_);
            motorEff_ = cfv.calculate();
        }
        /*
         * When ready uncomment the below.
         */
    //}
/*    else{
        motorEff_ = specifiedEfficiency_;
    }*/
    std::cout << "Out lf: " << loadFactor_ << "motoreff: " << motorEff_ << std::endl;
    return motorEff_;
    //return 94.36;
}
