//
// Created by zf9 on 7/16/18.
//

#ifndef AMO_TOOLS_SUITE_PUMPDATA_H
#define AMO_TOOLS_SUITE_PUMPDATA_H

#include <string>

class PumpData {
public:
    PumpData(std::string manufacturer, std::string model, std::string type, std::string serialNumber, std::string status, bool outOfService
            , double weight, std::string pumpType, int speed, double inletDiameter, double outletDiameter, std::string radialBearingType, std::string thrustBearingType
            , std::string shaftOrientation, std::string shaftSealType, int numShafts, int numStages, std::string fluidType
            , int yearlyOperatingHours, int yearInstalled, std::string priority, double percentageOfSchedule, double dailyPumpCapacity
            , double measuredPumpCapacity, double pumpPerformance, double staticSuctionHead, double staticDischargeHead, double fluidDensity
            , double lengthOfDischargePipe, double pipeDesignFrictionLosses, std::string driveType, double maxWorkingPressure, double maxAmbientTemperature
            , double maxSuctionLift, int finalMotorRpm, double displacement, double startingTorque, double ratedSpeed, double shaftDiameter
            , std::string flangeConnectionClass, std::string flangeConnectionSize, double minFlowSize, double pumpSize
            , double impellerDiameter, double efficiency, double output60Hz);





    const bool &getOutOfService() const;

    void setOutOfService(const bool &outOfService);

    const double &getInletDiameter() const;

    void setInletDiameter(const double &inletDiameter);

    const double &getOutletDiameter() const;

    void setOutletDiameter(const double &outletDiameter);

    const double &getPercentageOfSchedule() const;

    void setPercentageOfSchedule(const double &percentageOfSchedule);

    const double &getDailyPumpCapacity() const;

    void setDailyPumpCapacity(const double &dailyPumpCapacity);

    const double &getMeasuredPumpCapacity() const;

    void setMeasuredPumpCapacity(const double &measuredPumpCapacity);

    const double &getPumpPerformance() const;

    void setPumpPerformance(const double &pumpPerformance);

    const double &getStaticSuctionHead() const;

    void setStaticSuctionHead(const double &staticSuctionHead);

    const double &getStaticDischargeHead() const;

    void setStaticDischargeHead(const double &staticDischargeHead);

    const double &getFluidDensity() const;

    void setFluidDensity(const double &fluidDensity);

    const double &getLengthOfDischargePipe() const;

    void setLengthOfDischargePipe(const double &lengthOfDischargePipe);

    const double &getPipeDesignFrictionLosses() const;

    void setPipeDesignFrictionLosses(const double &pipeDesignFrictionLosses);

    const double &getMaxWorkingPressure() const;

    void setMaxWorkingPressure(const double &maxWorkingPressure);

    const double &getMaxAmbientTemperature() const;

    void setMaxAmbientTemperature(const double &maxAmbientTemperature);

    const double &getMaxSuctionLift() const;

    void setMaxSuctionLift(const double &maxSuctionLift);

    const double &getDisplacement() const;

    void setDisplacement(const double &displacement);

    const double &getStartingTorque() const;

    void setStartingTorque(const double &startingTorque);

    const double &getRatedSpeed() const;

    void setRatedSpeed(const double &ratedSpeed);

    const double &getMinFlowSize() const;

    void setMinFlowSize(const double &minFlowSize);

    const double &getPumpSize() const;

    void setPumpSize(const double &pumpSize);

    const double &getShaftDiameter() const;

    void setShaftDiameter(const double &shaftDiameter);

    const double &getImpellerDiameter() const;

    void setImpellerDiameter(const double &impellerDiameter);

    const double &getEfficiency() const;

    void setEfficiency(const double &efficiency);

    const double &getOutput60Hz() const;

    void setOutput60Hz(const double &output60Hz);

    const int &getSpeed() const;

    void setSpeed(const int &speed);

    const int &getNumShafts() const;

    void setNumShafts(const int &numShafts);

    const int &getNumStages() const;

    void setNumStages(const int &numStages);

    const int &getYearlyOperatingHours() const;

    void setYearlyOperatingHours(const int &yearlyOperatingHours);

    const int &getYearInstalled() const;

    void setYearInstalled(const int &yearInstalled);

    const std::string &getSerialNumber() const;

    void setSerialNumber(const std::string &serialNumber);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

    const std::string &getPumpType() const;

    void setPumpType(const std::string &pumpType);

    const std::string &getRadialBearingType() const;

    void setRadialBearingType(const std::string &radialBearingType);

    const std::string &getThrustBearingType() const;

    void setThrustBearingType(const std::string &thrustBearingType);

    const std::string &getShaftOrientation() const;

    void setShaftOrientation(const std::string &shaftOrientation);

    const std::string &getShaftSealType() const;

    void setShaftSealType(const std::string &shaftSealType);

    const std::string &getFluidType() const;

    void setFluidType(const std::string &fluidType);

    const std::string &getDriveType() const;

    void setDriveType(const std::string &driveType);

    const std::string &getFlangeConnectionClass() const;

    void setFlangeConnectionClass(const std::string &flangeConnectionClass);

    const std::string &getFlangeConnectionSize() const;

    void setFlangeConnectionSize(const std::string &flangeConnectionSize);

    const std::string &getType() const;

    void setType(const std::string &type);

    const std::string &getManufacturer() const;

    void setManufacturer(const std::string &manufacturer);

    const std::string &getModel() const;

    void setModel(const std::string &model);

    const std::string &getPriority() const;

    void setPriority(const std::string &priority);

    int getFinalMotorRpm() const;

    void setFinalMotorRpm(int finalMotorRpm);

    double getWeight() const;

    void setWeight(double weight);

    bool isOutOfService() const;

    int getId() const;

    void setId(int id);


private:
    std::string manufacturer, model, serialNumber, type, status, pumpType, radialBearingType,
            thrustBearingType, shaftOrientation, shaftSealType;
    std::string fluidType, priority, driveType, flangeConnectionClass, flangeConnectionSize;

    int numShafts, speed, numStages, yearlyOperatingHours, yearInstalled, finalMotorRpm;

    double inletDiameter, weight, outletDiameter, percentageOfSchedule, dailyPumpCapacity,
            measuredPumpCapacity, pumpPerformance;
    double staticSuctionHead, staticDischargeHead, fluidDensity, lengthOfDischargePipe,
            pipeDesignFrictionLosses, maxWorkingPressure;
    double maxAmbientTemperature, maxSuctionLift, displacement, startingTorque, ratedSpeed,
            shaftDiameter, impellerDiameter;
    double efficiency, output60Hz, minFlowSize, pumpSize;

    bool outOfService;

    int id; // used for the database

    friend class SQLite;
};

#endif //AMO_TOOLS_SUITE_PUMPDATA_H
