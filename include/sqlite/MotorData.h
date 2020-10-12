#ifndef AMO_TOOLS_SUITE_MOTORDATADB_H
#define AMO_TOOLS_SUITE_MOTORDATADB_H

#include <fast-cpp-csv-parser/csv.h>
#include <tuple>
#include <calculator/motor/MotorEfficiency.h>
#include <fstream>

class MotorData;

std::vector<std::tuple<double, int, double, Motor::EfficiencyClass, std::string, Motor::LineFrequency, int>> getStandardEffCombinations(
	const std::vector<double> &hpValues, const std::vector<int> &synchronousSpeedValues,
	const std::vector<Motor::EfficiencyClass> &efficiencyClassValues,
	const std::vector<std::string> &enclosureTypeValues, const std::vector<Motor::LineFrequency> &lineFrequencyValues,
	const std::vector<int> &voltageLimitValues)
{
	std::vector<std::tuple<double, int, double, Motor::EfficiencyClass, std::string, Motor::LineFrequency, int>> combinations;
	// Compute Cartesian product
	for (auto const &hp : hpValues)
	{
		for (auto const &synchronousSpeed : synchronousSpeedValues)
		{
			for (auto const &efficiencyClass : efficiencyClassValues)
			{
				for (auto const &enclosureType : enclosureTypeValues)
				{
					for (auto const &lineFrequency : lineFrequencyValues)
					{
						for (auto const &voltageLimit : voltageLimitValues)
						{
							// Calculate
							double nominalEfficiency = MotorEfficiency(lineFrequency, synchronousSpeed, Motor::EfficiencyClass::STANDARD, hp).calculate(1) * 100;
							std::tuple<double, int, double, Motor::EfficiencyClass, std::string, Motor::LineFrequency, int> combination = std::make_tuple(hp, synchronousSpeed, nominalEfficiency, efficiencyClass, enclosureType, lineFrequency, voltageLimit);
							combinations.push_back(combination);
						}
					}
				}
			}
		}
	}

	return combinations;
}

std::vector<MotorData> getStandardEfficiencyData()
{
	std::vector<double> hpValues = {1, 1.5, 2, 3, 5, 7.5, 10, 15, 20, 25, 30, 40, 50, 60, 75, 100, 125, 150, 200, 250, 300, 350, 400, 450, 500}; // 25 possibilities
	std::vector<int> synchronousSpeedValues = {900, 1000, 1200, 1500, 1800, 3000, 3600};														 // 7 possibilities
	//std::vector<int> polesValues = {2, 4, 6, 8}; // 4 possibilities
	std::vector<double> nominalEfficiencyValues;												   // To be calculated
	std::vector<Motor::EfficiencyClass> efficiencyTypeValues = {Motor::EfficiencyClass::STANDARD}; // 1 possibility
	//std::vector<std::string> nemaTableValues; N/A
	std::vector<std::string> enclosureTypeValues = {"TEFC", "ODP"};											   // 2 possibilities
	std::vector<Motor::LineFrequency> hzValues = {Motor::LineFrequency::FREQ50, Motor::LineFrequency::FREQ60}; // 2 possibilities
	std::vector<int> voltageLimitValues = {600, 5000};														   // 2 possibilities
	//std::vector<std::string> catalogValues; N/A

	std::vector<std::tuple<double, int, double, Motor::EfficiencyClass, std::string, Motor::LineFrequency, int>> combinations = getStandardEffCombinations(
		hpValues, synchronousSpeedValues,
		efficiencyTypeValues,
		enclosureTypeValues, hzValues,
		voltageLimitValues);

	std::vector<MotorData> standardEffMotorData;
	for (auto const &dataRow : combinations)
	{
		// 0 -> hp
		// 1 -> synchronousSpeed
		// 2 -> nominalEfficiency
		// 3 -> efficiencyClass
		// 4 -> enclosureType
		// 5 -> lineFrequency
		// 6 -> voltageLimit

		// Note: There are restrictions on combinations of synchronousSpeedValues and lineFrequencyValues.
		// hz = 50 -> synchronousSpeedValues in {1000, 1500, 3000}
		bool restriction1 = std::get<5>(dataRow) == Motor::LineFrequency::FREQ50 && (std::get<1>(dataRow) == 1000 || std::get<1>(dataRow) == 1500 || std::get<1>(dataRow) == 3000);
		// hz = 60 -> synchronousSpeedValues in {900, 1200, 1800, 3600}
		bool restriction2 = std::get<5>(dataRow) == Motor::LineFrequency::FREQ60 && (std::get<1>(dataRow) == 900 || std::get<1>(dataRow) == 1200 || std::get<1>(dataRow) == 1800 || std::get<1>(dataRow) == 3600);

		// Note: There are restrictions on combinations of hpValues and voltageLimitValues
		// voltageLimit = 600  -> hp < 500
		// voltageLimit = 5000 -> hp > 250
		bool restriction3 = (std::get<6>(dataRow) == 600 && std::get<0>(dataRow) < 500) || (std::get<6>(dataRow) == 5000 && std::get<0>(dataRow) > 250);

		if ((restriction1 || restriction2) && restriction3)
		{
			double hp = std::get<0>(dataRow);
			double synchronousSpeed = std::get<1>(dataRow);
			//int poles = std::get<2>(dataRow);
			int poles;
			double nominalEfficiency = std::get<2>(dataRow);
			Motor::EfficiencyClass efficiencyClass = std::get<3>(dataRow);
			std::string nemaTable = "N/A";
			std::string enclosureType = std::get<4>(dataRow);
			Motor::LineFrequency lineFrequency = std::get<5>(dataRow);
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
			if (lineFrequency == Motor::LineFrequency::FREQ60 && synchronousSpeed == 3600)
			{
				poles = 2;
			}
			else if (lineFrequency == Motor::LineFrequency::FREQ60 && synchronousSpeed == 1800)
			{
				poles = 4;
			}
			else if (lineFrequency == Motor::LineFrequency::FREQ60 && synchronousSpeed == 1200)
			{
				poles = 6;
			}
			else if (lineFrequency == Motor::LineFrequency::FREQ60 && synchronousSpeed == 900)
			{
				poles = 8;
			}
			else if (lineFrequency == Motor::LineFrequency::FREQ50 && synchronousSpeed == 3000)
			{
				poles = 2;
			}
			else if (lineFrequency == Motor::LineFrequency::FREQ50 && synchronousSpeed == 1500)
			{
				poles = 4;
			}
			else if (lineFrequency == Motor::LineFrequency::FREQ50 && synchronousSpeed == 1000)
			{
				poles = 6;
			}

			MotorData motorData(hp, synchronousSpeed, poles, nominalEfficiency, efficiencyClass, nemaTable, enclosureType, lineFrequency, voltageLimit, catalog);
			standardEffMotorData.push_back(motorData);
		}
	}

	return standardEffMotorData;
}

std::vector<MotorData> getDefaultCSVData()
{
	return {
		{1, 900, 8, 74, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 900, 8, 74, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 3600, 2, 75.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 900, 8, 75.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 900, 8, 75.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 3600, 2, 77, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 3600, 2, 77, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 1000, 6, 78.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1, 1000, 6, 78.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1, 1200, 6, 80, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 1200, 6, 80, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 3000, 2, 80.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1, 3000, 2, 80.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1, 1800, 4, 82.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 1800, 4, 82.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 1200, 6, 82.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 1200, 6, 82.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 1500, 4, 82.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1, 1500, 4, 82.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1, 1800, 4, 85.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1, 1800, 4, 85.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 900, 8, 75.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 900, 8, 77, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 900, 8, 77, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 900, 8, 78.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 1000, 6, 81.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1.5, 1000, 6, 81.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1.5, 3600, 2, 82.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 3600, 2, 82.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 3000, 2, 82.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1.5, 3000, 2, 82.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1.5, 1800, 4, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 1200, 6, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 1800, 4, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 3600, 2, 84, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 3600, 2, 84, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 1500, 4, 84.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1.5, 1500, 4, 84.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{1.5, 1200, 6, 85.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 1800, 4, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 1200, 6, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{1.5, 1200, 6, 87.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 900, 8, 82.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1000, 6, 82.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{2, 1000, 6, 82.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{2, 3600, 2, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1800, 4, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 3600, 2, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1800, 4, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 900, 8, 84, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 3000, 2, 84.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{2, 3000, 2, 84.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{2, 1500, 4, 85.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{2, 1500, 4, 85.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{2, 1200, 6, 85.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 900, 8, 85.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 3600, 2, 85.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 3600, 2, 85.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1200, 6, 86.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1800, 4, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 900, 8, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1800, 4, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1200, 6, 87.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{2, 1200, 6, 88.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 3600, 2, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 900, 8, 84, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1000, 6, 84.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{3, 1000, 6, 84.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{3, 3600, 2, 85.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 3600, 2, 85.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 900, 8, 85.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 3000, 2, 85.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{3, 3000, 2, 85.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{3, 1800, 4, 86.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1200, 6, 86.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 900, 8, 86.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 3600, 2, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1800, 4, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1500, 4, 86.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{3, 1500, 4, 86.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{3, 1800, 4, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1200, 6, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 900, 8, 87.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1200, 6, 88.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1800, 4, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{3, 1200, 6, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 3600, 2, 85.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 900, 8, 85.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 3600, 2, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 900, 8, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1000, 6, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{5, 1000, 6, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{5, 1800, 4, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1200, 6, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 900, 8, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 3600, 2, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1800, 4, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1200, 6, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 3000, 2, 87.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{5, 3000, 2, 87.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{5, 1500, 4, 88.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{5, 1500, 4, 88.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{5, 900, 8, 88.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 3600, 2, 88.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1800, 4, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1200, 6, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1800, 4, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{5, 1200, 6, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 900, 8, 85.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 900, 8, 86.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 3600, 2, 87.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 1000, 6, 88, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{7.5, 1000, 6, 88, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{7.5, 1800, 4, 88.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 1200, 6, 88.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 900, 8, 88.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 3600, 2, 88.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 3600, 2, 88.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 3000, 2, 89.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{7.5, 3000, 2, 89.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{7.5, 1800, 4, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 1200, 6, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 900, 8, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 3600, 2, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 1500, 4, 89.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{7.5, 1500, 4, 89.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{7.5, 1200, 6, 90.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 1800, 4, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 1200, 6, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{7.5, 1800, 4, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 3600, 2, 88.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 900, 8, 88.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 1000, 6, 89, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{10, 1000, 6, 89, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{10, 1800, 4, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 900, 8, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 3600, 2, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 1800, 4, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 1200, 6, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 3600, 2, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 900, 8, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 3000, 2, 90.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{10, 3000, 2, 90.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{10, 1200, 6, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 900, 8, 90.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 3600, 2, 90.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 1500, 4, 90.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{10, 1500, 4, 90.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{10, 1200, 6, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 1800, 4, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 1200, 6, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{10, 1800, 4, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 900, 8, 88.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 3600, 2, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 900, 8, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 900, 8, 89.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 1200, 6, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 3600, 2, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 1200, 6, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 3600, 2, 90.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 900, 8, 90.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 1000, 6, 90.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{15, 1000, 6, 90.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{15, 1800, 4, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 1800, 4, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 3600, 2, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 3000, 2, 91.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{15, 3000, 2, 91.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{15, 1500, 4, 91.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{15, 1500, 4, 91.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{15, 1200, 6, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 1200, 6, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 1800, 4, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{15, 1800, 4, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 900, 8, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 3600, 2, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 900, 8, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 3600, 2, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 1200, 6, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 900, 8, 90.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 1800, 4, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 1200, 6, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 1800, 4, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 3600, 2, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 900, 8, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 3600, 2, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 1000, 6, 91.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{20, 1000, 6, 91.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{20, 1200, 6, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 3000, 2, 91.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{20, 3000, 2, 91.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{20, 1500, 4, 92.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{20, 1500, 4, 92.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{20, 1200, 6, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 1800, 4, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{20, 1800, 4, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 900, 8, 89.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 900, 8, 90.2, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 900, 8, 90.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 3600, 2, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 3600, 2, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 900, 8, 91, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 1800, 4, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 1200, 6, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 1200, 6, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 3600, 2, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 3600, 2, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 1000, 6, 91.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{25, 1000, 6, 91.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{25, 1800, 4, 92.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 3000, 2, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{25, 3000, 2, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{25, 1500, 4, 92.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{25, 1500, 4, 92.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{25, 1200, 6, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 1200, 6, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 1800, 4, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{25, 1800, 4, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 3600, 2, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 900, 8, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 3600, 2, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 900, 8, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 1200, 6, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 3600, 2, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 900, 8, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 3600, 2, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 900, 8, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 1000, 6, 92.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{30, 1000, 6, 92.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{30, 1800, 4, 92.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 1200, 6, 92.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 1800, 4, 92.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 3000, 2, 92.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{30, 3000, 2, 92.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{30, 1200, 6, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 1500, 4, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{30, 1500, 4, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{30, 1200, 6, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 1800, 4, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{30, 1800, 4, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 900, 8, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 900, 8, 91, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 3600, 2, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 3600, 2, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 900, 8, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 900, 8, 91.7, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 3600, 2, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 3600, 2, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 1000, 6, 92.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{40, 1000, 6, 92.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{40, 1800, 4, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 1200, 6, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 1800, 4, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 1200, 6, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 3000, 2, 93.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{40, 3000, 2, 93.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{40, 1500, 4, 93.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{40, 1500, 4, 93.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{40, 1800, 4, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 1200, 6, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 1800, 4, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{40, 1200, 6, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 900, 8, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 900, 8, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 3600, 2, 92.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 3600, 2, 92.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 900, 8, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 900, 8, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1800, 4, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1200, 6, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1800, 4, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1200, 6, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 3600, 2, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 3600, 2, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1000, 6, 93.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{50, 1000, 6, 93.4, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{50, 3000, 2, 93.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{50, 3000, 2, 93.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{50, 1500, 4, 93.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{50, 1500, 4, 93.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{50, 1200, 6, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1200, 6, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1800, 4, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{50, 1800, 4, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 900, 8, 91.7, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 900, 8, 92.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 900, 8, 92.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 3600, 2, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 3600, 2, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 900, 8, 93, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1800, 4, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1200, 6, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1800, 4, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1200, 6, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 3600, 2, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 3600, 2, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1000, 6, 93.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{60, 1000, 6, 93.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{60, 3000, 2, 94, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{60, 3000, 2, 94, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{60, 1500, 4, 94.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{60, 1500, 4, 94.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{60, 1200, 6, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1200, 6, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{60, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 3600, 2, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 3600, 2, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 900, 8, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1200, 6, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 900, 8, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1200, 6, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 3600, 2, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 3600, 2, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 900, 8, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1800, 4, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1800, 4, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1000, 6, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{75, 1000, 6, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{75, 3000, 2, 94.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{75, 3000, 2, 94.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{75, 1200, 6, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1200, 6, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1500, 4, 94.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{75, 1500, 4, 94.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{75, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{75, 1800, 4, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 3600, 2, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 900, 8, 93, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 900, 8, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 3600, 2, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 3600, 2, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 900, 8, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1800, 4, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1200, 6, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1200, 6, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 3600, 2, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1800, 4, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1000, 6, 94.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{100, 1000, 6, 94.6, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{100, 3000, 2, 94.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{100, 3000, 2, 94.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{100, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1500, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{100, 1500, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{100, 1800, 4, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{100, 1800, 4, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 3600, 2, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 900, 8, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 900, 8, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 1200, 6, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 1200, 6, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 3600, 2, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 1800, 4, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 3600, 2, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 1800, 4, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 1000, 6, 94.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{125, 1000, 6, 94.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{125, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 3000, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{125, 3000, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{125, 1500, 4, 95.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{125, 1500, 4, 95.3, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{125, 1800, 4, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{125, 1800, 4, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 3600, 2, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 900, 8, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 900, 8, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 3600, 2, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 1200, 6, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 3600, 2, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 1800, 4, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 1800, 4, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 1200, 6, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 3000, 2, 95.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{150, 1000, 6, 95.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{150, 3000, 2, 95.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{150, 1000, 6, 95.2, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{150, 1200, 6, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 1500, 4, 95.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{150, 1500, 4, 95.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{150, 1800, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 1800, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{150, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 900, 8, 93.6, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 900, 8, 94.1, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 3600, 2, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 1200, 6, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 900, 8, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 1800, 4, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 3600, 2, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 1800, 4, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 1200, 6, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 1200, 6, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 3600, 2, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 3000, 2, 95.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{200, 1000, 6, 95.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{200, 3000, 2, 95.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{200, 1000, 6, 95.5, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{200, 1800, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{200, 1500, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{200, 1500, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{200, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 900, 8, 93.6, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 900, 8, 94.1, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 3600, 2, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 900, 8, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 900, 8, 94.5, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 3600, 2, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 1800, 4, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 1200, 6, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 900, 8, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 900, 8, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{250, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 1200, 6, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 3600, 2, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 3000, 2, 95.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{250, 1000, 6, 95.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{250, 3000, 2, 95.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{250, 1000, 6, 95.7, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{250, 1800, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 3600, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{250, 1500, 4, 95.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{250, 1500, 4, 95.9, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{250, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 3600, 2, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{300, 3600, 2, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 1200, 6, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{300, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{300, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{300, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{300, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{300, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 1200, 6, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 3600, 2, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 3600, 2, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 1800, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 3600, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{300, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{300, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{300, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{300, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{300, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{300, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{300, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 3600, 2, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{350, 3600, 2, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 1200, 6, 95, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{350, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{350, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{350, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{350, 1200, 6, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{350, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 1200, 6, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 3600, 2, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 3600, 2, 95.4, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 1800, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 3600, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 1200, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{350, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{350, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{350, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{350, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{350, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{350, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{350, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 3600, 2, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{400, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{400, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{400, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{400, 3600, 2, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 3600, 2, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 3600, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 1800, 4, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 3600, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{400, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{400, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{400, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{400, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{400, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{400, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{400, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 3600, 2, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{450, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{450, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{450, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{450, 3600, 2, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 1800, 4, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 3600, 2, 95.8, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 1800, 4, 95.8, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 3600, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{450, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{450, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{450, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{450, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{450, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{450, 3600, 2, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{450, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 3600, 2, 94.5, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{500, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "ODP", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{500, 3600, 2, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{500, 1800, 4, 95, Motor::EfficiencyClass::PREMIUM, "Table 12-13", "TEFC", Motor::LineFrequency::FREQ60, 5000, "NEMA MG - 1-2018"},
		{500, 3600, 2, 95.4, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 3600, 2, 95.8, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 1800, 4, 95.8, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 1800, 4, 95.8, Motor::EfficiencyClass::ENERGY_EFFICIENT, "Table 12-11", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 3600, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{500, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{500, 3000, 2, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{500, 1000, 6, 95.8, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{500, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "TEFC", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{500, 1500, 4, 96, Motor::EfficiencyClass::PREMIUM, "Table 12-14", "ODP", Motor::LineFrequency::FREQ50, 600, "NEMA MG - 1-2018"},
		{500, 3600, 2, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "ODP", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"},
		{500, 1800, 4, 96.2, Motor::EfficiencyClass::PREMIUM, "Table 12-12", "TEFC", Motor::LineFrequency::FREQ60, 600, "NEMA MG - 1-2018"}};
}

std::vector<MotorData> SQLite::get_default_motor_data()
{
	std::vector<MotorData> csvMotorData;
	std::vector<MotorData> defaultCSVMotorData = getDefaultCSVData();
	for (auto const &defaultMotorDataItem : defaultCSVMotorData)
	{
		csvMotorData.push_back(defaultMotorDataItem);
	}

	std::vector<MotorData> standardEffMotorData = getStandardEfficiencyData();
	std::vector<MotorData> defaultMotorData;
	defaultMotorData.reserve(csvMotorData.size() + standardEffMotorData.size());
	defaultMotorData.insert(defaultMotorData.end(), csvMotorData.begin(), csvMotorData.end());
	defaultMotorData.insert(defaultMotorData.end(), standardEffMotorData.begin(), standardEffMotorData.end());
	return defaultMotorData;
}
#endif //AMO_TOOLS_SUITE_MOTORDATADB_H