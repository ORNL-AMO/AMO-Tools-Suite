/**
 * @brief Contains the skeleton of HeadTool class.
 *      ***********calculate(): Calculates the Head? ***************
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_HEADTOOL_H
#define AMO_TOOLS_SUITE_HEADTOOL_H

class HeadToolSuctionTank {
public:

	/**
    * Constructor for Suction Tank HeadTool with all inputs specified
    *
    * @param specificGravity no units
    * @param flowRate units in meters cubed per hour (m^3/hour)
    * @param suctionPipeDiameter units in millimeters
    * @param suctionTankGasOverPressure units in kPa
    * @param suctionTankFluidSurfaceElevation units in meters
    * @param suctionLineLossCoefficients TODO no units ?
    * @param dischargePipeDiameter units in millimeters
    * @param dischargeGaugePressure units in kPa
    * @param dischargeGaugeElevation units in meters
    * @param dischargeLineLossCoefficients TODO no units ?
	*
 * */

	HeadToolSuctionTank(
			double specificGravity,
			double flowRate,
			double suctionPipeDiameter,
			double suctionTankGasOverPressure,
			double suctionTankFluidSurfaceElevation,
			double suctionLineLossCoefficients,
			double dischargePipeDiameter,
			double dischargeGaugePressure,
			double dischargeGaugeElevation,
			double dischargeLineLossCoefficients
	) :
			specificGravity_(specificGravity),
			flowRate_(flowRate),
			suctionPipeDiameter_(suctionPipeDiameter),
			suctionTankGasOverPressure_(suctionTankGasOverPressure),
			suctionTankFluidSurfaceElevation_(suctionTankFluidSurfaceElevation),
			suctionLineLossCoefficients_(suctionLineLossCoefficients),
			dischargePipeDiameter_(dischargePipeDiameter),
			dischargeGaugePressure_(dischargeGaugePressure),
			dischargeGaugeElevation_(dischargeGaugeElevation),
			dischargeLineLossCoefficients_(dischargeLineLossCoefficients)
	{}



	double calculate();


private:

	double velocity(double diameter, double flow);

	double velocityHead(double velocity, double gravity);

	const double specificGravity_, flowRate_;

	const double suctionPipeDiameter_, suctionTankGasOverPressure_;

	const double suctionTankFluidSurfaceElevation_, suctionLineLossCoefficients_;

	const double dischargePipeDiameter_, dischargeGaugePressure_;

	const double dischargeGaugeElevation_, dischargeLineLossCoefficients_;

	const double gravity_ = 9.8065, PI_ = 3.141592653589793238463, distF_ = 1000;
};

class HeadTool {
public:

/**
* Constructor for HeadTool with no Suction Tank, all inputs specified
*
* @param specificGravity no units
* @param flowRate units in meters cubed per hour (m^3/hour)
* @param suctionPipeDiameter units in millimeters
* @param suctionTankGaugePressure units in kPa
* @param suctionTankFluidSurfaceElevation units in meters
* @param suctionLineLossCoefficients TODO no units ?
* @param dischargePipeDiameter units in millimeters
* @param dischargeGaugePressure units in kPa
* @param dischargeGaugeElevation units in meters
* @param dischargeLineLossCoefficients TODO no units ?
*
* */

	HeadTool(
			double specificGravity,
			double flowRate,
			double suctionPipeDiameter,
			double suctionGaugePressure,
			double suctionGaugeElevation,
			double suctionLineLossCoefficients,
			double dischargePipeDiameter,
			double dischargeGaugePressure,
			double dischargeGaugeElevation,
			double dischargeLineLossCoefficients
	) :
			specificGravity_(specificGravity),
			flowRate_(flowRate),
			suctionPipeDiameter_(suctionPipeDiameter),
			suctionGaugePressure_(suctionGaugePressure),
			suctionGaugeElevation_(suctionGaugeElevation),
			suctionLineLossCoefficients_(suctionLineLossCoefficients),
			dischargePipeDiameter_(dischargePipeDiameter),
			dischargeGaugePressure_(dischargeGaugePressure),
			dischargeGaugeElevation_(dischargeGaugeElevation),
			dischargeLineLossCoefficients_(dischargeLineLossCoefficients) {}

	double calculate();

private:

	double velocity(double diameter, double flow);

	double velocityHead(double velocity, double gravity);

	const double specificGravity_, flowRate_;

	const double suctionPipeDiameter_, suctionGaugePressure_;

	const double suctionGaugeElevation_, suctionLineLossCoefficients_;

	const double dischargePipeDiameter_, dischargeGaugePressure_;

	const double dischargeGaugeElevation_, dischargeLineLossCoefficients_;

	const double gravity_ = 9.8065, PI_ = 3.141592653589793238463, distF_ = 1000;
};


#endif //AMO_TOOLS_SUITE_HEADTOOL_H
