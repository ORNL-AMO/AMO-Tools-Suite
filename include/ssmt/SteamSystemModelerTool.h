//
// Created by Preston Shires on 7/19/17.
//

#ifndef AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
#define AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H

#include <cmath>

class SteamSystemModelerTool {
public:
//	enum class Region {
//		LIQUIDREGION1,
//		GASREGION2,
//		LIQUIDREGION3
//	};

private:
	// constants

	static const double PRESSURE_MIN = 0.01;
	/**
	 * Maximum Temperature of Water K
	 */
	static const double TEMPERATURE_MIN = 273.15;
	/**
	 * Pressure of Water where ALL regions meet MPa
	 */
	static const double PRESSURE_Tp = 16.5291643;

	/**
	 * Temperature of Water where ALL regions meet K
	 */
	static const double TEMPERATURE_Tp = 623.15;

	/**
	 * Critical Pressure of Water MPa
	 */
	static const double PRESSURE_CRIT = 22.064;

	/**
	 * Critical Temperature of Water K
	 */
	static const double TEMPERATURE_CRIT = 647.096;

	/**
	 * Maximum Pressure of Water MPa
	 */
	static const double PRESSURE_MAX = 100;

	/**
	 * Maximum Temperature of Water MPa
	 */
	static const double TEMPERATURE_MAX = 1073.15;

	/**
	 * Maximum Temperature of Water for Region 3 MPa
	 */
	static const double TEMPERATURE_REGION3_MAX = 863.15;


	// helper functions?
	static inline double boundaryByTemperatureRegion3to2Temperature(const double t) {
		return 0.34805185628969E+03 - 0.11671859879975E+01 * 0.10192970039326E-02 * (t * t);
	}
	static inline double boundaryByTemperatureRegion3to2Pressure(const double p) {
		return 0.57254459862746E+03 + pow( p - (0.13918839778870E+02 / 0.10192970039326E-02), 0.5 );
	}

	static int regionSelect(const double pressure, const double temperature);
	static double region4(const double temperature);

	friend class SteamProperties;
};

#endif //AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
