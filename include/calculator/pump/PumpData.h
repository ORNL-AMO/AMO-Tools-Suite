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
             std::string radialBearingType,  
             std::string thrustBearingType,
             std::string shaftOrientation, 
             std::string shaftSealType, 
             std::string fluidType, 
             std::string priority,
             std::string driveType, 
             std::string flangeConnectionClass, 
             std::string flangeConnectionSize,
             std::string componentId,
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
             double motorEfficiency,
             bool outOfService,
             bool spare
             );

    const bool getOutOfService() const;

    void setOutOfService(const bool &outOfService);

    const double getInletDiameter() const;

    void setInletDiameter(const double &inletDiameter);

    const double getOutletDiameter() const;

    void setOutletDiameter(const double &outletDiameter);

    const double getStaticSuctionHead() const;

    void setStaticSuctionHead(const double &staticSuctionHead);

    const double getStaticDischargeHead() const;

    void setStaticDischargeHead(const double &staticDischargeHead);

    const double getFluidDensity() const;

    void setFluidDensity(const double &fluidDensity);

    const double getMaxWorkingPressure() const;

    void setMaxWorkingPressure(const double &maxWorkingPressure);

    const double getMaxAmbientTemperature() const;

    void setMaxAmbientTemperature(const double &maxAmbientTemperature);

    const double getMaxSuctionLift() const;

    void setMaxSuctionLift(const double &maxSuctionLift);

    const double getDisplacement() const;

    void setDisplacement(const double &displacement);

    const double getStartingTorque() const;

    void setStartingTorque(const double &startingTorque);

    const double getRatedSpeed() const;

    void setRatedSpeed(const double &ratedSpeed);

    const double getMinFlowSize() const;

    void setMinFlowSize(const double &minFlowSize);

    const double getPumpSize() const;

    void setPumpSize(const double &pumpSize);

    const double getImpellerDiameter() const;

    void setImpellerDiameter(const double &impellerDiameter);

    const double getEfficiency() const;

    void setEfficiency(const double &efficiency);

    const double getLineFrequency() const;

    void setLineFrequency(const double &lineFrequency);

    const int getSpeed() const;

    void setSpeed(const int &speed);

    const int getNumStages() const;

    void setNumStages(const int &numStages);

    const int getYearlyOperatingHours() const;

    void setYearlyOperatingHours(const int &yearlyOperatingHours);

    const int getYearInstalled() const;

    void setYearInstalled(const int &yearInstalled);

    const std::string getSerialNumber() const;

    void setSerialNumber(const std::string &serialNumber);

    const std::string getStatus() const;

    void setStatus(const std::string &status);

    const std::string getPumpType() const;

    void setPumpType(const std::string &pumpType);

    const std::string getRadialBearingType() const;

    void setRadialBearingType(const std::string &radialBearingType);

    const std::string getThrustBearingType() const;

    void setThrustBearingType(const std::string &thrustBearingType);

    const std::string getShaftOrientation() const;

    void setShaftOrientation(const std::string &shaftOrientation);

    const std::string getShaftSealType() const;

    void setShaftSealType(const std::string &shaftSealType);

    const std::string getFluidType() const;

    void setFluidType(const std::string &fluidType);

    const std::string getDriveType() const;

    void setDriveType(const std::string &driveType);

    const std::string getFlangeConnectionClass() const;

    void setFlangeConnectionClass(const std::string &flangeConnectionClass);

    const std::string getFlangeConnectionSize() const;

    void setFlangeConnectionSize(const std::string &flangeConnectionSize);

    const std::string getManufacturer() const;

    void setManufacturer(const std::string &manufacturer);

    const std::string getModel() const;

    void setModel(const std::string &model);

    const std::string getPriority() const;

    void setPriority(const std::string &priority);

    int getFinalMotorRpm() const;

    void setFinalMotorRpm(int finalMotorRpm);

    const double getDesignHead() const;

    void setDesignHead(const double &designHead);

    const double getDesignFlow() const;

    void setDesignFlow(const double &designFlow);

    const double getDesignEfficiency() const;

    void setDesignEfficiency(const double &designEfficiency);

    const double getMotorRatedPower() const;

    void setMotorRatedPower(const double &motorRatedPower);

    const double getMotorFullLoadAmps() const;

    void setMotorFullLoadAmps(const double &motorFullLoadAmps);

    const double getOperatingFlowRate() const;

    void setOperatingFlowRate(const double &operatingFlowRate);

    const double getOperatingHead() const;

    void setOperatingHead(const double &operatingHead);

    const double getMotorEfficiency() const;

    void setMotorEfficiency(const double &motorEfficiency);

    const std::string getMotorEfficiencyClass() const;

    void setMotorEfficiencyClass(const std::string &motorEfficiencyClass);

    const std::string getComponentId() const;

    void setComponentId(const std::string &componentId);
    
    const int getMotorRatedVoltage() const;

    void setMotorRatedVoltage(const int &motorRatedVoltage);

    const bool getSpare() const;

    void setSpare(const bool &spare);


    bool isOutOfService() const;

    int getId() const;

    void setId(int id);


private:
    std::string manufacturer, model, serialNumber, status, pumpType, radialBearingType, thrustBearingType, motorEfficiencyClass, componentId;
    std::string shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass;
    std::string flangeConnectionSize;

    int speed, numStages, yearlyOperatingHours, yearInstalled, finalMotorRpm, motorRatedVoltage;

    double inletDiameter, outletDiameter, designHead, designFlow, designEfficiency, motorRatedPower, motorFullLoadAmps, operatingFlowRate, operatingHead, motorEfficiency;
    double staticSuctionHead, staticDischargeHead, fluidDensity, maxWorkingPressure;
    double maxAmbientTemperature, maxSuctionLift, displacement, startingTorque, ratedSpeed, impellerDiameter;
    double efficiency, lineFrequency, minFlowSize, pumpSize;

    bool outOfService, spare;

    int id; // used for the database

    friend class SQLite;
};

#endif //AMO_TOOLS_SUITE_PUMPDATA_H