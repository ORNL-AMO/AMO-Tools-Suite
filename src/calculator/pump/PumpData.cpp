//
// Created by zf9 on 7/16/18.
//

#include "calculator/pump/PumpData.h"

PumpData::PumpData(std::string manufacturer, std::string model, std::string type, std::string serialNumber,
                   std::string status,  std::string pumpType, std::string radialBearingType,  std::string thrustBearingType, std::string shaftOrientation, std::string shaftSealType,
                   std::string fluidType, std::string priority, std::string driveType, std::string flangeConnectionClass, std::string flangeConnectionSize,
                   int numShafts, int speed, int numStages,  int yearlyOperatingHours, int yearInstalled, int finalMotorRpm,
                   double inletDiameter, double weight, double outletDiameter, double percentageOfSchedule, double dailyPumpCapacity,
                   double measuredPumpCapacity, double pumpPerformance, double staticSuctionHead,
                   double staticDischargeHead, double fluidDensity, double lengthOfDischargePipe,
                   double pipeDesignFrictionLosses,  double maxWorkingPressure,
                   double maxAmbientTemperature, double maxSuctionLift,  double displacement,
                   double startingTorque, double ratedSpeed, double shaftDiameter, double impellerDiameter,  
                   double efficiency, double output60Hz, double minFlowSize, double pumpSize,  bool outOfService, int id)
            : manufacturer(std::move(manufacturer)), model(std::move(model)), type(std::move(type)), serialNumber(std::move(serialNumber)),
              status(std::move(status)),  pumpType(std::move(pumpType)), radialBearingType(std::move(radialBearingType)),
              thrustBearingType(std::move(thrustBearingType)), shaftOrientation(std::move(shaftOrientation)), shaftSealType(std::move(shaftSealType)),
              fluidType(std::move(fluidType)), priority(std::move(priority)), driveType(std::move(driveType)), flangeConnectionClass(std::move(flangeConnectionClass)),
              flangeConnectionSize(std::move(flangeConnectionSize)), numShafts(numShafts), speed(speed), numStages(numStages),
              yearlyOperatingHours(yearlyOperatingHours), yearInstalled(yearInstalled), finalMotorRpm(finalMotorRpm),
              inletDiameter(inletDiameter), weight(weight), outletDiameter(outletDiameter), percentageOfSchedule(percentageOfSchedule), dailyPumpCapacity(dailyPumpCapacity),
              measuredPumpCapacity(measuredPumpCapacity), pumpPerformance(pumpPerformance), staticSuctionHead(staticSuctionHead),
              staticDischargeHead(staticDischargeHead), fluidDensity(fluidDensity), lengthOfDischargePipe(lengthOfDischargePipe),
              pipeDesignFrictionLosses(pipeDesignFrictionLosses),  maxWorkingPressure(maxWorkingPressure),
              maxAmbientTemperature(maxAmbientTemperature), maxSuctionLift(maxSuctionLift),  displacement(displacement),
              startingTorque(startingTorque), ratedSpeed(ratedSpeed), shaftDiameter(shaftDiameter), impellerDiameter(impellerDiameter),
              efficiency(efficiency), output60Hz(output60Hz), minFlowSize(minFlowSize), pumpSize(pumpSize), outOfService(outOfService), id(id)


{}


const bool &PumpData::getOutOfService() const {
    return outOfService;
}

void PumpData::setOutOfService(const bool &outOfService)  {
    PumpData::outOfService = outOfService;
}

const double &PumpData::getInletDiameter() const {
    return inletDiameter;
}

void PumpData::setInletDiameter(const double &inletDiameter) {
    PumpData::inletDiameter = inletDiameter;
}

const double &PumpData::getOutletDiameter() const {
    return outletDiameter;
}

void PumpData::setOutletDiameter(const double &outletDiameter) {
    PumpData::outletDiameter = outletDiameter;
}

const double &PumpData::getPercentageOfSchedule() const {
    return percentageOfSchedule;
}

void PumpData::setPercentageOfSchedule(const double &percentageOfSchedule) {
    PumpData::percentageOfSchedule = percentageOfSchedule;
}

const double &PumpData::getDailyPumpCapacity() const {
    return dailyPumpCapacity;
}

void PumpData::setDailyPumpCapacity(const double &dailyPumpCapacity) {
    PumpData::dailyPumpCapacity = dailyPumpCapacity;
}

const double &PumpData::getMeasuredPumpCapacity() const {
    return measuredPumpCapacity;
}

void PumpData::setMeasuredPumpCapacity(const double &measuredPumpCapacity) {
    PumpData::measuredPumpCapacity = measuredPumpCapacity;
}

const double &PumpData::getPumpPerformance() const {
    return pumpPerformance;
}

void PumpData::setPumpPerformance(const double &pumpPerformance) {
    PumpData::pumpPerformance = pumpPerformance;
}

const double &PumpData::getStaticSuctionHead() const {
    return staticSuctionHead;
}

void PumpData::setStaticSuctionHead(const double &staticSuctionHead) {
    PumpData::staticSuctionHead = staticSuctionHead;
}

const double &PumpData::getStaticDischargeHead() const {
    return staticDischargeHead;
}

void PumpData::setStaticDischargeHead(const double &staticDischargeHead) {
    PumpData::staticDischargeHead = staticDischargeHead;
}

const double &PumpData::getFluidDensity() const {
    return fluidDensity;
}

void PumpData::setFluidDensity(const double &fluidDensity) {
    PumpData::fluidDensity = fluidDensity;
}

const double &PumpData::getLengthOfDischargePipe() const {
    return lengthOfDischargePipe;
}

void PumpData::setLengthOfDischargePipe(const double &lengthOfDischargePipe) {
    PumpData::lengthOfDischargePipe = lengthOfDischargePipe;
}

const double &PumpData::getPipeDesignFrictionLosses() const {
    return pipeDesignFrictionLosses;
}

void PumpData::setPipeDesignFrictionLosses(const double &pipeDesignFrictionLosses) {
    PumpData::pipeDesignFrictionLosses = pipeDesignFrictionLosses;
}

const double &PumpData::getMaxWorkingPressure() const {
    return maxWorkingPressure;
}

void PumpData::setMaxWorkingPressure(const double &maxWorkingPressure) {
    PumpData::maxWorkingPressure = maxWorkingPressure;
}

const double &PumpData::getMaxAmbientTemperature() const {
    return maxAmbientTemperature;
}

void PumpData::setMaxAmbientTemperature(const double &maxAmbientTemperature) {
    PumpData::maxAmbientTemperature = maxAmbientTemperature;
}

const double &PumpData::getMaxSuctionLift() const {
    return maxSuctionLift;
}

void PumpData::setMaxSuctionLift(const double &maxSuctionLift) {
    PumpData::maxSuctionLift = maxSuctionLift;
}

const double &PumpData::getDisplacement() const {
    return displacement;
}

void PumpData::setDisplacement(const double &displacement) {
    PumpData::displacement = displacement;
}

const double &PumpData::getStartingTorque() const {
    return startingTorque;
}

void PumpData::setStartingTorque(const double &startingTorque) {
    PumpData::startingTorque = startingTorque;
}

const double &PumpData::getRatedSpeed() const {
    return ratedSpeed;
}

void PumpData::setRatedSpeed(const double &ratedSpeed)  {
	PumpData::ratedSpeed = ratedSpeed;
}

const double &PumpData::getMinFlowSize() const {
    return minFlowSize;
}

void PumpData::setMinFlowSize(const double &minFlowSize)  {
	PumpData::minFlowSize = minFlowSize;
}

const double &PumpData::getPumpSize() const {
    return pumpSize;
}

void PumpData::setPumpSize(const double &pumpSize)  {
	PumpData::pumpSize = pumpSize;
}

const double &PumpData::getShaftDiameter() const {
    return shaftDiameter;
}

void PumpData::setShaftDiameter(const double &shaftDiameter)  {
	PumpData::shaftDiameter = shaftDiameter;
}

const double &PumpData::getImpellerDiameter() const {
    return impellerDiameter;
}

void PumpData::setImpellerDiameter(const double &impellerDiameter)  {
	PumpData::impellerDiameter = impellerDiameter;
}

const double &PumpData::getEfficiency() const {
    return efficiency;
}

void PumpData::setEfficiency(const double &efficiency)  {
	PumpData::efficiency = efficiency;
}

const double &PumpData::getOutput60Hz() const {
    return output60Hz;
}

void PumpData::setOutput60Hz(const double &output60Hz)  {
	PumpData::output60Hz = output60Hz;
}

const int &PumpData::getSpeed() const {
    return speed;
}

void PumpData::setSpeed(const int &speed)  {
	PumpData::speed = speed;
}

const int &PumpData::getNumShafts() const {
    return numShafts;
}

void PumpData::setNumShafts(const int &numShafts)  {
	PumpData::numShafts = numShafts;
}

const int &PumpData::getNumStages() const {
    return numStages;
}

void PumpData::setNumStages(const int &numStages)  {
	PumpData::numStages = numStages;
}

const int &PumpData::getYearlyOperatingHours() const {
    return yearlyOperatingHours;
}

void PumpData::setYearlyOperatingHours(const int &yearlyOperatingHours)  {
	PumpData::yearlyOperatingHours = yearlyOperatingHours;
}

const int &PumpData::getYearInstalled() const {
    return yearInstalled;
}

void PumpData::setYearInstalled(const int &yearInstalled)  {
	PumpData::yearInstalled = yearInstalled;
}

const std::string &PumpData::getSerialNumber() const {
    return serialNumber;
}

void PumpData::setSerialNumber(const std::string &serialNumber)  {
	PumpData::serialNumber = serialNumber;
}

const std::string &PumpData::getStatus() const {
    return status;
}

void PumpData::setStatus(const std::string &status)  {
	PumpData::status = status;
}

const std::string &PumpData::getPumpType() const {
    return pumpType;
}

void PumpData::setPumpType(const std::string &pumpType)  {
	PumpData::pumpType = pumpType;
}

const std::string &PumpData::getRadialBearingType() const {
    return radialBearingType;
}

void PumpData::setRadialBearingType(const std::string &radialBearingType)  {
	PumpData::radialBearingType = radialBearingType;
}

const std::string &PumpData::getThrustBearingType() const {
    return thrustBearingType;
}

void PumpData::setThrustBearingType(const std::string &thrustBearingType)  {
	PumpData::thrustBearingType = thrustBearingType;
}

const std::string &PumpData::getShaftOrientation() const {
    return shaftOrientation;
}

void PumpData::setShaftOrientation(const std::string &shaftOrientation)  {
	PumpData::shaftOrientation = shaftOrientation;
}

const std::string &PumpData::getShaftSealType() const {
    return shaftSealType;
}

void PumpData::setShaftSealType(const std::string &shaftSealType)  {
	PumpData::shaftSealType = shaftSealType;
}

const std::string &PumpData::getFluidType() const {
    return fluidType;
}

void PumpData::setFluidType(const std::string &fluidType)  {
	PumpData::fluidType = fluidType;
}

const std::string &PumpData::getDriveType() const {
    return driveType;
}

void PumpData::setDriveType(const std::string &driveType)  {
	PumpData::driveType = driveType;
}

const std::string &PumpData::getFlangeConnectionClass() const {
    return flangeConnectionClass;
}

void PumpData::setFlangeConnectionClass(const std::string &flangeConnectionClass)  {
	PumpData::flangeConnectionClass = flangeConnectionClass;
}

const std::string &PumpData::getFlangeConnectionSize() const {
    return flangeConnectionSize;
}

void PumpData::setFlangeConnectionSize(const std::string &flangeConnectionSize)  {
	PumpData::flangeConnectionSize = flangeConnectionSize;
}

const std::string &PumpData::getType() const {
    return type;
}

void PumpData::setType(const std::string &type)  {
	PumpData::type = type;
}

const std::string &PumpData::getManufacturer() const {
    return manufacturer;
}

void PumpData::setManufacturer(const std::string &manufacturer)  {
	PumpData::manufacturer = manufacturer;
}

const std::string &PumpData::getModel() const {
    return model;
}

void PumpData::setModel(const std::string &model)  {
	PumpData::model = model;
}

const std::string &PumpData::getPriority() const {
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

double PumpData::getWeight() const {
    return weight;
}

void PumpData::setWeight(double weight)  {
	PumpData::weight = weight;
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

