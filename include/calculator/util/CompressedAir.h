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

class ReceiverTank {
public:
	enum class Method {
		General,
		DedicatedStorage,
		MeteredStorage,
		BridgingCompressorReactionDelay
	};

	/**
	 * Constructor for ReceiverTank - This is required when we need to order a receiver tank to meet our compressed air requirements.
	 * This calculator computes the quantity of compressed air that is actually available for use. When air receivers
	 * are installed, the system’s pressure profile and lack of storage limit the effectiveness of compressed air energy
	 * storage. Hence this calculator proves useful in such a context.
	 * @param method ReceiverTank::Method, Calculation Method, in this case it must be General
	 * @param airDemand const double, Amount of air needed, which comes out of the receiver tank - cubic ft
	 * @param allowablePressureDrop const double, This decides the pressure drop inside the receiver tank that we can tolerate - psi
	 * @param atmosphericPressure const double, This is generally 14.7 psi. In case the receiver tank is at higher altitude location, the respective atmospheric pressure at that location can be given - psi
	 */
	ReceiverTank(Method method, double airDemand, double allowablePressureDrop, double atmosphericPressure);

	/**
	 * Constructor for ReceiverTank - This is required when we need to order a receiver tank to meet our compressed air requirements.
	 * This calculator computes the quantity of compressed air that is actually available for use. When air receivers
	 * are installed, the system’s pressure profile and lack of storage limit the effectiveness of compressed air energy
	 * storage. Hence this calculator proves useful in such a context.
	 * @param method ReceiverTank::Method, Calculation Method, in this case it must be DedicatedStorageMethod OR BridgingCompressorReactionDelay due to a C++ overloading limitation
	 * @param lengthOfDemandOrDistanceToCompressorRoom const double, Time duration for which the compressed air is needed OR Distance of the event, that is removing the air, from the compressor room - minutes OR feet
	 * @param airFlowRequirementOrSpeedOfAir const double, The quantity of air needed OR Flow rate of air from the tank - cfm OR ft/sec
	 * @param atmosphericPressure const double, This is generally 14.7 psi. In case the receiver tank is at higher altitude location, the respective atmospheric pressure at that location can be given - psi
	 * @param initialTankPressureOrAirDemand const double, Tank pressure before release of air OR Amount of air needed, which comes out of the receiver tank - psi OR cubic ft
	 * @param finalTankPressureOrAllowablePressureDrop const double, Tank pressure after release of air OR This decides the pressure drop inside the receiver tank that we can tolerate - psi
	 */
	ReceiverTank(Method method, double lengthOfDemandOrDistanceToCompressorRoom, double airFlowRequirementOrSpeedOfAir,
	             double atmosphericPressure, double initialTankPressureOrAirDemand, double finalTankPressureOrAllowablePressureDrop);

	/**
	 * Constructor for ReceiverTank - This is required when we need to order a receiver tank to meet our compressed air requirements.
	 * This calculator computes the quantity of compressed air that is actually available for use. When air receivers
	 * are installed, the system’s pressure profile and lack of storage limit the effectiveness of compressed air energy
	 * storage. Hence this calculator proves useful in such a context.
	 * @param method ReceiverTank::Method, Calculation Method, in this case it must be MeteredStorage
	 * @param lengthOfDemand const double, Time duration for which the compressed air is needed - minutes
	 * @param airFlowRequirement const double, The quantity of air needed - cfm
	 * @param atmosphericPressure const double, This is generally 14.7 psi. In case the receiver tank is at higher altitude location, the respective atmospheric pressure at that location can be given - psi
	 * @param initialTankPressure const double, Tank pressure before release of air - psi
	 * @param finalTankPressure const double, Tank pressure after release of air - psi
	 * @param meteredFlowControl const double, Rate of flow through the metering valve (needle valve) - cfm
	 */
	ReceiverTank(Method method, double lengthOfDemand, double airFlowRequirement, double atmosphericPressure,
	             double initialTankPressure, double finalTankPressure, double meteredFlowControl);

	/**
	 * Calculates and returns receiver tank useable air capacity
	 * @param tankSize double, Quantity of air it can hold - gallons
	 * @param airPressureIn double, Pressure of air entering the Tank - psi
	 * @param airPressureOut double, a.	Pressure of air leaving the Tank - psi
	 * @return double, Useable air storage capacity - scf
	 */
	static double calculateUsableCapacity(double tankSize, double airPressureIn, double airPressureOut);

	/**
	 * Calculates and returns receiver tank useable air capacity
	 * @return double, receiver size - gallons
	 */
	double calculateSize();

private:
	Method method;
	double airDemand, allowablePressureDrop, atmosphericPressure;

	double lengthOfDemandOrDistanceToCompressorRoom, airFlowRequirementOrSpeedOfAir, initialTankPressureOrAirDemand, finalTankPressureOrAllowablePressureDrop;

	double meteredFlowControl;
};

//class CompressedAir {
//public:
//	CompressedAir(double blah) {}
//
//private:
//
//};


#endif //AMO_TOOLS_SUITE_COMPRESSEDAIR_H
