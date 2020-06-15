#include <iostream>
#include <cmath>
#include "chillers/CoolingTower.h"
#include <fstream>

CoolingTowerMakeupWaterCalculator::Output CoolingTowerMakeupWaterCalculator::calculate()
{
    auto const calculateWaterConsumption = [](const CoolingTowerOperatingConditionsData &operatingConditionsData, 
                                              const CoolingTowerWaterConservationData &waterConservationData)
    {
        double evaporationLoss, driftLoss, blowDown, waterConsumption;

        evaporationLoss = operatingConditionsData.getLossCorrectionFactor() * 0.01 * operatingConditionsData.getCoolingLoad() * 1000000 / (500 * 10); // 0.01 = evaporation loss for ideal case
        
        driftLoss = waterConservationData.getDriftLossFactor() * operatingConditionsData.getFlowRate();
        
        blowDown = evaporationLoss / (waterConservationData.getCyclesOfConcentration() - 1);
        
        waterConsumption = (evaporationLoss + driftLoss + blowDown) * operatingConditionsData.getOperationalHours() * 60;
        
        return waterConsumption;
    };

    double wcBaseline = calculateWaterConsumption(this->operatingConditionsData, this->waterConservationBaselineData);
    double wcModification = calculateWaterConsumption(this->operatingConditionsData, this->waterConservationModificationData);
    double waterSavings = wcBaseline - wcModification;

    return CoolingTowerMakeupWaterCalculator::Output(wcBaseline, wcModification, waterSavings);
}

// CoolingTowerOperatingConditionsData setters
void CoolingTowerOperatingConditionsData::setFlowRate(double flowRate)
{
    this->flowRate = flowRate;
}
void CoolingTowerOperatingConditionsData::setCoolingLoad(double coolingLoad)
{
    this->coolingLoad = coolingLoad;
}
void CoolingTowerOperatingConditionsData::setOperationalHours(int operationalHours)
{
    this->operationalHours = operationalHours;
}
void CoolingTowerOperatingConditionsData::setLossCorrectionFactor(double lossCorrectionFactor)
{
    this->lossCorrectionFactor = lossCorrectionFactor;
}

// CoolingTowerWaterConservationData setters
void CoolingTowerWaterConservationData::setCyclesOfConcentration(int cyclesOfConcentration)
{
    this->cyclesOfConcentration = cyclesOfConcentration;
}
void CoolingTowerWaterConservationData::setDriftLossFactor(double driftLossFactor)
{
    this->driftLossFactor = driftLossFactor;
}

// CoolingTowerMakeupWaterCalculator setters
void CoolingTowerMakeupWaterCalculator::setOperatingConditionsData(CoolingTowerOperatingConditionsData operatingConditionsData)
{
    this->operatingConditionsData = operatingConditionsData;
}
void CoolingTowerMakeupWaterCalculator::setWaterConservationBaselineData(CoolingTowerWaterConservationData waterConservationBaselineData)
{
    this->waterConservationBaselineData = waterConservationBaselineData;
}
void CoolingTowerMakeupWaterCalculator::setWaterConservationModificationData(CoolingTowerWaterConservationData waterConservationModificationData)
{
    this->waterConservationModificationData = waterConservationModificationData;
}