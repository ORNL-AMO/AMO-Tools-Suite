/**
 * @brief Contains all the implementations of the various components of a compressed air system
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */
#ifndef AMO_TOOLS_SUITE_COMPRESSEDAIR_H
#define AMO_TOOLS_SUITE_COMPRESSEDAIR_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

class PneumaticAirRequirement {
public:
	enum class PistonType {
		SingleActing,
		DoubleActing
	};

	/**
	 * Constructor for PneumaticAirRequirement
	 * This calculator computes the quantity of air required by a specific single acting or a double acting piston cylinder compressor.
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
	 * This calculator computes the quantity of air required by a specific single acting or a double acting piston cylinder compressor.
	 * The design specs of the compressor are entered in the calculator and the quantity of air needed is generated.
 	 * @param pistonType PistonType, type of Piston, single or double acting - in this case, must be single
 	 * @param cylinderDiameter double, Inner diameter of cylinder - inches
 	 * @param cylinderStroke double, Distance that the piston can travel inside a cylinder - inches
 	 * @param airPressure double, Pressure of the air coming out of the cylinder - psi
 	 * @param cyclesPerMin double, Number of cycles (1 cycle is a combination of 2 strokes of a piston) by the crankshaft in a minute - strokes
 	 */
	PneumaticAirRequirement(PistonType pistonType, double cylinderDiameter, double cylinderStroke, double airPressure,
	                        double cyclesPerMin);

	PneumaticAirRequirement() = default;

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

	ReceiverTank() = default;

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
	static double calculateUsableCapacity(const double tankSize, const double airPressureIn, const double airPressureOut) {
		return (tankSize / 7.48) * (airPressureIn - airPressureOut) / 14.7;
	}

	/**
	 * Calculates and returns receiver tank useable air capacity
	 * @return double, receiver size - gallons
	 */
	double calculateSize();

private:
	Method method;
	double airDemand, allowablePressureDrop, atmosphericPressure;

	double lengthOfDemandOrDistanceToCompressorRoom, airFlowRequirementOrSpeedOfAir, initialTankPressureOrAirDemand;
	double finalTankPressureOrAllowablePressureDrop;

	double meteredFlowControl;
};

namespace Compressor {
	struct PipeData {
		/**
		 * Constructor for Compressor::PipeData - This is used to hold all the pipe lengths in the system
		 * All params are the english spelling of their numeric equivalents, i.e. one half == 0.5, twoAndOneHalf == 2.5, etc.
		 * Used in AirSystemCapacity input and output.
		 */
		PipeData(const double oneHalf, const double threeFourths, const double one, const double oneAndOneFourth,
		         const double oneAndOneHalf, const double two, const double twoAndOneHalf, const double three,
		         const double threeAndOneHalf, const double four, const double five, const double six)
				: oneHalf(oneHalf * 0.0021), threeFourths(threeFourths * 0.0037), one(one * 0.006),
				  oneAndOneFourth(oneAndOneFourth * 0.0104), oneAndOneHalf(oneAndOneHalf * 0.0141),
				  two(two * 0.0233), twoAndOneHalf(twoAndOneHalf * 0.0333), three(three * 0.0513),
				  threeAndOneHalf(threeAndOneHalf * 0.0687), four(four * 0.0884), five(five * 0.1389),
				  six(six * 0.2006),
				  totalPipeVolume(this->oneHalf + this->threeFourths + this->one + this->oneAndOneFourth
				                  + this->oneAndOneHalf + this->two + this->twoAndOneHalf + this->three
				                  + this->threeAndOneHalf + this->four + this->five + this->six)
		{}

		/**
		 * Constructor for Compressor::PipeData - This is used to hold return values for air velocity estimations
		 * @param compVel std::function<double (const double)>, compVel is the compressed air velocity function, it
		 * calculates pipeline velocity given internal area of the pipe in square feet. An example of usage can be found
		 * in AirVelocity::calculate()
		 */
		explicit PipeData(std::function<double (const double)> const & compVel)
				: oneHalf(compVel(0.3)), threeFourths(compVel(0.53)), one(compVel(0.86)),
				  oneAndOneFourth(compVel(1.5)), oneAndOneHalf(compVel(2.04)),
				  two(compVel(3.36)), twoAndOneHalf(compVel(4.79)), three(compVel(7.39)),
				  threeAndOneHalf(compVel(9.89)), four(compVel(12.73)), five(compVel(20)),
				  six(compVel(28.89))
		{}

		const double oneHalf, threeFourths, one, oneAndOneFourth, oneAndOneHalf, two;
		const double twoAndOneHalf, three, threeAndOneHalf, four, five, six;
		const double totalPipeVolume = 0;
	};

	class OperatingCost {
	public:
		/**
		 * Constructor for Compressor::OperatingCost - This finds the cost of operation of the compressor
		 * in both fully and partially loaded instances.
		 * @param motorBhp double, Brake Horse Power is the input power required at the compressor input shaft for a specific speed,
		 * capacity and pressure condition. It is generally shown on the compressor panel. - bhp
		 * @param bhpUnloaded double, Brake horse power in the unloaded condition. - %
		 * @param annualOperatingHours double, Time for which the compressor operates in a year - hours
		 * @param runTimeLoaded double, Percentage of time the compressor runs in loaded condition - %
		 * @param efficiencyLoaded double, Percentage of efficiency in loaded condition - %
		 * @param efficiencyUnloaded double, Percentage of efficiency in un-loaded condition - %
		 * @param costOfElectricity double, Cost of electricity per kWh - $
		 */
		OperatingCost(double motorBhp, double bhpUnloaded, double annualOperatingHours, double runTimeLoaded,
		              double efficiencyLoaded, double efficiencyUnloaded, double costOfElectricity);

		struct Output {
			Output(const double runTimeUnloaded, const double costForLoaded, const double costForUnloaded,
			       const double totalAnnualCost)
					: runTimeUnloaded(runTimeUnloaded), costForLoaded(costForLoaded),
					  costForUnloaded(costForUnloaded), totalAnnualCost(totalAnnualCost)
			{}

			const double runTimeUnloaded, costForLoaded, costForUnloaded, totalAnnualCost;
		};

		Output calculate();

	private:
		double motorBhp, bhpUnloaded, annualOperatingHours, runTimeLoaded, efficiencyLoaded;
		double efficiencyUnloaded, costOfElectricity;
	};


	class AirSystemCapacity {
	public:
		struct Output {
			Output(const double totalPipeVolume, std::vector<double> receiverCapacities,
			       const double totalReceiverVol, const double totalCapacityOfCompressedAirSystem,
			       PipeData pipeLengths)
					: totalPipeVolume(totalPipeVolume), totalReceiverVol(totalReceiverVol),
					  totalCapacityOfCompressedAirSystem(totalCapacityOfCompressedAirSystem),
					  receiverCapacities(std::move(receiverCapacities)), pipeLengths(pipeLengths)
			{}

			const double totalPipeVolume, totalReceiverVol, totalCapacityOfCompressedAirSystem;
			const std::vector<double> receiverCapacities;
			const PipeData pipeLengths;
		};

		/**
		 * Constructor for Compressor::AirSystemCapacity - This is used to find the total air quantity that the
		 * compressed air system can contain at any instant of time, including the air in the pipes and receivers.
		 * @param pipeLengths Compressor::AirSystemCapacity::PipeLengths, Object containing the lengths of the various pipe sizes in your system - ft
		 * @param gallons std::vector<double>, a vector containing the number of gallons in each receiver
		 */
		AirSystemCapacity(PipeData pipeLengths, std::vector<double> gallons);

		Output calculate();

	private:
		PipeData pipeLengths;
		std::vector<double> receivers;
	};

	class AirVelocity {
	public:
		/**
		 * Constructor for Compressor::AirVelocity - This calculator finds the velocity of compressed air
		 * through all the different piping involved in the system.
		 * @attention Constraints - For main and branch lines, recommended maximum velocity is 20 fps,
		 * and it should not exceed 30fps. For line drops, feed lines or branch lines, the recommended velocity is
		 * 30 fps with an upper limit of 50 fps.
		 * @param airFlow double, Volumetric flow rate of air in the compressor system, referenced to the compressor inlet conditions - scfm
		 * @param pipePressure double, Pressure of air flowing through the pipe - psig
		 * @param atmosphericPressure double, Generally it will be 14.7 - psia
		 */
		AirVelocity(double airFlow, double pipePressure, double atmosphericPressure);

		Compressor::PipeData calculate();

	private:
		double airFlow, pipePressure, atmosphericPressure;
	};

	class PipeSizing {
	public:
		struct Output {
			Output(const double crossSectionalArea, const double pipeDiameter)
					: crossSectionalArea(crossSectionalArea), pipeDiameter(pipeDiameter)
			{}
			const double crossSectionalArea, pipeDiameter;
		};

		/**
		 * Constructor for Compressor::PipeSizing - This calculator finds the velocity of compressed air
		 * through all the different piping involved in the system.
		 * @param airflow double, volumetric flow velocity - cfm
		 * @param airlinePressure double, Pressure through the pipe  - psi
		 * @param designVelocity double, The air flow velocity that is meant to flow through the pipe.
		 * @attention Constraints: 20 fps is recommended for a header, but it should never exceed 30 fps - ft/sc
		 * @param atmosphericPressure double, generally it will be 14.7 - psia
		 */
		PipeSizing(double airflow, double airlinePressure, double designVelocity, double atmosphericPressure);

		/**
		 * calculate() will calculate and return the cross sectional area and the pipe diameter.
		 * @return PipeSizing::Output
		 */
		Output calculate();

	private:
		double airflow, airlinePressure, designVelocity, atmosphericPressure;
	};

	class PneumaticValve {
	public:
		/**
		 * Constructor for Compressor::PneumaticValve - Can be used for finding flow rate for a pipe with flow coefficient Cv = 1
		 * @param inletPressure double, psi
		 * @param outletPressure double, psi
		 */
		PneumaticValve(double inletPressure, double outletPressure);
		/**
		 * Constructor for Compressor::PneumaticValve - used for finding the flow coefficient (Cv) when the flow rate is known
		 * @param inletPressure double,
		 * @param outletPressure double,
		 * @param flowRate double,
		 */
		PneumaticValve(double inletPressure, double outletPressure, double flowRate);

		/**
		 * @return flowRate or flow coefficient depending on which constructor was used
		 */
		double calculate();

	private:
		double inletPressure, outletPressure, flowRate;
		bool flowRateKnown;
	};
}

class BagMethod {
public:
	struct Output {
		Output(const double flowRate, const double annualConsumption)
				: flowRate(flowRate), annualConsumption(annualConsumption)
		{}

		const double flowRate, annualConsumption;
	};

	/**
	 * Constructor for BagMethod - The bag method estimates the air flow using a trash bag by counting the time it
	 * takes to fill it. This is the second most accurate means of measuring compressed air consumption.
	 * @param operatingTime double, operating time of the system per year - hours
	 * @param bagFillTime double, time that it takes for the bag to fill with air - seconds
	 * @param heightOfBag double, height of the bag - inches
	 * @param diameterOfBag double, diameter of the bag - inches
	 * @param numberOfUnits int, number of trash bags
	 */
	BagMethod(double operatingTime, double bagFillTime, double heightOfBag, double diameterOfBag, int numberOfUnits);

	/**
	 * @return BagMethod::Output, flowRate and annual consumption
	 */
	Output calculate();

private:
	double operatingTime, bagFillTime, heightOfBag, diameterOfBag, numberOfUnits;
};



#endif //AMO_TOOLS_SUITE_COMPRESSEDAIR_H
