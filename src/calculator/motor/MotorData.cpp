/**
 * @file
 * @brief Contains the implementation of the MotorData calculator/table ORM class
 *
 * @author Colin Causey (causeyc)
 * @bug No known bugs.
 *
 */

#include "calculator/motor/MotorData.h"


MotorData::MotorData(double hp, int synchronousSpeed, int poles, double nominalEfficiency, std::string efficiencyType, std::string nemaTable,
			  		 std::string motorType, int hz, int voltageLimit, std::string catalog)
				   : hp(hp), synchronousSpeed(synchronousSpeed), poles(poles), nominalEfficiency(nominalEfficiency),
				   	 efficiencyType(std::move(efficiencyType)), nemaTable(std::move(nemaTable)), motorType(std::move(motorType)),
					 hz(hz), voltageLimit(voltageLimit), catalog(std::move(catalog))
{}

const std::string &MotorData::getEfficiencyType() const {
	return efficiencyType;
}
const std::string &MotorData::getNemaTable() const {
	return nemaTable;
}
const std::string &MotorData::getMotorType() const {
	return motorType;
}
const std::string &MotorData::getCatalog() const {
	return catalog;
}

int MotorData::getSynchronousSpeed() const {
	return synchronousSpeed;
}
int MotorData::getPoles() const {
	return poles;
}
int MotorData::getHz() const {
	return hz;
}
int MotorData::getVoltageLimit() const {
	return voltageLimit;
}

double MotorData::getHp() const {
	return hp;
}
double MotorData::getNominalEfficiency() const {
	return nominalEfficiency;
}
	

void MotorData::setEfficiencyType(const std::string &efficiencyType) {
	MotorData::efficiencyType = efficiencyType;
}
void MotorData::setNemaTable(const std::string &nemaTable) {
	MotorData::nemaTable = nemaTable;
}
void MotorData::setMotorType(const std::string &motorType) {
	MotorData::motorType = motorType;
}
void MotorData::setCatalog(const std::string &catalog) {
	MotorData::catalog = catalog;
}

void MotorData::setSynchronousSpeed(int synchronousSpeed) {
	MotorData::synchronousSpeed = synchronousSpeed;
}
void MotorData::setPoles(int poles) {
	MotorData::poles = poles;
}
void MotorData::setHz(int hz) {
	MotorData::hz = hz;
}
void MotorData::setVoltageLimit(int voltageLimit) {
	MotorData::voltageLimit = voltageLimit;
}

void MotorData::setHp(double hp) {
	MotorData::hp = hp;
}
void MotorData::setNominalEfficiency(double nominalEfficiency) {
	MotorData::nominalEfficiency = nominalEfficiency;
}


int MotorData::getId() const {
	return id;
}

void MotorData::setId(int id) {
	this->id = id;
}