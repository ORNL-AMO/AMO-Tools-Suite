#ifndef AMO_TOOLS_SUITE_MOTORDATA_H
#define AMO_TOOLS_SUITE_MOTORDATA_H

#include <results/InputData.h>
#include <string>
/*
TODO: Merge these columns with the current columns (Ask Alex/Kristine for help)
NOTE: Storing all this data in MEASUR
MotorData(std::string manufacturer, std::string model, std::string catalog, std::string motorType, int hp, int speed, int fullLoadSpeed, std::string enclosureType, std::string frameNumber,
	          int voltageRating, std::string purpose, int uFrame, int cFace, int verticalShaft, int dFlange, double serviceFactor, std::string insulationClass, double weight, double listPrice,
	          double windingResistance, double warranty, int rotorBars, int statorSlots, double efficiency100, double efficiency75, double efficiency50, double efficiency25, double powerFactor100,
	          double powerFactor75, double powerFactor50, double powerFactor25, double torqueFullLoad, double torqueBreakDown, double torqueLockedRotor, double ampsFullLoad, double ampsIdle,
	          double ampsLockedRotor, double stalledRotorTimeHot, double stalledRotorTimeCold, double peakVoltage0ms, double peakVoltage5ms);
*/
class MotorData
{
public:
	MotorData(double hp, int synchronousSpeed, int poles, double nominalEfficiency, Motor::EfficiencyClass efficiencyClass, std::string nemaTable,
			  std::string enclosureType, Motor::LineFrequency lineFrequency, int voltageLimit, std::string catalog);

	const Motor::EfficiencyClass getEfficiencyClass() const;

	const std::string getNemaTable() const;
	const std::string getEnclosureType() const;
	const std::string getCatalog() const;

	int getSynchronousSpeed() const;
	int getPoles() const;
	int getVoltageLimit() const;

	Motor::LineFrequency getLineFrequency() const;

	double getHp() const;
	double getNominalEfficiency() const;

	void setEfficiencyClass(const Motor::EfficiencyClass &efficiencyClass);
	void setNemaTable(const std::string &nemaTable);
	void setEnclosureType(const std::string &enclosureType);
	void setCatalog(const std::string &catalog);

	void setSynchronousSpeed(int synchronousSpeed);
	void setPoles(int poles);
	void setLineFrequency(Motor::LineFrequency hz);
	void setVoltageLimit(int voltageLimit);

	void setHp(double hp);
	void setNominalEfficiency(double nominalEfficiency);

	int getId() const; 

	void setId(int id);

private:
	std::string nemaTable, enclosureType, catalog;

	Motor::EfficiencyClass efficiencyClass;
	Motor::LineFrequency lineFrequency;

	int synchronousSpeed, poles, voltageLimit;

	double hp, nominalEfficiency;

	int id; // used for the database

	friend class SQLite;
};

#endif //AMO_TOOLS_SUITE_MOTORDATA_H
