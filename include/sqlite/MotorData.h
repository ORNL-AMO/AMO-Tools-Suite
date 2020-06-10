#ifndef AMO_TOOLS_SUITE_MOTORDATADB_H
#define AMO_TOOLS_SUITE_MOTORDATADB_H

#include <fast-cpp-csv-parser/csv.h>
#include <tuple>
#include <calculator/motor/MotorEfficiency.h>
#include <fstream>

class MotorData;

std::vector<std::tuple<double, int, double, std::string, std::string, int, int>> getStandardEffCombinations(
												   const std::vector<double> &hpValues, const std::vector<int> &synchronousSpeedValues, 
												   const std::vector<std::string> &efficiencyTypeValues, 
												   const std::vector<std::string> &motorTypeValues, const std::vector<int> &hzValues, 
												   const std::vector<int> &voltageLimitValues)
{
	std::vector<std::tuple<double, int, double, std::string, std::string, int, int>> combinations;
	// Compute Cartesian product
	for(auto const &hp : hpValues) {
		for(auto const &synchronousSpeed : synchronousSpeedValues) {
			for(auto const &efficiencyType : efficiencyTypeValues) {
				for(auto const &motorType : motorTypeValues) {
					for(auto const &hz : hzValues) {
						for(auto const &voltageLimit : voltageLimitValues) {
							double nominalEfficiency; // Calculate
							if(hz == 50)
							{
								nominalEfficiency = MotorEfficiency(Motor::LineFrequency::FREQ50, synchronousSpeed, Motor::EfficiencyClass::STANDARD, hp).calculate(1) * 100;
							}
							else if(hz == 60)
							{
								nominalEfficiency = MotorEfficiency(Motor::LineFrequency::FREQ60, synchronousSpeed, Motor::EfficiencyClass::STANDARD, hp).calculate(1) * 100;
							}
							std::tuple<double, int, double, std::string, std::string, int, int> combination;
							combination = std::make_tuple(hp, synchronousSpeed, nominalEfficiency, efficiencyType, motorType, hz, voltageLimit);
							combinations.push_back(combination);
    					}
    				}
    			}
    		}
    	}
    }

	return combinations;
}

std::vector<MotorData> getStandardEfficiencyData() {
	std::vector<double> hpValues = {1, 1.5, 2, 3, 5, 7.5, 10, 15, 20, 25, 30, 40, 50, 60, 75, 100, 125, 150, 200, 250, 300, 350, 400, 450, 500}; // 25 possibilities
	std::vector<int> synchronousSpeedValues = {900, 1000, 1200, 1500, 1800, 3000, 3600}; // 7 possibilities
	//std::vector<int> polesValues = {2, 4, 6, 8}; // 4 possibilities
	std::vector<double> nominalEfficiencyValues; // To be calculated
	std::vector<std::string> efficiencyTypeValues = {"Standard Efficiency"}; // 1 possibility
	//std::vector<std::string> nemaTableValues; N/A
	std::vector<std::string> motorTypeValues = {"TEFC", "ODP"}; // 2 possibilities
	std::vector<int> hzValues = {50, 60}; // 2 possibilities
	std::vector<int> voltageLimitValues = {600, 5000}; // 2 possibilities
	//std::vector<std::string> catalogValues; N/A

	std::vector<std::tuple<double, int, double, std::string, std::string, int, int>> combinations = getStandardEffCombinations(
																										  hpValues, synchronousSpeedValues,
																										  efficiencyTypeValues,
																										  motorTypeValues, hzValues,
																										  voltageLimitValues);

	std::vector<MotorData> standardEffMotorData;
	for(auto const &dataRow : combinations)
	{
		// 0 -> hp
		// 1 -> synchronousSpeed
		// 2 -> nominalEfficiency
		// 3 -> efficiencyType
		// 4 -> motorType
		// 5 -> hz
		// 6 -> voltageLimit

		// Note: There are restrictions on combinations of synchronousSpeedValues and hzValues. 
		// hz = 50 -> synchronousSpeedValues in {1000, 1500, 3000}
		bool restriction1 = std::get<5>(dataRow) == 50 && (std::get<1>(dataRow) == 1000 || std::get<1>(dataRow) == 1500 || std::get<1>(dataRow) == 3000);
		// hz = 60 -> synchronousSpeedValues in {900, 1200, 1800, 3600}
		bool restriction2 = std::get<5>(dataRow) == 60 && (std::get<1>(dataRow) == 900 || std::get<1>(dataRow) == 1200 || std::get<1>(dataRow) == 1800 || std::get<1>(dataRow) == 3600);

		// Note: There are restrictions on combinations of hpValues and voltageLimitValues
		// voltageLimit = 600  -> hp < 500
		// voltageLimit = 5000 -> hp > 250
		bool restriction3 = (std::get<6>(dataRow) == 600 && std::get<0>(dataRow) < 500) || (std::get<6>(dataRow) == 5000 && std::get<0>(dataRow) > 250);

		if((restriction1 || restriction2) && restriction3)
		{
			double hp = std::get<0>(dataRow);
			double synchronousSpeed = std::get<1>(dataRow);
			//int poles = std::get<2>(dataRow);
			int poles;
			double nominalEfficiency = std::get<2>(dataRow);
			std::string efficiencyType = std::get<3>(dataRow);
			std::string nemaTable = "N/A";
			std::string motorType = std::get<4>(dataRow);
			int hz = std::get<5>(dataRow);
			double voltageLimit = std::get<6>(dataRow);
			std::string catalog = "N/A";

			/*
			Poles HZ RPM
			2	  60 3600
			4	  60 1800
			6	  60 1200
			8	  60 900
			2	  50 3000
			4	  50 1500
			6	  50 1000
			*/
			if(hz == 60 && synchronousSpeed == 3600)
			{
				poles = 2;
			}
			else if(hz == 60 && synchronousSpeed == 1800)
			{
				poles = 4;
			}
			else if(hz == 60 && synchronousSpeed == 1200)
			{
				poles = 6;
			}
			else if(hz == 60 && synchronousSpeed == 900)
			{
				poles = 8;
			}
			else if(hz == 50 && synchronousSpeed == 3000)
			{
				poles = 2;
			}
			else if(hz == 50 && synchronousSpeed == 1500)
			{
				poles = 4;
			}
			else if(hz == 50 && synchronousSpeed == 1000)
			{
				poles = 6;
			}
			
			MotorData motorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, motorType, hz, voltageLimit, catalog);
			standardEffMotorData.push_back(motorData);
		}
	}
	
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
	
	std::vector<MotorData> csvMotorData;
	while(in.read_row(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, motorType, hz, voltageLimit, catalog))
	{
		MotorData motorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyType, nemaTable, motorType, hz, voltageLimit, catalog);
		csvMotorData.push_back(motorData);
	}

	std::vector<MotorData> standardEffMotorData = getStandardEfficiencyData();

	std::vector<MotorData> defaultMotorData;
	defaultMotorData.reserve(csvMotorData.size() + standardEffMotorData.size());
	defaultMotorData.insert(defaultMotorData.end(), csvMotorData.begin(), csvMotorData.end());
	defaultMotorData.insert(defaultMotorData.end(), standardEffMotorData.begin(), standardEffMotorData.end());

	///*
	std::ofstream fout;
    fout.open("debug.txt", std::ios::app);
	fout << "Number of rows: " << defaultMotorData.size() << std::endl;
	fout << "hp,Synchronous Speed (RPM),Poles,Nominal Efficiency ,Eff Type,NEMA Table,Motor Type,Hz,Voltage Limit,Catalog" << std::endl;
	for(auto const &row : defaultMotorData)
	{
		fout << row.getHp() << ",";
		fout << row.getSynchronousSpeed() << ",";
		fout << row.getPoles() << ",";
		fout << row.getNominalEfficiency() << ",";
		fout << row.getEfficiencyType() << ",";
		fout << row.getNemaTable() << ",";
		fout << row.getMotorType() << ",";
		fout << row.getHz() << ",";
		fout << row.getVoltageLimit() << ",";
		fout << row.getCatalog();
		fout << std::endl;
	}
	fout << "-------------------------------------------------";
	fout << std::endl << std::endl;
	fout.close();
	//*/

	return defaultMotorData;
}

#endif //AMO_TOOLS_SUITE_MOTORDATADB_H