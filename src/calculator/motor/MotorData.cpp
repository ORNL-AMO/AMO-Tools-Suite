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
