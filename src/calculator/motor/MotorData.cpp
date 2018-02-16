#include "calculator/motor/MotorData.h"

MotorData::MotorData(std::string manufacturer, std::string model, std::string catalog, std::string motorType, int hp, int speed, int fullLoadSpeed, std::string enclosureType, std::string frameNumber,
	          int voltageRating, std::string purpose, int uFrame, int cFace, int verticalShaft, int dFlange, double serviceFactor, std::string insulationClass, double weight, double listPrice,
	          double windingResistance, double warranty, int rotorBars, int statorSlots, double efficiency100, double efficiency75, double efficiency50, double efficiency25, double powerFactor100,
	          double powerFactor75, double powerFactor50, double powerFactor25, double torqueFullLoad, double torqueBreakDown, double torqueLockedRotor, double ampsFullLoad, double ampsIdle,
	          double ampsLockedRotor, double stalledRotorTimeHot, double stalledRotorTimeCold, double peakVoltage0ms, double peakVoltage5ms)
			: manufacturer(std::move(manufacturer)), model(std::move(model)), catalog(std::move(catalog)), motorType(std::move(motorType)), enclosureType(std::move(enclosureType)),
			  frameNumber(std::move(frameNumber)), purpose(std::move(purpose)), insulationClass(std::move(insulationClass)), hp(hp), speed(speed), fullLoadSpeed(fullLoadSpeed),
			  voltageRating(voltageRating), uFrame(uFrame), cFace(cFace), verticalShaft(verticalShaft), dFlange(dFlange), rotorBars(rotorBars), statorSlots(statorSlots), serviceFactor(serviceFactor),
			  weight(weight), listPrice(listPrice), windingResistance(windingResistance), warranty(warranty), efficiency100(efficiency100), efficiency75(efficiency75), efficiency50(efficiency50),
			  efficiency25(efficiency25), powerFactor100(powerFactor100), powerFactor75(powerFactor75), powerFactor50(powerFactor50), powerFactor25(powerFactor25), torqueFullLoad(torqueFullLoad),
			  torqueBreakDown(torqueBreakDown), torqueLockedRotor(torqueLockedRotor), ampsFullLoad(ampsFullLoad), ampsIdle(ampsIdle), ampsLockedRotor(ampsLockedRotor),
			  stalledRotorTimeHot(stalledRotorTimeHot), stalledRotorTimeCold(stalledRotorTimeCold), peakVoltage0ms(peakVoltage0ms), peakVoltage5ms(peakVoltage5ms)
{}

const std::string &MotorData::getManufacturer() const {
	return manufacturer;
}

void MotorData::setManufacturer(const std::string &manufacturer) {
	MotorData::manufacturer = manufacturer;
}

const std::string &MotorData::getModel() const {
	return model;
}

void MotorData::setModel(const std::string &model) {
	MotorData::model = model;
}

const std::string &MotorData::getCatalog() const {
	return catalog;
}

void MotorData::setCatalog(const std::string &catalog) {
	MotorData::catalog = catalog;
}

const std::string &MotorData::getMotorType() const {
	return motorType;
}

void MotorData::setMotorType(const std::string &motorType) {
	MotorData::motorType = motorType;
}

const std::string &MotorData::getEnclosureType() const {
	return enclosureType;
}

void MotorData::setEnclosureType(const std::string &enclosureType) {
	MotorData::enclosureType = enclosureType;
}

const std::string &MotorData::getFrameNumber() const {
	return frameNumber;
}

void MotorData::setFrameNumber(const std::string &frameNumber) {
	MotorData::frameNumber = frameNumber;
}

const std::string &MotorData::getPurpose() const {
	return purpose;
}

void MotorData::setPurpose(const std::string &purpose) {
	MotorData::purpose = purpose;
}

const std::string &MotorData::getInsulationClass() const {
	return insulationClass;
}

void MotorData::setInsulationClass(const std::string &insulationClass) {
	MotorData::insulationClass = insulationClass;
}

int MotorData::getHp() const {
	return hp;
}

void MotorData::setHp(int hp) {
	MotorData::hp = hp;
}

int MotorData::getSpeed() const {
	return speed;
}

void MotorData::setSpeed(int speed) {
	MotorData::speed = speed;
}

int MotorData::getFullLoadSpeed() const {
	return fullLoadSpeed;
}

void MotorData::setFullLoadSpeed(int fullLoadSpeed) {
	MotorData::fullLoadSpeed = fullLoadSpeed;
}

int MotorData::getVoltageRating() const {
	return voltageRating;
}

void MotorData::setVoltageRating(int voltageRating) {
	MotorData::voltageRating = voltageRating;
}

int MotorData::getUFrame() const {
	return uFrame;
}

void MotorData::setUFrame(int uFrame) {
	MotorData::uFrame = uFrame;
}

int MotorData::getCFace() const {
	return cFace;
}

void MotorData::setCFace(int cFace) {
	MotorData::cFace = cFace;
}

int MotorData::getVerticalShaft() const {
	return verticalShaft;
}

void MotorData::setVerticalShaft(int verticalShaft) {
	MotorData::verticalShaft = verticalShaft;
}

int MotorData::getDFlange() const {
	return dFlange;
}

void MotorData::setDFlange(int dFlange) {
	MotorData::dFlange = dFlange;
}

int MotorData::getRotorBars() const {
	return rotorBars;
}

void MotorData::setRotorBars(int rotorBars) {
	MotorData::rotorBars = rotorBars;
}

int MotorData::getStatorSlots() const {
	return statorSlots;
}

void MotorData::setStatorSlots(int statorSlots) {
	MotorData::statorSlots = statorSlots;
}

double MotorData::getServiceFactor() const {
	return serviceFactor;
}

void MotorData::setServiceFactor(double serviceFactor) {
	MotorData::serviceFactor = serviceFactor;
}

double MotorData::getWeight() const {
	return weight;
}

void MotorData::setWeight(double weight) {
	MotorData::weight = weight;
}

double MotorData::getListPrice() const {
	return listPrice;
}

void MotorData::setListPrice(double listPrice) {
	MotorData::listPrice = listPrice;
}

double MotorData::getWindingResistance() const {
	return windingResistance;
}

void MotorData::setWindingResistance(double windingResistance) {
	MotorData::windingResistance = windingResistance;
}

double MotorData::getWarranty() const {
	return warranty;
}

void MotorData::setWarranty(double warranty) {
	MotorData::warranty = warranty;
}

double MotorData::getEfficiency100() const {
	return efficiency100;
}

void MotorData::setEfficiency100(double efficiency100) {
	MotorData::efficiency100 = efficiency100;
}

double MotorData::getEfficiency75() const {
	return efficiency75;
}

void MotorData::setEfficiency75(double efficiency75) {
	MotorData::efficiency75 = efficiency75;
}

double MotorData::getEfficiency50() const {
	return efficiency50;
}

void MotorData::setEfficiency50(double efficiency50) {
	MotorData::efficiency50 = efficiency50;
}

double MotorData::getEfficiency25() const {
	return efficiency25;
}

void MotorData::setEfficiency25(double efficiency25) {
	MotorData::efficiency25 = efficiency25;
}

double MotorData::getPowerFactor100() const {
	return powerFactor100;
}

void MotorData::setPowerFactor100(double powerFactor100) {
	MotorData::powerFactor100 = powerFactor100;
}

double MotorData::getPowerFactor75() const {
	return powerFactor75;
}

void MotorData::setPowerFactor75(double powerFactor75) {
	MotorData::powerFactor75 = powerFactor75;
}

double MotorData::getPowerFactor50() const {
	return powerFactor50;
}

void MotorData::setPowerFactor50(double powerFactor50) {
	MotorData::powerFactor50 = powerFactor50;
}

double MotorData::getPowerFactor25() const {
	return powerFactor25;
}

void MotorData::setPowerFactor25(double powerFactor25) {
	MotorData::powerFactor25 = powerFactor25;
}

double MotorData::getTorqueFullLoad() const {
	return torqueFullLoad;
}

void MotorData::setTorqueFullLoad(double torqueFullLoad) {
	MotorData::torqueFullLoad = torqueFullLoad;
}

double MotorData::getTorqueBreakDown() const {
	return torqueBreakDown;
}

void MotorData::setTorqueBreakDown(double torqueBreakDown) {
	MotorData::torqueBreakDown = torqueBreakDown;
}

double MotorData::getTorqueLockedRotor() const {
	return torqueLockedRotor;
}

void MotorData::setTorqueLockedRotor(double torqueLockedRotor) {
	MotorData::torqueLockedRotor = torqueLockedRotor;
}

double MotorData::getAmpsFullLoad() const {
	return ampsFullLoad;
}

void MotorData::setAmpsFullLoad(double ampsFullLoad) {
	MotorData::ampsFullLoad = ampsFullLoad;
}

double MotorData::getAmpsIdle() const {
	return ampsIdle;
}

void MotorData::setAmpsIdle(double ampsIdle) {
	MotorData::ampsIdle = ampsIdle;
}

double MotorData::getAmpsLockedRotor() const {
	return ampsLockedRotor;
}

void MotorData::setAmpsLockedRotor(double ampsLockedRotor) {
	MotorData::ampsLockedRotor = ampsLockedRotor;
}

double MotorData::getStalledRotorTimeHot() const {
	return stalledRotorTimeHot;
}

void MotorData::setStalledRotorTimeHot(double stalledRotorTimeHot) {
	MotorData::stalledRotorTimeHot = stalledRotorTimeHot;
}

double MotorData::getStalledRotorTimeCold() const {
	return stalledRotorTimeCold;
}

void MotorData::setStalledRotorTimeCold(double stalledRotorTimeCold) {
	MotorData::stalledRotorTimeCold = stalledRotorTimeCold;
}

double MotorData::getPeakVoltage0ms() const {
	return peakVoltage0ms;
}

void MotorData::setPeakVoltage0ms(double peakVoltage0ms) {
	MotorData::peakVoltage0ms = peakVoltage0ms;
}

double MotorData::getPeakVoltage5ms() const {
	return peakVoltage5ms;
}

void MotorData::setPeakVoltage5ms(double peakVoltage5ms) {
	MotorData::peakVoltage5ms = peakVoltage5ms;
}

int MotorData::getId() const {
	return id;
}

void MotorData::setId(int id) {
	this->id = id;
}
