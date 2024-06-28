/**
 * @file Header file for Power Factor (pf) Calculations
 *
 * @brief Power Triangle, relationship of P Q S Φ and pf
 *        Calculate Apparent Power S, Real Power P, Reactive Power Q, Phase Angle Φ, Power Factor pf and Capacitance based on inputs.
 *        Inputs Combinations must include two known parameters viz
 *         1. Apparent Power +
 *            a. Real Power
 *            b. Reactive Power
 *            c. Phase Angle
 *            d. Power Factor
 *         2. Real Power +
 *            a. Reactive Power
 *            b. Phase Angle
 *            c. Power Factor
 *         3. Reactive Power +
 *            a. Phase Angle
 *            b. Power Factor
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_POWERFACTOR_H
#define AMO_TOOLS_SUITE_POWERFACTOR_H

#include <cmath>

class PowerFactor {
public:
    enum Mode {
        ApparentPower_RealPower,
        ApparentPower_ReactivePower,
        ApparentPower_PhaseAngle,
        ApparentPower_PowerFactor,
        RealPower_ReactivePower,
        RealPower_PhaseAngle,
        RealPower_PowerFactor,
        ReactivePower_PhaseAngle,
        ReactivePower_PowerFactor,
    };
    struct Output {
        Output(double realDemand, double demandPenalty, double reactivePower,
               double proposedReactivePower, double proposedCapacitance) :
        realDemand(realDemand), demandPenalty(demandPenalty), reactivePower(reactivePower),
        proposedReactivePower(proposedReactivePower), proposedCapacitance(proposedCapacitance) {}

        Output() = default;
        double realDemand = 0, demandPenalty = 0, reactivePower = 0, proposedReactivePower = 0, proposedCapacitance = 0;
    };

    /**
     * @param no arguments
     */
    PowerFactor()= default;

    /**
     *
     * @param mode represents which two inputs are provided
     * @param input1
     * @param input2
     *        inputs: input1 and input2 based on Mode maintaining order of inputs as
     *           Apparent Power double, units kVA
     *           Real Power double, units kW
     *           Reactive Power double, units kVAr
     *           Phase Angle double, units deg
     *           Power Factor double, units % as decimal value
     *        EX: Mode ApparentPower_RealPower, input1 is ApparentPower and input2 is RealPower
     * @param inputPowerFactor, based on mode parameter supplied is either Minimum Required / Target Power Factor
     *
     * @return Output
     *  @param realDemand double, units kW
     *  @param demandPenalty double, units kW
     *  @param reactivePower double, units kVAr
     *  @param proposedReactivePower double, units kVAr
     *  @param proposedCapacitance double, units kVAr
     */
    Output calculate(Mode mode, double input1, double input2, double inputPowerFactor = 0.95);

private:
    double realPower = 0, reactivePower = 0, apparentPower = 0, powerFactor = 0, phaseAngle = 0;
};

#endif //AMO_TOOLS_SUITE_POWERFACTOR_H
