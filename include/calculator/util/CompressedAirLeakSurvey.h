#ifndef AMO_LIBRARY_COMPRESSEDAIRLEAKSURVEY_H
#define AMO_LIBRARY_COMPRESSEDAIRLEAKSURVEY_H

#include <exception>
#include <stdexcept>
#include <vector>
#include "calculator/util/CompressedAirReduction.h"

class EstimateMethodData
{
  public:
    EstimateMethodData(const double leakRateEstimate) : leakRateEstimate(leakRateEstimate) {}

    double getLeakRateEstimate() const {return leakRateEstimate; }
    void setLeakRateEstimate(double leakRateEstimate);

  private:
    double leakRateEstimate;
};

class DecibelsMethodData
{
  public:
    DecibelsMethodData(const double linePressure, const double decibels, const double decibelRatingA, 
		  const double pressureA, const double firstFlowA, const double secondFlowA, const double decibelRatingB, const double pressureB,
		  const double firstFlowB, const double secondFlowB)
		  : linePressure(linePressure), decibels(decibels), decibelRatingA(decibelRatingA), 
		    pressureA(pressureA), firstFlowA(firstFlowA), secondFlowA(secondFlowA), decibelRatingB(decibelRatingB),
		    pressureB(pressureB), firstFlowB(firstFlowB), secondFlowB(secondFlowB) {}

    double getLinePressure() const { return linePressure; }
    double getDecibels() const { return decibels; }
    double getDecibelRatingA() const { return decibelRatingA; }
    double getPressureA() const { return pressureA; }
    double getFirstFlowA() const { return firstFlowA; }
    double getSecondFlowA() const { return secondFlowA; }
    double getDecibelRatingB() const { return decibelRatingB; }
    double getPressureB() const { return pressureB; }
    double getFirstFlowB() const { return firstFlowB; }
    double getSecondFlowB() const { return secondFlowB; }

    void setLinePressure(double linePressure);
    void setDecibels(double decibels);
    void setDecibelRatingA(double decibelRatingA);
    void setPressureA(double pressureA);
    void setFirstFlowA(double firstFlowA);
    void setSecondFlowA(double secondFlowA);
    void setDecibelRatingB(double decibelRatingB);
    void setPressureB(double pressureB);
    void setFirstFlowB(double firstFlowB);
    void setSecondFlowB(double secondFlowB);

    double calculate();

  private:
    double linePressure; // X
    double decibels; // Y
    double decibelRatingA; // Y1
    double pressureA; // X1
    double firstFlowA; // Q11
    double secondFlowA; // Q21
    double decibelRatingB; // Y2
    double pressureB; // X2
    double firstFlowB; // Q12
    double secondFlowB; // Q22
};

// BagMethodData implemented in CompressedAirReduction.h

class OrificeMethodData
{
  public:
    OrificeMethodData(const double airTemp, const double atmPressure, const double dischargeCoef, const double diameter, 
                      const double supplyPressure, const int numOrifices)
			: airTemp(airTemp), atmPressure(atmPressure), dischargeCoef(dischargeCoef), diameter(diameter),
			  supplyPressure(supplyPressure), numOrifices(numOrifices) {}

    double getAirTemp() const { return airTemp; }
    double getAtmPressure() const { return atmPressure; }
    double getDischargeCoef() const { return dischargeCoef; }
    double getDiameter() const { return diameter; }
    double getSupplyPressure() const { return supplyPressure; }
    int getNumOrifices() const { return numOrifices; }

    void setAirTemp(double airTemp);
    void setAtmPressure(double atmPressure);
    void setDischargeCoef(double dischargeCoef);
    void setDiameter(double diameter);
    void setSupplyPressure(double supplyPressure);
    void setNumOrifices(int numOrifices);

    double calculate();

  private:
    double airTemp, atmPressure, dischargeCoef, diameter, supplyPressure;
    int numOrifices;
};

class CompressedAirLeakSurveyInput
{
  public:
    CompressedAirLeakSurveyInput(const int hoursPerYear, const int utilityType, const double utilityCost, const int measurementMethod,
                                const EstimateMethodData estimateMethodData, const DecibelsMethodData decibelsMethodData, 
                                const BagMethodData bagMethodData, const OrificeMethodData orificeMethodData,  
                                const CompressorElectricityData compressorElectricityData, const int units)
        : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost), measurementMethod(measurementMethod),
          estimateMethodData(estimateMethodData), decibelsMethodData(decibelsMethodData), bagMethodData(bagMethodData), 
          orificeMethodData(orificeMethodData), compressorElectricityData(compressorElectricityData), units(units) {}

    int getHoursPerYear() const { return hoursPerYear; } // operating time
    int getUtilityType() const { return utilityType; }
    int getMeasurementMethod() const { return measurementMethod; }
    int getUnits() const { return units; }
    double getUtilityCost() const { return utilityCost; }
    EstimateMethodData getEstimateMethodData() const { return estimateMethodData; }
    DecibelsMethodData getDecibelsMethodData() const { return decibelsMethodData; }
    BagMethodData getBagMethodData() const { return bagMethodData; }
    OrificeMethodData getOrificeMethodData() const { return orificeMethodData; }
    CompressorElectricityData getCompressorElectricityData() const { return compressorElectricityData; }

  private:
    int hoursPerYear, utilityType;
    double utilityCost;
    int measurementMethod;
    EstimateMethodData estimateMethodData;
    DecibelsMethodData decibelsMethodData;
    BagMethodData bagMethodData;
    OrificeMethodData orificeMethodData;
    CompressorElectricityData compressorElectricityData;
    int units;
};

class CompressedAirLeakSurvey
{
  public:
    struct Output
    {
        Output(double annualTotalElectricity, double annualTotalElectricityCost, double totalFlowRate, double annualTotalFlowRate)
            : annualTotalElectricity(annualTotalElectricity), annualTotalElectricityCost(annualTotalElectricityCost), 
              totalFlowRate(totalFlowRate), annualTotalFlowRate(annualTotalFlowRate) {}

        Output() = default;
        double annualTotalElectricity = 0, annualTotalElectricityCost = 0, totalFlowRate = 0, annualTotalFlowRate = 0;
    };

    CompressedAirLeakSurvey(std::vector<CompressedAirLeakSurveyInput> &compressedAirLeakSurveyInputVec) : compressedAirLeakSurveyInputVec(compressedAirLeakSurveyInputVec)
    {
    }

    CompressedAirLeakSurvey::Output calculate();
    std::vector<CompressedAirLeakSurveyInput> const &getCompressedAirLeakSurveyInputVec() const
    {
        return compressedAirLeakSurveyInputVec;
    }
    void setCompressedAirReductionInputVec(std::vector<CompressedAirReductionInput> &compressedAirReductionInputVec);

  private:
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec;
    CompressedAirLeakSurvey::Output output;
};

#endif // AMO_LIBRARY_COMPRESSEDAIRLEAKSURVEY_H