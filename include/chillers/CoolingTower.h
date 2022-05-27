/**
 * @brief Contains the Consumption (Water / Power / Energy) & Savings calculators for
 *  Cooling Tower
 *          Makeup Water
 *          Basin Heater Energy
 *          Fan Energy
 *  Chiller
 *          Efficiency : Temperature Reset Capacity
 *          Staging
 *
 * @author Colin Causey (causeyc), Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_COOLING_TOWER_H
#define AMO_TOOLS_SUITE_COOLING_TOWER_H

#include <math.h>
#include <vector>

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


class CoolingTower{
public:
    enum FanControlSpeedType {
        One,
        Two,
        Variable
    };

    struct PowerEnergyConsumptionOutput
    {
        PowerEnergyConsumptionOutput(double baselinePower, double baselineEnergy, double modPower, double modEnergy, double savingsEnergy) :
                baselinePower(baselinePower), baselineEnergy(baselineEnergy), modPower(modPower), modEnergy(modEnergy), savingsEnergy(savingsEnergy){}

        PowerEnergyConsumptionOutput() = default;
        double baselinePower = 0, baselineEnergy = 0, modPower = 0, modEnergy = 0, savingsEnergy = 0;
    };

    /**
     *
     * @param ratedCapacity double, units ton
     * @param ratedTempSetPoint double, units F
     * @param ratedTempDryBulb double, units F
     * @param ratedWindSpeed double, units mph
     *
     * @param operatingTempDryBulb double, units F
     * @param operatingWindSpeed double, units mph
     * @param operatingHours double, units hours
     *
     * @param baselineTempSetPoint double, units F
     * @param modTempSetPoint double, units F
     * @param panLossRatio double, fraction
     *
     * @return
     *      @param baselinePower double, units kW
     *      @param baselineEnergy double, units kWh
     *      @param modPower double, units, kW
     *      @param modEnergy double, units, kWh
     *      @param savingsEnergy double, units kWh
     *
     */
    static PowerEnergyConsumptionOutput BasinHeaterEnergyConsumption(
            const double ratedCapacity, const double ratedTempSetPoint, const double ratedTempDryBulb, const double ratedWindSpeed,
            const double operatingTempDryBulb, const double operatingWindSpeed, const double operatingHours,
            const double baselineTempSetPoint, const double modTempSetPoint, const double panLossRatio){
        const double calc1 = ratedCapacity * 4.394960445356 * panLossRatio /        /*4.394960445356 = 15000 btu/hr/ton  / 3413 kW/btu*/
                (ratedTempSetPoint - ratedTempDryBulb) /
                pow((ratedTempSetPoint + ratedTempDryBulb) / 2,-0.181) /
                pow((ratedTempSetPoint - ratedTempDryBulb),0.266) /
                pow((1.277 * ratedWindSpeed + 1),0.5) *
                pow((1.277 * operatingWindSpeed + 1),0.5);

        double baselinePower = CalculatePower(operatingTempDryBulb, baselineTempSetPoint, calc1);
        double modPower = CalculatePower(operatingTempDryBulb, modTempSetPoint, calc1);

        const double baselineEnergy = baselinePower * operatingHours;
        const double modEnergy = modPower * operatingHours;

        return PowerEnergyConsumptionOutput(baselinePower, baselineEnergy, modPower, modEnergy, baselineEnergy - modEnergy);
    }

    /**
     *
     * @param ratedFanPower double, units HP
     * @param noOfCells integer, between 1 and 10
     *
     * @param waterLeavingTemp double, units F
     * @param waterEnteringTemp double, units F
     * @param waterFlowRate double, units gpm
     * @param operatingTempWetBulb double, units F
     * @param operatingHours double, units hours
     *
     * @param baselineSpeedType enum, One / Two / Variable
     * @param modSpeedType enum, One / Two / Variable
     *
     * @return
     *      @param baselinePower double, units HP
     *      @param baselineEnergy double, units kWh
     *      @param modPower double, units, HP
     *      @param modEnergy double, units, kWh
     *      @param savingsEnergy double, units kWh
     *
     */
    static PowerEnergyConsumptionOutput FanEnergyConsumption(const double ratedFanPower,
            const double waterLeavingTemp, const double waterEnteringTemp, const double operatingTempWetBulb, const double operatingHours,
            const FanControlSpeedType baselineSpeedType, const FanControlSpeedType modSpeedType){
        const double a = -0.09646816;
        const double b = 1.04669762;
        const double c = 0.04976825 -
                CalculateFactor(std::vector<double> {0.08352359,0.11247273,-0.00135847,0.00003417,0.00003125,-0.00034001}, operatingTempWetBulb, waterEnteringTemp - waterLeavingTemp) /
                CalculateFactor(std::vector<double> {0.50061393,0.00588251,0.0002163,-0.01913189,0.00022360,0.00106108}, operatingTempWetBulb, waterLeavingTemp - operatingTempWetBulb);
        const double airFlow = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

        const double powerFactorFlow = CalculatePowerFactor(airFlow);
        const double powerFactorFull = CalculatePowerFactor(1);
        const double powerFactorHalf = CalculatePowerFactor(0.5);
        const double powerFactorZero = CalculatePowerFactor(0);

        const double highSpeedTime = airFlow < 0.5 ? airFlow / 0.5 : (airFlow - 0.5) / 0.5;
        const double twoSpeedPower = airFlow < 0.5 ?
                ratedFanPower * powerFactorHalf * highSpeedTime +
                ratedFanPower * powerFactorZero * (1 - highSpeedTime):
                ratedFanPower * powerFactorFull * highSpeedTime +
                ratedFanPower * powerFactorHalf * (1 - highSpeedTime);

        const double oneSpeedPower =
                ratedFanPower * powerFactorFull * airFlow +
                ratedFanPower * powerFactorZero * (1 - airFlow);

        const double vfdPower =
                ratedFanPower * powerFactorFlow;

        const double baselinePower =
                baselineSpeedType == FanControlSpeedType::Variable ? vfdPower :
                baselineSpeedType == FanControlSpeedType::Two ? twoSpeedPower :
                baselineSpeedType == FanControlSpeedType::One ? oneSpeedPower : 0;
        const double modPower =
                modSpeedType == FanControlSpeedType::Variable ? vfdPower :
                modSpeedType == FanControlSpeedType::Two ? twoSpeedPower :
                modSpeedType == FanControlSpeedType::One ? oneSpeedPower : 0;

        const double baselineEnergy = baselinePower * 0.746 * operatingHours;
        const double modEnergy = modPower * 0.746 * operatingHours;

        return PowerEnergyConsumptionOutput(baselinePower, baselineEnergy, modPower, modEnergy, baselineEnergy - modEnergy);
    }

private:
    static double CalculatePowerFactor(const double var) { return (0.01055507 - 0.05704023 * var + 0.14686301 * var * var + 0.92961746 * var * var * var); }

    static double CalculateFactor(const std::vector<double> &cf, const double operatingTempWetBulb, const double deltaTemp) {
        return cf[0] +
               cf[1] * deltaTemp + cf[2] * deltaTemp * deltaTemp +
               cf[3] * operatingTempWetBulb + cf[4] * operatingTempWetBulb * operatingTempWetBulb +
               cf[5] * deltaTemp * operatingTempWetBulb;
    }

    static double CalculatePower(const double operatingTempDryBulb, const double tempSetPoint, const double calc1) {
        return operatingTempDryBulb > tempSetPoint ? 0 :
               calc1 * (tempSetPoint - operatingTempDryBulb) *
               pow((tempSetPoint + operatingTempDryBulb) / 2, -0.181) *
               pow((tempSetPoint - operatingTempDryBulb),0.266);
    }
};

class ChillerEfficiency {
public:
    enum ChillerType {
        Centrifugal,
        Screw
    };

    enum CondenserCoolingType {
        Water,
        Air
    };

    enum CompressorConfigType {
        NoVFD,
        VFD,
        MagneticBearing
    };

    struct StagingPowerConsumptionOutput
    {
        StagingPowerConsumptionOutput(std::vector<double> baselinePowerList, std::vector<double> modPowerList,
                                     double baselineTotalPower, double baselineTotalEnergy,
                                     double modTotalPower, double modTotalEnergy, double savingsEnergy) :
                                     baselinePowerList(baselinePowerList), modPowerList(modPowerList),
                                     baselineTotalPower(baselineTotalPower), baselineTotalEnergy(baselineTotalEnergy),
                                     modTotalPower(modTotalPower), modTotalEnergy(modTotalEnergy), savingsEnergy(savingsEnergy){}

        StagingPowerConsumptionOutput() = default;
        std::vector<double> baselinePowerList;
        std::vector<double> modPowerList;
        double baselineTotalPower = 0, baselineTotalEnergy = 0, modTotalPower = 0, modTotalEnergy = 0, savingsEnergy = 0;
    };

    struct CapacityPowerEnergyConsumptionOutput
    {
        CapacityPowerEnergyConsumptionOutput(
                double baselineActualCapacity, double baselineActualEfficiency, double baselinePower, double baselineEnergy,
                double modActualCapacity, double modActualEfficiency, double modPower, double modEnergy, double savingsEnergy) :
                baselineActualCapacity(baselineActualCapacity), baselineActualEfficiency(baselineActualEfficiency),
                baselinePower(baselinePower), baselineEnergy(baselineEnergy),
                modActualCapacity(modActualCapacity), modActualEfficiency(modActualEfficiency),
                modPower(modPower), modEnergy(modEnergy), savingsEnergy(savingsEnergy){}

        CapacityPowerEnergyConsumptionOutput() = default;
        double baselineActualCapacity = 0, baselineActualEfficiency = 0, baselinePower = 0, baselineEnergy = 0,
                modActualCapacity = 0, modActualEfficiency = 0, modPower = 0, modEnergy = 0, savingsEnergy = 0;
    };

    /**
     *
     * @param chillerType enum Centrifugal, Screw
     * @param condenserCoolingType enum Water, Air
     * @param compressorConfigType enum NoVFD, VFD, MagneticBearing
     *
     * @param ariCapacity double, units ton
     * @param ariEfficiency double, units kW/ton
     * @param maxCapacityRatio double
     *
     * @param operatingHours double, units hours
     * @param waterFlowRate double, units GPM
     * @param waterDeltaT double, units F
     *
     * @param baselineWaterSupplyTemp double, units F
     * @param baselineWaterEnteringTemp double, units F
     * @param modWaterSupplyTemp double, units F
     * @param modWaterEnteringTemp double, units F
     *
     * @return
     * @param baselineActualCapacity double, units ton
     * @param baselineActualEfficiency double, units  kW/ton
     * @param baselinePower double, units kW
     * @param baselineEnergy double, units kWh
     * @param modActualCapacity double, units ton
     * @param modActualEfficiency double, units kW/ton
     * @param modPower double, units kW
     * @param modEnergy double, units kWh
     * @param savingsEnergy double, units kWh
     *
     */
    static CapacityPowerEnergyConsumptionOutput ChillerCapacityEfficiency(
            const ChillerType chillerType, const CondenserCoolingType condenserCoolingType, const CompressorConfigType compressorConfigType,
            const double ariCapacity, const double ariEfficiency, const double maxCapacityRatio,
            const double operatingHours, const double waterFlowRate, const double waterDeltaT,
            const double baselineWaterSupplyTemp, const double baselineWaterEnteringTemp,
            const double modWaterSupplyTemp, const double modWaterEnteringTemp) {
        std::vector<double> cCAP;
        std::vector<double> cCHWT;
        std::vector<double> cPLR;
        double cFactor;
        double ratedEIR;
        double percentCapacity;

        InitConstCoefficients(chillerType, condenserCoolingType, compressorConfigType, ariCapacity, ariEfficiency, maxCapacityRatio,
                              cCAP, cCHWT, cPLR, cFactor, ratedEIR, percentCapacity);

        const double load = waterFlowRate * waterDeltaT * 0.041667 /*500.0 / 12000*/;

        auto baselineOutput = ChillerPowerConsumption(
                baselineWaterSupplyTemp, baselineWaterEnteringTemp,
                cCAP, cCHWT, cPLR, load, cFactor, percentCapacity, ratedEIR);
        auto modOutput = ChillerPowerConsumption(
                modWaterSupplyTemp, modWaterEnteringTemp,
                cCAP, cCHWT, cPLR, load, cFactor, percentCapacity, ratedEIR);

        const double baselineEnergy = baselineOutput.consumptionPower * operatingHours;
        const double modEnergy = modOutput.consumptionPower * operatingHours;
        return CapacityPowerEnergyConsumptionOutput(
                baselineOutput.actualCapacity, baselineOutput.actualEfficiency, baselineOutput.consumptionPower, baselineEnergy,
                modOutput.actualCapacity, modOutput.actualEfficiency, modOutput.consumptionPower, modEnergy,
                baselineEnergy - modEnergy);
    }

    /**
     *
     * @param ariCapacity double, units ton
     * @param ariEfficiency double, units kW/ton
     * @param maxCapacityRatio double
     *
     * @param ariCapacity double, units ton
     * @param ariEfficiency double, units kW/ton
     * @param maxCapacityRatio double
     *
     * @param operatingHours double, units hours
     * @param waterSupplyTemp double, units F
     * @param waterEnteringTemp double, units F
     * @param baselineLoadList, list of doubles for each baseline chiller load
     * @param modLoadList, list of doubles for each modifications chiller load
     *
     * @return
     * @param baselinePowerList, list of doubles of power consumption corresponding to each baseline chiller load
     * @param modPowerList, list of doubles of power consumption corresponding to each modifications chiller load
     * @param baselineTotalPower double, units kW
     * @param baselineTotalEnergy double, units kWh
     * @param modTotalPower double, units kW
     * @param modTotalEnergy double, units kWh
     * @param savingsEnergy double, units kWh
     *
     */
    static StagingPowerConsumptionOutput ChillerStagingEfficiency(
            const ChillerType chillerType, const CondenserCoolingType condenserCoolingType, const CompressorConfigType compressorConfigType,
            const double ariCapacity, const double ariEfficiency, const double maxCapacityRatio,
            const double operatingHours, const double waterSupplyTemp, const double waterEnteringTemp,
            const std::vector<double> baselineLoadList, const std::vector<double> modLoadList) {
        unsigned int chillersCount = baselineLoadList.size();

        if(chillersCount != modLoadList.size())
            throw std::runtime_error("Chiller counts for baseline and modification does not match");

        std::vector<double> cCAP;
        std::vector<double> cCHWT;
        std::vector<double> cPLR;
        double cFactor;
        double ratedEIR;
        double percentCapacity;

        InitConstCoefficients(chillerType, condenserCoolingType, compressorConfigType, ariCapacity, ariEfficiency, maxCapacityRatio,
                              cCAP, cCHWT, cPLR, cFactor, ratedEIR, percentCapacity);

        std::vector<double> baselinePowerList;
        std::vector<double> modPowerList;
        double baselineTotalPower = 0, baselineTotalEnergy = 0, modTotalPower = 0, modTotalEnergy = 0;

        baselinePowerList.assign(chillersCount, 0);
        modPowerList.assign(chillersCount, 0);

        for (unsigned int i = 0; i < chillersCount; i++)
        {
            if(baselineLoadList[i] > 0) {
                auto baselineOutput = ChillerPowerConsumption(waterSupplyTemp, waterEnteringTemp, cCAP, cCHWT, cPLR,
                                                              baselineLoadList[i], cFactor, percentCapacity, ratedEIR);
                baselineTotalPower += baselineOutput.consumptionPower;
                baselineTotalEnergy += baselineOutput.consumptionPower * operatingHours;

                baselinePowerList[i] = baselineOutput.consumptionPower;
            }

            if(modLoadList[i] > 0) {
                auto modOutput = ChillerPowerConsumption(waterSupplyTemp, waterEnteringTemp, cCAP, cCHWT, cPLR,
                                                         modLoadList[i], cFactor, percentCapacity, ratedEIR);
                modTotalPower += modOutput.consumptionPower;
                modTotalEnergy += modOutput.consumptionPower * operatingHours;

                modPowerList[i] = modOutput.consumptionPower;
            }
        }

        return StagingPowerConsumptionOutput(baselinePowerList, modPowerList,
                                             baselineTotalPower, baselineTotalEnergy, modTotalPower, modTotalEnergy,
                                             baselineTotalEnergy - modTotalEnergy);
    }

private:
    struct Output
    {
        Output(double actualCapacity, double actualEfficiency, double consumptionPower) :
                actualCapacity(actualCapacity), actualEfficiency(actualEfficiency), consumptionPower(consumptionPower) {}

        Output() = default;
        double actualCapacity = 0, actualEfficiency = 0, consumptionPower = 0;
    };

    static void InitConstCoefficients(
            const ChillerType &chillerType, const CondenserCoolingType &condenserCoolingType, const CompressorConfigType &compressorConfigType,
            const double ariCapacity, const double ariEfficiency, const double maxCapacityRatio,
            std::vector<double> &cCAP, std::vector<double> &cCHWT, std::vector<double> &cPLR,
            double &cFactor, double &ratedEIR, double &percentCapacity) {
        cFactor= 0.284333 /*3.412 / 12*/;
        ratedEIR= ariEfficiency * cFactor;
        percentCapacity= ariCapacity / maxCapacityRatio;

        if(chillerType == Centrifugal && condenserCoolingType == Water && compressorConfigType == NoVFD){
            cCAP = {-0.49737319,-0.00956073,-0.00059561,0.04352099,-0.00058394,0.00096007};
            cCHWT = {1.15361547,-0.03067901,0.00030591,0.00670874,0.0000528,-0.00009297};
            cPLR  = {0.27969646,0.57375735,0.25690463,-0.00580717,0.00014649,-0.00353007};
        }
        else if(chillerType == Centrifugal && condenserCoolingType == Water && compressorConfigType == VFD) {
            cCAP = {-0.38924542,-0.02195141,-0.00027343,0.04974775,-0.00053441,0.00067295};
            cCHWT = {1.42868233,-0.08227751,0.00030243,0.03622194,-0.00029211,0.00043788};
            cPLR  = {0.14703037,-0.00349667,1.01161313,-0.00359697,0.00027167,-0.01164471};
        }
        else  if(chillerType == Centrifugal && condenserCoolingType == Water && compressorConfigType == MagneticBearing) {
            cCAP = {1.37074482,-0.04210769,-0.00029363,0.01559556,-0.00051769,0.00119421};
            cCHWT = {1.37895823,-0.03063673,0.00013163,-0.0004975,0.00005392,0.00009815};
            cPLR  = {-0.08770346,0.63231272,0.52312154,0.00289049,0.00008105,-0.00786588};
        }
        else if(chillerType == Centrifugal && condenserCoolingType == Air && compressorConfigType == NoVFD) {
            cCAP = {-1.38147235,0.10363494,-0.00103756,0.00368918,-0.00006936,0.00002531};
            cCHWT = {-0.40465075,0.03093917,-0.00029274,0.00840319,0.00002946,-0.00010866};
            cPLR  = {0.24258001,0.41468,0.34273973,0,0,0};
        }
        else if(chillerType == Screw && condenserCoolingType == Air && compressorConfigType == NoVFD) {
            cCAP = {0.67083991,0.00274941,0.00018121,0.00326176,-0.00003443,-0.0000339};
            cCHWT = {0.93630582,-0.0101571,0.00021678,-0.00245357,0.00013577,-0.00021563};
            cPLR  = {0.01040687,1.05183303,-0.09462459,0.00163543,-0.00000779,-0.00060324};
        }
        else if(chillerType == Screw && condenserCoolingType == Water && compressorConfigType == NoVFD) {
            cCAP = {0.89823061,0.0004535,0.0002369,-0.0010475,-0.0000293,-0.00002035};
            cCHWT = {0.62493622,-0.00099309,0.00017366,-0.00086447,0.00019627,-0.0003377};
            cPLR  = {-0.11699212,1.26354492,-0.21946673,0.00294536,0.00001688,-0.00185917};
        }
        else{
            throw std::runtime_error("Undefined Chiller characteristics");
        }
    }

    static Output ChillerPowerConsumption(const double waterSupplyTemp, const double waterEnteringTemp,
                                          const std::vector<double> &cCAP, const std::vector<double> &cCHWT, const std::vector<double> &cPLR,
                                          const double load, const double cFactor, const double percentCapacity, const double ratedEIR) {
        const double deltaT = waterEnteringTemp - waterSupplyTemp;

        double capacity =
                cCAP[0] +
                cCAP[1] * waterSupplyTemp + cCAP[2] * waterSupplyTemp * waterSupplyTemp +
                cCAP[3] * waterEnteringTemp + cCAP[4] * waterEnteringTemp * waterEnteringTemp +
                cCAP[5] * waterSupplyTemp * waterEnteringTemp;
        const double actualCapacity = capacity * capacity * percentCapacity;

        const double fCHWT =
                cCHWT[0] +
                cCHWT[1] * waterSupplyTemp + cCHWT[2] * waterSupplyTemp * waterSupplyTemp +
                cCHWT[3] * waterEnteringTemp + cCHWT[4] * waterEnteringTemp * waterEnteringTemp +
                cCHWT[5] * waterSupplyTemp * waterEnteringTemp;

        double percentLoad = load / actualCapacity;
        if(percentLoad < 0.1) percentLoad = 0.1;
        const double fFPLR =
                cPLR[0] +
                cPLR[1] * percentLoad + cPLR[2] * percentLoad * percentLoad +
                cPLR[3] * deltaT + cPLR[4] * deltaT * deltaT +
                cPLR[5] * deltaT * percentLoad;

        const double baselineEfficiency = (fCHWT * fFPLR * ratedEIR) / cFactor;

        return Output(actualCapacity, baselineEfficiency, actualCapacity * baselineEfficiency);
    }
};

#endif //AMO_TOOLS_SUITE_COOLING_TOWER_H
