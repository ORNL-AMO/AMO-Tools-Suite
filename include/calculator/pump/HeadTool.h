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
	/**
    * Constructor for the ReturnCalcValues class with all inputs specified
    *
    * @param differentialElevationHead double, differenial elevation head in ft
    * @param differentialPressureHead double, differential pressure head in ft
    * @param differentialVelocityHead double, differential velocity head in ft
    * @param estimatedSuctionFrictionHead double, estimated suction friction head in ft
    * @param estimatedDischargeFrictionHead double, estimated discharge friction head in ft
    * @param pumpHead double, pump head in ft
    *
    * @return nothing
	*
 * */
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

	///units of ft
	const double differentialElevationHead;

	///units of ft
	const double differentialPressureHead;

	///units of ft
	const double differentialVelocityHead;

    ///units of ft
	const double estimatedSuctionFrictionHead;

	///units of ft
	const double estimatedDischargeFrictionHead;

	///units of ft
	const double pumpHead;
};

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
			specificGravity_(specificGravity),
			flowRate_(flowRate),
			suctionPipeDiameter_(suctionPipeDiameter),
			suctionLineLossCoefficients_(suctionLineLossCoefficients),
			dischargePipeDiameter_(dischargePipeDiameter),
			dischargeGaugePressure_(dischargeGaugePressure),
			dischargeGaugeElevation_(dischargeGaugeElevation),
			dischargeLineLossCoefficients_(dischargeLineLossCoefficients)
	{}

	/**
     * Calculates the operating pump head
     *
     * @return ReturnCalcValues class with all its values calculated
     */
	virtual ReturnCalcValues calculate() = 0;

	/**
     * Calculates the velocity
     *
     * @param diameter const double, diameter in inches
     * @param flow const double, flow rate in gpm
     *
     * @return double, velocity in ft/s
     */
	double velocity(const double diameter, const double flow);

	/**
     * Calculates the velocity head
     *
     * @param velocity const double, velocity in ft/s
     * @param gravity const double, gravity in ft/s^2
     *
     * @return nothing
     */
	double velocityHead(const double velocity, const double gravity);

	/// specific gravity - unitless
	const double specificGravity_;
	/// flow rate in gpm
	const double flowRate_;
	/// suction pipe diamter in inches
	const double suctionPipeDiameter_;
	/// suction line loss coefficient - unitless
	const double suctionLineLossCoefficients_;
	/// discharge  pipe diameter in inches
	const double dischargePipeDiameter_;
	/// discharge gauge pressure in psi
	const double dischargeGaugePressure_;
	/// discharge gauge elevation in ft
	const double dischargeGaugeElevation_;
	/// discharge line loss coefficients - unitless
	const double dischargeLineLossCoefficients_;
	/// gravity constant
	const double gravity_ = 32.1740;
	/// value of Pi
	const double PI_ = 3.141592653589793238463;
};

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
			suctionTankGasOverPressure_(suctionTankGasOverPressure),
			suctionTankFluidSurfaceElevation_(suctionTankFluidSurfaceElevation)
	{}

	/**
     * Calculates the operating pump head
     *
     * @return ReturnCalcValues, all the values calculated for operating pump head
     */
	ReturnCalcValues calculate();

private:
	const double suctionTankGasOverPressure_, suctionTankFluidSurfaceElevation_;
};

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
			suctionGaugePressure_(suctionGaugePressure),
			suctionGaugeElevation_(suctionGaugeElevation)
	{}
/**
     * Calculates the operating pump head
     *
     * @return ReturnCalcValues class with internal values calculated
     */
	ReturnCalcValues calculate();

private:
	const double suctionGaugePressure_, suctionGaugeElevation_;
};

#endif //AMO_TOOLS_SUITE_HEADTOOL_H
