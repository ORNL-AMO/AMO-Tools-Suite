//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorShaftPower.h"


double MotorShaftPower::calculate() {
    /* Declaring local variables for now, will change later after I figure out everything !!
     /*
     * FLA Basic coefficients
     */
    double flaBasic_[5][6] = {
            {1.07000005, 1.07860196, 1.11131799, 1.20000005, 1.25399995, 1.296},
            {0.04457,    0.06776789, 0.1038059,  0.09800907, 0.10241948, 0.1058498},
            {0.00075042, 0.00112793, 0.00208467, 0.00239285, 0.00239285, 0.00239285},
            {0.1177211,  0.1706723,  0.3346993,  0.44619089, 0.46626949, 0.48188618},
            {0.0328443,  0.03456966, 0.1037901,  0.07508431, 0.07508431, 0.07508431}
    };
    /*
     * FLA EE Multipliers
     */
    double eeFlamultipliers_[5][6] = {
            {0.99800003,  0.99959999,  0.99800003,  0.995,       0.995,       0.995},
            {-0.00686105, -0.00768858, -0.01313299, -0.02334039, -0.02334039, -0.02334039},
            {0.00086324,  0.00471104,  0.01482941,  0.05637734,  0.05637734,  0.05637734},
            {-0.02477271, -0.01760195, -0.2489823,  -0.79541528, -0.79541528, -0.79541528},
            {0.07267418,  0.04482816,  0.63720071,  0.59844083,  0.59844083,  0.59844083}
    };

    /*
     * FLA SE Multipliers
     */
    double seFlamultipliers_[5][6] = {
            {1.00199997, 1.00150001, 1.00399995, 1.005,       1.005,       1.005},
            {0.0305805,  0.02305459, 0.06148619, 0.04535436,  0.04535436,  0.04535436},
            {0.00538086, 0.00630689, 0.01415263, 0.01991553,  0.01991553,  0.01991553},
            {0.02411943, 0.02706193, 1.247298,   24.98793983, 24.98793983, 24.98793983},
            {0.03430828, 0.01757208, 0.72734421, 1.14514899,  1.14514899,  1.14514899}
    };

    /*
     * Part load coefficients
     */
    double p2Coeff_[5][6] = {
            {0.239, 0.320, 0.520, 0.754, 1, 1.253},
            {0.043, 0.036, 0.023, 0.008, 0, 0},
            {0.012, 0.002, 0.000, 0.000, 0, 0},
            {0.177, 0.128, 0.084, 0.033, 0, 0},
            {0.185, 0.183, 0.162, 0.186, 0, 0}
    };
    double p4Coeff_[5][6] = {
            {0.268, 0.354, 0.540, 0.764, 1, 1.251},
            {0.080, 0.064, 0.027, 0.008, 0, 0},
            {0.012, 0.011, 0.003, 0.007, 0, 0},
            {0.203, 0.171, 0.098, 0.047, 0, 0},
            {0.154, 0.132, 0.094, 0.119, 0, 0}

    };
    double p6Coeff_[5][6] = {
            {0.290, 0.395, 0.555, 0.770, 1, 1.254},
            {0.075, 0.064, 0.030, 0.024, 0, 0},
            {0.003, 0.011, 0.004, 0.088, 0, 0},
            {0.241, 0.171, 0.137, 0.023, 0, 0},
            {0.098, 0.132, 0.155, 0.089, 0, 0}

    };
    double p8Coeff_[5][6] = {
            {0.330, 0.430, 0.561, 0.784, 1, 1.237},
            {0.060, 0.106, 0.049, 0.008, 0, 0},
            {0.001, 0.032, 0.000, 0.002, 0, 0},
            {0.194, 0.115, 0.084, 0.008, 0, 0},
            {0.056, 0.158, 0.055, 0.003, 0, 0}

    };
    double p10Coeff_[5][6] = {
            {0.370, 0.440, 0.579, 0.786, 1, 1.233},
            {0.045, 0.042, 0.063, 0.017, 0, 0},
            {0.001, 0.001, 0.001, 0.001, 0, 0},
            {0.207, 0.176, 0.089, 0.018, 0, 0},
            {0.055, 0.055, 0.052, 0.040, 0, 0}


    };
    double p12Coeff_[5][6] = {
            {0.420, 0.500, 0.610, 0.800, 1, 1.215},
            {0.045, 0.042, 0.063, 0.017, 0, 0},
            {0.001, 0.001, 0.001, 0.001, 0, 0},
            {0.207, 0.176, 0.089, 0.018, 0, 0},
            {0.055, 0.055, 0.052, 0.040, 0, 0}
    };


    /*
     * Calculate the number of poles based on the RPM
     */
    int poles;
    if (motorRPM_ > 3600) {
        poles = 2;
    } else {
        if (floor(floor(7200 / motorRPM_) / 2) * 2 > 12) {
            poles = 12;
        } else {
            poles = floor(floor(7200 / motorRPM_) / 2) * 2;
        }
    }
    /*
     * Index for the arrays based on the pole
     */
    int poleChooser_ = poles / 2 - 1;

    /*
     * Calculate basic FLA value. There is better way to do this.
     * =$B13*(C$4+(C$5*EXP(-C$6*$B13))+(C$7*EXP(-C$8*$B13)))
     */
    double basicFLAValue_ = motorPower_ * (flaBasic_[0][poleChooser_] +
                                           (flaBasic_[1][poleChooser_] *
                                            exp(-1 * flaBasic_[2][poleChooser_] * motorPower_)) +
                                           (flaBasic_[3][poleChooser_] *
                                            exp(-1 * flaBasic_[4][poleChooser_] * motorPower_)));
    /*
     * Calculate EE multiplier
     */
    double eeMultiplier = (eeFlamultipliers_[0][poleChooser_] +
                           (eeFlamultipliers_[1][poleChooser_] *
                            exp(-1 * eeFlamultipliers_[2][poleChooser_] * motorPower_)) +
                           (eeFlamultipliers_[3][poleChooser_] *
                            exp(-1 * eeFlamultipliers_[4][poleChooser_] * motorPower_)));
    /*
     * Calculate SE multiplier
     */
    double seMultiplier = (seFlamultipliers_[0][poleChooser_] +
                           (seFlamultipliers_[1][poleChooser_] *
                            exp(-1 * seFlamultipliers_[2][poleChooser_] * motorPower_)) +
                           (seFlamultipliers_[3][poleChooser_] *
                            exp(-1 * seFlamultipliers_[4][poleChooser_] * motorPower_)));

    /*
     * Calculate EE or SE values
     */
    double eeFLAValue = eeMultiplier * basicFLAValue_;
    double seFLAValue = seMultiplier * basicFLAValue_;

    /*
     * Select partial load multipliers based on pole. There is better way to do this.
     */
    double tempCoeff[5][6];
    if (poleChooser_ == 0) std::copy(&p2Coeff_[0][0], &p2Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 1) std::copy(&p4Coeff_[0][0], &p4Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 2) std::copy(&p6Coeff_[0][0], &p6Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 3) std::copy(&p8Coeff_[0][0], &p8Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 4) std::copy(&p10Coeff_[0][0], &p10Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 5) std::copy(&p12Coeff_[0][0], &p12Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);

    /*
     * Calculating Multiplier for partial loads in 25% intervals
     */
    double plMultiplier[6];

    for (int i = 0; i < 6; i++) {
        plMultiplier[i] = (tempCoeff[0][i] +
                           (tempCoeff[1][i] *
                            exp(-1 * tempCoeff[2][i] * motorPower_)) +
                           (tempCoeff[3][i] *
                            exp(-1 * tempCoeff[4][i] * motorPower_)));
    }

    /*
     * Calculating the 25% interval Amps
     */
    double plValues[6];
    if (efficiencyClass_ == EfficiencyClass::ENERGY_EFFICIENT) {
        for (int i = 0; i < 6; i++) {
            plValues[i] = eeFLAValue * plMultiplier[i];
        }

    } else if (efficiencyClass_ == EfficiencyClass::STANDARD) {
        for (int i = 0; i < 6; i++) {
            plValues[i] = seFLAValue * plMultiplier[i];
        }
    };

    /*
     * ****************************************************************
     */
    double loadfraction_ = 0.5;//vlookup
    double motorPowerKWe_ = 79.085;//vlookup (loadfraction_)
    double loadfraction2_ = loadfraction_ + 0.01;
    double motorPowerKWe2_ = 80.626; //vlookup (loadfraction2_)
    double motorPowerdiff_ = motorPowerKWe2_ - motorPowerKWe_;
    double measuredMotorPowerdiff_ = measuredPower_ - motorPowerKWe_;
    double fractionalIndex_ = loadfraction_ + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
    /*
     * Calculate rest of the interpolated values as well as the motorShaftPower
     */
    motorShaftPower_;
    return 101.19;
}