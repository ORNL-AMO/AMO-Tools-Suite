/**
 * @brief Contains the definition of functions of EstimateFLA class.
 *      calculate(): Calculates the estimated FLA and 25% interval values of Current.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

//
// Created by Mishra, Subhankar on 10/4/16.
//

#include "calculator/EstimateFLA.h"
#include "calculator/MotorEfficiency.h"
#include "calculator/Poles.h"
#include <cmath>

/**
 * Estimating FLA methodology
 * - PSAT has four different methods of estimating FLA, with the four methods corresponding to the four efficiency choices.
 *  - For Standard Efficiency selection, it selects the FLA for the motor size and speed class that has been selected.  For example, the SE FLA for a 200 hp 4-pole motor is 228.6 amps.
 *  - For Energy Efficient selection, it selects the FLA for the motor size and speed class that has been selected.  For example, the EE FLA for a 200 hp 4-pole motor is 225.8 amps.
 *  - For Average Efficiency selection, it averages the FLA for Energy Efficient and Standard Efficiency choices.  The average of the two values listed above is 227.2 amps, which is what PSAT returns.
 *  - For a case where the efficiency has been specified, there is a multiple step process:
 *      1. The absolute value of the differences between the specified efficiency and the efficiency values for EE and SE motors are calculated
 *      2. Pick the smaller of the two absolute values, and use the nominal efficiency of that selection going forward
 *      3. Divide the selected (EE or SE) efficiency by the specified efficiency and then multiply that by the FLA for the corresponding selection.  See the example below.
 *
 * 	EE	SE	Specified		Choose:
 * Full load efficiency	95.63	93.92	95.0		EE
 * Full load amps (FLA)	225.8	228.6	227.3
 *
 * In this case, the specified efficiency is closer to the EE value, so the EE FLA and EE efficiency values are used.
 *
 * Equation for the calculation is:
 * Estimated FLA (specified efficiency) =EE FLA * (EE full load efficiency / Specified efficiency)
 * or, if the specified efficiency is closer to SE,
 * Estimated FLA (specified efficiency) =SE FLA * (SE full load efficiency / Specified efficiency)
 *
 * Nameplate voltage adjustment
 * If the motor nameplate is other than 460 V, the Estimate FLA process includes one more adjustment
 * Use an example of a motor known to have a 575 volt rating, but the FLA is not readable and the user wants to Estimate the FLA
 * The process is the same as above, except that the estimated FLA is adjusted in inverse proportion to the rated voltage.
 *
 * Estimated FLA (575) = Estimated FLA (460) * (460/575)
 * Estimated FLA (575)=	181.8
 *
 * @return 25% interval values of current.
 */
std::vector<double> EstimateFLA::calculate() {
    std::vector<double> plValues(6);
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
     * Part load coefficients, 2004
     */
    double p2Coeff_[5][6] = {
            {0.2385152,  0.31999999, 0.51999998, 0.75400001, 1, 1.253},
            {0.04319932, 0.03559835, 0.02311537, 0.00837315, 0, 0},
            {0.01191111, 0.00243387, 0.00018377, 0.00013998, 0, 0},
            {0.176818,   0.1282783,  0.08376596, 0.03318606, 0, 0},
            {0.1847319,  0.1831789,  0.16219489, 0.1855139,  0, 0}
    };
    double p4Coeff_[5][6] = {
            {0.26803651, 0.3535319,  0.54000002, 0.76428652, 1, 1.251},
            {0.08,       0.06387088, 0.02691548, 0.0081415,  0, 0},
            {0.01172604, 0.01068725, 0.00297117, 0.00686711, 0, 0},
            {0.2029126,  0.1705882,  0.09793611, 0.0471422,  0, 0},
            {0.15413959, 0.1315202,  0.09374535, 0.1191377,  0, 0}
    };
    double p6Coeff_[5][6] = {
            {0.28999999, 0.39519981, 0.55500001, 0.76973772, 1, 1.254},
            {0.07532283, 0.06387088, 0.03,       0.02362101, 0, 0},
            {0.00291026, 0.01068725, 0.00380051, 0.08841167, 0, 0},
            {0.2405144,  0.1705882,  0.13686571, 0.02321446, 0, 0},
            {0.09842682, 0.1315202,  0.15484551, 0.08854395, 0, 0}
    };
    double p8Coeff_[5][6] = {
            {0.33000001, 0.43000001, 0.56062472, 0.78429687, 1, 1.237},
            {0.06,       0.1060414,  0.04872012, 0.00763685, 0, 0},
            {0.00125301, 0.031788,   0.00041673, 0.0023581,  0, 0},
            {0.1939563,  0.115,      0.0841061,  0.00756603, 0, 0},
            {0.05575958, 0.15824869, 0.05538078, 0.00250876, 0, 0}
    };
    double p10Coeff_[5][6] = {
            {0.37,       0.44,       0.57857579, 0.78581947, 1, 1.233},
            {0.04507853, 0.04205693, 0.06270286, 0.01749944, 0, 0},
            {0.00098519, 0.00121622, 0.0005819,  0.00068763, 0, 0},
            {0.20683549, 0.1764105,  0.08895831, 0.01809594, 0, 0},
            {0.0551472,  0.05516704, 0.05197735, 0.03981217, 0, 0}
    };
    double p12Coeff_[5][6] = {
            {0.41999999, 0.5,        0.61000001, 0.80000001, 1, 1.215},
            {0.04507853, 0.04205693, 0.06270286, 0.01749944, 0, 0},
            {0.00098519, 0.00121622, 0.0005819,  0.00068763, 0, 0},
            {0.20683549, 0.1764105,  0.08895831, 0.01809594, 0, 0},
            {0.0551472,  0.05516704, 0.05197735, 0.03981217, 0, 0}
    };


    /**
     * Calculate the number of poles based on the RPM
     */
    Poles polesobj(motorRPM_, lineFrequency_);
    int poles = polesobj.calculate();

    /**
     * Index for the arrays based on the pole
     */
    int poleChooser_ = poles / 2 - 1;

    /**
     * Calculate basic FLA value. There is better way to do this.
     * =$B13*(C$4+(C$5*EXP(-C$6*$B13))+(C$7*EXP(-C$8*$B13)))
     */
    double basicFLAValue_ = motorRatedPower_ * (flaBasic_[0][poleChooser_] +
                                                (flaBasic_[1][poleChooser_] *
                                                 exp(-1 * flaBasic_[2][poleChooser_] * motorRatedPower_)) +
                                                (flaBasic_[3][poleChooser_] *
                                                 exp(-1 * flaBasic_[4][poleChooser_] * motorRatedPower_)));
    /**
     * Calculate EE multiplier
     */
    double eeMultiplier = (eeFlamultipliers_[0][poleChooser_] +
                           (eeFlamultipliers_[1][poleChooser_] *
                            exp(-1 * eeFlamultipliers_[2][poleChooser_] * motorRatedPower_)) +
                           (eeFlamultipliers_[3][poleChooser_] *
                            exp(-1 * eeFlamultipliers_[4][poleChooser_] * motorRatedPower_)));
    /**
     * Calculate SE multiplier
     */
    double seMultiplier = (seFlamultipliers_[0][poleChooser_] +
                           (seFlamultipliers_[1][poleChooser_] *
                            exp(-1 * seFlamultipliers_[2][poleChooser_] * motorRatedPower_)) +
                           (seFlamultipliers_[3][poleChooser_] *
                            exp(-1 * seFlamultipliers_[4][poleChooser_] * motorRatedPower_)));

    /**
     * Calculate EE or SE values
     */
    double eeFLAValue = eeMultiplier * basicFLAValue_;
    double seFLAValue = seMultiplier * basicFLAValue_;

    /**
     * Select partial load multipliers based on pole. There is better way to do this.
     */
    double tempCoeff[5][6];
    if (poleChooser_ == 0) std::copy(&p2Coeff_[0][0], &p2Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 1) std::copy(&p4Coeff_[0][0], &p4Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 2) std::copy(&p6Coeff_[0][0], &p6Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 3) std::copy(&p8Coeff_[0][0], &p8Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 4) std::copy(&p10Coeff_[0][0], &p10Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);
    if (poleChooser_ == 5) std::copy(&p12Coeff_[0][0], &p12Coeff_[0][0] + 5 * 6, &tempCoeff[0][0]);

    /**
     * Calculating Multiplier for partial loads in 25% intervals
     */
    double plMultiplier[6] = {};

    for (int i = 0; i < 6; i++) {
        plMultiplier[i] = (tempCoeff[0][i] +
                           (tempCoeff[1][i] *
                            exp(-1 * tempCoeff[2][i] * motorRatedPower_)) +
                           (tempCoeff[3][i] *
                            exp(-1 * tempCoeff[4][i] * motorRatedPower_)));
    }

    /**
     * Calculating the 25% interval Amps
     */

    double effVal = 0.0;

    if (efficiencyClass_ == Motor::EfficiencyClass::ENERGY_EFFICIENT) {
        for (int i = 0; i < 6; i++) {
            plValues[i] = eeFLAValue * plMultiplier[i];
        }

    } else if (efficiencyClass_ == Motor::EfficiencyClass::STANDARD) {
        for (int i = 0; i < 6; i++) {
            plValues[i] = seFLAValue * plMultiplier[i];
        }
    } else if (efficiencyClass_ == Motor::EfficiencyClass::SPECIFIED) {
        /**
         * For a case where the efficiency has been specified, there is a multiple step process:
         * 1. The absolute value of the differences between the specified efficiency and the efficiency values for EE and SE motors are calculated
         * 2. Pick the smaller of the two absolute values, and use the nominal efficiency of that selection going forward
         * 3. Divide the selected (EE or SE) efficiency by the specified efficiency and then multiply that by the FLA for the corresponding selection.
         */
        specifiedEfficiency_ = 95;
        if (fabs(eeFLAValue * plMultiplier[4] - specifiedEfficiency_) >
            fabs(seFLAValue * plMultiplier[4] - specifiedEfficiency_)) {
            MotorEfficiency motorEfficiency(lineFrequency_,motorRPM_, Motor::EfficiencyClass::STANDARD, specifiedEfficiency_,
                                            motorRatedPower_, 1);
            effVal = motorEfficiency.calculate();
            /// SE is the nominal efficiency
            for (int i = 0; i < 6; i++) {
                plValues[i] = seFLAValue * plMultiplier[i];

                //plValues[i] = seEff * plValues[i] * 100 / specifiedEfficiency_;
            }
        } else {
            /// EE is the nominal efficiency
            MotorEfficiency motorEfficiency(lineFrequency_,motorRPM_, Motor::EfficiencyClass::ENERGY_EFFICIENT, specifiedEfficiency_,
                                            motorRatedPower_, 1);
            effVal = motorEfficiency.calculate();
            for (int i = 0; i < 6; i++) {
                plValues[i] = eeFLAValue * plMultiplier[i];
                //plValues[i] = eeEff * plValues[i] * 100 / specifiedEfficiency_;
            }
        }
    }


    /// Estimated FLA refers to the 100% value.
    double tempAmp100 = plValues[4];
    plValues[4] = plValues[4] * 460 / ratedVoltage_;
    if (efficiencyClass_ == Motor::EfficiencyClass::SPECIFIED) {
        estimatedFLA_ = effVal * plValues[4] * 100 / specifiedEfficiency_;
    } else
        estimatedFLA_ = plValues[4];
    plValues[4] = tempAmp100;
    return plValues;
}
