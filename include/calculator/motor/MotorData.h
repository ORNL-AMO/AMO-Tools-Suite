#ifndef AMO_TOOLS_SUITE_MOTORDATA_H
#define AMO_TOOLS_SUITE_MOTORDATA_H

#include <string>

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
