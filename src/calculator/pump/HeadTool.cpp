/**
 * @brief Contains the implementations of the HeadTool hierarchy methods.
 *      calculate(): Calculates the operating pump head
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "calculator/pump/HeadTool.h"

double HeadToolBase::velocity(const double diameter, const double flow) {
	return flow / ( PI * diameter / 2.0 * diameter / 2.0 );
}

double HeadToolBase::velocityHead(const double velocity, const double gravity) {
	return ( ( velocity * velocity ) / 2.0 )  / gravity;
}

std::unordered_map<std::string, double> HeadToolSuctionTank::calculate() {
	// this flow and pressure head should be used when units are metric, and the number 12 should be replaced with 1000
	// in the velocityHead Suction and Discharge calculations
//	const double flow = flowRate * 4.402867544 / 15850.32316;
//	const double pressureHead =
//			(((dischargeGaugePressure - suctionTankGasOverPressure) * 0.145037738007) / 1.42197020632) / specificGravity;

	const double flow = flowRate / 448.8311693;
	const double elevationHead = dischargeGaugeElevation - suctionTankFluidSurfaceElevation;
	const double pressureHead =
			((dischargeGaugePressure - suctionTankGasOverPressure) / 0.432750001) / specificGravity;
	const double velocityHeadSuction = velocityHead( velocity( suctionPipeDiameter / 12, flow ), gravity );
	const double velocityHeadDischarge = velocityHead( velocity( dischargePipeDiameter / 12, flow ), gravity );

	const double velocityHeadDifferential = velocityHeadDischarge;
	const double suctionHead = suctionLineLossCoefficients * velocityHeadSuction;
	const double dischargeHead = dischargeLineLossCoefficients * velocityHeadDischarge;

	const double pumpHead = elevationHead + pressureHead + velocityHeadDifferential + suctionHead + dischargeHead;

	return {
			{"elevationHead",            elevationHead},
			{"pressureHead",             pressureHead},
			{"velocityHeadDifferential", velocityHeadDifferential},
			{"suctionHead",              suctionHead},
			{"dischargeHead",            dischargeHead},
			{"pumpHead",                 pumpHead}
	};
}

std::unordered_map<std::string, double> HeadTool::calculate() {
//	const double flow = flowRate * 4.402867544 / 15850.32316;
//	const double pressureHead =
//			(((dischargeGaugePressure - suctionGaugePressure) * 0.145037738007) / 1.42197020632) / specificGravity;

	const double flow = flowRate / 448.8311693;
	const double elevationHead = dischargeGaugeElevation - suctionGaugeElevation;
	const double pressureHead =
			((dischargeGaugePressure - suctionGaugePressure) / 0.432750001) / specificGravity;
	const double velocityHeadSuction = velocityHead( velocity( suctionPipeDiameter / 12, flow ), gravity );
	const double velocityHeadDischarge = velocityHead( velocity( dischargePipeDiameter / 12, flow ), gravity );

	const double velocityHeadDifferential = velocityHeadDischarge - velocityHeadSuction;
	const double suctionHead = suctionLineLossCoefficients * velocityHeadSuction;
	const double dischargeHead = dischargeLineLossCoefficients * velocityHeadDischarge;

	const double pumpHead = elevationHead + pressureHead + velocityHeadDifferential + suctionHead + dischargeHead;

	return {
			{"elevationHead",            elevationHead},
			{"pressureHead",             pressureHead},
			{"velocityHeadDifferential", velocityHeadDifferential},
			{"suctionHead",              suctionHead},
			{"dischargeHead",            dischargeHead},
			{"pumpHead",                 pumpHead}
	};
}

