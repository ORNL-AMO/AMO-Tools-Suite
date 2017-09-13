#include "fsat/Fan.h"

// used for method 1
BaseGasDensity::BaseGasDensity(const double tdo, const double pso, const double pbo, const double po, const GasType gasType)
			: tdo(tdo), pso(pso), pbo(pbo), po(po), gasType(gasType) {}

	// TODO incomplete, po (density) shouldn't be an input in either of the constructors below bc it needs to be calculated
//	// used for method 2 without wet bulb temperature as "data to establish gas humidity"
//	BaseGasDensity(const double tdo, const double pso, const double pbo, const double po, const double g,
//	               const double two)
//			: tdo(tdo), pso(pso), pbo(pbo), po(po), g(g), two(two) {}

//	// used for method 2 with wet bulb temp being used for "data to establish gas humidity"
//	BaseGasDensity(const double tdo, const double pso, const double pbo, const double po, const double g,
//	               const double percentRH)
//			: tdo(tdo), pso(pso), pbo(pbo), po(po), g(g), percentRH(percentRH) {}

PlaneData::PlaneData(FanInletFlange & fanInletFlange, FanOrEvaseOutletFlange & fanOrEvaseOutletFlange,
                     FlowTraverse & flowTraverse, std::vector<AddlTravPlane> & addlTravPlanes,
                     InletMstPlane & inletMstPlane, OutletMstPlane & outletMstPlane,
                     bool const variationsInPlanarBarometricPressure, bool const estimatePlaneTemp,
                     const double totalPressureLossBtwnPlanes1and4, const double totalPressureLossBtwnPlanes2and5,
                     bool const plane5upstreamOfPlane2)
		: fanInletFlange(fanInletFlange), fanOrEvaseOutletFlange(fanOrEvaseOutletFlange), flowTraverse(flowTraverse),
		  addlTravPlanes(addlTravPlanes), inletMstPlane(inletMstPlane), outletMstPlane(outletMstPlane),
		  variationsInPlanarBarometricPressure(variationsInPlanarBarometricPressure),
		  estimatePlaneTemp(estimatePlaneTemp), plane5upstreamOfPlane2(plane5upstreamOfPlane2),
		  totalPressureLossBtwnPlanes1and4(totalPressureLossBtwnPlanes1and4),
		  totalPressureLossBtwnPlanes2and5(totalPressureLossBtwnPlanes2and5)
{}

void PlaneData::establishFanInletOrOutletDensity(Planar & plane, std::function<double (Planar const &, const double)> const & calcDensity,
                                                 double const mTotal, double const assumedDensity) {
	double calculatedDensity = assumedDensity;
	for (auto i = 0; i < 50; i++) {
		plane.gasDensity = calculatedDensity;
		plane.gasVolumeFlowRate = mTotal / plane.gasDensity;
		plane.gasVelocity = plane.gasVolumeFlowRate / plane.area;
		plane.gasVelocityPressure = plane.gasDensity * std::pow(plane.gasVelocity / 1096, 2);
		auto fanInletOrOutletStaticPressure = plane.gasTotalPressure - plane.gasVelocityPressure;
		auto fanInletOrOutletGasDensity = calcDensity(plane, fanInletOrOutletStaticPressure);

		calculatedDensity = fanInletOrOutletGasDensity;
		if (std::abs(fanInletOrOutletGasDensity - plane.gasDensity) < 0.0001) {
			plane.gasDensity = calculatedDensity;
			return;
		}
	}
	throw std::runtime_error("density iteration did not converge");
}

void PlaneData::calculate(BaseGasDensity const & bgd) {
	auto const calcDensity = [&bgd] (Planar const & plane, const double psx) {
		return bgd.po * (bgd.tdo + 460) * (psx + 13.63 * plane.pbx) / ((plane.tdx + 460) * (bgd.pso + 13.63 * bgd.pbo));
	};

	flowTraverse.gasDensity = calcDensity(flowTraverse, flowTraverse.getPsx());
	for (auto & p : addlTravPlanes) {
		p.gasDensity = calcDensity(p, p.getPsx());
	}
	inletMstPlane.gasDensity = calcDensity(inletMstPlane, inletMstPlane.getPsx());
	outletMstPlane.gasDensity = calcDensity(outletMstPlane, outletMstPlane.getPsx());

	flowTraverse.gasVelocity = 1096 * std::sqrt(flowTraverse.pv3 / flowTraverse.gasDensity);
	flowTraverse.gasVolumeFlowRate = flowTraverse.gasVelocity * flowTraverse.area;

	auto mTotal = flowTraverse.gasDensity * flowTraverse.gasVolumeFlowRate;
	for (auto & plane : addlTravPlanes) {
		plane.gasVelocity = 1096 * std::sqrt(plane.pv3 / plane.gasDensity);
		plane.gasVolumeFlowRate = plane.gasVelocity * plane.area;
		mTotal += plane.gasDensity * plane.gasVolumeFlowRate;
	}

	inletMstPlane.gasVolumeFlowRate = mTotal / inletMstPlane.gasDensity;
	inletMstPlane.gasVelocity = inletMstPlane.gasVolumeFlowRate / inletMstPlane.area;
	inletMstPlane.gasVelocityPressure = inletMstPlane.gasDensity * std::pow((inletMstPlane.gasVelocity / 1096), 2);
	inletMstPlane.gasTotalPressure = inletMstPlane.getPsx() + inletMstPlane.gasVelocityPressure;

	// step 7
	fanInletFlange.gasTotalPressure = inletMstPlane.gasTotalPressure - totalPressureLossBtwnPlanes1and4;

	// steps 8 - 13
	establishFanInletOrOutletDensity(fanInletFlange, calcDensity, mTotal, inletMstPlane.gasDensity);


	// calculating plane 2 inlet density and pressure
	outletMstPlane.gasVolumeFlowRate = mTotal / outletMstPlane.gasDensity;
	outletMstPlane.gasVelocity = outletMstPlane.gasVolumeFlowRate / outletMstPlane.area;
	outletMstPlane.gasVelocityPressure = outletMstPlane.gasDensity * std::pow(outletMstPlane.gasVelocity / 1096, 2);
	outletMstPlane.gasTotalPressure = outletMstPlane.getPsx() + outletMstPlane.gasVelocityPressure;

	// step 7
	fanOrEvaseOutletFlange.gasTotalPressure = outletMstPlane.gasTotalPressure;
	fanOrEvaseOutletFlange.gasTotalPressure +=
			(plane5upstreamOfPlane2) ? -totalPressureLossBtwnPlanes2and5 : totalPressureLossBtwnPlanes2and5;

	// step 8 - iteration
	establishFanInletOrOutletDensity(fanOrEvaseOutletFlange, calcDensity, mTotal, outletMstPlane.gasDensity);
}

void Fan::calculate() {
	// TODO pbx = barometric pressure, what to do if barometric pressure does vary between planes ? pg
	auto x = (planeData.fanOrEvaseOutletFlange.gasTotalPressure - planeData.fanInletFlange.gasTotalPressure)
	         / (planeData.fanInletFlange.gasTotalPressure + 13.63 * planeData.fanInletFlange.pbx);

	double isentropicExponent = 0; // TODO what value to use for GasTypes other than Air ?
	if (baseGasDensity.gasType == BaseGasDensity::GasType::AIR) isentropicExponent = 1.4;


	// TODO pbx = barometric pressure, what to do if barometric pressure does vary between planes ? pg 61
	// TODO the calculation of z returns 0.430 instead of 0.03515
	auto z = (isentropicExponent / (isentropicExponent - 1))
	         * ((6362 * (fanShaftPower.getFanShaftPower() / planeData.fanInletFlange.gasVolumeFlowRate))
	            / (planeData.fanInletFlange.gasTotalPressure + 13.63 * planeData.fanInletFlange.pbx));



	auto blah = "blah";
}

// hard coded numbers for the sake of testing the convergence algorithm
//	void PlaneData::calculate(BaseGasDensity const & bgd) {
//		auto const calcDensity = [&bgd] (Planar const & plane, const double psx) {
//			return bgd.po * (bgd.tdo + 460) * (psx + 13.63 * plane.pbx) / ((plane.tdx + 460) * (bgd.pso + 13.63 * bgd.pbo));
//		};
//
//		flowTraverse.gasDensity = 0.0546;
//		for (auto & p : addlTravPlanes) {
//			p.gasDensity = 0.0548;
//		}
//		inletMstPlane.gasDensity = 0.0547;
//		outletMstPlane.gasDensity = 0.0568;
//
//		flowTraverse.gasVelocity = 4063.5;
//		flowTraverse.gasVolumeFlowRate = 132226;
//
//		auto mTotal = 13692;
//		for (auto & plane : addlTravPlanes) {
//			plane.gasVelocity = 3628.5;
//			plane.gasVolumeFlowRate = 118073;
////			mTotal += plane.gasDensity * plane.gasVolumeFlowRate;
//		}
//
//		inletMstPlane.gasVolumeFlowRate = 250276;
//		inletMstPlane.gasVelocity = 3846;
//		inletMstPlane.gasVelocityPressure = 0.674;
//		inletMstPlane.gasTotalPressure = -16.88;
//
//		// step 7
//		fanInletFlange.gasTotalPressure = -16.88;
//
//		// steps 8 - 13
//		establishFanInletOrOutletDensity(fanInletFlange, calcDensity, mTotal, inletMstPlane.gasDensity);
//
//
//		// calculating plane 2 inlet density and pressure
//		outletMstPlane.gasVolumeFlowRate = 240912;
//		outletMstPlane.gasVelocity = 10348;
//		outletMstPlane.gasVelocityPressure = 5.067;
//		outletMstPlane.gasTotalPressure = 6.867;
//
//		// step 7
//		fanOrEvaseOutletFlange.gasTotalPressure = outletMstPlane.gasTotalPressure;
//		fanOrEvaseOutletFlange.gasTotalPressure +=
//				(plane5upstreamOfPlane2) ? -totalPressureLossBtwnPlanes2and5 : totalPressureLossBtwnPlanes2and5;
//
//		// step 8 - iteration
//		establishFanInletOrOutletDensity(fanOrEvaseOutletFlange, calcDensity, mTotal, outletMstPlane.gasDensity);
//
//		auto blah = "blah";
//	}

Fan::Fan(FanRatedInfo & fanRatedInfo, PlaneData & planeData, BaseGasDensity & baseGasDensity,
         FanShaftPower & fanShaftPower)
		: fanRatedInfo(fanRatedInfo), planeData(std::move(planeData)), baseGasDensity(baseGasDensity),
		  fanShaftPower(fanShaftPower)
{
	this->planeData.calculate(this->baseGasDensity);
	this->calculate();
};
