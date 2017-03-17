/**
 * @brief Contains the entire hierarchy of the HeadTool classes.
 *      calculate(): Calculates the operating pump head
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_HEADTOOL_H
#define AMO_TOOLS_SUITE_HEADTOOL_H

/**
* Used to return the calculation made in both HeadTool classes, should not be used otherwise
* */
class ReturnCalcValues {
public:
	ReturnCalcValues(
			const double differentialElevationHead,
			const double differentialPressureHead,
			const double differentialVelocityHead,
			const double estimatedSuctionFrictionHead,
			const double estimatedDischargeFrictionHead,
			const double pumpHead
	) :
			differentialElevationHead(differentialElevationHead),
			differentialPressureHead(differentialPressureHead),
			differentialVelocityHead(differentialVelocityHead),
			estimatedSuctionFrictionHead(estimatedSuctionFrictionHead),
			estimatedDischargeFrictionHead(estimatedDischargeFrictionHead),
			pumpHead(pumpHead)
	{}

	const double differentialElevationHead, differentialPressureHead, differentialVelocityHead;
	const double estimatedSuctionFrictionHead, estimatedDischargeFrictionHead, pumpHead;
};

class HeadToolBase {
protected:
	/**
    * Constructor for the abstract HeadToolBase class with all inputs specified
    *
    * @param specificGravity no units
    * @param flowRate units in meters cubed per hour (m^3/hour)
    * @param suctionPipeDiameter units in millimeters
    * @param suctionLineLossCoefficients no units
    * @param dischargePipeDiameter units in millimeters
    * @param dischargeGaugePressure units in kPa
    * @param dischargeGaugeElevation units in meters
    * @param dischargeLineLossCoefficients no units
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
			specificGravity_(specificGravity),
			flowRate_(flowRate),
			suctionPipeDiameter_(suctionPipeDiameter),
			suctionLineLossCoefficients_(suctionLineLossCoefficients),
			dischargePipeDiameter_(dischargePipeDiameter),
			dischargeGaugePressure_(dischargeGaugePressure),
			dischargeGaugeElevation_(dischargeGaugeElevation),
			dischargeLineLossCoefficients_(dischargeLineLossCoefficients)
	{}

	virtual ReturnCalcValues calculate() = 0;

	double velocity(const double diameter, const double flow);

	double velocityHead(const double velocity, const double gravity);

	const double specificGravity_, flowRate_;

	const double suctionPipeDiameter_, suctionLineLossCoefficients_;

	const double dischargePipeDiameter_, dischargeGaugePressure_;

	const double dischargeGaugeElevation_, dischargeLineLossCoefficients_;

	const double gravity_ = 9.8065, PI_ = 3.141592653589793238463;
};

class HeadToolSuctionTank : private HeadToolBase {
public:

	/**
    * Constructor for the HeadToolSuctionTank class with all inputs specified
    *
    * @param specificGravity no units
    * @param flowRate units in meters cubed per hour (m^3/hour)
    * @param suctionPipeDiameter units in millimeters
    * @param suctionTankGasOverPressure units in kPa
    * @param suctionTankFluidSurfaceElevation units in meters
    * @param suctionLineLossCoefficients no units
    * @param dischargePipeDiameter units in millimeters
    * @param dischargeGaugePressure units in kPa
    * @param dischargeGaugeElevation units in meters
    * @param dischargeLineLossCoefficients no units
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
			suctionTankGasOverPressure_(suctionTankGasOverPressure),
			suctionTankFluidSurfaceElevation_(suctionTankFluidSurfaceElevation)
	{}

	ReturnCalcValues calculate();

private:
	const double suctionTankGasOverPressure_, suctionTankFluidSurfaceElevation_;
};

class HeadTool : private HeadToolBase {
public:

/**
* Constructor for HeadTool with no Suction Tank, all inputs specified
*
* @param specificGravity no units
* @param flowRate units in meters cubed per hour (m^3/hour)
* @param suctionPipeDiameter units in millimeters
* @param suctionGaugePressure units in kPa
* @param suctionGaugeElevation units in meters
* @param suctionLineLossCoefficients no units
* @param dischargePipeDiameter units in millimeters
* @param dischargeGaugePressure units in kPa
* @param dischargeGaugeElevation units in meters
* @param dischargeLineLossCoefficients no units
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
			suctionGaugePressure_(suctionGaugePressure),
			suctionGaugeElevation_(suctionGaugeElevation)
	{}

	ReturnCalcValues calculate();

private:
	const double suctionGaugePressure_, suctionGaugeElevation_;
};

#endif //AMO_TOOLS_SUITE_HEADTOOL_H
