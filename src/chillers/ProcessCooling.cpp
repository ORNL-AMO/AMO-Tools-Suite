/**
 * @file Implementation of Process Fluid Cooling Energy Calculations
 * Originally (CWSAT) writen in VB by University of Massachusetts - Amherst with funding from the U.S. Department of Energy
 * @author Converted by Omer Aziz from VB to C++ (omerb).
 */

#include "chillers/ProcessCooling.h"

const double nominalWaterFlowGPMPerTon = 3.0; // Typical value for towers

ProcessCooling::ProcessCooling(const vector<int>& systemOperationAnnualHours,
                               const vector<double>& weatherDryBulbHourlyTemp, const vector<double>& weatherWetBulbHourlyTemp,
                               const vector<ChillerInput>& chillerInputList,
                               AirCooledSystemInput airCooledSystemInput, TowerInput towerInput, WaterCooledSystemInput waterCooledSystemInput) {
    if(systemOperationAnnualHours.size() != HOURS_IN_YEAR || systemOperationAnnualHours.size() != weatherDryBulbHourlyTemp.size() ||
       systemOperationAnnualHours.size() != weatherWetBulbHourlyTemp.size() || chillerInputList.empty()) {
        throw invalid_argument("Invalid input, requires weather and operation data of size " + to_string(HOURS_IN_YEAR) + " and at least one chiller.");
    }

    if((airCooledSystemInput.isAirCooled && waterCooledSystemInput.isWaterCooled) ||
       (!airCooledSystemInput.isAirCooled && !waterCooledSystemInput.isWaterCooled)) {
        throw invalid_argument("Invalid cooling system.");
    }

    systemOperationAnnual = systemOperationAnnualHours;
    dryBulbHourlyTemp = weatherDryBulbHourlyTemp;
    wetBulbHourlyTemp = weatherWetBulbHourlyTemp;

    tower = towerInput;

    if(airCooledSystemInput.isAirCooled) {
        coolingType = CoolingSystemType::Air;
        airCooledSystem = airCooledSystemInput;
    }
    else if(waterCooledSystemInput.isWaterCooled) {
        coolingType = CoolingSystemType::Water;
        waterCooledSystem = waterCooledSystemInput;

        FCTemp = waterCooledSystem.CHWT - waterCooledSystem.HEXApproachTemp - 10;

        CWTHourly.resize(HOURS_IN_YEAR, 0);
    }

    chillers = chillerInputList;

    numChillers = (int)chillers.size();
    chillerHourlyLoad.resize(numChillers, vector<double>(HOURS_IN_YEAR, 0));
    chillerHourlyLoadOperational.resize(numChillers, vector<double>(LOAD_NUM, 0));
    chillerHourlyEfficiencyARI.resize(numChillers, vector<double>(HOURS_IN_YEAR, 0));
    chillerHourlyEfficiency.resize(numChillers, vector<double>(HOURS_IN_YEAR, 0));
    chillerHourlyPower.resize(numChillers, vector<double>(HOURS_IN_YEAR, 0));

    annualChillerLoadProfile();
    annualChillerEfficiencyProfileARI();
    annualChillerEfficiencyProfile();
    annualChillerPowerProfile();
}

ProcessCooling::TowerOutput ProcessCooling::calculateTowerEnergy() {
    vector<double> tempBins = TowerOutput().tempBins;
    int numBins = (int)tempBins.size();
    vector<double> towerHours(numBins, 0);
    vector<double> towerEnergy(numBins, 0);

    for (int j = 0; j < HOURS_IN_YEAR; ++j) {
        double towerPowerHourly;
        if (systemOperationAnnual[j] == 1) {
            double TWetBulb = wetBulbHourlyTemp[j];
            double percentWaterFlow = getPercentWaterFlow(j);
            double range = getRange(j);
            double approach = getApproach(TWetBulb, 60); // Minimum temperature to chillers 60
            double percentFanPower = getPercentFanPower(TWetBulb, percentWaterFlow, range, approach, j);

            towerPowerHourly = tower.fanHP * tower.numFanPerTower_Cells * tower.numTower * 0.746 * percentFanPower;

            int binNum = numBins - 1;
            int wbTemp = static_cast<int>(round(wetBulbHourlyTemp[j]));
            if (wbTemp < tempBins[binNum]) {
                for (int i = 0; i < binNum; i++) {
                    if (wbTemp < tempBins[i]) {
                        binNum = i;
                        break;
                    }
                }
            }

            towerHours[binNum] += 1;
            towerEnergy[binNum] += towerPowerHourly;
        }
    }

    return {towerHours, towerEnergy};
}

ProcessCooling::ChillerOutput ProcessCooling::calculateChillerEnergy() {
    vector<vector<double>> chillerEnergy(numChillers, vector<double>(LOAD_NUM, 0));
    vector<vector<double>> chillerPower(numChillers, vector<double>(LOAD_NUM, 0));
    vector<vector<double>> chillerEff(numChillers, vector<double>(LOAD_NUM, 0));

    for (int c = 0; c < numChillers; ++c) {
        for (int j = 0; j < HOURS_IN_YEAR; ++j) {
            int l = static_cast<int>(chillerHourlyLoad[c][j] / 10);
            chillerEnergy[c][l] += chillerHourlyPower[c][j];

            if (chillerHourlyLoad[c][j] > 0) {
                chillerPower[c][l] += chillerHourlyPower[c][j];
                chillerEff[c][l] += chillerHourlyEfficiency[c][j];
            }
        }

        for (int loadIndex = 0; loadIndex < LOAD_NUM; loadIndex++) {
            if (chillerHourlyLoadOperational[c][loadIndex] > 0) {
                chillerEff[c][loadIndex] /= chillerHourlyLoadOperational[c][loadIndex];
                chillerPower[c][loadIndex] /= chillerHourlyLoadOperational[c][loadIndex];
            }
        }
    }

    return {chillerEff, chillerHourlyLoadOperational, chillerPower, chillerEnergy};
}

ProcessCooling::ChillerPumpingEnergyOutput ProcessCooling::calculatePumpEnergy(PumpInput pump) {
    vector<double> chillerPumpingEnergy(numChillers, 0);
    vector<double> chillerVSDPumpingEnergy(numChillers, 0);

    if (pump.motorSize == 0) { //Size unknown
        pump.motorSize = getPumpHP(
                getChillerTonnageTotal() * pump.flowRate * 30 / 3960 / (pump.efficiency / 100) / numChillers);
    }

    for (int c = 0; c < numChillers; ++c) {
        double pumpEnergyTotal = 0;
        double pumpVSDEnergyTotal = 0;

        for (int l = 1; l < LOAD_NUM; ++l) {
            double VSDM = 0.31;
            switch (l) {
                case 6:
                    VSDM = 0.41;
                    break;
                case 7:
                    VSDM = 0.52;
                    break;
                case 8:
                    VSDM = 0.66;
                    break;
                case 9:
                    VSDM = 0.81;
                    break;
                case 10:
                    VSDM = 1.02;
                    break;
                default:
                    break;
            }
            double pumpPower = pump.motorSize * 0.746 / (pump.motorEfficiency / 100);
            double pumpVSDPower = pumpPower * VSDM;

            pumpEnergyTotal += pumpPower * chillerHourlyLoadOperational[c][l];
            pumpVSDEnergyTotal += pumpVSDPower * chillerHourlyLoadOperational[c][l];
        }

        if (pump.variableFlow) {
            chillerVSDPumpingEnergy[c] = pumpVSDEnergyTotal;
        }
        else {
            chillerPumpingEnergy[c] = pumpEnergyTotal;
        }
    }

    return pump.variableFlow ? ChillerPumpingEnergyOutput(chillerVSDPumpingEnergy) : ChillerPumpingEnergyOutput(chillerPumpingEnergy);
}

void ProcessCooling::annualChillerLoadProfile() {
    vector<vector<vector<double>>> chillerMonthlyLoads(numChillers, vector<vector<double>>(MONTHS, vector<double>(LOAD_NUM, 0)));
    vector<int> monthHourStart = {0, 744, 1416, 2160, 2880, 3624, 4344, 5088, 5832, 6552, 7296, 8016, 8760};
    vector<double> systemOperationMonthly = {744, 672, 744, 720, 744, 720, 744, 744, 720, 744, 720, 744};

    int monthIndex = 0;
    int monthHours = 0;
    int cutOffHours = monthHourStart[monthIndex + 1] - 1;

    for (int c = 0; c < numChillers; ++c) {
        for (int m = 0; m < MONTHS; ++m) {
            if (chillers[c].useARIMonthlyLoadSchedule)
                chillerMonthlyLoads[c][m] = {0, 0, 1, 5, 13, 23, 26, 19, 9, 3, 1};
            else
                chillerMonthlyLoads[c][m] = chillers[c].monthlyLoads[m];
        }
    }

    for (int j = 0; j < HOURS_IN_YEAR; j++) {
        if (j > cutOffHours) {
            systemOperationMonthly[monthIndex] = monthHours;
            ++monthIndex;
            monthHours = 0;
            cutOffHours = monthHourStart[monthIndex + 1] - 1;
        }
        if (systemOperationAnnual[j] == 1) ++monthHours;
    }

    for (int c = 0; c < numChillers; ++c) {
        for (int m = 0; m < MONTHS; ++m) {
            int count = 0;
            int j = 12;
            double remainder = 0;
            bool evenMarker = true;

            vector<double> temp(LOAD_NUM, 0);
            for (int l = 0; l < LOAD_NUM; ++l) {
                temp[l] = chillerMonthlyLoads[c][m][l] / 100 * systemOperationMonthly[m];
            }

            int loadNum = LOAD_NUM - 1;
            while (loadNum >= 0) {
                if (j == 0) {
                    loadNum--;
                }
                else if (j > 0) {
                    int index = monthHourStart[m] + j - 1;
                    if (index < HOURS_IN_YEAR) {
                        if (systemOperationAnnual[index] == 1 && chillerHourlyLoad[c][index] == 0) {
                            temp[loadNum] += remainder;

                            double tempValueRounded = round(temp[loadNum]);
                            if (tempValueRounded - temp[loadNum] < 0.1 && tempValueRounded - temp[loadNum] > 0) {
                                temp[loadNum] = tempValueRounded;
                            }

                            if (temp[loadNum] >= 1) {
                                chillerHourlyLoad[c][index] = loadNum * 10;
                                temp[loadNum]--;
                                remainder = 0;
                            } else {
                                remainder = temp[loadNum];
                                loadNum--;
                                j -= 24;
                            }
                        } else {
                            chillerHourlyLoad[c][index] = 0;
                        }
                    }

                    j += 24;

                    if (monthHourStart[m] + j > monthHourStart[m + 1]) {
                        if (evenMarker) {
                            count++;
                            j = 12 + count;
                            evenMarker = false;
                        } else {
                            j = 12 - count;
                            evenMarker = true;
                        }
                    }
                }
            }
        }

        for (int j = 0; j < HOURS_IN_YEAR; ++j) {
            chillerHourlyLoadOperational[c][static_cast<int>(chillerHourlyLoad[c][j] / 10)] += 1;
        }
    }
}

void ProcessCooling::annualChillerEfficiencyProfileARI() {
    // Method 2 - Part Load Efficiency Curves [%Load vs. %kW], All chiller types, fullLoadEff known
    vector<vector<double>> ArrayMethod2 = {
            // x^3 - x, B [constant]
            {0.3807, 0.2203, 0.2485, 0.1553},  // CentrifugalFan / Water-Cooled
            {0.0, 0.3412, 0.6792, -0.0154},    // Reciprocating / Water-Cooled
            {0.5024, -0.022, 0.3832, 0.136},   // Helical Rotary / Water-Cooled
            {0.0, -0.0263, 0.9971, 0.0103},    // Reciprocating / Air-Cooled
            {0.5024, -0.022, 0.3832, 0.136}    // Helical Rotary / Air-Cooled
    };

    // Method 1 CentrifugalFan / Water-Cooled, Water, centrifugal, fullLoadEff unknown
    vector<vector<double>> ArrayCDataWater{
            // capacity [tons], Full Load Efficiency [kW/ton], x^5 - x, B [constant]
            {200, 0.84, 0.0, 0.0, -2.1395, 5.2528, -3.7337, 1.4533},
            {250, 0.68, 0.0, 0.0, -1.732, 4.2522, -3.0225, 1.1764} // Includes 250-1000 by 50, 1000-2000 by 100
    };

    // Method 1 Reciprocating / Water-Cooled, Water, reciprocating, fullLoadEff unknown
    vector<vector<double>> ArrayRDataWater = {
            // capacity [tons], Full Load Efficiency [kW/ton], x^5 - x, B [constant]
            {20, 0.88, 0.0, 0.0, 0.0, -0.0954, 0.4706, 0.502},
            {25, 0.88, 0.0, 0.0, 0.0, -0.0954, 0.4706, 0.502},
            {30, 32.5 / 34.5, 0.0, 0.0, 0.0, -0.1023, 0.5049, 0.5386},
            {35, 32.5 / 34.5, 0.0, 0.0, 0.0, -0.1023, 0.5049, 0.5386},
            {40, 32.5 / 34.5, 0.0, 0.0, 0.0, -0.1023, 0.5049, 0.5386},
            {45, 50.5 / 49.4, 0.0, 0.0, 0.0, -0.111, 0.5479, 0.5844},
            {50, 50.5 / 49.4, 0.0, 0.0, 0.0, -0.111, 0.5479, 0.5844},
            {60, 12.0 / 13.2, 0.0, 0.0, 0.0, -0.098, 0.486, 0.5196},
            {70, 12.0 / 13.0, 0.0, 0.0, 0.2574, -0.6057, 0.799, 0.4719},
            {80, 12.0 / 13.8, 0.0, 0.0, 0.2365, -0.5533, 0.7141, 0.4748},
            {90, 12.0 / 13.9, 0.0, -10.43, 28.937, -28.825, 12.435, -1.2535},
            {100, 12.0 / 13.1, 0.0, -20.508, 56.982, -56.78, 24.15, -2.9284},
            {110, 12.0 / 13.8, 0.0, -11.693, 32.445, -32.318, 13.903, -1.4673},
            {115, 12.0 / 13.5, 0.0, -7.9441, 21.944, -21.655, 9.2935, -0.7489},
            {120, 12.0 / 13.2, 0.0, -19.057, 52.955, -52.81, 22.529, -2.7065},
            {130, 12.0 / 12.7, 0.0, 0.0, 0.7169, -1.0517, 0.7741, 0.5088},
            {140, 12.0 / 12.8, 0.0, 0.0, 0.0, 0.223, 0.1025, 0.6095},
            {150, 12.0 / 12.7, 0.0, 4.9661, -11.483, 9.3654, -2.7811, 0.8762},
            {160, 12.0 / 13.0, 0.0, 4.1948, -9.2594, 7.2022, -1.9972, 0.7876},
            {170, 12.0 / 12.6, 0.0, 4.275, -9.3462, 7.0888, -1.8392, 0.7739},
            {175, 12.0 / 12.6, 0.0, 4.275, -9.3462, 7.0888, -1.8392, 0.7739},
            {180, 12.0 / 12.6, 0.0, 4.275, -9.3462, 7.0888, -1.8392, 0.7739},
            {190, 12.0 / 12.2, 0.0, 4.9849, -11.281, 9.0204, -2.6834, 0.946},
            {200, 12.0 / 12.5, -10.1, 32.577, -38.646, 20.939, -4.8209, 1.0106},
            {210, 12.0 / 12.5, -10.1, 32.577, -38.646, 20.939, -4.8209, 1.0106},
            {220, 12.0 / 12.5, -10.1, 32.577, -38.646, 20.939, -4.8209, 1.0106},
            {230, 12.0 / 12.1, -15.869, 47.034, -52.156, 26.754, -6.0112, 1.237},
            {240, 12.0 / 12.1, -15.869, 47.034, -52.156, 26.754, -6.0112, 1.237},
            {250, 12.0 / 12.1, -15.869, 47.034, -52.156, 26.754, -6.0112, 1.237}
    };

    // Method 1 Helical Rotary / Water-Cooled, Water, helical rotary, fullLoadEff unknown
    vector<vector<double>> ArraySDataWater = {
            // capacity [tons], Full Load Efficiency [kW/ton], x^5 - x, B [constant]
            {70, 12.0 / 15.3, 0.0, 0.0, 0.0, 0.493, -0.3382, 0.6329},
            {80, 12.0 / 15.6, 0.0, 0.0, -3.0228, 6.8805, -4.5542, 1.4658},
            {90, 12.0 / 15.5, 0.0, 0.0, -1.6269, 3.8762, -2.5615, 1.0865},
            {100, 12.0 / 15.4, 0.0, 0.0, -1.3381, 3.141, -1.982, 0.9584},
            {110, 12.0 / 15.2, 0.0, 0.0, -1.5986, 3.6242, -2.2305, 0.9944},
            {120, 12.0 / 15.3, 0.0, 0.0, -2.4371, 5.5781, -3.7157, 1.3591},
            {125, 12.0 / 15.3, 0.0, 0.0, -2.4371, 5.5781, -3.7157, 1.3591},
            {130, 12.0 / 15.3, 0.0, 0.0, -2.4371, 5.5781, -3.7157, 1.3591},
            {140, 0.84, 0.0, 0.0, 0.0, 1.0149, -1.1397, 0.9731} // Includes 140-200 by 10, 200-800 by 50
    };

    // Method 1 Reciprocating / Air-Cooled, Air, reciprocating, fullLoadEff unknown
    vector<vector<double>> ArrayRDataAir = {
            // capacity [tons], Full Load Efficiency [kW/ton], x^5 - x, B [constant]
            {40, 1.05, 0.0, 0.0, 0.0, 0.0482, -0.1241, 1.125},
            {50, 1.09, 0.0, 0.0, 0.0, 0.05, -0.1286, 1.166},
            {60, 1.09, 0.0, 0.0, 0.0, 0.05, -0.1286, 1.166},
            {70, 1.11, 0.0, 0.0, 0.0, 0.051, -0.1313, 1.1903},
            {80, 1.11, 0.0, 0.0, 0.0, 0.051, -0.1313, 1.1903},
            {90, 1.09, 0.0, 0.0, 0.0, 0.05, -0.1286, 1.166},
            {100, 1.06, 0.0, 0.0, 0.0, 0.0487, -0.1252, 1.135},
            {110, 1.11, 0.0, 0.0, 0.0, 0.051, -0.1313, 1.1903},
            {200, 1.15, 0.0, 0.0, 0.0, 0.0527, -0.1355, 1.2284},
            {210, 1.15, 0.0, 0.0, 0.0, 0.0527, -0.1355, 1.2284},
            {220, 1.15, 0.0, 0.0, 0.0, 0.0527, -0.1355, 1.2284},
            {230, 12.0 / 9.5, 0.0, -17.753, 42.824, -34.985, 10.845, 0.2139},
            {240, 12.0 / 9.5, 0.0, -17.753, 42.824, -34.985, 10.845, 0.2139},
            {250, 12.0 / 9.5, 0.0, -17.753, 42.824, -34.985, 10.845, 0.2139},
            {275, 12.0 / 9.7, 0.0, -20.957, 53.744, -47.559, 16.471, -0.5675},
            {300, 12.0 / 9.7, 53.156, -159.84, 182.28, -97.116, 23.5, -0.8358},
            {325, 12.0 / 9.6, 57.771, -173.81, 198.34, -105.76, 25.624, -0.9891},
            {350, 12.0 / 9.6, 57.771, -173.81, 198.34, -105.76, 25.624, -0.9891},
            {370, 12.0 / 9.5, 16.672, -53.78, 65.6, -36.521, 8.7508, 0.427},
            {375, 12.0 / 9.5, 16.672, -53.78, 65.6, -36.521, 8.7508, 0.427},
            {400, 12.0 / 9.7, 11.306, -39.007, 50.56, -29.343, 7.0493, 0.577},
            {425, 12.0 / 9.6, 12.317, -42.59, 55.331, -32.217, 7.777, 0.5474},
            {450, 12.0 / 9.6, 12.317, -42.59, 55.331, -32.217, 7.777, 0.5474}
    };

    // Method 1 Helical Rotary / Air-Cooled Air, helical rotary, fullLoadEff unknown
    vector<vector<double>> ArraySDataAir = {
            {70, 12.0 / 10.2, 0.0, 0.0, 0.0, 0.3996, 0.0891, 0.6929},
            {80, 12.0 / 10.2, 0.0, 0.0, -4.6584, 9.9259, -5.9944, 1.9034},
            {90, 12.0 / 9.9, 0.0, 0.0, -2.0203, 4.3627, -2.362, 1.2317},
            {100, 12.0 / 9.7, 0.0, 0.0, -1.9174, 3.8677, -1.7496, 1.0364},
            {110, 12.0 / 9.7, 0.0, 0.0, -2.3327, 4.6982, -2.2427, 1.1143},
            {120, 12.0 / 9.8, 0.0, 0.0, -2.7475, 5.8423, -3.2581, 1.3878},
            {125, 12.0 / 9.8, 0.0, 0.0, -2.7475, 5.8423, -3.2581, 1.3878},
            {130, 12.0 / 9.5, 0.0, 0.0, 0.0, 0.5195, 0.0769, 0.6646},
            {140, 12.0 / 9.5, 0.0, 0.0, 0.0, 0.4609, 0.1068, 0.6556},
            {150, 12.0 / 9.5, 0.0, 0.0, 0.0, 0.4609, 0.1068, 0.6556},
            {155, 12.0 / 9.4, 0.0, 0.0, 0.0, 0.3573, 0.2743, 0.6364},
            {160, 12.0 / 9.2, 0.0, 0.0, 0.0, 0.8587, -0.3208, 0.7601},
            {170, 12.0 / 9.2, 0.0, 0.0, 0.0, 0.8587, -0.3208, 0.7601},
            {180, 12.0 / 9.2, 0.0, 0.0, 0.0, 1.2421, -0.9662, 1.0278},
            {185, 12.0 / 9.2, 0.0, 0.0, 0.0, 1.2421, -0.9662, 1.0278},
            {190, 12.0 / 9.2, 0.0, 0.0, 0.0, 1.2421, -0.9662, 1.0278},
            {200, 12.0 / 9.0, 0.0, 0.0, 3.3211, -5.4082, 3.2153, 0.2052},
            {215, 12.0 / 9.2, 0.0, 0.0, 3.2895, -5.4202, 3.2557, 0.1793},
            {220, 12.0 / 9.2, 0.0, 0.0, 3.2895, -5.4202, 3.2557, 0.1793},
            {230, 12.0 / 9.4, 0.0, 0.0, 0.0, 0.7427, -0.131, 0.6627},
            {240, 12.0 / 9.4, 0.0, 0.0, 0.0, 0.7427, -0.131, 0.6627},
            {250, 12.0 / 9.4, 0.0, 0.0, 0.0, 0.7427, -0.131, 0.6627},
            {270, 12.0 / 9.3, 0.0, 0.0, 0.0, 0.9024, -0.2977, 0.687},
            {275, 12.0 / 9.3, 0.0, 0.0, 0.0, 0.9024, -0.2977, 0.687},
            {300, 12.0 / 9.2, 0.0, 0.0, 0.0, 0.8341, -0.2, 0.6749},
            {325, 12.0 / 9.4, 0.0, 0.0, 0.0, 0.7244, -0.0863, 0.637},
            {340, 12.0 / 9.4, 0.0, 0.0, 0.0, 0.7244, -0.0863, 0.637},
            {350, 12.0 / 9.4, 0.0, 0.0, 0.0, 0.7244, -0.0863, 0.637},
            {370, 12.0 / 9.3, 0.0, 0.0, 0.0, 0.7642, -0.1199, 0.6474},
            {375, 12.0 / 9.3, 0.0, 0.0, 0.0, 0.7642, -0.1199, 0.6474},
            {400, 12.0 / 9.3, 0.0, 0.0, 0.0, 0.7331, -0.0961, 0.6528}
    };

    vector<int> capacityIndex(31, 0);
    vector<vector<double>> efficiencyData(numChillers, vector<double>(7, 0)); // 7 columns for each chiller. Dummy array for chiller values
    for (int c = 0; c < numChillers; ++c) { //gvg for custom chiller
        // Method 1 CentrifugalFan / Water-Cooled
        if (chillers[c].chillerType == ChillerCompressorType::Centrifugal && coolingType == CoolingSystemType::Water) {
            if (capacityIndex[c] > 1) capacityIndex[c] = 2;
        }

        // Method 1 Helical Rotary / Water-Cooled;
        if (chillers[c].chillerType == ChillerCompressorType::Screw && coolingType == CoolingSystemType::Water) {
            if(capacityIndex[c] > 8) capacityIndex[c] = 9;
        }

        // Method 1 Reciprocating / Air-Cooled;
        if (chillers[c].chillerType == ChillerCompressorType::Reciprocating && coolingType == CoolingSystemType::Air){
            if (capacityIndex[c] > 7 && capacityIndex[c] < 17) capacityIndex[c] = 8;
            else if (capacityIndex[c] > 16) capacityIndex[c] = capacityIndex[c] - 8;
        }

        if (chillers[c].isFullLoadEffKnown) {
            if (chillers[c].isCustomChiller) {
                for (int i = 0; i < 4; i++) {
                    efficiencyData[c][i] = chillers[c].customCoeffs[i];
                }
            }
            else {
                if (coolingType == CoolingSystemType::Water) {
                    if (chillers[c].chillerType == ChillerCompressorType::Centrifugal) {
                        for (int i = 0; i < 4; i++) {
                            efficiencyData[c][i] = ArrayMethod2[0][i];
                        }
                    }
                    else if (chillers[c].chillerType == ChillerCompressorType::Reciprocating) {
                        for (int i = 0; i < 4; i++) {
                            efficiencyData[c][i] = ArrayMethod2[1][i];
                        }
                    }
                    else if (chillers[c].chillerType == ChillerCompressorType::Screw) {
                        for (int i = 0; i < 4; i++) {
                            efficiencyData[c][i] = ArrayMethod2[2][i];
                        }
                    }
                }
                else if (coolingType == CoolingSystemType::Air) {
                    if (chillers[c].chillerType == ChillerCompressorType::Reciprocating) {
                        for (int i = 0; i < 4; i++) {
                            efficiencyData[c][i] = ArrayMethod2[3][i];
                        }
                    }
                    else if (chillers[c].chillerType == ChillerCompressorType::Screw) {
                        for (int i = 0; i < 4; i++) {
                            efficiencyData[c][i] = ArrayMethod2[4][i];
                        }
                    }
                }
            }

            for (int j = 0; j < HOURS_IN_YEAR; ++j) {
                double load = chillerHourlyLoad[c][j];

                if (load == 0) {
                    chillerHourlyEfficiencyARI[c][j] = (1 + chillers[c].age / 100.0f) *
                                                       (efficiencyData[c][0] * pow(1.0f / 10, 3) +
                                                        efficiencyData[c][1] * pow(1.0f / 10, 2) +
                                                        efficiencyData[c][2] * (1.0f / 10) +
                                                        efficiencyData[c][3]) *
                                                       chillers[c].fullLoadEff / 1.0f / (1.0f / 10);
                }
                else if (load == 100) {
                    chillerHourlyEfficiencyARI[c][j] = (1 + chillers[c].age / 100.0f) *
                                                       chillers[c].fullLoadEff / 1.0f;
                }
                else {
                    chillerHourlyEfficiencyARI[c][j] = (1 + chillers[c].age / 100.0f) *
                                                       (efficiencyData[c][0] * pow(load / 100.0f, 3) +
                                                        efficiencyData[c][1] * pow(load / 100.0f, 2) +
                                                        efficiencyData[c][2] * (load / 100.0f) +
                                                        efficiencyData[c][3]) *
                                                       chillers[c].fullLoadEff / 1.0f / (load / 100.0f);
                }
            }
        }
        else {
            int idx = capacityIndex[c];
            if (coolingType == CoolingSystemType::Water) {
                if (chillers[c].chillerType == ChillerCompressorType::Centrifugal) {
                    efficiencyData[c][0] = ArrayCDataWater[idx][2];
                    efficiencyData[c][1] = ArrayCDataWater[idx][3];
                    efficiencyData[c][2] = ArrayCDataWater[idx][4];
                    efficiencyData[c][3] = ArrayCDataWater[idx][5];
                    efficiencyData[c][4] = ArrayCDataWater[idx][6];
                    efficiencyData[c][5] = ArrayCDataWater[idx][7];
                    efficiencyData[c][6] = ArrayCDataWater[idx][1];
                }
                else if (chillers[c].chillerType == ChillerCompressorType::Reciprocating) {
                    efficiencyData[c][0] = ArrayRDataWater[idx][2];
                    efficiencyData[c][1] = ArrayRDataWater[idx][3];
                    efficiencyData[c][2] = ArrayRDataWater[idx][4];
                    efficiencyData[c][3] = ArrayRDataWater[idx][5];
                    efficiencyData[c][4] = ArrayRDataWater[idx][6];
                    efficiencyData[c][5] = ArrayRDataWater[idx][7];
                    efficiencyData[c][6] = ArrayRDataWater[idx][1];
                }
                else if (chillers[c].chillerType == ChillerCompressorType::Screw) {
                    efficiencyData[c][0] = ArraySDataWater[idx][2];
                    efficiencyData[c][1] = ArraySDataWater[idx][3];
                    efficiencyData[c][2] = ArraySDataWater[idx][4];
                    efficiencyData[c][3] = ArraySDataWater[idx][5];
                    efficiencyData[c][4] = ArraySDataWater[idx][6];
                    efficiencyData[c][5] = ArraySDataWater[idx][7];
                    efficiencyData[c][6] = ArraySDataWater[idx][1];
                }
            }
            else if (coolingType == CoolingSystemType::Air) {
                if (chillers[c].chillerType == ChillerCompressorType::Reciprocating) {
                    efficiencyData[c][0] = ArrayRDataAir[idx][2];
                    efficiencyData[c][1] = ArrayRDataAir[idx][3];
                    efficiencyData[c][2] = ArrayRDataAir[idx][4];
                    efficiencyData[c][3] = ArrayRDataAir[idx][5];
                    efficiencyData[c][4] = ArrayRDataAir[idx][6];
                    efficiencyData[c][5] = ArrayRDataAir[idx][7];
                    efficiencyData[c][6] = ArrayRDataAir[idx][1];
                }
                else if (chillers[c].chillerType == ChillerCompressorType::Screw) {
                    efficiencyData[c][0] = ArraySDataAir[idx][2];
                    efficiencyData[c][1] = ArraySDataAir[idx][3];
                    efficiencyData[c][2] = ArraySDataAir[idx][4];
                    efficiencyData[c][3] = ArraySDataAir[idx][5];
                    efficiencyData[c][4] = ArraySDataAir[idx][6];
                    efficiencyData[c][5] = ArraySDataAir[idx][7];
                    efficiencyData[c][6] = ArraySDataAir[idx][1];
                }
            }

            for (int j = 0; j < HOURS_IN_YEAR; ++j) {
                double load = chillerHourlyLoad[c][j];

                if (load == 0) {
                    chillerHourlyEfficiencyARI[c][j] = (1 + chillers[c].age / 100.0f) *
                                                       (efficiencyData[c][0] * pow(1.0f / 10, 5) +
                                                        efficiencyData[c][1] * pow(1.0f / 10, 4) +
                                                        efficiencyData[c][2] * pow(1.0f / 10, 3) +
                                                        efficiencyData[c][3] * pow(1.0f / 10, 2) +
                                                        efficiencyData[c][4] * (1.0f / 10) +
                                                        efficiencyData[c][5]) * 2 -
                                                       (1 + chillers[c].age / 100.0f) *
                                                       (efficiencyData[c][0] * pow(2.0f / 10, 5) +
                                                        efficiencyData[c][1] * pow(2.0f / 10, 4) +
                                                        efficiencyData[c][2] * pow(2.0f / 10, 3) +
                                                        efficiencyData[c][3] * pow(2.0f / 10, 2) +
                                                        efficiencyData[c][4] * (2.0f / 10) +
                                                        efficiencyData[c][5]);
                }
                else if (load == 100) {
                    chillerHourlyEfficiencyARI[c][j] = (1 + chillers[c].age / 100.0f) *
                                                       efficiencyData[c][6];
                }
                else {
                    chillerHourlyEfficiencyARI[c][j] = (1 + chillers[c].age / 100.0f) *
                                                       (efficiencyData[c][0] * pow(load / 100.0f, 5) +
                                                        efficiencyData[c][1] * pow(load / 100.0f, 4) +
                                                        efficiencyData[c][2] * pow(load / 100.0f, 3) +
                                                        efficiencyData[c][3] * pow(load / 100.0f, 2) +
                                                        efficiencyData[c][4] * (load / 100.0f) +
                                                        efficiencyData[c][5]);
                }

                if (load <= 40) {
                    double tempEff = (1 + chillers[c].age / 100.0f) *
                                     (efficiencyData[c][0] * pow((load / 100.0f + 0.1f), 5) +
                                      efficiencyData[c][1] * pow((load / 100.0f + 0.1f), 4) +
                                      efficiencyData[c][2] * pow((load / 100.0f + 0.1f), 3) +
                                      efficiencyData[c][3] * pow((load / 100.0f + 0.1f), 2) +
                                      efficiencyData[c][4] * (load / 100.0f + 0.1f) +
                                      efficiencyData[c][5]);

                    if (chillerHourlyEfficiencyARI[c][j] < tempEff) {
                        chillerHourlyEfficiencyARI[c][j] = tempEff * 1.1f;
                    }
                }
            }
        }
    }
}

void ProcessCooling::annualChillerEfficiencyProfile() {
    int measureCount = 0;
    double CWTdiff;
    double CWTeffAdjust = 0;
    double ECMeffAdjust;

    double CHWTVar = (44 - (coolingType == Water ? waterCooledSystem.CHWT : airCooledSystem.CHWT));
    vector<double> CHWTMult(numChillers, 0);
    vector<double> CtypeMult(numChillers, 0);
    vector<double> refrigMult(numChillers, 1);
    vector<vector<double>> VSDMult(numChillers, vector<double>(LOAD_NUM, 1));

    for (int c = 0; c < numChillers; ++c) {
        if (chillers[c].chillerType == ChillerCompressorType::Reciprocating) {
            CtypeMult[c] = 0.013;
        }
        else if (chillers[c].chillerType == ChillerCompressorType::Screw) {
            CtypeMult[c] = 0.0179;
        }
        else if (chillers[c].chillerType == ChillerCompressorType::Centrifugal) {
            CtypeMult[c] = 0.01;
        }
        CHWTMult[c] = 1 + (CtypeMult[c] * CHWTVar);

        if (chillers[c].chillerType == ChillerCompressorType::Centrifugal && chillers[c].installVSD) {
            VSDMult[c] = {0.5, 0.5, 0.5, 0.514, 0.542, 0.57, 0.694, 0.818, 0.904, 0.952, 1.02};
        }

        vector<double> refrigFactor = {0.45, 0.46, 0.51, 0.52, 0.5, 0.48};
        refrigMult[c] = chillers[c].changeRefrig ?
                        refrigFactor[chillers[c].proposedRefrig] / refrigFactor[chillers[c].currentRefrig] : 1;
    }

    if (coolingType == CoolingSystemType::Water) {
        for (int Chiller = 0; Chiller < numChillers; ++Chiller) {
            for (int j = 0; j < HOURS_IN_YEAR; ++j) {
                double CWTBase = 65; // Default ARI base

                if (chillerHourlyLoad[Chiller][j] >= 0 && chillerHourlyLoad[Chiller][j] <= 50) {
                    CWTBase = 65;
                } else if (chillerHourlyLoad[Chiller][j] == 60) {
                    CWTBase = 69;
                } else if (chillerHourlyLoad[Chiller][j] == 70) {
                    CWTBase = 73;
                } else if (chillerHourlyLoad[Chiller][j] == 80) {
                    CWTBase = 77;
                } else if (chillerHourlyLoad[Chiller][j] == 90) {
                    CWTBase = 81;
                } else if (chillerHourlyLoad[Chiller][j] == 100) {
                    CWTBase = 85;
                }

                if (CWTHourly[j] != 0) {
                    CWTdiff = CWTBase - CWTHourly[j];
                } else {
                    double CWTWater;
                    if (waterCooledSystem.constantCWT) {
                        CWTdiff = (CWTBase - waterCooledSystem.CWT);
                    } else {
                        CWTWater = wetBulbHourlyTemp[j] + waterCooledSystem.CWTFollow;
                        CWTWater = max(60.0, min(CWTWater, 110.0));
                        CWTdiff = (CWTBase - CWTWater);
                    }
                }

                if (chillers[Chiller].chillerType == ChillerCompressorType::Reciprocating) {
                    CWTeffAdjust = (CWTdiff >= 0)
                                   ? 1 + (0.0273 * CWTdiff * CWTdiff - 1.5769 * CWTdiff) / 100
                                   : 1 + (-0.0273 * CWTdiff * CWTdiff - 1.5769 * CWTdiff) / 100;
                }
                else if (chillers[Chiller].chillerType == ChillerCompressorType::Screw) {
                    CWTeffAdjust = (CWTdiff >= 0)
                                   ? 1 + (0.0282 * CWTdiff * CWTdiff - 2.0172 * CWTdiff) / 100
                                   : 1 + (-0.0282 * CWTdiff * CWTdiff - 2.0172 * CWTdiff) / 100;
                }
                else if (chillers[Chiller].chillerType == ChillerCompressorType::Centrifugal) {
                    CWTeffAdjust = (CWTdiff >= 0)
                                   ? 1 + (0.0014 * CWTdiff * CWTdiff - 0.4363 * CWTdiff) / 100
                                   : 1 + (-0.0014 * CWTdiff * CWTdiff - 0.4363 * CWTdiff) / 100;
                }

                if (measureCount == 0) {
                    ECMeffAdjust = 1.0;
                    measureCount = 1;
                } else {
                    ECMeffAdjust = refrigMult[Chiller] * VSDMult[Chiller][static_cast<int>(chillerHourlyLoad[Chiller][j] / 10)];
                }

                chillerHourlyEfficiency[Chiller][j] = chillerHourlyEfficiencyARI[Chiller][j] * CHWTMult[Chiller] * CWTeffAdjust * ECMeffAdjust;
            }
        }
    }
    else if (coolingType == CoolingSystemType::Air) {
        for (int c = 0; c < numChillers; ++c) {
            for (int j = 0; j < HOURS_IN_YEAR; ++j) {
                double OADT_ARI = 95;
                double OADTVar = (OADT_ARI - airCooledSystem.OADT);

                // Determine CATBase based on load
                double CATBase = 55; // Default value
                if (chillerHourlyLoad[c][j] == 10 || chillerHourlyLoad[c][j] == 0) {
                    CATBase = 55;
                } else if (chillerHourlyLoad[c][j] == 30) {
                    CATBase = 57;
                } else if (chillerHourlyLoad[c][j] == 40) {
                    CATBase = 61;
                } else if (chillerHourlyLoad[c][j] == 50) {
                    CATBase = 65;
                } else if (chillerHourlyLoad[c][j] == 60) {
                    CATBase = 71;
                } else if (chillerHourlyLoad[c][j] == 70) {
                    CATBase = 77;
                } else if (chillerHourlyLoad[c][j] == 80) {
                    CATBase = 83;
                } else if (chillerHourlyLoad[c][j] == 90) {
                    CATBase = 89;
                } else if (chillerHourlyLoad[c][j] == 100) {
                    CATBase = 95;
                }

                double CATdiff = 0;
                if (airCooledSystem.ACSource == ACSourceLocation::Inside) {
                    CATdiff = (CATBase - airCooledSystem.indoorTemp);
                }
                else if (airCooledSystem.ACSource == ACSourceLocation::Outside) {
                    double CWTAir = dryBulbHourlyTemp[j] + airCooledSystem.CWTFollow;
                    CATdiff = (CATBase - CWTAir);
                }

                double OADeffAdjust = 1.0;
                double CATeffAdjust = 1.0;

                if (chillers[c].chillerType == ChillerCompressorType::Reciprocating) {
                    OADeffAdjust = (OADTVar >= 0) ?
                                   1 + (-0.0273 * pow(OADTVar, 2) - 1.5769 * OADTVar) / 100 :
                                   1 + (0.0273 * pow(OADTVar, 2) - 1.5769 * OADTVar) / 100;
                }
                else if (chillers[c].chillerType == ChillerCompressorType::Screw) {
                    OADeffAdjust = (OADTVar >= 0) ?
                                   1 + (-0.0282 * pow(OADTVar, 2) - 2.0172 * OADTVar) / 100 :
                                   1 + (0.0282 * pow(OADTVar, 2) - 2.0172 * OADTVar) / 100;
                }

                if (chillers[c].chillerType == ChillerCompressorType::Reciprocating) {
                    CATeffAdjust = (CATdiff >= 0) ?
                                   1 + (0.0273 * pow(CATdiff, 2) - 1.5769 * CATdiff) / 100 :
                                   1 + (-0.0273 * pow(CATdiff, 2) - 1.5769 * CATdiff) / 100;
                }
                else if (chillers[c].chillerType == ChillerCompressorType::Screw) {
                    CATeffAdjust = (CATdiff >= 0) ?
                                   1 + (0.0282 * pow(CATdiff, 2) - 2.0172 * CATdiff) / 100 :
                                   1 + (-0.0282 * pow(CATdiff, 2) - 2.0172 * CATdiff) / 100;
                }

                if (measureCount == 0) {
                    ECMeffAdjust = 1.0;
                    measureCount = 1;
                } else {
                    ECMeffAdjust = refrigMult[c] *
                                   VSDMult[c][static_cast<int>(chillerHourlyLoad[c][j] / 10)];
                }

                chillerHourlyEfficiency[c][j] = chillerHourlyEfficiencyARI[c][j] * CHWTMult[c] * OADeffAdjust * CATeffAdjust * ECMeffAdjust;
            }
        }
    }
}

void ProcessCooling::annualChillerPowerProfile() {
    for (int c = 0; c < numChillers; ++c) {
        for (int j = 0; j < HOURS_IN_YEAR; ++j) {
            chillerHourlyPower[c][j] = (waterCooledSystem.useFreeCooling && wetBulbHourlyTemp[j] <= FCTemp) ? 0 :
                                       chillerHourlyLoad[c][j] / 100 * chillers[c].capacity * chillerHourlyEfficiency[c][j];
        }
    }
}

double ProcessCooling::getFanHP(double tonnage, TowerSizedBy towerSizing, int fanNum, CellFanType fanType, double fanHP) {
    if (towerSizing == TowerSizedBy::Fan_HP) {
        return fanHP;
    }

    vector<double> fanHPOptions = {
            0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 7.5, 10.0, 15.0,
            20.0, 25.0, 30.0, 40.0, 50.0, 60.0, 75.0, 100.0, 125.0
    };

    if (fanNum == 0) {
        fanNum = 1;
    }

    double calculatedHP = 0.065 * tonnage / fanNum;

    if (fanType == CellFanType::CentrifugalFan) {
        calculatedHP *= 2;
    }

    int a = 0;
    int size = static_cast<int>(fanHPOptions.size());
    while (a < size - 1 && !(calculatedHP > fanHPOptions[a] && calculatedHP < fanHPOptions[a + 1])) {
        ++a;
    }

    if (a >= size - 1) {
        return fanHPOptions.back();
    } else {
        return fanHPOptions[a + 1];
    }
}

double ProcessCooling::getPercentFanPower(double wetBulbTemp, double percentWaterFlow, double range, double desiredApproach, int yearHourIndex) {
    double percentFanPower = 0.0;
    double percentFanPowerReturned = 0.0;
    double deltaPercentFanPower = 0.05;
    double oldDeltaApproach = 1000;
    string towerFlowType = "X";

    for (int percentFanPowerCount = 0; percentFanPowerCount <= 20; ++percentFanPowerCount) {
        double approach1, approach2, approach, deltaApproach;

        if (towerFlowType == "X") { // Cross flow
            approach1 = -2.1985908408527 * 1 +
                        -24.3108065555106 * percentFanPower +
                        21.9333667825398 * percentFanPower * percentFanPower +
                        -4.94979078884808 * percentFanPower * percentFanPower * percentFanPower +
                        14.6788552214526 * percentWaterFlow +
                        -15.4612468065777 * percentFanPower * percentWaterFlow +
                        2.83753688605444 * percentFanPower * percentFanPower * percentWaterFlow +
                        10.0023162199558 * percentWaterFlow * percentWaterFlow +
                        2.70780345372045 * percentFanPower * percentWaterFlow * percentWaterFlow +
                        -5.91993527180418 * percentWaterFlow * percentWaterFlow * percentWaterFlow +
                        0.194222288920726 * wetBulbTemp +
                        0.142543400927955 * percentFanPower * wetBulbTemp +
                        -0.0818947291400898 * percentFanPower * percentFanPower * wetBulbTemp +
                        -0.169584760441541 * percentWaterFlow * wetBulbTemp +
                        0.0186741309635284 * percentFanPower * percentWaterFlow * wetBulbTemp +
                        0.0536824177590012 * percentWaterFlow * percentWaterFlow * wetBulbTemp +
                        -0.00375848174056975 * wetBulbTemp * wetBulbTemp +
                        0.000623763881051551 * percentFanPower * wetBulbTemp * wetBulbTemp +
                        -0.000709769430542879 * percentWaterFlow * wetBulbTemp * wetBulbTemp +
                        0.0000234697776728891 * wetBulbTemp * wetBulbTemp * wetBulbTemp +
                        2.45541543720225 * range +
                        -0.607566456611435 * percentFanPower * range +
                        0.117339576910507 * percentFanPower * percentFanPower * range;

            approach2 = 1.64648551160799 * percentWaterFlow * range +
                        -0.135898905926974 * percentFanPower * percentWaterFlow * range +
                        -0.152577581866506 * percentWaterFlow * percentWaterFlow * range +
                        -0.034055419164321 * wetBulbTemp * range +
                        0.00274052705314173 * percentFanPower * wetBulbTemp * range +
                        -0.00442366885652332 * percentWaterFlow * wetBulbTemp * range +
                        0.0000687098236486247 * wetBulbTemp * wetBulbTemp * range +
                        -0.0416435261408276 * range * range +
                        0.00263481599534274 * percentFanPower * range * range +
                        -0.010325259545311 * percentWaterFlow * range * range +
                        0.000356999078067433 * wetBulbTemp * range * range +
                        0.000249188476685273 * range * range * range;

        }
        else { // Counter flow
            approach1 = -4.48760943345722 * 1 +
                        0.741749875850003 * percentFanPower +
                        1.74679844252553 * percentFanPower * percentFanPower +
                        -0.397320959632943 * percentFanPower * percentFanPower * percentFanPower +
                        19.5106208955792 * percentWaterFlow +
                        -9.79489761472574 * percentFanPower * percentWaterFlow +
                        1.96690857354709 * percentFanPower * percentFanPower * percentWaterFlow +
                        -1.40803729637148 * percentWaterFlow * percentWaterFlow +
                        0.633867141219563 * percentFanPower * percentWaterFlow * percentWaterFlow +
                        -0.517255742412696 * percentWaterFlow * percentWaterFlow * percentWaterFlow +
                        0.0546335532842876 * wetBulbTemp +
                        0.0468060318806566 * percentFanPower * wetBulbTemp +
                        -0.0244033403339062 * percentFanPower * percentFanPower * wetBulbTemp +
                        -0.267365212754448 * percentWaterFlow * wetBulbTemp +
                        0.0385664546399435 * percentFanPower * percentWaterFlow * wetBulbTemp +
                        0.037765628073743 * percentWaterFlow * percentWaterFlow * wetBulbTemp +
                        -0.000928698541521428 * wetBulbTemp * wetBulbTemp +
                        -0.000122211107650076 * percentFanPower * wetBulbTemp * wetBulbTemp +
                        0.000682937021895334 * percentWaterFlow * wetBulbTemp * wetBulbTemp +
                        0.00000679217734960548 * wetBulbTemp * wetBulbTemp * wetBulbTemp +
                        1.47274732178792 * range +
                        -0.869303590626237 * percentFanPower * range +
                        0.149995781695274 * percentFanPower * percentFanPower * range;

            approach2 = 2.4548219494635 * percentWaterFlow * range +
                        -0.161092120908292 * percentFanPower * percentWaterFlow * range +
                        -0.0830303891087807 * percentWaterFlow * percentWaterFlow * range +
                        -0.0251101427687245 * wetBulbTemp * range +
                        0.00430042875730149 * percentFanPower * wetBulbTemp * range +
                        -0.013969370453107 * percentWaterFlow * wetBulbTemp * range +
                        0.000096171182587938 * wetBulbTemp * wetBulbTemp * range +
                        -0.0251558254472348 * range * range +
                        0.0077094706621763 * percentFanPower * range * range +
                        -0.0173842428341529 * percentWaterFlow * range * range +
                        0.000244578460749651 * wetBulbTemp * range * range +
                        0.000123026859143619 * range * range * range;
        }

        approach = approach1 + approach2;
        deltaApproach = abs(approach - desiredApproach);

        if (deltaApproach < oldDeltaApproach || deltaApproach > 100) {
            oldDeltaApproach = deltaApproach;
            percentFanPowerReturned = percentFanPower;
        }

        percentFanPower += deltaPercentFanPower;
    }

    percentFanPowerReturned = modifyPercentFanPower(percentFanPowerReturned);

    if (range == 0) {
        percentFanPowerReturned = 0;
    }

    if (percentFanPowerReturned >= 1) {
        CWTHourly[yearHourIndex] = wetBulbHourlyTemp[yearHourIndex] + oldDeltaApproach + desiredApproach;

        if (CWTHourly[yearHourIndex] > 150) {
            CWTHourly[yearHourIndex] = 150;
        }
    } else {
        CWTHourly[yearHourIndex] = wetBulbHourlyTemp[yearHourIndex] + desiredApproach;
    }

    return percentFanPowerReturned;
}

double ProcessCooling::getPercentWaterFlow(int yearHourIndex) {
    double percentWaterFlowTemporary;
    double chillerTonnageTotal;

    chillerTonnageTotal = getChillerTonnageTotal();
    percentWaterFlowTemporary = (waterCooledSystem.CWFlowRate * chillerTonnageTotal) / (nominalWaterFlowGPMPerTon * tower.tonnage * tower.numTower);

    if (waterCooledSystem.CWVariableFlow) {
        double weightedAverageChillerLoad = getWeightedAverageChillerLoad(yearHourIndex) / chillerTonnageTotal;
        percentWaterFlowTemporary *= weightedAverageChillerLoad;
    }

    percentWaterFlowTemporary = max(0.5, percentWaterFlowTemporary); // Minimum 50% flow
    percentWaterFlowTemporary = min(2.0, percentWaterFlowTemporary); // Maximum 200% flow

    return percentWaterFlowTemporary;
}

double ProcessCooling::getRange(int yearHourIndex) {
    double chillerTonnageTotal = getChillerTonnageTotal();
    double weightedAverageChillerLoad = getWeightedAverageChillerLoad(yearHourIndex) / chillerTonnageTotal;
    if (weightedAverageChillerLoad == 0) {
        return 0.0;
    }

    double percentWaterFlowTemporary = (waterCooledSystem.CWFlowRate * chillerTonnageTotal) / (nominalWaterFlowGPMPerTon * tower.tonnage * tower.numTower);

    double averageChillerEfficiency = 0.0;
    for (int Chiller = 0; Chiller < numChillers; ++Chiller) {
        averageChillerEfficiency += chillerHourlyPower[Chiller][yearHourIndex] / chillerTonnageTotal;
    }

    double range;
    if (waterCooledSystem.CWVariableFlow) {
        percentWaterFlowTemporary *= weightedAverageChillerLoad;

        if (weightedAverageChillerLoad < 0.5) {
            range = ((1 * weightedAverageChillerLoad + averageChillerEfficiency * 3413 / 12000) / (waterCooledSystem.CWFlowRate * 0.5)) * 24;
        } else {
            range = ((1 * weightedAverageChillerLoad + averageChillerEfficiency * 3413 / 12000) / (waterCooledSystem.CWFlowRate * weightedAverageChillerLoad)) * 24;
        }

    } else {
        range = ((1 * weightedAverageChillerLoad + averageChillerEfficiency * 3413 / 12000) / waterCooledSystem.CWFlowRate) * 24;
    }

    if (percentWaterFlowTemporary > 2) { // Maximum 200% flow (need bypass)
        range *= percentWaterFlowTemporary / 2;
    }

    return range;
}

double ProcessCooling::getApproach(double wetBulbTemp, double minToChillersTemp) const {
    double approach;

    if (waterCooledSystem.useFreeCooling && wetBulbTemp <= FCTemp) {
        approach = FCTemp - wetBulbTemp;
    } else {
        if (waterCooledSystem.constantCWT) {
            approach = waterCooledSystem.CWT - wetBulbTemp;
        } else {
            double followDiffTemp = coolingType == Water ? waterCooledSystem.CWVariableFlow : airCooledSystem.CWTFollow;
            if (wetBulbTemp < (minToChillersTemp - followDiffTemp)) {
                approach = minToChillersTemp - wetBulbTemp;
            } else {
                if (wetBulbTemp + followDiffTemp > 110) {
                    approach = 110 - wetBulbTemp;
                    if (approach <= 0) {
                        approach = 1;
                    }
                } else {
                    approach = followDiffTemp;
                }
            }
        }
    }

    return approach;
}

double ProcessCooling::modifyPercentFanPower(double percentFanPower) const {
    double percentFanPowerTemporary1 = percentFanPower;
    double percentFanPowerTemporary2;
    double VSDEfficiency;
    double motorEfficiency;

    if (tower.fanSpeedType == FanMotorSpeedType::One) {
        percentFanPowerTemporary1 = getCubeRoot(percentFanPowerTemporary1);
    }
    else if (tower.fanSpeedType == FanMotorSpeedType::Two) {
        percentFanPowerTemporary1 = getCubeRoot(percentFanPowerTemporary1);
        percentFanPowerTemporary2 = percentFanPowerTemporary1 * 0.25; // 0.25 slope of first segment

        if (percentFanPowerTemporary1 > 0.5) {
            percentFanPowerTemporary2 = percentFanPowerTemporary1 * 1.75 - 0.75; // Adjust for second segment
        }

        percentFanPowerTemporary1 = percentFanPowerTemporary2;
    }
    else if (tower.fanSpeedType == FanMotorSpeedType::Variable) {
        motorEfficiency = 1;

        VSDEfficiency = (50.87 +
                         1.283 * percentFanPowerTemporary1 * 100 -
                         0.0142 * percentFanPowerTemporary1 * 100 * percentFanPowerTemporary1 * 100 +
                         0.0000583 * percentFanPowerTemporary1 * 100 * percentFanPowerTemporary1 * 100 * percentFanPowerTemporary1 * 100) / 100;

        percentFanPowerTemporary1 /= (VSDEfficiency * motorEfficiency);
    }

    return percentFanPowerTemporary1;
}

double ProcessCooling::getWeightedAverageChillerLoad(int yearHourIndex) {
    double weightedAverageChillerLoad = 0.0;
    for (int c = 0; c < numChillers; ++c) {
        weightedAverageChillerLoad += (chillerHourlyLoad[c][yearHourIndex] / 100.0) * chillers[c].capacity;
    }

    return weightedAverageChillerLoad;
}

double ProcessCooling::getChillerTonnageTotal() {
    double chillerTonnageTotalTemp = 0.0;

    for (int c = 0; c < numChillers; ++c) {
        chillerTonnageTotalTemp += chillers[c].capacity;
    }

    return chillerTonnageTotalTemp;
}

double ProcessCooling::getCubeRoot(double number) {
    if (number > 0.0) {
        return exp(log(number) / 3.0);
    } else {
        return number;
    }
}

double ProcessCooling::getPumpHP(double power) {
    double pumpHPOptions[21] = {0.5, 1, 1.5, 2, 3, 5, 7.5, 10, 15, 20,
                                25, 30, 40, 50, 60, 75, 100, 125, 150, 175, 200};

    double result = power;
    for (int p = 0; p < 20; ++p) {
        if (result > pumpHPOptions[p] && result < pumpHPOptions[p + 1]) {
            result = pumpHPOptions[p + 1];
            break;
        }
    }

    return result;
}
