#ifndef AMO_TOOLS_SUITE_MOTORDATADB_H
#define AMO_TOOLS_SUITE_MOTORDATADB_H

#include <fast-cpp-csv-parser/csv.h>

class MotorData;

std::vector<MotorData> SQLite::get_default_motor_data() {
	io::CSVReader<10> in("include/sqlite/MotorData.csv");
	in.read_header(io::ignore_extra_column, "hp", "Synchronous Speed (RPM)", "Poles", "Nominal Efficiency", "Eff Type", "NEMA Table", "Motor Type", "Hz", "Voltage Limit", "Catalog");
	
	double hp;
	int synchronousSpeed;
	int poles;
	double nominalEfficiency;
	std::string efficiencyType;
	std::string nemaTable;
	std::string motorType;
	int hz;
	int voltageLimit;
	std::string catalog;
	
	std::vector<MotorData> defaultMotorData;
	while(in.read_row(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, motorType, hz, voltageLimit, catalog))
	{
		MotorData motorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, motorType, hz, voltageLimit, catalog);
		defaultMotorData.push_back(motorData);
	}

	return defaultMotorData;
}


#endif //AMO_TOOLS_SUITE_MOTORDATADB_H