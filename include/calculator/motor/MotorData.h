#ifndef AMO_TOOLS_SUITE_MOTORDATA_H
#define AMO_TOOLS_SUITE_MOTORDATA_H

#include <string>

class MotorData {
public:
	MotorData(std::string manufacturer, std::string model, std::string catalog, std::string motorType, int hp, int speed, int fullLoadSpeed, std::string enclosureType, std::string frameNumber,
	          int voltageRating, std::string purpose, int uFrame, int cFace, int verticalShaft, int dFlange, double serviceFactor, std::string insulationClass, double weight, double listPrice,
	          double windingResistance, double warranty, int rotorBars, int statorSlots, double efficiency100, double efficiency75, double efficiency50, double efficiency25, double powerFactor100,
	          double powerFactor75, double powerFactor50, double powerFactor25, double torqueFullLoad, double torqueBreakDown, double torqueLockedRotor, double ampsFullLoad, double ampsIdle,
	          double ampsLockedRotor, double stalledRotorTimeHot, double stalledRotorTimeCold, double peakVoltage0ms, double peakVoltage5ms);

private:
	std::string manufacturer, model, catalog, motorType, enclosureType, frameNumber, purpose, insulationClass;

	int hp, speed, fullLoadSpeed, voltageRating, uFrame, cFace, verticalShaft, dFlange, rotorBars, statorSlots;

	double serviceFactor, weight, listPrice, windingResistance, warranty, efficiency100, efficiency75, efficiency50, efficiency25;
	double powerFactor100, powerFactor75, powerFactor50, powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor;
	double ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot, stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms;

	friend class SQLite;
};

#endif //AMO_TOOLS_SUITE_MOTORDATA_H
