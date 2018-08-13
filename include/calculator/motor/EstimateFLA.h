/**
 * @brief EstimateFLA class.
 *  This contains the prototypes for the Estimate FLA calculator and 25% interval value calculator.
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef UNTITLED_ESTIMATEFLA_H
#define UNTITLED_ESTIMATEFLA_H

#include <vector>
#include <results/InputData.h>

class EstimateFLA {
public:
    /**
     * Constructor
     * @param motorRatedPower double, rated power of motor in hp
     * @param motorRPM double, RPM of motor
     * @param lineFrequency Motor::LineFrequency, line frequency of motor in 50Hz or 60Hz
     * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor
     * @param specifiedEfficiency double, specified efficiency of motor as defined by %
     * @param ratedVoltage double, rated voltage of motor in volts
     */
    EstimateFLA(
        double motorRatedPower,
        double motorRPM,
        Motor::LineFrequency lineFrequency,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double ratedVoltage
    ) :
        motorRatedPower(motorRatedPower),
        motorRPM(motorRPM),
        lineFrequency(lineFrequency),
        efficiencyClass(efficiencyClass),
        specifiedEfficiency(specifiedEfficiency),
        ratedVoltage(ratedVoltage)
    {};

    /**
     * Calculates the 25% interval
     * @return std::array<double, 6>, 25% interval values of current.
     */
    std::array<double, 6> calculate();

    /**
     * Getter for estimated Full load amps
     * @return double, Estimated full load amp
     */
    double getEstimatedFLA() const {
        return estimatedFLA;
    }

private:
	const std::array<std::array<double, 6>, 5> calculatePartialLoadCoefficients(int pole) const;

    /// Estimated full load amp
    double estimatedFLA;
    /// Rated Power of motor
    double motorRatedPower = 0.0;
    /// Motor RPM
    double motorRPM;
    /// Line Frequency of Motor
    Motor::LineFrequency lineFrequency;
    /// Efficiency class of Motor
    Motor::EfficiencyClass efficiencyClass;
    /// Specified Efficiency of motor, if efficiency class is SPECIFIED
    double specifiedEfficiency;
    /// Rated voltage of motor
    double ratedVoltage;


    /*
     * * FLA Basic coefficients
     */
    std::array<std::array<double, 6>, 5> flaBasic = {
            {
                    {{1.07000005, 1.07860196, 1.11131799, 1.20000005, 1.25399995, 1.296}},
                    {{0.04457, 0.06776789, 0.1038059, 0.09800907, 0.10241948, 0.1058498}},
                    {{0.00075042, 0.00112793, 0.00208467, 0.00239285, 0.00239285, 0.00239285}},
                    {{0.1177211, 0.1706723, 0.3346993, 0.44619089, 0.46626949, 0.48188618}},
                    {{0.0328443, 0.03456966, 0.1037901, 0.07508431, 0.07508431, 0.07508431}}
            }
    };

    /*
     * FLA EE Multipliers
     */
    std::array<std::array<double, 6>, 5> eeFlaMultipliers = {
            {
                    {{0.99800003, 0.99959999, 0.99800003, 0.995, 0.995, 0.995}},
                    {{-0.00686105, -0.00768858, -0.01313299, -0.02334039, -0.02334039, -0.02334039}},
                    {{0.00086324, 0.00471104, 0.01482941, 0.05637734, 0.05637734, 0.05637734}},
                    {{-0.02477271, -0.01760195, -0.2489823, -0.79541528, -0.79541528, -0.79541528}},
                    {{0.07267418, 0.04482816, 0.63720071, 0.59844083, 0.59844083, 0.59844083}}
            }
    };

    /*
     * FLA SE Multipliers
     */
    std::array<std::array<double, 6>, 5> seFlaMultipliers = {
            {
                    {{1.00199997, 1.00150001, 1.00399995, 1.005, 1.005, 1.005}},
                    {{0.0305805, 0.02305459, 0.06148619, 0.04535436, 0.04535436, 0.04535436}},
                    {{0.00538086, 0.00630689, 0.01415263, 0.01991553, 0.01991553, 0.01991553}},
                    {{0.02411943, 0.02706193, 1.247298, 24.98793983, 24.98793983, 24.98793983}},
                    {{0.03430828, 0.01757208, 0.72734421, 1.14514899, 1.14514899, 1.14514899}}
            }
    };

    std::array<std::array<double, 3>, 5> peFlaMultipliers = {
            {
                    {{0.972803032, 0.988822468, 0.990453682}},
                    {{2.132557437, 0.385982899, -0.775656291}},
                    {{0.013323999, 0.410275377, 0.078563841}},
                    {{-2.145127031, -0.045828557, 0.735405576}},
                    {{0.013678436, 0.057848012, 0.071461107}}
            }
    };
};


#endif //UNTITLED_ESTIMATEFLA_H
