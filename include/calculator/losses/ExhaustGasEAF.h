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
     *
     * @param cycleTime double, time of cycle measured in hrs
     * @param offGasTemp double, temperature of exhaust gases from EAF before the gases mix with outside air measured in °F
     * @param CO double, % of CO in exhaust gas
     * @param H2 double, % of H2 in exhaust gas
     * @param O2 double, % of O2 in exhaust gas
     * @param CO2 double, % of CO2 in exhaust gas
     * @param combustibleGases double, average value of combustible gases % in exhaust gases
     * @param vfr double, (volume flow rate) total volume of exhaust gases measured in cfm
     * @param dustLoading double, dust loading for exhaust gases measured in s/scf (number of dust particles per scf)
     * @param otherLosses double, other heat losses not accounted for measured in btu/cycle
     * @return nothing
     *
     * */
    ExhaustGasEAF(
            double cycleTime,
            double offGasTemp,
            double CO,
            double H2,
            double O2,
            double CO2,
            double combustibleGases,
            double vfr,
            double dustLoading,
            double otherLosses)
            : cycleTime_(cycleTime),
              offGasTemp_(offGasTemp),
              CO_(CO),
              H2_(H2),
              O2_(O2),
              CO2_(CO2),
              combustibleGases_(combustibleGases),
              vfr_(vfr),
              dustLoading_(dustLoading),
              otherLosses_(otherLosses) {
        COHeatingValue_ = 0.0;
        H2HeatingValue_ = 0.0;
        combustibles_ = 0.0;
        chemicalHeat_ = 0.0;
        totalVfr_ = 0.0;
        sensibleHeat_ = 0.0;
        heatInDust_ = 0.0;
        totalHeatFlue_ = 0.0;
        totalHeatExhaust_ = 0.0;
        totalKwhPerCycle_ = 0.0;
        chemicalHeatPercent_ = 0.0;
        sensibleHeatPercent_ = 0.0;
        otherHeatPercent_ = 0.0;
    }

    ExhaustGasEAF() = default;

    /**
     * Getter for the cycle time
     *
     * @return double, cycle time in hrs
     */
    double getCycleTime() const{
        return cycleTime_;
    }

    /**
     * Sets the cycle time
     *
     * @param cycleTime double, cycle time in hrs
     *
     * @return nothing
     */
    void setCycleTime(double cycleTime){
        cycleTime_ = cycleTime;
    }

    /**
     * Gets the off exhaust gas temperature
     *
     * @return double, off exhaust gas temperature in °F
     */
    double getOffGasTemp() const {
        return offGasTemp_;
    }

    /**
     * Sets the off exhaust gas temperature
     *
     * @param offGasTemp double, off exhaust gas temperature in °F
     *
     * @return none
     */
    void setOffGasTemp(double offGasTemp) {
        offGasTemp_ = offGasTemp;
    }

    /**
     * Gets the average % of CO in off exhaust gas
     *
     * @return double, average % of CO in off exhaust gas
     */
    double getCO() const {
        return CO_;
    }

    /**
     * Sets the average % of CO gas in off gas
     *
     * @return double, average % of CO in off exhaust gas
     */
    void setCO(double CO) {
        CO_ = CO;
    }

    /**
     * Gets the average % of H2 in off exhaust gas
     *
     * @return double, average % of H2 in off exhaust gas
     */
    double getH2() const {
        return H2_;
    }

    /**
     * Sets the average % of H2 in off exhaust gas
     *
     * @param H2 double, average % of H2 in off exhaust gas
     *
     * @return nothing
     */
    void setH2(double H2) {
        H2_ = H2;
    }

    /**
     * Gets the average % of O2 in off exhaust gas
     *
     * @return double, average % of O2 in off exhaust gas
     */
    double getO2() const {
        return O2_;
    }

    /**
     * Sets the average % of O2 in off exhaust gas
     *
     * @param O2 double, average % of O2 in off exhaust gas
     *
     * @return nothing
     */
    void setO2(double O2) {
        O2_ = O2;
    }

    /**
     * Gets the average % of CO2 in off exhaust gas
     *
     * @return double, average % of CO2 in off exhaust gas
     */
    double getCO2_() const {
        return CO2_;
    }

    /**
     * Sets the average % of CO2 in off exhaust gas
     *
     * @param CO2 double, average % of CO2 in off exhaust gas
     *
     * @return nothing
     */
    void setCO2_(double CO2) {
        CO2_ = CO2;
    }

    /**
     * Gets the % of combustible gases in off exhaust gas
     *
     * @return double, % of combustible gases in off exhaust gas
     */
    double getCombustibleGases_() const {
        return combustibleGases_;
    }

    /**
     * Sets the % of combustibles gases in off exhaust gas
     *
     * @param combustibleGases double, % of combustibles gases in off exhaust gas
     *
     * @return nothing
     */
    void setCombustibleGases_(double combustibleGases) {
        combustibleGases_ = combustibleGases;
    }

    /**
     * Gets the measured/estimated total volume flow rate
     *
     * @return double, total volume flow rate in cfm
     */
    double getVfr_() const {
        return vfr_;
    }

    /**
     * Sets the measured/estimated total volume flow rate
     *
     * @param vfr double, total volume flow rate in cfm
     *
     * @return nothing
     */
    void setVfr_(double vfr) {
        vfr_ = vfr;
    }

    /**
     * Gets the dust loading
     *
     * @return double, dust loading in s/scf (number of particles per scf)
     */
    double getDustLoading_() const {
        return dustLoading_;
    }

    /**
     *
     * Sets the dust loading
     *
     * @param dustLoading double, dust loading in s/scf (number of particles per scf)
     *
     * @return nothing
     */
    void setDustLoading_(double dustLoading) {
        dustLoading_ = dustLoading;
    }

    /**
     * Gets the other heat losses
     *
     * @return double, other heat losses in btu/cycle
     */
    double getOtherLosses_() const {
        return otherLosses_;
    }

    /**
     * Sets the other heat losses
     *
     * @param otherLosses double, ohter heat losses in btu/cycle
     *
     * @return nothing
     */
    void setOtherLosses(double otherLosses) {
        otherLosses_ = otherLosses;
    }



    /**
     * Calculates the CO heating value
     *
     * @return double, Co heating value in btu/scf
     */
    double getCOHeatingValue();


    /**
     * Calculates the H2 heating value
     *
     * @return double, H2 heating value in btu/scf
     */
    double getH2HeatingValue();



    /**
     * Calculates the combustibles heating value
     *
     * @return double, combustibles heating value in btu/scf
     */
    double getCombustibles();



    /**
     * Calculates the total heating value (chemical heat)
     *
     * @return double, chemical heat in btu/scf
     */
    double getChemicalHeat();


    /**
     * Calculates the total volume flow rate
     *
     * @return double, total volume flow rate in scfm
     */
    double getTotalVfr();


    /**
     * Calculates the sensible heat in exhaust gases
     *
     * @return double, sesible heat in btu/scf
     */
    double getSensibleHeat();


    /**
     * Calculates the heat in dust
     *
     * @return double, heat in dust in btu/scf
     */
    double getHeatInDust();


    /**
     * Calculates the total heat in flue gases
     *
     * @return double, total heat in flue gases in btu/scf
     */
    double getTotalHeatFlue();


    /**
     * Calculates the total heat loss in exhaust gases
     *
     * @return double, total heat loss in exhaust gases in btu/cycle
     */
    double getTotalHeatExhaust();

    /**
     * Gets the total heat exhaust in kwh/cycle
     *
     * @return double, total heat exhaust in kwh/cycle
     */
    double getTotalKwhPerCycle();

    /**
     * Calculates % of chemical heat loss
     *
     * @return double, % of chemical heat loss
     */
    double getChemicalHeatPercent();


    /**
     * Calculates the % of sensible heat loss
     *
     * @return double, % of sensible heat loss
     */
    double getSensibleHeatPercent();


    /**
     * Calculates the % of other heat loss
     *
     * @return double, % of other heat loss
     */
    double getOtherHeatPercent();


private:
    // In values
    double cycleTime_ = 0.0;
    double offGasTemp_ = 0.0;
    double CO_ = 0.0;
    double H2_ = 0.0;
    double O2_ = 0.0;
    double CO2_ = 0.0;
    double combustibleGases_ = 0.0;
    double vfr_ = 0.0;
    double dustLoading_ = 0.0;
    double otherLosses_ = 0.0;


    // Out values
    double COHeatingValue_ = 0.0;
    double H2HeatingValue_ = 0.0;
    double combustibles_ = 0.0;
    double chemicalHeat_ = 0.0;
    double totalVfr_ = 0.0;
    double sensibleHeat_ = 0.0;
    double heatInDust_ = 0.0;
    double totalHeatFlue_ = 0.0;
    double totalHeatExhaust_ = 0.0;
    double totalKwhPerCycle_ = 0.0;
    double chemicalHeatPercent_ = 0.0;
    double sensibleHeatPercent_ = 0.0;
    double otherHeatPercent_ = 0.0;

};

#endif //AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
