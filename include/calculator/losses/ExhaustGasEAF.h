/**
 * @file
 * @brief Calculator for gas exhaust losses in an Electric Arc Furnace (EAF)
 *
 * This contains the inputs for calculating the exhaust gas losses for an Electric Arc
 * Furnace (EAF)
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
#define AMO_TOOLS_SUITE_EXHAUSTGASEAF_H

/**
 * Exhaust Gas for an Electric Arc Furnace class
 * Contains all of the properties of the exhaust gas from the furnace.
 * Used to calculate the heat loss caused by the exhaust gas coming out of the electric arc furnace.
 */
class ExhaustGasEAF {
public:
    /**
     * Constructor for the exhaust gas EAF heat loss with all inputs specified
     * @param offGasTemp double, temperature of exhaust gases from EAF before the gases mix with outside air measured in °F
     * @param CO double, % of CO in exhaust gas
     * @param H2 double, % of H2 in exhaust gas
     * @param combustibleGases double, average value of combustible gases % in exhaust gases
     * @param vfr double, (volume flow rate) total volume of exhaust gases measured in cfm
     * @param dustLoading double, dust loading for exhaust gases measured in s/scf (number of dust particles per scf)
     * */
    ExhaustGasEAF(const double offGasTemp, const double CO, const double H2,
                  const double combustibleGases, const double vfr, const double dustLoading)
            : offGasTemp(offGasTemp), CO(CO), H2(H2), combustibleGases(combustibleGases),
              vfr(vfr), dustLoading(dustLoading)
    {}

    double getTotalHeatExhaust();

private:
    const double offGasTemp, CO, H2, combustibleGases, vfr, dustLoading;
};

#endif //AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
