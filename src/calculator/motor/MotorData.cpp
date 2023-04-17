/**
 * @file
 * @brief Contains the implementation of the MotorData calculator/table ORM class
 *
 * @author Colin Causey (causeyc)
 * @bug No known bugs.
 *
 */

#include <results/InputData.h>
#include "calculator/motor/MotorData.h"


MotorData::MotorData(double hp, int synchronousSpeed, int poles, double nominalEfficiency, Motor::EfficiencyClass efficiencyClass, std::string nemaTable,
			  		 std::string enclosureType,  Motor::LineFrequency lineFrequency, int voltageLimit, std::string catalog)
				   : hp(hp), synchronousSpeed(synchronousSpeed), poles(poles), nominalEfficiency(nominalEfficiency),
				   	 efficiencyClass(efficiencyClass), nemaTable(std::move(nemaTable)), enclosureType(std::move(enclosureType)),
					 lineFrequency(lineFrequency), voltageLimit(voltageLimit), catalog(std::move(catalog))
{}

Motor::EfficiencyClass MotorData::getEfficiencyClass() const {
	return efficiencyClass;
}
std::string MotorData::getNemaTable() const {
	return nemaTable;
}
std::string MotorData::getEnclosureType() const {
	return enclosureType;
}
std::string MotorData::getCatalog() const {
	return catalog;
}

int MotorData::getSynchronousSpeed() const {
	return synchronousSpeed;
}
int MotorData::getPoles() const {
	return poles;
}
Motor::LineFrequency MotorData::getLineFrequency() const {
	return lineFrequency;
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
	

void MotorData::setEfficiencyClass(const Motor::EfficiencyClass &efficiencyClass) {
	MotorData::efficiencyClass = efficiencyClass;
}
void MotorData::setNemaTable(const std::string &nemaTable) {
	MotorData::nemaTable = nemaTable;
}
void MotorData::setEnclosureType(const std::string &enclosureType) {
	MotorData::enclosureType = enclosureType;
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
void MotorData::setLineFrequency(const Motor::LineFrequency lineFrequency) {
	MotorData::lineFrequency = lineFrequency;
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