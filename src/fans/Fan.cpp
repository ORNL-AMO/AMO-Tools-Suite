#include "fans/Fan.h"

// used for method 1
BaseGasDensity::BaseGasDensity(const double dryBulbTemp, const double staticPressure, const double barometricPressure,
                               const double gasDensity, const GasType gasType)
			: tdo(dryBulbTemp), pso(staticPressure), pbo(barometricPressure), po(gasDensity), gasType(gasType)
{}

// TODO ensure correctness
//BaseGasDensity::BaseGasDensity(double const dryBulbTemp, double const staticPressure, double const barometricPressure,
//                               double const relativeHumidityOrDewPoint, GasType const gasType,
//                               InputType const inputType, double const specificGravity)
//		: tdo(dryBulbTemp), pso(staticPressure), pbo(barometricPressure), g(specificGravity), gasType(gasType) {
//	auto const satPress = calculateSaturationPressure(tdo);
//	double rh = 0;
//	if (inputType == InputType::RH) {
//		rh = relativeHumidityOrDewPoint;
//	} else if (inputType == InputType::DEW) {
//		rh = calculateSaturationPressure(relativeHumidityOrDewPoint) / satPress;
//	} else if (inputType == InputType::WET) {
//		throw std::runtime_error("The wrong constructor for BaseGasDensity was called here.");
//	}
//
//	auto const rhRatio = calculateRatioRH(tdo, rh, pbo, specificGravity);
//	po = (((pbo + (pso / 13.6)) - satPress * rh) * g + satPress * rh * rhRatio) / ((21.85 / (g * 29.98)) * (tdo + 459.7));
//}
//
//BaseGasDensity::BaseGasDensity(double const dryBulbTemp, double const staticPressure, double const barometricPressure,
//                               double const wetBulbTemp, GasType const gasType,
//                               InputType const inputType, double const specificGravity, const double cpGas)
//		: tdo(dryBulbTemp), pso(staticPressure), pbo(barometricPressure), g(specificGravity), gasType(gasType)
//{
//	if (inputType != InputType::WET) throw std::runtime_error("The wrong constructor for BaseGasDensity was called");
//	auto const satPress = calculateSaturationPressure(tdo);
//	auto const rh = calculateRelativeHumidityFromWetBulb(tdo, wetBulbTemp, cpGas);
//	auto const rhRatio = calculateRatioRH(tdo, rh, pbo, specificGravity);
//	po = (((pbo + (pso / 13.6)) - satPress * rh) * g + satPress * rh + rhRatio) / ((21.85 / (g * 29.98)) * (tdo + 459.7));
//}

double BaseGasDensity::calculateSaturationPressure(double dryBulbTemp) const {
	auto const C1 = -5674.5359, C2 = -0.51523058, C3 = -0.009677843, C4 = 0.00000062215701;
	auto const C5 = 2.0747825 * std::pow(10, -9), C6 = -9.0484024 * std::pow(10, -13), C7 = 4.1635019, C8 = -5800.2206;
	auto const C9 = -5.516256, C10 = -0.048640239, C11 = 0.000041764768, C12 = -0.000000014452093, C13 = 6.5459673;

	auto const tKelvin = (dryBulbTemp + 459.67) *  0.555556;

	if (tKelvin < 273.15) {
		auto const p = std::exp(C1 / tKelvin + C2 + tKelvin * C3 + tKelvin * tKelvin
		                                                           * (C4 + tKelvin * (C5 + C6 * tKelvin))
		                        + C7 * std::log(tKelvin));
		return p * (29.9216 / 101.325);
	}
	auto const p = std::exp(C8 / tKelvin + C9 + tKelvin * (C10 + tKelvin * (C11 + tKelvin * C12))
	                        + C13 * std::log(tKelvin));

	return p * (29.9216 / 101.325);
}

double BaseGasDensity::calculateRatioRH(const double dryBulbTemp, const double relativeHumidity,
                                        const double barometricPressure, const double specificGravity) const
{
	auto const pw = (calculateSaturationPressure(dryBulbTemp) * relativeHumidity);
	return (18.02 / (specificGravity * 28.98)) * pw / (barometricPressure - pw);
}

double BaseGasDensity::calculateRelativeHumidityFromWetBulb(const double dryBulbTemp, const double wetBulbTemp,
                                                            const double cpGas) const {
	auto const pAtm = 29.9213 / pbo, nMol = 18.02 / (g * 28.98);
	auto const psatDb = calculateSaturationPressure(dryBulbTemp);
//	auto const wSat = nMol * psatDb / (pAtm - psatDb);
	auto const psatWb = calculateSaturationPressure(wetBulbTemp);
	auto const wStar = nMol * psatWb / (pAtm - psatWb);
	auto const w = ((1061 - (1 - 0.444) * wetBulbTemp) * wStar - cpGas * (dryBulbTemp - wetBulbTemp))
	               / (1061 + (0.444 * dryBulbTemp) - wetBulbTemp);

	auto const pV = pAtm * w / (nMol + w);
	return pV / psatDb;
}

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

void PlaneData::establishFanInletOrOutletDensity(Planar & plane,
                                                 std::function<double (Planar const &, const double)> const & calcDensity,
                                                 double const mTotal, double const assumedDensity)
{
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
			plane.gasDensity = fanInletOrOutletGasDensity;
			plane.psx = fanInletOrOutletStaticPressure;
			return;
		}
	}
	throw std::runtime_error("density iteration did not converge");
}

void PlaneData::calculate(BaseGasDensity const & bgd) {
	auto const calcDensity = [&bgd] (Planar const & plane, const double psx) {
		return bgd.po * (bgd.tdo + 460) * (psx + 13.63 * plane.pbx) / ((plane.tdx + 460) * (bgd.pso + 13.63 * bgd.pbo));
	};

	flowTraverse.gasDensity = calcDensity(flowTraverse, flowTraverse.psx);
	for (auto & p : addlTravPlanes) {
		p.gasDensity = calcDensity(p, p.psx);
	}
	inletMstPlane.gasDensity = calcDensity(inletMstPlane, inletMstPlane.psx);
	outletMstPlane.gasDensity = calcDensity(outletMstPlane, outletMstPlane.psx);

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
	inletMstPlane.gasTotalPressure = inletMstPlane.psx + inletMstPlane.gasVelocityPressure;

	// step 7
	fanInletFlange.gasTotalPressure = inletMstPlane.gasTotalPressure - totalPressureLossBtwnPlanes1and4;

	// steps 8 - 13
	establishFanInletOrOutletDensity(fanInletFlange, calcDensity, mTotal, inletMstPlane.gasDensity);


	// calculating plane 2 inlet density and pressure
	outletMstPlane.gasVolumeFlowRate = mTotal / outletMstPlane.gasDensity;
	outletMstPlane.gasVelocity = outletMstPlane.gasVolumeFlowRate / outletMstPlane.area;
	outletMstPlane.gasVelocityPressure = outletMstPlane.gasDensity * std::pow(outletMstPlane.gasVelocity / 1096, 2);
	outletMstPlane.gasTotalPressure = outletMstPlane.psx + outletMstPlane.gasVelocityPressure;

	// step 7
	fanOrEvaseOutletFlange.gasTotalPressure = outletMstPlane.gasTotalPressure;
	fanOrEvaseOutletFlange.gasTotalPressure +=
			(plane5upstreamOfPlane2) ? -totalPressureLossBtwnPlanes2and5 : totalPressureLossBtwnPlanes2and5;

	// step 8 - iteration
	establishFanInletOrOutletDensity(fanOrEvaseOutletFlange, calcDensity, mTotal, outletMstPlane.gasDensity);
}

std::unordered_map<std::string, double> Fan::calculate() {
	// TODO pbx = barometric pressure, what to do if barometric pressure does vary between planes ? pg
	auto const x = (planeData.fanOrEvaseOutletFlange.gasTotalPressure - planeData.fanInletFlange.gasTotalPressure)
	         / (planeData.fanInletFlange.gasTotalPressure + 13.63 * planeData.fanInletFlange.pbx);

	double isentropicExponent = 0; // TODO what value to use for GasTypes other than Air ?
	if (baseGasDensity.gasType == BaseGasDensity::GasType::AIR) isentropicExponent = 1.4;

	// TODO pbx = barometric pressure, what to do if barometric pressure does vary between planes ? pg 61
	// TODO the calculation of z returns 0.430 instead of 0.03515
	auto const z = ((isentropicExponent - 1) / isentropicExponent)
	         * ((6362 * fanShaftPower.getFanShaftPower() / planeData.fanInletFlange.gasVolumeFlowRate)
	            / (planeData.fanInletFlange.gasTotalPressure + 13.63 * planeData.fanInletFlange.pbx));

	auto const kp = (std::log(1 + x) / x) * (z / (std::log(1 + z)));

	planeData.flowTraverse.gasTotalPressure = planeData.flowTraverse.psx + planeData.flowTraverse.gasVelocityPressure;
	for (auto & p : planeData.addlTravPlanes) {
		 p.gasTotalPressure =  p.psx +  p.gasVelocityPressure;
	}

	auto const fanTotalPressure = planeData.fanOrEvaseOutletFlange.gasTotalPressure
	                              - planeData.fanInletFlange.gasTotalPressure + fanShaftPower.getSEF();

	auto const fanStaticPressure = planeData.fanOrEvaseOutletFlange.psx
	                               - planeData.fanInletFlange.gasTotalPressure + fanShaftPower.getSEF();

	auto const staticPressureRise = planeData.fanOrEvaseOutletFlange.psx - planeData.fanInletFlange.psx + fanShaftPower.getSEF();

	auto const kpFactorRatio = calculateCompressibilityFactor(x, z, isentropicExponent);

	// corrected variables
	auto const qc = planeData.fanInletFlange.gasVolumeFlowRate * (fanRatedInfo.nc / fanRatedInfo.fanSpeed)
	                * kpFactorRatio;

	auto const ptc = fanTotalPressure * kpFactorRatio * std::pow(fanRatedInfo.nc / fanRatedInfo.fanSpeed, 2)
	                 * (fanRatedInfo.pc / planeData.fanInletFlange.gasDensity);

	auto const psc = fanStaticPressure * kpFactorRatio * std::pow(fanRatedInfo.nc / fanRatedInfo.fanSpeed, 2)
	                 * (fanRatedInfo.pc / planeData.fanInletFlange.gasDensity);

	auto const sprc = staticPressureRise * kpFactorRatio * std::pow(fanRatedInfo.nc / fanRatedInfo.fanSpeed, 2)
	                  * (fanRatedInfo.pc / planeData.fanInletFlange.gasDensity);

	auto const hc = fanShaftPower.getFanShaftPower() * kpFactorRatio
	                * std::pow(fanRatedInfo.nc / fanRatedInfo.fanSpeed, 3)
	                * (fanRatedInfo.pc / planeData.fanInletFlange.gasDensity);

	auto const kpc = kp / kpFactorRatio;

	auto const efficiency = qc * kpc / (6362 * hc);

	return {
			{"fanEfficiencyTp", ptc * efficiency * 100},
			{"fanEfficiencySp", psc * efficiency * 100},
			{"fanEfficiencySpr", sprc * efficiency * 100},
			{"Kpc", kpc},
			{"Hc", hc},
			{"Qc", qc},
			{"Ptc", ptc},
			{"Psc", psc},
			{"SPRc", sprc}
	};
}

double Fan::calculateCompressibilityFactor(const double x, const double z, const double isentropic) {
	double assumedKpOverKpc = 1.0;
	auto const & p1 = planeData.fanInletFlange;
	for (auto i = 0; i < 50; i++) {
		auto const pt1c = p1.gasTotalPressure * std::pow(fanRatedInfo.nc / fanRatedInfo.fanSpeed, 2)
		                  * (fanRatedInfo.pc / p1.gasDensity) * assumedKpOverKpc;

		// TODO how to get isentropic exponent for gas at converted conditions? section 9.4.1 step 2
		auto const zOverZc = ((pt1c + 13.63 * fanRatedInfo.pbc) / (p1.gasTotalPressure + 13.63 * p1.pbx))
		                     * (p1.gasDensity /  fanRatedInfo.pc) * std::pow(fanRatedInfo.fanSpeed / fanRatedInfo.nc, 2)
		                     * ((isentropic - 1) / isentropic) * (isentropic / (isentropic - 1));

		auto const zc = z  / zOverZc;

		auto const ln1xc = std::log(1 + x) * ((std::log(1 + zc) / std::log(1 + z))) * ((isentropic - 1) / isentropic)
		                   * (isentropic / (isentropic - 1));

		auto const xc = std::exp(ln1xc) - 1;

		auto const kpOverKpc = (z / zc) * (xc / x) * (isentropic / (isentropic - 1)) * ((isentropic - 1) / isentropic);
		if (std::abs(kpOverKpc - assumedKpOverKpc) < 0.0000001) {
			return kpOverKpc;
		}
		assumedKpOverKpc = kpOverKpc;
	}
	throw std::runtime_error("compressibility factor ratio iteration did not converge");
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
