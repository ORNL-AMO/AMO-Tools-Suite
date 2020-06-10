#ifndef AMO_TOOLS_SUITE_MOTORDATA_H
#define AMO_TOOLS_SUITE_MOTORDATA_H

#include <string>
/*
TODO: Merge these columns with the current columns (Ask Alex/Kristine for help)
MotorData(std::string manufacturer, std::string model, std::string catalog, std::string motorType, int hp, int speed, int fullLoadSpeed, std::string enclosureType, std::string frameNumber,
	          int voltageRating, std::string purpose, int uFrame, int cFace, int verticalShaft, int dFlange, double serviceFactor, std::string insulationClass, double weight, double listPrice,
	          double windingResistance, double warranty, int rotorBars, int statorSlots, double efficiency100, double efficiency75, double efficiency50, double efficiency25, double powerFactor100,
	          double powerFactor75, double powerFactor50, double powerFactor25, double torqueFullLoad, double torqueBreakDown, double torqueLockedRotor, double ampsFullLoad, double ampsIdle,
	          double ampsLockedRotor, double stalledRotorTimeHot, double stalledRotorTimeCold, double peakVoltage0ms, double peakVoltage5ms);
*/
class MotorData {
public:
	MotorData(double hp, int synchronousSpeed, int poles, double nominalEfficiency, std::string efficiencyType, std::string nemaTable,
			  std::string motorType, int hz, int voltageLimit, std::string catalog);

	const std::string &getEfficiencyType() const;
	const std::string &getNemaTable() const;
	const std::string &getMotorType() const;
	const std::string &getCatalog() const;

	int getSynchronousSpeed() const;
	int getPoles() const;
	int getHz() const;
	int getVoltageLimit() const;

	double getHp() const;
	double getNominalEfficiency() const;
	

	void setEfficiencyType(const std::string &efficiencyType);
	void setNemaTable(const std::string &nemaTable);
	void setMotorType(const std::string &motorType);
	void setCatalog(const std::string &catalog);

	void setSynchronousSpeed(int synchronousSpeed);
	void setPoles(int poles);
	void setHz(int hz);
	void setVoltageLimit(int voltageLimit);

	void setHp(double hp);
	void setNominalEfficiency(double nominalEfficiency);


	int getId() const;

	void setId(int id);

private:
	std::string efficiencyType, nemaTable, motorType, catalog;

	int synchronousSpeed, poles, hz, voltageLimit;

	double hp, nominalEfficiency;

	int id; // used for the database

	friend class SQLite;
};

#endif //AMO_TOOLS_SUITE_MOTORDATA_H
