//
// Created by Preston Shires on 7/19/17.
//

#ifndef AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
#define AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H

#include <cmath>
#include <string>
#include <unordered_map>

class Point {
public:
    /**
     *
     * Constructor for a point
     *
     * @param x double, x-value of point
     * @param y double, y-value of point
     *
     * @return nothing
     *
     * */
    Point(
            double x,
            double y)
            : x_(x),
              y_(y)
    {}

    /**
    * Gets the x-value
    *
    * @return double, x-value
    */
    double getX() const {
        return x_;
    }

    /**
     * Sets the x-value
     *
     * @param x double, x-value
     *
     * @return nothing
     */
    void setX(double x) {
        x_ = x;
    }

    /**
    * Gets the y-value
    *
    * @return double, y-value
    */
    double getY() const {
        return y_;
    }

    /**
     * Sets the y-value
     *
     * @param y double, y-value
     *
     * @return nothing
     */
    void setY(double y) {
        y_ = y;
    }

private:
    // In values
    double x_ = 0.0;
    double y_ = 0.0;
};


class SteamSystemModelerTool {
public:
//	enum class Region {
//		LIQUIDREGION1,
//		GASREGION2,
//		LIQUIDREGION3
//	};

enum class Key{
    ENTHALPY,
    ENTROPY
};

	static int regionSelect(const double pressure, const double temperature);
	static std::unordered_map <std::string, double> region1(const double temperature, const double pressure);
	static std::unordered_map <std::string, double> region2(const double temperature, const double pressure);
	static std::unordered_map <std::string, double> region3(const double temperature, const double pressure);
	static std::unordered_map <std::string, double> region3Density(const double density, const double temperature);
	static double region4(const double temperature);

    /**
     * Calculates temperature based in pressure and enthalpy for region 1
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
     static double backwardPressureEnthalpyRegion1(const double pressure, const double enthalpy);

    /**
     * Calculates temperature based in pressure and enthalpy for region 2A
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEnthalpyRegion2A(const double pressure, const double enthalpy);

    /**
     * Calculates temperature based in pressure and enthalpy for region 2B
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEnthalpyRegion2B(const double pressure, const double enthalpy);

    /**
     * Calculates temperature based in pressure and enthalpy for region 2C
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEnthalpyRegion2C(const double pressure, const double enthalpy);

    /**
     * Calculates temperature based on pressure and entropy for region 2A
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion2A(const double pressure, const double entropy);

    /**
     * Calculates temperature based on pressure and entropy for region 2B
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion2B(const double pressure, const double entropy);

    /**
     * Calculates temperature based on pressure and entropy for region 2C
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion2C(const double pressure, const double entropy);

    /**
     * Calculates temperature based on pressure and entropy for region 1
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion1(const double pressure, const double entropy);

    /**
     * Generates a data point
     *
     * @param region int, region of substance
     * @param key string, property such as specificEnthalpy or specificEntropy
     * @param var1 double, first value
     * @param var2 double, second value
     *
     * @return Point, a point with x-value and y-value
     */
    static Point generatePoint(int region, SteamSystemModelerTool::Key key, double var1, double var2);

    /**
     * Uses linear extrapolation to determine the location of X relative to both points
     *
     * @param X double, x-value
     * @param point1 Point, the first point
     * @param point2 Point, the second point
     *
     * @return double, y-value
     */
    static double linearTestPoint(const double X, Point point1, Point point2);

    static double backwardRegion3Exact(const double pressure, const double X, SteamSystemModelerTool::Key key);

    static double backwardPressureEnthalpyRegion3(const double pressure, const double enthalpy);

    static double backwardPressureEntropyRegion3(const double pressure, const double entropy);

    //static double SteamSystemModelerTool::backwardPHregion2bExact(const double pressure, const double enthalpy);

    //static double SteamSystemModelerTool::backwardExact(int region, SteamSystemModelerTool::Key key, const double pressure, const double var2);

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
    static const inline double boundaryByTemperatureRegion3to2(const double t) {
        return 0.34805185628969E+03 - 0.11671859879975E+01 * 0.10192970039326E-02 * std::pow(t, 2);
    }
    static const inline double boundaryByPressureRegion3to2(const double p) {
        return p - 0.13918839778870E+02;//0.57254459862746E+03 + pow( (p - 0.13918839778870E+02) / 0.10192970039326E-02, 0.5 );
    }

private:


//	static int regionSelect(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region1(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region2(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region3(const double pressure, const double temperature);
//	static std::unordered_map <std::string, double> region3Density(const double density, const double temperature);
//	static double region4(const double temperature);

	friend class SteamProperties;
};


#endif //AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
