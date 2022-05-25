//
// Created by zf9 on 7/16/18.
// Re-implemented by causeyc on 1/27/2020

#include "calculator/pump/PumpData.h"

PumpData::PumpData(std::string manufacturer, 
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
             bool spare)
        : manufacturer(std::move(manufacturer)), 
          model(std::move(model)), 
          serialNumber(std::move(serialNumber)),
          status(std::move(status)),  
          pumpType(std::move(pumpType)), 
          radialBearingType(std::move(radialBearingType)),
          thrustBearingType(std::move(thrustBearingType)), 
          shaftOrientation(std::move(shaftOrientation)), 
          shaftSealType(std::move(shaftSealType)),
          fluidType(std::move(fluidType)), 
          priority(std::move(priority)), 
          driveType(std::move(driveType)), 
          flangeConnectionClass(std::move(flangeConnectionClass)),
          flangeConnectionSize(std::move(flangeConnectionSize)), 
          componentId(std::move(componentId)), 
          motorEfficiencyClass(std::move(motorEfficiencyClass)), 
          speed(speed), 
          numStages(numStages),
          yearlyOperatingHours(yearlyOperatingHours), 
          yearInstalled(yearInstalled), 
          finalMotorRpm(finalMotorRpm),
          motorRatedVoltage(motorRatedVoltage),
          inletDiameter(inletDiameter), 
          outletDiameter(outletDiameter),
          staticSuctionHead(staticSuctionHead),
          staticDischargeHead(staticDischargeHead), 
          fluidDensity(fluidDensity), 
          maxWorkingPressure(maxWorkingPressure),
          maxAmbientTemperature(maxAmbientTemperature),
          maxSuctionLift(maxSuctionLift),  
          displacement(displacement),
          startingTorque(startingTorque),
          ratedSpeed(ratedSpeed), 
          impellerDiameter(impellerDiameter),
          efficiency(efficiency), 
          lineFrequency(lineFrequency), 
          minFlowSize(minFlowSize), 
          pumpSize(pumpSize), 
          designHead(designHead), 
          designFlow(designFlow), 
          designEfficiency(designEfficiency), 
          motorRatedPower(motorRatedPower), 
          motorFullLoadAmps(motorFullLoadAmps), 
          operatingFlowRate(operatingFlowRate), 
          operatingHead(operatingHead), 
          motorEfficiency(motorEfficiency), 
          outOfService(outOfService),
          spare(spare),
          id(NULL)
{}


const bool PumpData::getOutOfService() const {
    return outOfService;
}

void PumpData::setOutOfService(const bool &outOfService)  {
    PumpData::outOfService = outOfService;
}

const bool PumpData::getSpare() const {
    return spare;
}

void PumpData::setSpare(const bool &spare)  {
    PumpData::spare = spare;
}

const double PumpData::getInletDiameter() const {
    return inletDiameter;
}

void PumpData::setInletDiameter(const double &inletDiameter) {
    PumpData::inletDiameter = inletDiameter;
}

const double PumpData::getOutletDiameter() const {
    return outletDiameter;
}

void PumpData::setOutletDiameter(const double &outletDiameter) {
    PumpData::outletDiameter = outletDiameter;
}


const double PumpData::getStaticSuctionHead() const {
    return staticSuctionHead;
}

void PumpData::setStaticSuctionHead(const double &staticSuctionHead) {
    PumpData::staticSuctionHead = staticSuctionHead;
}

const double PumpData::getStaticDischargeHead() const {
    return staticDischargeHead;
}

void PumpData::setStaticDischargeHead(const double &staticDischargeHead) {
    PumpData::staticDischargeHead = staticDischargeHead;
}

const double PumpData::getFluidDensity() const {
    return fluidDensity;
}

void PumpData::setFluidDensity(const double &fluidDensity) {
    PumpData::fluidDensity = fluidDensity;
}

const double PumpData::getMaxWorkingPressure() const {
    return maxWorkingPressure;
}

void PumpData::setMaxWorkingPressure(const double &maxWorkingPressure) {
    PumpData::maxWorkingPressure = maxWorkingPressure;
}

const double PumpData::getMaxAmbientTemperature() const {
    return maxAmbientTemperature;
}

void PumpData::setMaxAmbientTemperature(const double &maxAmbientTemperature) {
    PumpData::maxAmbientTemperature = maxAmbientTemperature;
}

const double PumpData::getMaxSuctionLift() const {
    return maxSuctionLift;
}

void PumpData::setMaxSuctionLift(const double &maxSuctionLift) {
    PumpData::maxSuctionLift = maxSuctionLift;
}

const double PumpData::getDisplacement() const {
    return displacement;
}

void PumpData::setDisplacement(const double &displacement) {
    PumpData::displacement = displacement;
}

const double PumpData::getStartingTorque() const {
    return startingTorque;
}

void PumpData::setStartingTorque(const double &startingTorque) {
    PumpData::startingTorque = startingTorque;
}

const double PumpData::getRatedSpeed() const {
    return ratedSpeed;
}

void PumpData::setRatedSpeed(const double &ratedSpeed)  {
	PumpData::ratedSpeed = ratedSpeed;
}

const double PumpData::getMinFlowSize() const {
    return minFlowSize;
}

void PumpData::setMinFlowSize(const double &minFlowSize)  {
	PumpData::minFlowSize = minFlowSize;
}

const double PumpData::getPumpSize() const {
    return pumpSize;
}

void PumpData::setPumpSize(const double &pumpSize)  {
	PumpData::pumpSize = pumpSize;
}



const double PumpData::getImpellerDiameter() const {
    return impellerDiameter;
}

void PumpData::setImpellerDiameter(const double &impellerDiameter)  {
	PumpData::impellerDiameter = impellerDiameter;
}

const double PumpData::getEfficiency() const {
    return efficiency;
}

void PumpData::setEfficiency(const double &efficiency)  {
	PumpData::efficiency = efficiency;
}

const double PumpData::getLineFrequency() const {
    return lineFrequency;
}

void PumpData::setLineFrequency(const double &lineFrequency)  {
	PumpData::lineFrequency = lineFrequency;
}


const double PumpData::getDesignHead() const {
    return designHead;
}

void PumpData::setDesignHead(const double &designHead)  {
	PumpData::designHead = designHead;
}

const double PumpData::getDesignFlow() const {
    return designFlow;
}

void PumpData::setDesignFlow(const double &designFlow)  {
	PumpData::designFlow = designFlow;
}

const double PumpData::getDesignEfficiency() const {
    return designFlow;
}

void PumpData::setDesignEfficiency(const double &designEfficiency)  {
	PumpData::designEfficiency = designEfficiency;
}


const double PumpData::getMotorRatedPower() const {
    return motorRatedPower;
}

void PumpData::setMotorRatedPower(const double &motorRatedPower)  {
	PumpData::motorRatedPower = motorRatedPower;
}


const double PumpData::getMotorFullLoadAmps() const {
    return motorFullLoadAmps;
}

void PumpData::setMotorFullLoadAmps(const double &motorFullLoadAmps)  {
	PumpData::motorFullLoadAmps = motorFullLoadAmps;
}


const double PumpData::getOperatingFlowRate() const {
    return operatingFlowRate;
}

void PumpData::setOperatingFlowRate(const double &operatingFlowRate)  {
	PumpData::operatingFlowRate = operatingFlowRate;
}


const double PumpData::getOperatingHead() const {
    return operatingHead;
}

void PumpData::setOperatingHead(const double &operatingHead)  {
	PumpData::operatingHead = operatingHead;
}

const double PumpData::getMotorEfficiency() const {
    return motorEfficiency;
}

void PumpData::setMotorEfficiency(const double &motorEfficiency)  {
	PumpData::motorEfficiency = motorEfficiency;
}


const int PumpData::getSpeed() const {
    return speed;
}

void PumpData::setSpeed(const int &speed)  {
	PumpData::speed = speed;
}

const int PumpData::getNumStages() const {
    return numStages;
}

void PumpData::setNumStages(const int &numStages)  {
	PumpData::numStages = numStages;
}

const int PumpData::getYearlyOperatingHours() const {
    return yearlyOperatingHours;
}

void PumpData::setYearlyOperatingHours(const int &yearlyOperatingHours)  {
	PumpData::yearlyOperatingHours = yearlyOperatingHours;
}

const int PumpData::getYearInstalled() const {
    return yearInstalled;
}

void PumpData::setYearInstalled(const int &yearInstalled)  {
	PumpData::yearInstalled = yearInstalled;
}

const std::string PumpData::getSerialNumber() const {
    return serialNumber;
}

void PumpData::setSerialNumber(const std::string &serialNumber)  {
	PumpData::serialNumber = serialNumber;
}

const std::string PumpData::getStatus() const {
    return status;
}

void PumpData::setStatus(const std::string &status)  {
	PumpData::status = status;
}

const std::string PumpData::getPumpType() const {
    return pumpType;
}

void PumpData::setPumpType(const std::string &pumpType)  {
	PumpData::pumpType = pumpType;
}

const std::string PumpData::getRadialBearingType() const {
    return radialBearingType;
}

void PumpData::setRadialBearingType(const std::string &radialBearingType)  {
	PumpData::radialBearingType = radialBearingType;
}

const std::string PumpData::getThrustBearingType() const {
    return thrustBearingType;
}

void PumpData::setThrustBearingType(const std::string &thrustBearingType)  {
	PumpData::thrustBearingType = thrustBearingType;
}

const std::string PumpData::getShaftOrientation() const {
    return shaftOrientation;
}

void PumpData::setShaftOrientation(const std::string &shaftOrientation)  {
	PumpData::shaftOrientation = shaftOrientation;
}

const std::string PumpData::getShaftSealType() const {
    return shaftSealType;
}

void PumpData::setShaftSealType(const std::string &shaftSealType)  {
	PumpData::shaftSealType = shaftSealType;
}

const std::string PumpData::getFluidType() const {
    return fluidType;
}

void PumpData::setFluidType(const std::string &fluidType)  {
	PumpData::fluidType = fluidType;
}

const std::string PumpData::getDriveType() const {
    return driveType;
}

void PumpData::setDriveType(const std::string &driveType)  {
	PumpData::driveType = driveType;
}

const std::string PumpData::getFlangeConnectionClass() const {
    return flangeConnectionClass;
}

void PumpData::setFlangeConnectionClass(const std::string &flangeConnectionClass)  {
	PumpData::flangeConnectionClass = flangeConnectionClass;
}

const std::string PumpData::getFlangeConnectionSize() const {
    return flangeConnectionSize;
}

void PumpData::setFlangeConnectionSize(const std::string &flangeConnectionSize)  {
	PumpData::flangeConnectionSize = flangeConnectionSize;
}

const std::string PumpData::getManufacturer() const {
    return manufacturer;
}

void PumpData::setManufacturer(const std::string &manufacturer)  {
	PumpData::manufacturer = manufacturer;
}

const std::string PumpData::getModel() const {
    return model;
}

void PumpData::setModel(const std::string &model)  {
	PumpData::model = model;
}


const std::string PumpData::getMotorEfficiencyClass() const {
    return motorEfficiencyClass;
}

void PumpData::setMotorEfficiencyClass(const std::string &motorEfficiencyClass)  {
	PumpData::motorEfficiencyClass = motorEfficiencyClass;
}


const std::string PumpData::getComponentId() const {
    return componentId;
}

void PumpData::setComponentId(const std::string &componentId)  {
	PumpData::componentId = componentId;
}

const int PumpData::getMotorRatedVoltage() const {
    return motorRatedVoltage;
}

void PumpData::setMotorRatedVoltage(const int &motorRatedVoltage)  {
	PumpData::motorRatedVoltage = motorRatedVoltage;
}

const std::string PumpData::getPriority() const {
    return priority;
}

void PumpData::setPriority(const std::string &priority)  {
	PumpData::priority = priority;
}

int PumpData::getFinalMotorRpm() const {
    return finalMotorRpm;
}

void PumpData::setFinalMotorRpm(int finalMotorRpm)  {
	PumpData::finalMotorRpm = finalMotorRpm;
}


bool PumpData::isOutOfService() const {
    return outOfService;
}

int PumpData::getId() const {
    return id;
}

void PumpData::setId(int id)  {
	PumpData::id = id;
}

