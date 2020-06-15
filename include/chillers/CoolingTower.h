/**
 * @brief Contains the declarations of cooling tower classes including the getters and setters as well as the
 * calculators for cooling tower makeup water.
 *
 * @author Colin Causey (causeyc)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_COOLING_TOWER_H
#define AMO_TOOLS_SUITE_COOLING_TOWER_H


class CoolingTowerOperatingConditionsData
{
    public:
        /**
        * @param flowRate double, water flow rate in gpm
        * @param coolingLoad double, in MMBtu/h 
        * @param operationalHours int, number of hours cooling tower operates
        * @param lossCorrectionFactor double, correction factor for evaporation loss
        */
        CoolingTowerOperatingConditionsData(const double flowRate, const double coolingLoad, const int operationalHours, 
                                            const double lossCorrectionFactor)
                                            : flowRate(flowRate), coolingLoad(coolingLoad), operationalHours(operationalHours),
                                              lossCorrectionFactor(lossCorrectionFactor) {}

        double getFlowRate() const { return flowRate; }
        double getCoolingLoad() const { return coolingLoad; }
        int getOperationalHours() const { return operationalHours; }
        double getLossCorrectionFactor() const { return lossCorrectionFactor; }

        void setFlowRate(double flowRate);
        void setCoolingLoad(double coolingLoad);
        void setOperationalHours(int operationalHours);
        void setLossCorrectionFactor(double lossCorrectionFactor);

    private:
        double flowRate;
        double coolingLoad;
        int operationalHours;
        double lossCorrectionFactor = 0.85;
};

class CoolingTowerWaterConservationData
{
    public:
        /**
        * @param cyclesOfConcentration int
        * @param driftLossFactor double, correction factor for drift loss
        */
        CoolingTowerWaterConservationData(const int cyclesOfConcentration, const double driftLossFactor)
                                            : cyclesOfConcentration(cyclesOfConcentration), driftLossFactor(driftLossFactor) {}

    int getCyclesOfConcentration() const { return cyclesOfConcentration; }
    double getDriftLossFactor() const { return driftLossFactor; }

    void setCyclesOfConcentration(int cyclesOfConcentration);
    void setDriftLossFactor(double driftLossFactor);

    private:
        int cyclesOfConcentration;
        double driftLossFactor;
};

class CoolingTowerMakeupWaterCalculator
{
    public:
        struct Output
        {
            /**
            * @param wcBaseline double, water consumption before modifications in gallons
            * @param wcModification double, water consumption after modifications in gallons
            * @param waterSavings double, water saved in gallons
            */
            Output(double wcBaseline, double wcModification, double waterSavings)
                    : wcBaseline(wcBaseline), wcModification(wcModification), waterSavings(waterSavings) {}

            double wcBaseline     = 0;
            double wcModification = 0;
            double waterSavings   = 0;
        };

        CoolingTowerMakeupWaterCalculator(const CoolingTowerOperatingConditionsData &operatingConditionsData, 
                                          const CoolingTowerWaterConservationData &waterConservationBaselineData,
                                          const CoolingTowerWaterConservationData &waterConservationModificationData)
                                          : operatingConditionsData(operatingConditionsData), 
                                            waterConservationBaselineData(waterConservationBaselineData),
                                            waterConservationModificationData(waterConservationModificationData)
        {}

        CoolingTowerMakeupWaterCalculator::Output calculate();

        CoolingTowerOperatingConditionsData getOperatingConditionsData() const { return operatingConditionsData; }
        CoolingTowerWaterConservationData getWaterConservationBaselineData() const { return waterConservationBaselineData; }
        CoolingTowerWaterConservationData getWaterConservationModificationData() const { return waterConservationModificationData; }

        void setOperatingConditionsData(CoolingTowerOperatingConditionsData operatingConditionsData);
        void setWaterConservationBaselineData(CoolingTowerWaterConservationData waterConservationBaselineData);
        void setWaterConservationModificationData(CoolingTowerWaterConservationData waterConservationModificationData);

    private:
        CoolingTowerOperatingConditionsData operatingConditionsData;
        CoolingTowerWaterConservationData waterConservationBaselineData;
        CoolingTowerWaterConservationData waterConservationModificationData;
};


#endif //AMO_TOOLS_SUITE_COOLING_TOWER_H

