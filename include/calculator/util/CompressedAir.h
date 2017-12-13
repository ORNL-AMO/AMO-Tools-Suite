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
	/**
	* Constructor for PneumaticAirRequirement
 	* @param cylinderDiameter double, inches
 	* @param cylinderStroke double, inches
 	* @param pistonRodDiameter double, inches
 	* @param airPressure double, psi
 	* @param cyclesPerMin double, strokes per minute
 	*/
	PneumaticAirRequirement(double cylinderDiameter, double cylinderStroke, double pistonRodDiameter,
	                        double airPressure, double cyclesPerMin);

	class Output {
	public:
		/**
		* Constructor for PneumaticAirRequirement::Output
		* Used to hold return values
		* @param volumeAirIntakeSingleActingPiston const double, cubic feet
		* @param volumeAirIntakeDoubleActingPiston const double, cubic feet
	 	* @param compressionRatio const double
		* @param airRequirementSingleActingPneumaticCylinder const double, scfm
		* @param airRequirementDoubleActingPneumaticCylinder const double, scfm
		*/
		Output(const double volumeAirIntakeSingleActingPiston, const double volumeAirIntakeDoubleActingPiston,
		       const double compressionRatio, const double airRequirementSingleActingPneumaticCylinder,
		       const double airRequirementDoubleActingPneumaticCylinder)
				: volumeAirIntakeSingleActingPiston(volumeAirIntakeSingleActingPiston),
				  volumeAirIntakeDoubleActingPiston(volumeAirIntakeDoubleActingPiston),
				  compressionRatio(compressionRatio),
				  airRequirementSingleActingPneumaticCylinder(airRequirementSingleActingPneumaticCylinder),
				  airRequirementDoubleActingPneumaticCylinder(airRequirementDoubleActingPneumaticCylinder)
		{}

		const double volumeAirIntakeSingleActingPiston, volumeAirIntakeDoubleActingPiston, compressionRatio;
		const double airRequirementSingleActingPneumaticCylinder, airRequirementDoubleActingPneumaticCylinder;
	};

	/**
	 * Calculates and returns an Output object
	 * @return PneumaticAirRequirement::Output, const output
	 */
	Output calculate();

private:
	double cylinderDiameter, cylinderStroke, pistonRodDiameter, airPressure, cyclesPerMin;
};

//class CompressedAir {
//public:
//	CompressedAir(double blah) {}
//
//private:
//
//};


#endif //AMO_TOOLS_SUITE_COMPRESSEDAIR_H
