/**
 * @brief Contains the entire hierarchy of the HeadTool classes.
 *      calculate(): Calculates the operating pump head
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 */

#ifndef AMO_TOOLS_SUITE_HEADTOOL_H
#define AMO_TOOLS_SUITE_HEADTOOL_H

#include <string>
#include <unordered_map>

/**
 * Head Tool Base class
 * Contains all of the basic properties of a head tool.
 * Used to calculate velocity and velocity head so those values can be used in the HeadToolSuctionTank class or HeadTool class to calculate all of the values in the returned map.
 */
class HeadToolBase {
protected:
	/**
    * Constructor for the abstract HeadToolBase class with all inputs specified
    *
    * @param specificGravity double, specific gravity - unitless
    * @param flowRate double, flow rate in gpm (gallons per minute)
    * @param suctionPipeDiameter double, diameter of suction pipe in inches
    * @param suctionLineLossCoefficients double, suction line loss coefficient - unitless
    * @param dischargePipeDiameter double, diameter of discharge pipe in inches
    * @param dischargeGaugePressure double, gauge pressure of discharge in psig (pounds per square inch gauge)
    * @param dischargeGaugeElevation double, gauge elevation of discharge in feet
    * @param dischargeLineLossCoefficients double, line loss coefficients of discharge - unitless
	*
 * */

	HeadToolBase(
			const double specificGravity,
			const double flowRate,
			const double suctionPipeDiameter,
			const double suctionLineLossCoefficients,
			const double dischargePipeDiameter,
			const double dischargeGaugePressure,
			const double dischargeGaugeElevation,
			const double dischargeLineLossCoefficients
	) :
			specificGravity(specificGravity),
			flowRate(flowRate),
			suctionPipeDiameter(suctionPipeDiameter),
			suctionLineLossCoefficients(suctionLineLossCoefficients),
			dischargePipeDiameter(dischargePipeDiameter),
			dischargeGaugePressure(dischargeGaugePressure),
			dischargeGaugeElevation(dischargeGaugeElevation),
			dischargeLineLossCoefficients(dischargeLineLossCoefficients)
	{}

	/**
     * Calculates the operating pump head
     *
     * @return unordered map with all its values calculated
     */
	virtual std::unordered_map<std::string, double> calculate() = 0;

	/**
     * Calculates the velocity
     *
     * @param diameter const double, diameter in inches
     * @param flow const double, flow rate in gpm
     *
     * @return double, velocity in ft/s
     */
	double velocity(double diameter, double flow);

	/**
     * Calculates the velocity head
     * @param velocity const double, velocity in ft/s
     * @param gravity const double, gravity in ft/s^2
     */
	double velocityHead(double velocity, double gravity);

	/// specific gravity - unitless
	const double specificGravity;
	/// flow rate in gpm
	const double flowRate;
	/// suction pipe diameter in inches
	const double suctionPipeDiameter;
	/// suction line loss coefficient - unitless
	const double suctionLineLossCoefficients;
	/// discharge  pipe diameter in inches
	const double dischargePipeDiameter;
	/// discharge gauge pressure in psi
	const double dischargeGaugePressure;
	/// discharge gauge elevation in ft
	const double dischargeGaugeElevation;
	/// discharge line loss coefficients - unitless
	const double dischargeLineLossCoefficients;
	/// gravity constant
	const double gravity = 32.1740;
	/// value of Pi
	const double PI = 3.141592653589793238463;
};

/**
 * Head Tool Suction Tank class
 * Contains all of the properties of a head tool suction tank.
 * Used to calculate all of the values in the returned map.
 */
class HeadToolSuctionTank : private HeadToolBase {
public:

	/**
    * Constructor for the HeadToolSuctionTank class with all inputs specified
    *
    * @param specificGravity double, specific gravity - unitless
    * @param flowRate double, flow rate in gpm (gallons per minute)
    * @param suctionPipeDiameter double, diameter of suction pipe in feet
    * @param suctionTankGasOverPressure double, gas over pressure of suction tank in psig (pounds per square inch gauage)
    * @param suctionTankFluidSurfaceElevation double, fluid surface elevation of suction tank in feet
    * @param suctionLineLossCoefficients double, line loss coefficients of suction - unitless
    * @param dischargePipeDiameter double, diameter of discharge pipe in feet
    * @param dischargeGaugePressure double, gauge pressure of discharge in psig (pounds per square inch gauge)
    * @param dischargeGaugeElevation double, gauge elevation of discharge in inches
    * @param dischargeLineLossCoefficients double, line loss coefficients of discharge - unitless
	*
 * */

	HeadToolSuctionTank(
			const double specificGravity,
			const double flowRate,
			const double suctionPipeDiameter,
			const double suctionTankGasOverPressure,
			const double suctionTankFluidSurfaceElevation,
			const double suctionLineLossCoefficients,
			const double dischargePipeDiameter,
			const double dischargeGaugePressure,
			const double dischargeGaugeElevation,
			const double dischargeLineLossCoefficients
	) :
			HeadToolBase( specificGravity,
			              flowRate,
			              suctionPipeDiameter,
			              suctionLineLossCoefficients,
			              dischargePipeDiameter,
			              dischargeGaugePressure,
			              dischargeGaugeElevation,
			              dischargeLineLossCoefficients),
			suctionTankGasOverPressure(suctionTankGasOverPressure),
			suctionTankFluidSurfaceElevation(suctionTankFluidSurfaceElevation)
	{}

	/**
     * Calculates the operating pump head
     * @return unordered map with all the values calculated for operating pump head
     */
	std::unordered_map<std::string, double> calculate() override;

private:
	const double suctionTankGasOverPressure, suctionTankFluidSurfaceElevation;
};

/**
 * Head Tool class
 * Contains all of the properties of a head tool.
 * Used to calculate all of the values of the returned unordered map.
 */
class HeadTool : private HeadToolBase {
public:

/**
* Constructor for HeadTool with no Suction Tank, all inputs specified
*
* @param specificGravity double, specific gravity - unitless
* @param flowRate double, flow rate in gpm (gallons per minute)
* @param suctionPipeDiameter double, diameter of suction pipe in feet
* @param suctionGaugePressure double, gauge pressure of suction in psig (pounds per square inch guage)
* @param suctionGaugeElevation double, gauge elevation of suction in feet
* @param suctionLineLossCoefficients double, line loss coefficients of suction - unitless
* @param dischargePipeDiameter double, diameter of discharge pipe in feet
* @param dischargeGaugePressure double, gauge pressure of discharge in psig (pounds per square inch guage)
* @param dischargeGaugeElevation double, gauge elevation of discharge in feet
* @param dischargeLineLossCoefficients double, line loss coefficients of discharge - unitless
*
* */

	HeadTool(
			const double specificGravity,
			const double flowRate,
			const double suctionPipeDiameter,
			const double suctionGaugePressure,
			const double suctionGaugeElevation,
			const double suctionLineLossCoefficients,
			const double dischargePipeDiameter,
			const double dischargeGaugePressure,
			const double dischargeGaugeElevation,
			const double dischargeLineLossCoefficients
	) :
			HeadToolBase( specificGravity,
			              flowRate,
			              suctionPipeDiameter,
			              suctionLineLossCoefficients,
			              dischargePipeDiameter,
			              dischargeGaugePressure,
			              dischargeGaugeElevation,
			              dischargeLineLossCoefficients),
			suctionGaugePressure(suctionGaugePressure),
			suctionGaugeElevation(suctionGaugeElevation)
	{}
	/**
     * Calculates the operating pump head
     * @return unordered_map with internal values calculated
     */
	std::unordered_map<std::string, double> calculate() override;

private:
	const double suctionGaugePressure, suctionGaugeElevation;
};

#endif //AMO_TOOLS_SUITE_HEADTOOL_H
