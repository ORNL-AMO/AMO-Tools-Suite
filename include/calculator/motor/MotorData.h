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

	const std::string &getManufacturer() const;

	void setManufacturer(const std::string &manufacturer);

	const std::string &getModel() const;

	void setModel(const std::string &model);

	const std::string &getCatalog() const;

	void setCatalog(const std::string &catalog);

	const std::string &getMotorType() const;

	void setMotorType(const std::string &motorType);

	const std::string &getEnclosureType() const;

	void setEnclosureType(const std::string &enclosureType);

	const std::string &getFrameNumber() const;

	void setFrameNumber(const std::string &frameNumber);

	const std::string &getPurpose() const;

	void setPurpose(const std::string &purpose);

	const std::string &getInsulationClass() const;

	void setInsulationClass(const std::string &insulationClass);

	int getHp() const;

	void setHp(int hp);

	int getSpeed() const;

	void setSpeed(int speed);

	int getFullLoadSpeed() const;

	void setFullLoadSpeed(int fullLoadSpeed);

	int getVoltageRating() const;

	void setVoltageRating(int voltageRating);

	int getUFrame() const;

	void setUFrame(int uFrame);

	int getCFace() const;

	void setCFace(int cFace);

	int getVerticalShaft() const;

	void setVerticalShaft(int verticalShaft);

	int getDFlange() const;

	void setDFlange(int dFlange);

	int getRotorBars() const;

	void setRotorBars(int rotorBars);

	int getStatorSlots() const;

	void setStatorSlots(int statorSlots);

	double getServiceFactor() const;

	void setServiceFactor(double serviceFactor);

	double getWeight() const;

	void setWeight(double weight);

	double getListPrice() const;

	void setListPrice(double listPrice);

	double getWindingResistance() const;

	void setWindingResistance(double windingResistance);

	double getWarranty() const;

	void setWarranty(double warranty);

	double getEfficiency100() const;

	void setEfficiency100(double efficiency100);

	double getEfficiency75() const;

	void setEfficiency75(double efficiency75);

	double getEfficiency50() const;

	void setEfficiency50(double efficiency50);

	double getEfficiency25() const;

	void setEfficiency25(double efficiency25);

	double getPowerFactor100() const;

	void setPowerFactor100(double powerFactor100);

	double getPowerFactor75() const;

	void setPowerFactor75(double powerFactor75);

	double getPowerFactor50() const;

	void setPowerFactor50(double powerFactor50);

	double getPowerFactor25() const;

	void setPowerFactor25(double powerFactor25);

	double getTorqueFullLoad() const;

	void setTorqueFullLoad(double torqueFullLoad);

	double getTorqueBreakDown() const;

	void setTorqueBreakDown(double torqueBreakDown);

	double getTorqueLockedRotor() const;

	void setTorqueLockedRotor(double torqueLockedRotor);

	double getAmpsFullLoad() const;

	void setAmpsFullLoad(double ampsFullLoad);

	double getAmpsIdle() const;

	void setAmpsIdle(double ampsIdle);

	double getAmpsLockedRotor() const;

	void setAmpsLockedRotor(double ampsLockedRotor);

	double getStalledRotorTimeHot() const;

	void setStalledRotorTimeHot(double stalledRotorTimeHot);

	double getStalledRotorTimeCold() const;

	void setStalledRotorTimeCold(double stalledRotorTimeCold);

	double getPeakVoltage0ms() const;

	void setPeakVoltage0ms(double peakVoltage0ms);

	double getPeakVoltage5ms() const;

	void setPeakVoltage5ms(double peakVoltage5ms);

	int getId() const;

	void setId(int id);

private:
	std::string manufacturer, model, catalog, motorType, enclosureType, frameNumber, purpose, insulationClass;

	int hp, speed, fullLoadSpeed, voltageRating, uFrame, cFace, verticalShaft, dFlange, rotorBars, statorSlots;

	double serviceFactor, weight, listPrice, windingResistance, warranty, efficiency100, efficiency75, efficiency50, efficiency25;
	double powerFactor100, powerFactor75, powerFactor50, powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor;
	double ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot, stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms;

	int id; // used for the database

	friend class SQLite;
};

#endif //AMO_TOOLS_SUITE_MOTORDATA_H
