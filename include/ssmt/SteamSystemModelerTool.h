//
// Created by Preston Shires on 7/19/17.
//

#ifndef AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
#define AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H

#include <cmath>
#include <string>
#include <unordered_map>

class SteamSystemModelerTool {
public:
//	enum class Region {
//		LIQUIDREGION1,
//		GASREGION2,
//		LIQUIDREGION3
//	};

	static int regionSelect(const double pressure, const double temperature);
	static std::unordered_map <std::string, double> region1(const double pressure, const double temperature);
	static std::unordered_map <std::string, double> region2(const double pressure, const double temperature);
	static std::unordered_map <std::string, double> region3(const double pressure, const double temperature);
	static std::unordered_map <std::string, double> region3Density(const double density, const double temperature);
	static double region4(const double temperature);

private:
	// constants

	static constexpr double PRESSURE_MIN = 0.01;
	/**
	 * Maximum Temperature of Water K
	 */
	static constexpr double TEMPERATURE_MIN = 273.15;
	/**
	 * Pressure of Water where ALL regions meet MPa
	 */
	static constexpr double PRESSURE_Tp = 16.5291643;

	/**
	 * Temperature of Water where ALL regions meet K
	 */
	static constexpr double TEMPERATURE_Tp = 623.15;

	/**
	 * Critical Pressure of Water MPa
	 */
	static constexpr double PRESSURE_CRIT = 22.064;

	/**
	 * Critical Temperature of Water K
	 */
	static constexpr double TEMPERATURE_CRIT = 647.096;

	/**
	 * Maximum Pressure of Water MPa
	 */
	static constexpr double PRESSURE_MAX = 100;

	/**
	 * Maximum Temperature of Water MPa
	 */
	static constexpr double TEMPERATURE_MAX = 1073.15;

	/**
	 * Maximum Temperature of Water for Region 3 MPa
	 */
	static constexpr double TEMPERATURE_REGION3_MAX = 863.15;


	// helper functions?
	static const inline double boundaryByTemperatureRegion3to2Temperature(const double t) {
		return 0.34805185628969E+03 - 0.11671859879975E+01 * 0.10192970039326E-02 * std::pow(t, 2);
	}
	static const inline double boundaryByTemperatureRegion3to2Pressure(const double p) {
		return 0.57254459862746E+03 + std::pow( p - (0.13918839778870E+02 / 0.10192970039326E-02), 0.5 );
	}

//	static int regionSelect(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region1(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region2(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region3(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region3Density(const double density, const double temperature);
//	static double region4(const double temperature);

	friend class SteamProperties;
};

#endif //AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
