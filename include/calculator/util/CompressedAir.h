/**
 * @brief Contains all the implementations of the various components of a compressed air system
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */
#ifndef AMO_TOOLS_SUITE_COMPRESSEDAIR_H
#define AMO_TOOLS_SUITE_COMPRESSEDAIR_H


class PneumaticAirRequirement {
public:
	enum class PistonType {
		SingleActing,
		DoubleActing
	};

	/**
	 * Constructor for PneumaticAirRequirement
	 * This calculator helps in computing the quantity of air required by a specific single acting or a double acting piston cylinder compressor.
	 * The design specs of the compressor are entered in the calculator and the quantity of air needed is generated.
 	 * @param pistonType PistonType, type of Piston, single or double acting - in this case, must be double
 	 * @param cylinderDiameter double, Inner diameter of cylinder - inches
 	 * @param cylinderStroke double, Distance that the piston can travel inside a cylinder - inches
 	 * @param pistonRodDiameter double, Diameter of the piston rod (required only in case of a double acting cylinder) - inches
 	 * @param airPressure double, Pressure of the air coming out of the cylinder - psi
 	 * @param cyclesPerMin double, Number of cycles (1 cycle is a combination of 2 strokes of a piston) by the crankshaft in a minute - strokes
 	 */
	PneumaticAirRequirement(PistonType pistonType, double cylinderDiameter, double cylinderStroke, double pistonRodDiameter,
	                        double airPressure, double cyclesPerMin);

	/**
	 * Constructor for PneumaticAirRequirement
	 * This calculator helps in computing the quantity of air required by a specific single acting or a double acting piston cylinder compressor.
	 * The design specs of the compressor are entered in the calculator and the quantity of air needed is generated.
 	 * @param pistonType PistonType, type of Piston, single or double acting - in this case, must be single
 	 * @param cylinderDiameter double, Inner diameter of cylinder - inches
 	 * @param cylinderStroke double, Distance that the piston can travel inside a cylinder - inches
 	 * @param airPressure double, Pressure of the air coming out of the cylinder - psi
 	 * @param cyclesPerMin double, Number of cycles (1 cycle is a combination of 2 strokes of a piston) by the crankshaft in a minute - strokes
 	 */
	PneumaticAirRequirement(PistonType pistonType, double cylinderDiameter, double cylinderStroke, double airPressure,
	                        double cyclesPerMin);

	class Output {
	public:
		/**
		* Constructor for PneumaticAirRequirement::Output
		* Used to hold return values
		* @param volumeAirIntakePiston const double, Volume of air intake in a piston - cubic feet
	 	* @param compressionRatio const double, The ratio of pressures - Air pressure with atmospheric pressure.
		* @param airRequirementPneumaticCylinder const double, Total cubic feet/min of air requirement for a Pneumatic cylinder - scfm
		*/
		Output(const double volumeAirIntakePiston, const double compressionRatio,
		       const double airRequirementPneumaticCylinder)
				: volumeAirIntakePiston(volumeAirIntakePiston),
				  compressionRatio(compressionRatio),
				  airRequirementPneumaticCylinder(airRequirementPneumaticCylinder)
		{}

		const double volumeAirIntakePiston, compressionRatio, airRequirementPneumaticCylinder;
	};

	/**
	 * Calculates and returns an Output object
	 * @return PneumaticAirRequirement::Output, const output
	 */
	Output calculate();

private:
	PistonType pistonType;
	double cylinderDiameter, cylinderStroke, pistonRodDiameter = 0, airPressure, cyclesPerMin;
};

//class ReceiverTank {
//public:
//
//};

//class CompressedAir {
//public:
//	CompressedAir(double blah) {}
//
//private:
//
//};


#endif //AMO_TOOLS_SUITE_COMPRESSEDAIR_H
