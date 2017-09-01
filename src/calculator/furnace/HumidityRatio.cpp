
/**
 * @file
 * @brief Contains the implementation of the humidity ratio calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "calculator/furnace/HumidityRatio.h"
#include <cmath>

double HumidityRatio::getSaturationPressure(double temperature) {
    const double C1 = -5674.5359;
    const double C2 = -0.51523058;
    const double C3 = -0.009677843;
    const double C4 = 0.00000062215701;
    const double C5 = 2.0747825 * pow(10,-9);
    const double C6 = -9.0484024 * pow(10,-13);
    const double C7 = 4.1635019;
    const double C8 = -5800.2206;
    const double C9 = -5.516256;
    const double C10 = -0.048640239;
    const double C11 = 0.000041764768;
    const double C12 = -0.000000014452093;
    const double C13 = 6.5459673;
    const double absoluteTempConversion = 459.67;
    const double kelvinConversion = 0.555556;
    const double atmConversion = 101.325;
    double tempInKelvins = (temperature + absoluteTempConversion) * kelvinConversion;

    double pressure = 0.0;

    if (tempInKelvins < 273.15)
    {
        pressure = exp(C1 / tempInKelvins + C2 + tempInKelvins * C3 + tempInKelvins * tempInKelvins * (C4 + tempInKelvins * (C5 + C6 * tempInKelvins)) + C7 * log(tempInKelvins));
    }
    else
    {
        pressure = exp(C8 / tempInKelvins + C9 + tempInKelvins * (C10 + tempInKelvins * (C11 + tempInKelvins * C12)) + C13 * log(tempInKelvins));
    }
    this->saturationPressure_ = pressure/atmConversion;
    return this->saturationPressure_;
}

double HumidityRatio::getHumidityRatioUsingRH() {
    const double molecularWeightRatio = 0.62198;
    double satPressure = getSaturationPressure(this->dryBulbTemp_);
    double waterPressure = satPressure * (this->relativeHumidity_)/100;
    this->humidityRatioUsingRH_ = molecularWeightRatio * waterPressure/((this->atmosphericPressure_) - waterPressure);
    return this->humidityRatioUsingRH_;
}

double HumidityRatio::getHumidityRatioUsingWBT() {
    const double molecularWeightRatio = 0.62198;
    const double vaporizationHeat = 1061;
    const double waterSpecificHeat = 1;
    const double vaporSpecificHeat = 0.444;
    const double airSpecificHeat = 0.24;

//    double satPressureDB = getSaturationPressure(this->dryBulbTemp_);
//    double ratioDB = molecularWeightRatio * satPressureDB / ((this->atmosphericPressure_) - satPressureDB);

    double satPressureWB = getSaturationPressure(this->wetBulbTemp_);
    double ratioWB = molecularWeightRatio * satPressureWB / ((this->atmosphericPressure_) - satPressureWB);

    this->humidityRatioUsingWBT_ = ((vaporizationHeat - (waterSpecificHeat - vaporSpecificHeat) * (this->wetBulbTemp_)) * ratioWB - airSpecificHeat * ((this->dryBulbTemp_) - (this->wetBulbTemp_))) / (vaporizationHeat + vaporSpecificHeat * (this->dryBulbTemp_) - waterSpecificHeat * (this->wetBulbTemp_));
    return this->humidityRatioUsingWBT_;
}