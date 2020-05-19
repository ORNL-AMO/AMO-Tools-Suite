#ifndef AMO_TOOLS_SUITE_MOTORDATADB_H
#define AMO_TOOLS_SUITE_MOTORDATADB_H

#include <fast-cpp-csv-parser/csv.h>
#include <tuple>
#include <calculator/motor/MotorEfficiency.h>
#include <fstream>

class MotorData;

std::vector<std::tuple<double, int, int, double, std::string, std::string, int, int>> getStandardEffCombinations(
												   const std::vector<double> &hpValues, const std::vector<int> &synchronousSpeedValues, 
												   const std::vector<int> &polesValues, const std::vector<std::string> &efficiencyTypeValues, 
												   const std::vector<std::string> &motorTypeValues, const std::vector<int> &hzValues, 
												   const std::vector<int> &voltageLimitValues)
{
	std::vector<std::tuple<double, int, int, double, std::string, std::string, int, int>> combinations;

	for(auto const &hp : hpValues) {
		for(auto const &synchronousSpeed : synchronousSpeedValues) {
			for(auto const &poles : polesValues) {
				for(auto const &efficiencyType : efficiencyTypeValues) {
					for(auto const &motorType : motorTypeValues) {
						for(auto const &hz : hzValues) {
							for(auto const &voltageLimit : voltageLimitValues) {
								double nominalEfficiency;
								if(hz == 50)
								{
									nominalEfficiency = MotorEfficiency(Motor::LineFrequency::FREQ50, synchronousSpeed, Motor::EfficiencyClass::STANDARD, hp).calculate(1);
								}
								else if(hz == 60)
								{
									nominalEfficiency = MotorEfficiency(Motor::LineFrequency::FREQ60, synchronousSpeed, Motor::EfficiencyClass::STANDARD, hp).calculate(1);
								}
								std::tuple<double, int, int, double, std::string, std::string, int, int> combination;
								combination = std::make_tuple(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, motorType, hz, voltageLimit);
								combinations.push_back(combination);
    						}
    					}
    				}
    			}
    		}
    	}
    }

	return combinations;
}

std::vector<MotorData> getStandardEfficiencyData() {
	std::vector<double> hpValues = {1, 1.5, 2, 3, 5, 7.5, 10, 15, 20, 25, 30, 40, 50, 60, 75, 100, 125, 150, 200, 250, 300, 350, 400, 450, 500}; // 25
	std::vector<int> synchronousSpeedValues = {900, 1000, 1200, 1500, 1800, 3000, 3600}; // 7
	std::vector<int> polesValues = {2, 4, 6, 8}; // 4
	std::vector<double> nominalEfficiencyValues; // To be calculated
	std::vector<std::string> efficiencyTypeValues = {"Standard Efficiency"}; // 1
	//std::vector<std::string> nemaTableValues; N/A
	std::vector<std::string> motorTypeValues = {"TEFC", "ODP"}; // 2
	std::vector<int> hzValues = {50, 60}; // 2
	std::vector<int> voltageLimitValues = {600, 5000}; // 2
	//std::vector<std::string> catalogValues; N/A

	// Note: There is a restriction on combinations of synchronousSpeedValues and hzValues. 
	// hz = 50 -> synchronousValues in {1000, 1500, 3000}
	// hz = 60 -> synchronousValues in {900, 1200, 1800, 3600}

	std::vector<std::tuple<double, int, int, double, std::string, std::string, int, int>> combinations = getStandardEffCombinations(
																										  hpValues, synchronousSpeedValues,
																										  polesValues, efficiencyTypeValues,
																										  motorTypeValues, hzValues,
																										  voltageLimitValues);
	//std::vector<MotorData> standardEffMotorData;
	//MotorData motorData(0, 0.0, 0, 0.0, "N/A", "N/A", "N/A", 0, 0, "N/A");
	//standardEffMotorData.push_back(motorData);

	std::vector<MotorData> standardEffMotorData;
	for(auto const &dataRow : combinations)
	{
		// 0 -> hp
		// 1 -> synchronousSpeed
		// 2 -> poles
		// 3 -> nominalEfficiency
		// 4 -> efficiencyType
		// 5 -> motorType
		// 6 -> hz
		// 7 -> voltageLimit

		// Note: There are restrictions on combinations of synchronousSpeedValues and hzValues. 
		// hz = 50 -> synchronousValues in {1000, 1500, 3000}
		bool restriction1 = std::get<6>(dataRow) == 50 && (std::get<1>(dataRow) == 1000 || std::get<1>(dataRow) == 1500 || std::get<1>(dataRow) == 3000);
		// hz = 60 -> synchronousValues in {900, 1200, 1800, 3600}
		bool restriction2 = std::get<6>(dataRow) == 60 && (std::get<1>(dataRow) == 900 || std::get<1>(dataRow) == 1200 || std::get<1>(dataRow) == 1800 || std::get<1>(dataRow) == 3600);
		if(restriction1 || restriction2)
		{
			double hp = std::get<0>(dataRow);
			double synchronousSpeed = std::get<1>(dataRow);
			int poles = std::get<2>(dataRow);
			double nominalEfficiency = std::get<3>(dataRow);
			std::string efficiencyType = std::get<4>(dataRow);
			std::string nemaTable = "N/A";
			std::string motorType = std::get<5>(dataRow);
			int hz = std::get<6>(dataRow);
			double voltageLimit = std::get<7>(dataRow);
			std::string catalog = "N/A";
			
			MotorData motorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, motorType, hz, voltageLimit, catalog);
			standardEffMotorData.push_back(motorData);
		}
	}

	std::ofstream fout;
    fout.open("debug.txt", std::ios::app);
	fout << "Number of combinations: " << standardEffMotorData.size() << std::endl;
	for(auto const &dataEntry : standardEffMotorData)
	{
		fout << dataEntry.getHp() << "  ";
		fout << dataEntry.getSynchronousSpeed() << "  ";
		fout << dataEntry.getPoles() << "  ";
		fout << dataEntry.getNominalEfficiency() << "  ";
		fout << dataEntry.getEfficiencyType() << "  ";
		fout << dataEntry.getNemaTable() << "  ";
		fout << dataEntry.getMotorType() << "  ";
		fout << dataEntry.getHz() << "  ";
		fout << dataEntry.getVoltageLimit() << "  ";
		fout << dataEntry.getCatalog() << "  ";
		fout << std::endl;
	}
	fout << "-------------------------------------------------";
	fout << std::endl << std::endl;
	fout.close();

	return standardEffMotorData;
}

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

	getStandardEfficiencyData();

	return defaultMotorData;
}

#endif //AMO_TOOLS_SUITE_MOTORDATADB_H