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
	double elevationHead = dischargeGaugeElevation_ - suctionTankFluidSurfaceElevation_;
	double pressureHead = ( dischargeGaugePressure_ - suctionTankGasOverPressure_ ) / specificGravity_;
	double velocityHeadSuction = velocityHead( velocity( suctionPipeDiameter_ / distF_, flowRate_ ), gravity_ );
	double velocityHeadDischarge = velocityHead( velocity( dischargePipeDiameter_ / distF_, flowRate_ ), gravity_ );

	double velocityHeadDifferential = velocityHeadSuction;
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
