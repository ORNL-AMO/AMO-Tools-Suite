/**
 * @file Header file for Water Assessment
 * 
 * @brief Calculate
 *        ProcessWaterUse, CoolingTowerLoss, BoilerWaterLosses,
 *        KitchenRestroomGrossWaterUse, LandscapingGrossWaterUse, HeatEnergyInDischarge, AddedMotorEnergyUse
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_WATERASSESSMENT_H
#define AMO_TOOLS_SUITE_WATERASSESSMENT_H

class WaterAssessment {
public:
    struct ProcessWaterUseOutput {
        ProcessWaterUseOutput(double recirculatedWater, double incomingWater, double wasteDischargedAndRecycledOther) :
                recirculatedWater(recirculatedWater), incomingWater(incomingWater),
                wasteDischargedAndRecycledOther(wasteDischargedAndRecycledOther) {}

        ProcessWaterUseOutput() = default;
        double recirculatedWater = 0, incomingWater = 0, wasteDischargedAndRecycledOther = 0;
    };

    struct CoolingTowerLossOutput {
        CoolingTowerLossOutput(double grossWaterUse, double evaporationLoss, double cycleOfConcentration, double makeupWater, double blowdownLoss) :
                grossWaterUse(grossWaterUse), evaporationLoss(evaporationLoss), cycleOfConcentration(cycleOfConcentration),
                makeupWater(makeupWater), blowdownLoss(blowdownLoss) {}

        CoolingTowerLossOutput() = default;
        double grossWaterUse = 0, evaporationLoss = 0, cycleOfConcentration = 0, makeupWater = 0, blowdownLoss = 0;
    };

    struct BoilerWaterLossOutput {
        BoilerWaterLossOutput(double cycleOfConcentration, double grossWaterUse, double makeupWater, double steamLoss,
                              double blowdownLoss, double condensateReturn, double rateOfRecirculation) :
                cycleOfConcentration(cycleOfConcentration), grossWaterUse(grossWaterUse), makeupWater(makeupWater), steamLoss(steamLoss),
                blowdownLoss(blowdownLoss), condensateReturn(condensateReturn), rateOfRecirculation(rateOfRecirculation) {}

        BoilerWaterLossOutput() = default;
        double cycleOfConcentration = 0, grossWaterUse = 0, makeupWater = 0, steamLoss = 0,
                blowdownLoss = 0, condensateReturn = 0, rateOfRecirculation = 0;
    };

    /**
     * @param no arguments
     */
    WaterAssessment()= default;

    /**
     *
     * @param waterRequired double
     * @param waterConsumed double
     * @param waterLoss double
     * @param fractionGrossWaterRecirculated double
     *
     * @return ProcessWaterUseOutput
     *  @param recirculatedWater double
     *  @param incomingWater double
     *  @param wasteDischargedAndRecycledOther double
     */
    ProcessWaterUseOutput calculateProcessWaterUse(double waterRequired, double waterConsumed, double waterLoss, double fractionGrossWaterRecirculated) {
        const double recirculatedWater = waterRequired * fractionGrossWaterRecirculated;
        const double incomingWater = waterRequired - recirculatedWater;
        const double wasteDischargedAndRecycledOther = incomingWater - waterConsumed - waterLoss;

        return {recirculatedWater, incomingWater, wasteDischargedAndRecycledOther};
    }

    /**
     *
     * @param hoursPerYear double
     * @param tonnage double
     * @param loadFactor double
     * @param evaporationRateDegree double
     * @param temperatureDrop double
     * @param makeupConductivity double
     * @param blowdownConductivity double
     *
     * @return CoolingTowerLossOutput
     *  @param grossWaterUse double
     *  @param evaporationLoss double
     *  @param cycleOfConcentration double
     *  @param makeupWater double
     *  @param blowdownLoss double
     */
    CoolingTowerLossOutput calculateCoolingTowerLoss(double hoursPerYear, double tonnage, double loadFactor, double evaporationRateDegree,
                                                     double temperatureDrop, double makeupConductivity, double blowdownConductivity) {
        const double grossWaterUse = 3 * tonnage * loadFactor * 60 * hoursPerYear;
        const double evaporationLoss = (evaporationRateDegree / 10) * temperatureDrop * grossWaterUse;
        const double cycleOfConcentration = blowdownConductivity / makeupConductivity;
        const double makeupWater = evaporationLoss / (1 - (1 / cycleOfConcentration));
        const double blowdownLoss = makeupWater - evaporationLoss;

        return {grossWaterUse, evaporationLoss, cycleOfConcentration, makeupWater, blowdownLoss};
    }

    /**
     *
     * @param hoursPerYear double
     * @param power double
     * @param loadFactor double
     * @param steamPerPower double
     * @param feedWaterConductivity double
     * @param makeupConductivity double
     * @param blowdownConductivity double
     *
     * @return BoilerWaterLossOutput
     *  @param cycleOfConcentration double
     *  @param grossWaterUse double
     *  @param makeupWater double
     *  @param steamLoss double
     *  @param blowdownLoss double
     *  @param condensateReturn double
     *  @param rateOfRecirculation double
     */
    BoilerWaterLossOutput calculateBoilerWaterLosses(double hoursPerYear, double power, double loadFactor, double steamPerPower,
                                                     double feedWaterConductivity, double makeupConductivity, double blowdownConductivity) {
        const double cycleOfConcentration = blowdownConductivity / feedWaterConductivity;
        const double grossWaterUse = hoursPerYear * power * loadFactor * 0.002 * 60 * steamPerPower / (1 - (1 / cycleOfConcentration));
        const double makeupWater = (feedWaterConductivity / makeupConductivity) * grossWaterUse;
        const double blowdownLoss = (1 / cycleOfConcentration) * grossWaterUse;
        const double steamLoss = makeupWater - blowdownLoss;
        const double condensateReturn = (1 - (feedWaterConductivity / makeupConductivity)) * grossWaterUse;
        const double rateOfRecirculation = makeupWater / grossWaterUse;

        return {cycleOfConcentration, grossWaterUse, makeupWater, steamLoss, blowdownLoss, condensateReturn, rateOfRecirculation};
    }

    /**
     *
     * @param employeeCount double
     * @param workdaysPerYear double
     * @param dailyUsePerEmployee double
     *
     * @return grossWaterUse double
     */
    double calculateKitchenRestroomGrossWaterUse(double employeeCount, double workdaysPerYear, double dailyUsePerEmployee){
        return employeeCount * workdaysPerYear * dailyUsePerEmployee;
    }

    /**
     *
     * @param areaIrrigated double
     * @param yearlyInchesIrrigated double
     *
     * @return grossWaterUse double
     */
    double calculateLandscapingGrossWaterUse(double areaIrrigated , double yearlyInchesIrrigated){
        return areaIrrigated * yearlyInchesIrrigated;
    }

    /**
     *
     * @param incomingTemp double
     * @param outgoingTemp double
     * @param heatingEfficiency double
     * @param wasteWaterDischarge double
     *
     * @return heatEnergyUseInDischarge double
     */
    double calculateHeatEnergyInDischarge(double incomingTemp, double outgoingTemp, double heatingEfficiency, double wasteWaterDischarge){
        return wasteWaterDischarge * (outgoingTemp - incomingTemp) * 1 * 8.3454 * heatingEfficiency / 1000000;
    }

    /**
     *
     * @param numberUnits double
     * @param hoursPerYear double
     * @param ratedPower double
     * @param loadFactor double
     * @param systemEfficiency double
     *
     * @return energyUse double
     */
    double calculateAddedMotorEnergyUse(double numberUnits, double hoursPerYear, double ratedPower, double loadFactor, double systemEfficiency){
        return  ratedPower * numberUnits * loadFactor * hoursPerYear / systemEfficiency;
    }
};

#endif //AMO_TOOLS_SUITE_WATERASSESSMENT_H
