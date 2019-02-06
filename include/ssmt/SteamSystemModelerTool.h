#ifndef AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
#define AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H

#include <cmath>
#include <string>

class Point {
public:
    Point(double x, double y)
            : x_(x), y_(y) {}

    double getX() const { return x_; }

    double getY() const { return y_; }

private:
    double x_, y_;
};


class SteamSystemModelerTool {
public:
    /**
    * SteamPropertiesOutput contains the properties of steam
    * @param temperature, double in Kelvin
    * @param pressure, double in MPa
    * @param quality, double - unitless
    * @param specificVolume, double in m³/kg
    * @param density, double in kg/m³
    * @param specificEnthalpy, double in kJ/kg
    * @param specificEntropy, double in kJ/kg/K
    * @param internalEnergy, double - optional parameter - in MJ
    */
    struct SteamPropertiesOutput {
        SteamPropertiesOutput(const double temperature, const double pressure, const double quality,
                              const double specificVolume, const double density, const double specificEnthalpy,
                              const double specificEntropy, const double internalEnergy = 0):
                temperature(temperature), pressure(pressure), quality(quality), specificVolume(specificVolume),
                density(density), specificEnthalpy(specificEnthalpy), specificEntropy(specificEntropy),
                internalEnergy(internalEnergy)
        {}

        SteamPropertiesOutput() = default;

        double temperature = 0, pressure = 0, quality = 0, specificVolume = 0, density = 0;
        double specificEnthalpy = 0, specificEntropy = 0, internalEnergy = 0;
    };

    /**
    * SaturatedPropertiesOutput contains properties of saturated steam
     * @param pressure, double in MPa
     * @param temperature, double in Kelvin
     * @param gasSpecificEnthalpy, double in kJ/kg
     * @param gasSpecificEntropy,  double in kJ/kg/K
     * @param gasSpecificVolume, double in m³/kg
     * @param liquidSpecificEnthalpy, double in kJ/kg
     * @param liquidSpecificEntropy, double in kJ/kg/K
     * @param liquidSpecificVolume, double in m³/kg
     * @param evaporationSpecificEnthalpy, double in kJ/kg
     * @param evaporationSpecificEntropy, double in kJ/kg/K
     * @param evaporationSpecificVolume, double in m³/kg
    */
    struct SaturatedPropertiesOutput {
        SaturatedPropertiesOutput(const double temperature, const double pressure,
                                  const double gasSpecificVolume, const double gasSpecificEnthalpy, const double gasSpecificEntropy,
                                  const double liquidSpecificVolume, const double liquidSpecificEnthalpy, const double liquidSpecificEntropy,
                                  const double evaporationSpecificVolume, const double evaporationSpecificEnthalpy, const double evaporationSpecificEntropy):
                temperature(temperature), pressure(pressure),
                gasSpecificVolume(gasSpecificVolume), gasSpecificEnthalpy(gasSpecificEnthalpy), gasSpecificEntropy(gasSpecificEntropy),
                liquidSpecificVolume(liquidSpecificVolume), liquidSpecificEnthalpy(liquidSpecificEnthalpy), liquidSpecificEntropy(liquidSpecificEntropy),
                evaporationSpecificVolume(evaporationSpecificVolume), evaporationSpecificEnthalpy(evaporationSpecificEnthalpy), evaporationSpecificEntropy(evaporationSpecificEntropy)
        {}

        SaturatedPropertiesOutput() = default;

        double temperature = 0, pressure = 0;
        double gasSpecificVolume = 0, gasSpecificEnthalpy = 0, gasSpecificEntropy = 0;
        double liquidSpecificVolume = 0, liquidSpecificEnthalpy = 0, liquidSpecificEntropy = 0;
        double evaporationSpecificVolume = 0, evaporationSpecificEnthalpy = 0, evaporationSpecificEntropy = 0;
    };

    /**
    * FluidProperties contains the properties of steam and fluid, inherits from SteamPropertiesOutput
    * @param massFlow, double kg/hr
    * @param energyFlow, double
    * @param temperature, double Kelvin
    * @param pressure, double MPa
    * @param quality, double - unitless
    * @param specificVolume, double m³/kg
    * @param density, double kg/m³
    * @param specificEnthalpy, double kJ/kg
    * @param specificEntropy, double kJ/kg/K
    * @param internalEnergy, double - optional parameter - in MJ
    */
    struct FluidProperties: public SteamPropertiesOutput {
        FluidProperties(const double massFlow, const double energyFlow, const double temperature, const double pressure,
                        const double quality, const double specificVolume, const double density, const double specificEnthalpy,
                        const double specificEntropy, const double internalEnergy = 0):
                SteamPropertiesOutput(temperature, pressure, quality, specificVolume, density, specificEnthalpy,
                                      specificEntropy, internalEnergy),
                massFlow(massFlow), energyFlow(energyFlow)
        {}

        FluidProperties(const double massFlow, const double energyFlow, SteamPropertiesOutput const & sp):
                SteamPropertiesOutput(sp.temperature, sp.pressure, sp.quality, sp.specificVolume, sp.density,
                                      sp.specificEnthalpy, sp.specificEntropy, sp.internalEnergy),
                massFlow(massFlow), energyFlow(energyFlow)
        {}

        FluidProperties() = default;

        double massFlow = 0, energyFlow = 0;
    };

    enum class Key{
        ENTHALPY,
        ENTROPY
    };

    enum class Region{
        REGION1,
        REGION2A,
        REGION2B,
        REGION2C
    };

private:

    /**
     * Determines the IAPWS region based on pressure and temperature
     * @param pressure double, pressure in MPa
     * @param temperature double, temperature in Kelvins
     * @return int, region number
     */
	static int regionSelect(double pressure, double temperature);

    /**
     * Calculates the steam properties using region 1 equations
     *
     * @param temperature double, temperature in Kelvin
     * @param pressure double, pressure in MPa
     *
     * @return SteamPropertiesOutput, steam properties
     */
	static SteamPropertiesOutput region1(double temperature, double pressure);

    /**
     * Calculates the steam properties using region 2 equations
     *
     * @param temperature double, temperature in Kelvin
     * @param pressure double, pressure in MPa
     *
     * @return SteamProperties::Output, steam properties
     */
	static SteamPropertiesOutput region2(double temperature, double pressure);

    /**
     * Calculates the steam properties using region 3 equations
     *
     * @param temperature double, temperature in Kelvin
     * @param pressure double, pressure in MPa
     *
     * @return SteamProperties::Output, steam properties
     */
	static SteamPropertiesOutput region3(double temperature, double pressure);

	static SteamPropertiesOutput region3Density(double density, double temperature);

    /**
     * Calculates the steam properties using region 4 equations (saturated properties)
     *
     * @param temperature double, temperature in Kelvin
     * @param pressure double, pressure in MPa
     *
     * @return SteamProperties::Output, steam properties
     */
	static double region4(double temperature);

    /**
     * Calculates temperature based in pressure and enthalpy for region 1
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
     static double backwardPressureEnthalpyRegion1(double pressure, double enthalpy);

    /**
     * Calculates temperature based in pressure and enthalpy for region 2A
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEnthalpyRegion2A(double pressure, double enthalpy);

    /**
     * Calculates temperature based in pressure and enthalpy for region 2B
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEnthalpyRegion2B(double pressure, double enthalpy);

    /**
     * Calculates temperature based in pressure and enthalpy for region 2C
     *
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEnthalpyRegion2C(double pressure, double enthalpy);

    /**
     * Calculates temperature based on pressure and entropy for region 2A
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion2A(double pressure, double entropy);

    /**
     * Calculates temperature based on pressure and entropy for region 2B
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion2B(double pressure, double entropy);

    /**
     * Calculates temperature based on pressure and entropy for region 2C
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion2C(double pressure, double entropy);

    /**
     * Calculates temperature based on pressure and entropy for region 1
     *
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     *
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion1(double pressure, double entropy);

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
    static double linearTestPoint(double X, Point point1, Point point2);


    static double backwardRegion3Exact(double pressure, double X, SteamSystemModelerTool::Key key);

    /**
     * Uses linear interpolation to goal seek  region 3 using pressure and enthalpy
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEnthalpyRegion3(double pressure, double enthalpy);

    /**
     * Uses linear interpolation to goal seek  region 3 using pressure and entropy
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @param entropy double, specific entropy in kJ/kg/K
     * @return double, temperature in Kelvins
     */
    static double backwardPressureEntropyRegion3(double pressure, double entropy);

    static double backwardPressureEnthalpyRegion1Exact(double pressure, double enthalpy);

    static double backwardPressureEntropyRegion1Exact(double pressure, double entropy);

    /**
     * Returns a more accurate temperature than backwardPressureEnthalpyRegion2A
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return double, temperature in Kelvin
     */
    static double backwardPressureEnthalpyRegion2AExact(double pressure, double enthalpy);

    /**
     * Returns a more accurate temperature than backwardPressureEntropyRegion2A
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     * @return double, temperature in Kelvin
     */
    static double backwardPressureEntropyRegion2AExact(double pressure, double entropy);

    /**
     * Returns a more accurate temperature than backwardPressureEnthalpyRegion2B
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return double, temperature in Kelvin
     */
    static double backwardPressureEnthalpyRegion2BExact(double pressure, double enthalpy);

    /**
     * Returns a more accurate temperature than backwardPressureEntropyRegion2B
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     * @return double, temperature in Kelvin
     */
    static double backwardPressureEntropyRegion2BExact(double pressure, double entropy);

    /**
     * Returns a more accurate temperature than backwardPressureEnthalpyRegion2C
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return double, temperature in Kelvin
     */
    static double backwardPressureEnthalpyRegion2CExact(double pressure, double enthalpy);

    /**
     * Returns a more accurate temperature than backwardPressureEntropyRegion2C
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     * @return double, temperature in Kelvin
     */
    static double backwardPressureEntropyRegion2CExact(double pressure, double entropy);

    /**
     * Uses linear extrapolation for estimate equation to determine much more accurate temperature
     * @param region int, region number
     * @param key Key, value type like ENTROPY ot ENTHALPY
     * @param regionFunction Region, the region of which function to be used (REGION1, REGION2A, etc)
     * @param pressure double, pressure in MPa
     * @param var2 double, value of either entropy (in kJ/kg/K) or enthalpy (in kJ/kg)
     * @return double, temperature in Kelvin
     */
    static double backwardExact(int region, SteamSystemModelerTool::Key key, SteamSystemModelerTool::Region regionFunction , double pressure, double var2);

    // constants

    /**
     * Minimum Pressure of Water MPa
     */
    static constexpr double PRESSURE_MIN = 0.01;
    /**
     * Minimum Temperature of Water K
     */
    static constexpr double TEMPERATURE_MIN = 273.15;
    /**
     * Pressure of Water where ALL regions meet MPa
     */
    static constexpr double PRESSURE_Tp = 16.5291643;

    /**
     * Temperature of Water where ALL regions meet; K
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
     * Maximum Temperature of Water K
     */
    static constexpr double TEMPERATURE_MAX = 1073.15;

    /**
     * Maximum Temperature of Water for Region 3 MPa
     */
    static constexpr double TEMPERATURE_REGION3_MAX = 863.15;

    /**
     * Calculates the boundary pressure associated with the given temperature
     * @param t double, temperature in Kelvins
     *
     * @return double, pressure in MPa
     */
    static inline double boundaryByTemperatureRegion3to2(const double t) {
        return 0.34805185628969E+03 - 0.11671859879975E+01 * t + 0.10192970039326E-02 * std::pow(t, 2.0);
    }

    /**
     * Calculates the boundary temperature associated with the given pressure
     *
     * @param p double, pressure in MPa
     *
     * @return double, temperature in Kelvins
     */
    static inline double boundaryByPressureRegion3to2(const double p) {
        return 0.57254459862746E+03 + std::pow((p - 0.13918839778870E+02) / 0.10192970039326E-02, 0.5);
    }

	friend class SteamProperties;
    friend class SaturatedProperties;
};


#endif //AMO_TOOLS_SUITE_STEAMSYSTEMMODELERTOOL_H
