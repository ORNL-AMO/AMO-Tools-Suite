/**
 * @brief Contains the skeleton of HeadTool class.
 *      ***********calculate(): Calculates the ***************
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "calculator/pump/HeadTool.h"

double HeadToolSuctionTank::calculate() {
	double flow = flowRate_ * 4.402867544 / 15850.32316;
	double elevationHead = dischargeGaugeElevation_ - suctionTankFluidSurfaceElevation_;
	double pressureHead =
			(((dischargeGaugePressure_ - suctionTankGasOverPressure_) * 0.145037738007) / 1.42197020632) / specificGravity_;
	double velocityHeadSuction = velocityHead( velocity( suctionPipeDiameter_ / distF_, flow ), gravity_ );
	double velocityHeadDischarge = velocityHead( velocity( dischargePipeDiameter_ / distF_, flow ), gravity_ );

	double velocityHeadDifferential = velocityHeadDischarge;
	double suctionHead = suctionLineLossCoefficients_ * velocityHeadSuction;
	double dischargeHead = dischargeLineLossCoefficients_ * velocityHeadDischarge;

	double head = elevationHead + pressureHead + velocityHeadDifferential + suctionHead + dischargeHead;

	return head;
}

double HeadToolSuctionTank::velocity(double diameter, double flow) {
	return flow / ( PI_ * diameter / 2.0 * diameter / 2.0 );
}

double HeadToolSuctionTank::velocityHead(double velocity, double gravity) {
	return ( ( velocity * velocity ) / 2.0 )  / gravity;
}

double HeadTool::calculate() {
	double flow = flowRate_ * 4.402867544 / 15850.32316;
	double elevationHead = dischargeGaugeElevation_ - suctionGaugeElevation_;
	double pressureHead =
			(((dischargeGaugePressure_ - suctionGaugePressure_) * 0.145037738007) / 1.42197020632) / specificGravity_;
	double velocityHeadSuction = velocityHead( velocity( suctionPipeDiameter_ / distF_, flow ), gravity_ );
	double velocityHeadDischarge = velocityHead( velocity( dischargePipeDiameter_ / distF_, flow ), gravity_ );

	double velocityHeadDifferential = velocityHeadDischarge - velocityHeadSuction;
	double suctionHead = suctionLineLossCoefficients_ * velocityHeadSuction;
	double dischargeHead = dischargeLineLossCoefficients_ * velocityHeadDischarge;

	double head = elevationHead + pressureHead + velocityHeadDifferential + suctionHead + dischargeHead;

	return head;
}

double HeadTool::velocity(double diameter, double flow) {
	return flow / ( PI_ * diameter / 2.0 * diameter / 2.0 );
}

double HeadTool::velocityHead(double velocity, double gravity) {
	return ( ( velocity * velocity ) / 2.0 )  / gravity;
}
