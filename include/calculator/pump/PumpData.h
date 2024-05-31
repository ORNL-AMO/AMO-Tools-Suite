//
// Created by zf9 on 7/16/18.
// Re-implemented by causeyc on 1/27/2020
// Changes made nbintertech 4/21/2022

#ifndef AMO_TOOLS_SUITE_PUMPDATA_H
#define AMO_TOOLS_SUITE_PUMPDATA_H

#include <string>

class PumpData {
public:
    PumpData(std::string manufacturer, 
             std::string model, 
             std::string serialNumber,
             std::string status, 
             std::string pumpType, 
             std::string shaftOrientation, 
             std::string shaftSealType, 
             std::string fluidType, 
             std::string priority,
             std::string driveType, 
             std::string flangeConnectionClass, 
             std::string flangeConnectionSize,
             std::string componentId,
             std::string system,
             std::string location,
             std::string motorEfficiencyClass,
             int speed, 
             int numStages,  
             int yearlyOperatingHours, 
             int yearInstalled, 
             int finalMotorRpm,
             int motorRatedVoltage,
             double inletDiameter, 
             double outletDiameter,
             double staticSuctionHead,
             double staticDischargeHead, 
             double fluidDensity, 
             double maxWorkingPressure, 
             double maxAmbientTemperature,
             double maxSuctionLift,  
             double displacement, 
             double startingTorque, 
             double ratedSpeed,
             double impellerDiameter, 
             double efficiency, 
             double lineFrequency, 
             double minFlowSize,
             double pumpSize,  
             double designHead,
             double designFlow,
             double designEfficiency,
             double motorRatedPower,
             double motorFullLoadAmps,
             double operatingFlowRate,
             double operatingHead,
             double measuredCurrent,
             double measuredPower,
             double measuredVoltage,
             double motorEfficiency);


    double getInletDiameter() const;

    void setInletDiameter(const double &inletDiameter);

    double getOutletDiameter() const;

    void setOutletDiameter(const double &outletDiameter);

    double getStaticSuctionHead() const;

    void setStaticSuctionHead(const double &staticSuctionHead);

    double getStaticDischargeHead() const;

    void setStaticDischargeHead(const double &staticDischargeHead);

    double getFluidDensity() const;

    void setFluidDensity(const double &fluidDensity);

    double getMaxWorkingPressure() const;

    void setMaxWorkingPressure(const double &maxWorkingPressure);

    double getMaxAmbientTemperature() const;

    void setMaxAmbientTemperature(const double &maxAmbientTemperature);

    double getMaxSuctionLift() const;

    void setMaxSuctionLift(const double &maxSuctionLift);

    double getDisplacement() const;

    void setDisplacement(const double &displacement);

    double getStartingTorque() const;

    void setStartingTorque(const double &startingTorque);

    double getRatedSpeed() const;

    void setRatedSpeed(const double &ratedSpeed);

    double getMinFlowSize() const;

    void setMinFlowSize(const double &minFlowSize);

    double getPumpSize() const;

    void setPumpSize(const double &pumpSize);

    double getImpellerDiameter() const;

    void setImpellerDiameter(const double &impellerDiameter);

    double getEfficiency() const;

    void setEfficiency(const double &efficiency);

    double getLineFrequency() const;

    void setLineFrequency(const double &lineFrequency);

    int getSpeed() const;

    void setSpeed(const int &speed);

    int getNumStages() const;

    void setNumStages(const int &numStages);

    int getYearlyOperatingHours() const;

    void setYearlyOperatingHours(const int &yearlyOperatingHours);

    int getYearInstalled() const;

    void setYearInstalled(const int &yearInstalled);

    std::string getSerialNumber() const;

    void setSerialNumber(const std::string &serialNumber);

    std::string getStatus() const;

    void setStatus(const std::string &status);

    std::string getPumpType() const;

    void setPumpType(const std::string &pumpType);

    std::string getShaftOrientation() const;

    void setShaftOrientation(const std::string &shaftOrientation);

    std::string getSystem() const;

    void setSystem(const std::string &system);

    std::string getLocation() const;

    void setLocation(const std::string &location);

    std::string getShaftSealType() const;

    void setShaftSealType(const std::string &shaftSealType);

    std::string getFluidType() const;

    void setFluidType(const std::string &fluidType);

    std::string getDriveType() const;

    void setDriveType(const std::string &driveType);

    std::string getFlangeConnectionClass() const;

    void setFlangeConnectionClass(const std::string &flangeConnectionClass);

    std::string getFlangeConnectionSize() const;

    void setFlangeConnectionSize(const std::string &flangeConnectionSize);

    std::string getManufacturer() const;

    void setManufacturer(const std::string &manufacturer);

    std::string getModel() const;

    void setModel(const std::string &model);

    std::string getPriority() const;

    void setPriority(const std::string &priority);

    int getFinalMotorRpm() const;

    void setFinalMotorRpm(int finalMotorRpm);

    double getDesignHead() const;

    void setDesignHead(const double &designHead);

    double getDesignFlow() const;

    void setDesignFlow(const double &designFlow);

    double getDesignEfficiency() const;

    void setDesignEfficiency(const double &designEfficiency);

    double getMotorRatedPower() const;

    void setMotorRatedPower(const double &motorRatedPower);

    double getMotorFullLoadAmps() const;

    void setMotorFullLoadAmps(const double &motorFullLoadAmps);

    double getOperatingFlowRate() const;

    void setOperatingFlowRate(const double &operatingFlowRate);

    double getOperatingHead() const;

    void setOperatingHead(const double &operatingHead);

    double getMeasuredCurrent() const;

    void setMeasuredCurrent(const double &measuredCurrent);

    double getMeasuredPower() const;

    void setMeasuredPower(const double &measuredPower);

    double getMeasuredVoltage() const;

    void setMeasuredVoltage(const double &measuredVoltage);

    double getMotorEfficiency() const;

    void setMotorEfficiency(const double &motorEfficiency);

    std::string getMotorEfficiencyClass() const;

    void setMotorEfficiencyClass(const std::string &motorEfficiencyClass);

    std::string getComponentId() const;

    void setComponentId(const std::string &componentId);
    
    int getMotorRatedVoltage() const;

    void setMotorRatedVoltage(const int &motorRatedVoltage);

    int getId() const;

    void setId(int id);


private:
    std::string manufacturer, model, serialNumber, status, pumpType;
    std::string shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass;
    std::string flangeConnectionSize, componentId, system, location, motorEfficiencyClass;

    int speed, numStages, yearlyOperatingHours, yearInstalled, finalMotorRpm, motorRatedVoltage;

    double inletDiameter, outletDiameter, staticSuctionHead, staticDischargeHead, fluidDensity;
    double maxWorkingPressure, maxAmbientTemperature, maxSuctionLift, displacement, startingTorque, ratedSpeed;
    double impellerDiameter, efficiency, lineFrequency, minFlowSize, pumpSize, designHead, designFlow, designEfficiency;
    double motorRatedPower, motorFullLoadAmps, operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency;

    int id; // used for the database

    friend class SQLite;
};

#endif //AMO_TOOLS_SUITE_PUMPDATA_H