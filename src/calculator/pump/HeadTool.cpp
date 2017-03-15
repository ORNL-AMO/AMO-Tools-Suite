/**
 * @brief Contains the skeleton of HeadTool class.
 *      calculate(): Calculates the operating pump head
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "calculator/pump/HeadTool.h"

double HeadToolBase::velocity(const double diameter, const double flow) {
	return flow / ( PI_ * diameter / 2.0 * diameter / 2.0 );
}

double HeadToolBase::velocityHead(const double velocity, const double gravity) {
	return ( ( velocity * velocity ) / 2.0 )  / gravity;
}

double HeadToolSuctionTank::calculate() {
	const double flow = flowRate_ * 4.402867544 / 15850.32316;
	const double elevationHead = dischargeGaugeElevation_ - suctionTankFluidSurfaceElevation_;
	const double pressureHead =
			(((dischargeGaugePressure_ - suctionTankGasOverPressure_) * 0.145037738007) / 1.42197020632) / specificGravity_;
	const double velocityHeadSuction = velocityHead( velocity( suctionPipeDiameter_ / 1000, flow ), gravity_ );
	const double velocityHeadDischarge = velocityHead( velocity( dischargePipeDiameter_ / 1000, flow ), gravity_ );

	const double velocityHeadDifferential = velocityHeadDischarge;
	const double suctionHead = suctionLineLossCoefficients_ * velocityHeadSuction;
	const double dischargeHead = dischargeLineLossCoefficients_ * velocityHeadDischarge;

	const double head = elevationHead + pressureHead + velocityHeadDifferential + suctionHead + dischargeHead;

	return head;
}

double HeadTool::calculate() {
	const double flow = flowRate_ * 4.402867544 / 15850.32316;
	const double elevationHead = dischargeGaugeElevation_ - suctionGaugeElevation_;
	const double pressureHead =
			(((dischargeGaugePressure_ - suctionGaugePressure_) * 0.145037738007) / 1.42197020632) / specificGravity_;
	const double velocityHeadSuction = velocityHead( velocity( suctionPipeDiameter_ / 1000, flow ), gravity_ );
	const double velocityHeadDischarge = velocityHead( velocity( dischargePipeDiameter_ / 1000, flow ), gravity_ );

	const double velocityHeadDifferential = velocityHeadDischarge - velocityHeadSuction;
	const double suctionHead = suctionLineLossCoefficients_ * velocityHeadSuction;
	const double dischargeHead = dischargeLineLossCoefficients_ * velocityHeadDischarge;

	const double head = elevationHead + pressureHead + velocityHeadDifferential + suctionHead + dischargeHead;

	return head;
}

