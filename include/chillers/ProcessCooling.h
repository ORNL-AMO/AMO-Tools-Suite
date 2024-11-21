/**
 * @file Header file for Process Fluid Cooling Energy Calculations
 *
 * @brief Originally (CWSAT) writen in VB by University of Massachusetts - Amherst with funding from the U.S. Department of Energy
 *        Calculator estimates energy consumption of operating Chillers, Pumps and Towers in a cooling system (both air & water).
 *        Allows:
 *              Input multiple & varying capacity and types of Chillers that are operating together.
 *              Flexible input for operating schedule for each Chiller.
 *              Apply changes ( improvements / measures) and compare & examine, quantifying energy and cost savings.
 *                  Changes:
 *                      Increasing the chilled water temperature
 *                      Decreasing the condenser water temperature
 *                      Replacing the chillers
 *                      Applying variable speed control to circulation pump motors
 *                      Upgrade Tower Cell Fan Motor controls
 *                  Upgrades:
 *                      Replace chiller refrigerant
 *                      Install Variable Speed Drive (VSD) on Centrifugal compressors
 *                      Use Free Cooling
 *
 * @extends This converted implementation version removes the limit on number of Pumps and Chillers.
 *
 * @author Converted by Omer Aziz from VB to C++ (omerb).
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_PROCESSCOOLING_H
#define AMO_TOOLS_SUITE_PROCESSCOOLING_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

const int MONTHS = 12;
const int LOAD_NUM = 11;
const int HOURS_IN_YEAR = 8760;

class ProcessCooling{
public:
    enum RefrigerantType {
        R_11,
        R_123,
        R_12,
        R_134a,
        R_22,
        R_717
    };

    enum ACSourceLocation {
        Inside,
        Outside
    };

    enum CoolingSystemType {
        Water,
        Air
    };

    enum CellFanType {
        AxialFan,
        CentrifugalFan
    };

    enum TowerSizedBy {
        Tonnage,
        Fan_HP
    };

    enum ChillerCompressorType {
        Centrifugal,
        Screw,
        Reciprocating
    };

    enum FanMotorSpeedType {
        One,
        Two,
        Variable
    };

    struct ChillerOutput {
        /**
         *
         * @returns arrays of double corresponding to 11 % load bins (0,10,20,30,40,50,60,70,80,90,100)
         *
         * @param efficiency array of double, units kW/ton
         * @param hours array of double, units hours
         * @param power array of double, units kW
         * @param energy array of double, units kWh
         */
        ChillerOutput(vector<vector<double>> efficiency, vector<vector<double>> hours, vector<vector<double>> power, vector<vector<double>> energy) :
                efficiency(std::move(efficiency)), hours(std::move(hours)), power(std::move(power)), energy(std::move(energy)) {}

        vector<vector<double>> efficiency;
        vector<vector<double>> hours;
        vector<vector<double>> power;
        vector<vector<double>> energy;
    };

    struct ChillerPumpingEnergyOutput {
        /**
         *
         * @returns array of double (Pumps Energy), size corresponding to the # of chillers
         *
         * @param chillerPumpingEnergy double, units kWh
         */
        explicit ChillerPumpingEnergyOutput(vector<double> pumpingEnergy) :
                chillerPumpingEnergy(std::move(pumpingEnergy)){}

        vector<double> chillerPumpingEnergy;
    };

    struct TowerOutput {
        /**
         *
         * @param no arguments
         */
        TowerOutput()= default;

        /**
         *
         * @returns arrays of double corresponding to 6 wet bulb temp bins => <35, 35-44, 45-54, 55-64, 65-74, >=75;
         *
         * @param tempBins, constant array  {35, 45, 55, 65, 75, 75}
         * @param hours array of double, units hours
         * @param energy array of double, units kWh
         */
        TowerOutput(vector<double> hours, vector<double> energy) :
                hours(std::move(hours)), energy(std::move(energy)) {}

        vector<double> tempBins = {35, 45, 55, 65, 75, 75};
        vector<double> hours;
        vector<double> energy;
    };

    struct WaterCooledSystemInput {
        /**
         *
         * @param no arguments
         */
        WaterCooledSystemInput()= default;

        /**
         *
         * @param CHWT double, units F, 35 - 55 Default 44, Chilled Water Supply Temperature
         * @param useFreeCooling boolean
         * @param HEXApproachTemp double, units F,  5 - 20, heat exchange temp when free cooling and heat exchanger used
         * @param constantCWT boolean, Is CW temperature constant
         * @param CWT double, units F, 70 - 90, CW temperature constant
         * @param CWVariableFlow boolean
         * @param CWFlowRate double, units gpm/ton
         * @param CWTFollow double, units F, when CW temperature not constant
         */
        WaterCooledSystemInput(double CHWT, bool useFreeCooling, double HEXApproachTemp,
                               bool constantCWT, double CWT, bool CWVariableFlow, double CWFlowRate, double CWTFollow) :
                CHWT(CHWT), useFreeCooling(useFreeCooling), HEXApproachTemp(HEXApproachTemp),
                constantCWT(constantCWT), CWT(CWT), CWVariableFlow(CWVariableFlow), CWFlowRate(CWFlowRate), CWTFollow(CWTFollow) {
            isWaterCooled = true;
        }

        double CHWT = 44;
        bool useFreeCooling = false;
        double HEXApproachTemp = 0;
        bool constantCWT = true;
        double CWT = 85;
        bool CWVariableFlow = true;
        double CWFlowRate = 3;
        double CWTFollow = 0;
        bool isWaterCooled = false;
    };

    struct AirCooledSystemInput {
        /**
         *
         * @param no arguments
         */
        AirCooledSystemInput()= default;

        /**
         *
         * @param CHWT double, units F, 35 - 55 Default 44, Chilled Water Supply Temperature
         * @param OADT double, units F, 80 - 110 Standard 95, Outdoor Air Design Temperature
         * @param ACSource Enumeration ACSourceLocation, Cooling Air Source, Indoor or Outside
         * @param indoorTemp double, units F, if Air Source Indoor 60 - 90
         * @param CWTFollow double, units F, if Air Source Outside 5 - 20
         */
        AirCooledSystemInput(double CHWT, double OADT, ACSourceLocation ACSource, double indoorTemp, double CWTFollow) :
                CHWT(CHWT), OADT(OADT), ACSource(ACSource), indoorTemp(indoorTemp), CWTFollow(CWTFollow) {
            isAirCooled = true;
        }

        double CHWT = 44;
        double OADT = 95;
        ACSourceLocation ACSource = ACSourceLocation::Outside;
        double indoorTemp = 75;
        double CWTFollow = 0;
        bool isAirCooled = false;
    };

    struct PumpInput {
        /**
         *
         * @param variableFlow boolean
         * @param flowRate double, units gpm/ton
         * @param efficiency double, percentage as fraction
         * @param motorSize double, units hp
         * @param motorEfficiency double, percentage as fraction
         */
        PumpInput(bool variableFlow, double flowRate, double efficiency, double motorSize, double motorEfficiency) :
                variableFlow(variableFlow), flowRate(flowRate), efficiency(efficiency*100), motorSize(motorSize), motorEfficiency(motorEfficiency*100) {}

        bool variableFlow;
        double flowRate;
        double efficiency;
        double motorSize;
        double motorEfficiency;
    };

    struct TowerInput {
        /**
         *
         * @param no arguments
         */
        TowerInput()= default;

        /**
         *
         * @param numTower integer, # of Towers
         * @param numFanPerTower_Cells integer, # Cells
         * @param fanSpeedType Enumeration FanMotorSpeedType
         * @param towerSizing Enumeration TowerSizedBy, sized by tonnage or fan hp
         * @param towerCellFanType Enumeration CellFanType
         * @param cellFanHP double, units hp, 1 -100 hp
         * @param tonnage double, units ton, 20 - 3000
         */
        TowerInput(int numTower, int numFanPerTower_Cells, FanMotorSpeedType fanSpeedType,
                   TowerSizedBy towerSizing, CellFanType towerCellFanType, double cellFanHP, double tonnage) :
                numTower(numTower), numFanPerTower_Cells(numFanPerTower_Cells), fanSpeedType(fanSpeedType),
                fanHP(cellFanHP), tonnage(tonnage) {
            fanHP = getFanHP(tonnage, towerSizing, numFanPerTower_Cells, towerCellFanType, fanHP);
        }

        int numTower;
        int numFanPerTower_Cells;
        FanMotorSpeedType fanSpeedType;
        double fanHP;
        double tonnage;
    };

    struct ChillerInput {
        /**
         *
         * @details Use this constructor when not defining custom Chiller and not replacing chiller refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, units ton
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar months
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff, double age,
                     bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads) :
                chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown), fullLoadEff(fullLoadEff), age(age),
                installVSD(installVSD), useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
                isCustomChiller(false), loadAtPercent({}), kwPerTonLoads({}) ,
                changeRefrig(false), currentRefrig(RefrigerantType::R_11), proposedRefrig(RefrigerantType::R_11){}

        /**
         *
         * @details Use this constructor when replacing chiller refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, units ton
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar months
         *
         * @param currentRefrig Enumeration RefrigerantType
         * @param proposedRefrig Enumeration RefrigerantType
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff, double age,
                     bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     bool changeRefrig, RefrigerantType currentRefrig, RefrigerantType proposedRefrig) :
                chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown), fullLoadEff(fullLoadEff), age(age),
                installVSD(installVSD), useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
                isCustomChiller(false), loadAtPercent({}), kwPerTonLoads({}) ,
                changeRefrig(changeRefrig), currentRefrig(currentRefrig), proposedRefrig(proposedRefrig){}

        /**
         *
         * @details Use this constructor when replacing chiller refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, units ton
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar months
         *
         * @param currentRefrig Enumeration RefrigerantType
         * @param proposedRefrig Enumeration RefrigerantType
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff, double age,
                     bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     RefrigerantType currentRefrig, RefrigerantType proposedRefrig) :
                chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown), fullLoadEff(fullLoadEff), age(age),
                installVSD(installVSD), useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
                isCustomChiller(false), loadAtPercent({}), kwPerTonLoads({}) ,
                changeRefrig(true), currentRefrig(currentRefrig), proposedRefrig(proposedRefrig){}

        /**
         *
         * @details Use this constructor to define custom Chiller
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, units ton
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar months
         *
         * @param loadAtPercent double array, % loading
         * @param kwPerTonLoads double array, kW/ton at the corresponding % loading
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff, double age,
                     bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     vector<double> loadAtPercent, vector<double> kwPerTonLoads) :
                chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown), fullLoadEff(fullLoadEff), age(age),
                installVSD(installVSD), useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
                isCustomChiller(true), loadAtPercent(std::move(loadAtPercent)), kwPerTonLoads(std::move(kwPerTonLoads)),
                changeRefrig(false), currentRefrig(RefrigerantType::R_11), proposedRefrig(RefrigerantType::R_11){
            SetCustomCoefficient();
        }

        /**
         *
         * @details Use this constructor for custom Chiller with replacing refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, units ton
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar months
         *
         * @param loadAtPercent double array, % loading
         * @param kwPerTonLoads double array, kW/ton at the corresponding % loading
         *
         * @param currentRefrig Enumeration RefrigerantType
         * @param proposedRefrig Enumeration RefrigerantType
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff, double age,
                     bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     vector<double> loadAtPercent, vector<double> kwPerTonLoads,
                     RefrigerantType currentRefrig, RefrigerantType proposedRefrig) :
                chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown), fullLoadEff(fullLoadEff), age(age),
                installVSD(installVSD), useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
                isCustomChiller(true), loadAtPercent(std::move(loadAtPercent)), kwPerTonLoads(std::move(kwPerTonLoads)),
                changeRefrig(true), currentRefrig(currentRefrig), proposedRefrig(proposedRefrig){
            SetCustomCoefficient();
        }

        ChillerCompressorType chillerType;
        double capacity;
        bool isFullLoadEffKnown;
        double fullLoadEff;
        double age;
        bool installVSD;
        bool useARIMonthlyLoadSchedule;
        vector<vector<double>> monthlyLoads;

        bool isCustomChiller;
        vector<double> loadAtPercent;
        vector<double> kwPerTonLoads;

        bool changeRefrig = false;
        RefrigerantType currentRefrig;
        RefrigerantType proposedRefrig;

        vector<double> customCoeffs;

    private:
        void SetCustomCoefficient() {
            auto size = static_cast<int>(loadAtPercent.size());
            vector<double> x(size, 0);
            vector<double> y(size, 0);
            for (int i = 0; i < size; i++) {
                x[i] = loadAtPercent[i];
                y[i] = kwPerTonLoads[i] * loadAtPercent[i] / kwPerTonLoads[0];
            }
            vector<double> coeff = solveForCoefficients(x, y);

            size = static_cast<int>(coeff.size());
            customCoeffs.resize(size, 0);
            for (int i = 0; i < size; i++) {
                customCoeffs[i] = coeff[i];
            }
        }

        static vector<double> solveForCoefficients(vector<double> x, vector<double> y) {
            if(x.empty() || x.size() != y.size()) return {};

            const int n = (int)x.size();

            vector<vector<double>> a(n, vector<double>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = pow(x[i], n-1-j);
                }
            }

            // Forward Elimination
            for (int k = 0; k < n - 1; ++k) {
                for (int i = k + 1; i < n; ++i) {
                    double factor = a[i][k] / a[k][k];
                    for (int j = k + 1; j < n; ++j) {
                        a[i][j] -= factor * a[k][j];
                    }
                    y[i] -= factor * y[k];
                }
            }

            // Back Substitution
            vector<double> coeff(n, 0);
            coeff[n-1] = y[n-1] / a[n-1][n-1];
            for (int i = n - 2; i >= 0; --i) {
                double sum = y[i];
                for (int j = i + 1; j < n; ++j) {
                    sum -= a[i][j] * coeff[j];
                }
                coeff[i] = sum / a[i][i];
            }

            return coeff;
        }
    };

    ~ProcessCooling() = default;

    /**
     *
     * @details Use this constructor for water cooling system
     *
     * @param systemOperationAnnualHours integer array of 8760 hours of the year with values as 0 or 1
     * @param weatherDryBulbHourlyTemp double, units F, array of 8760 hours of the year with dry bulb hourly recorded temperature
     * @param weatherWetBulbHourlyTemp double, units F, array of 8760 hours of the year with wet bulb hourly recorded temperature
     * @param chillerInputList ChillerInput array
     *
     * @param towerInput TowerInput
     * @param waterCooledSystemInput WaterCooledSystemInput
     */
    ProcessCooling(const vector<int>& systemOperationAnnualHours,
                   const vector<double>& weatherDryBulbHourlyTemp, const vector<double>& weatherWetBulbHourlyTemp,
                   const vector<ChillerInput>& chillerInputList,
                   TowerInput towerInput, WaterCooledSystemInput waterCooledSystemInput) :
            ProcessCooling(systemOperationAnnualHours, weatherDryBulbHourlyTemp, weatherWetBulbHourlyTemp, chillerInputList,
                           {}, towerInput, waterCooledSystemInput){}

    /**
     *
     ** @details Use this constructor for air cooled system
     *
     * @param systemOperationAnnualHours integer array of 8760 hours of the year with values as 0 or 1
     * @param weatherDryBulbHourlyTemp double array of 8760 hours of the year with dry bulb hourly recorded temperature
     * @param weatherWetBulbHourlyTemp double array of 8760 hours of the year with wet bulb hourly recorded temperature
     * @param chillerInputList ChillerInput array
     *
     * @param airCooledSystemInput AirCooledSystemInput
     */
    ProcessCooling(const vector<int>& systemOperationAnnualHours,
                   const vector<double>& weatherDryBulbHourlyTemp, const vector<double>& weatherWetBulbHourlyTemp,
                   const vector<ChillerInput>& chillerInputList,
                   AirCooledSystemInput airCooledSystemInput) :
            ProcessCooling(systemOperationAnnualHours, weatherDryBulbHourlyTemp, weatherWetBulbHourlyTemp, chillerInputList,
                           airCooledSystemInput, {}, {}){}

    /**
     *
     * @return TowerOutput
     */
    TowerOutput calculateTowerEnergy();

    /**
     *
     * @return ChillerOutput
     */
    ChillerOutput calculateChillerEnergy();

    /**
     *
     * @param pump PumpInput
     * @return ChillerPumpingEnergyOutput
     */
    ChillerPumpingEnergyOutput calculatePumpEnergy(PumpInput pump);

private:
    ProcessCooling(const vector<int>& systemOperationAnnualHours,
                   const vector<double>& weatherDryBulbHourlyTemp, const vector<double>& weatherWetBulbHourlyTemp,
                   const vector<ChillerInput>& chillerInputList,
                   AirCooledSystemInput airCooledSystemInput, TowerInput towerInput, WaterCooledSystemInput waterCooledSystemInput);

    vector<int> systemOperationAnnual;
    vector<double> dryBulbHourlyTemp;
    vector<double> wetBulbHourlyTemp;

    TowerInput tower{};
    WaterCooledSystemInput waterCooledSystem;
    AirCooledSystemInput airCooledSystem;
    CoolingSystemType coolingType;

    double FCTemp = 0;       // Free Cooling Temperature
    vector<double> CWTHourly;

    int numChillers;
    vector<ChillerInput> chillers;
    vector<vector<double>> chillerHourlyLoad;
    vector<vector<double>> chillerHourlyLoadOperational;
    vector<vector<double>> chillerHourlyEfficiencyARI;
    vector<vector<double>> chillerHourlyEfficiency;
    vector<vector<double>> chillerHourlyPower;

    void annualChillerLoadProfile();

    void annualChillerEfficiencyProfileARI();

    void annualChillerEfficiencyProfile();

    void annualChillerPowerProfile();

    static double getFanHP(double tonnage, TowerSizedBy towerSizing, int fanNum, CellFanType fanType, double fanHP);

    double getPercentFanPower(double wetBulbTemp, double percentWaterFlow, double range, double desiredApproach, int yearHourIndex);

    double getPercentWaterFlow(int yearHourIndex);

    double getRange(int yearHourIndex);

    double getApproach(double wetBulbTemp, double minToChillersTemp) const;

    double modifyPercentFanPower(double percentFanPower) const;

    double getWeightedAverageChillerLoad(int yearHourIndex);

    double getChillerTonnageTotal();

    static double getCubeRoot(double number);

    static double getPumpHP(double power);
};

#endif //AMO_TOOLS_SUITE_PROCESSCOOLING_H
