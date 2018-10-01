/**
 * @brief Contains some of the Fan related classes
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_FAN_H
#define AMO_TOOLS_SUITE_FAN_H

#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <functional>
#include "Planar.h"
#include "FanShaftPower.h"

class FanRatedInfo;
class Planar;
class FlangePlane;
class TraversePlane;
class MstPlane;

class BaseGasDensity {
public:

	enum class GasType {
		AIR,
		STANDARDAIR,
		OTHERGAS
	};

	enum class InputType {
		DewPoint,
		RelativeHumidity,
		WetBulbTemp
	};

	// used for method 1
	BaseGasDensity(const double dryBulbTemp, const double staticPressure, const double barometricPressure,
	               const double gasDensity, const GasType gasType)
			: tdo(dryBulbTemp), pso(staticPressure), pbo(barometricPressure), po(gasDensity), gasType(gasType)
	{}

	// TODO ensure correctness
	BaseGasDensity(double const dryBulbTemp, double const staticPressure, double const barometricPressure,
	               double const relativeHumidityOrDewPoint, GasType const gasType,
	               InputType const inputType, double const specificGravity)
			: tdo(dryBulbTemp), pso(staticPressure), pbo(barometricPressure), g(specificGravity), gasType(gasType)
	{
		double const satPress = calculateSaturationPressure(tdo);
		double rh = 0;
		if (inputType == InputType::RelativeHumidity) {
			rh = relativeHumidityOrDewPoint / 100;
		} else if (inputType == InputType::DewPoint) {
			rh = calculateSaturationPressure(relativeHumidityOrDewPoint) / satPress;
		} else if (inputType == InputType::WetBulbTemp) {
			throw std::runtime_error("The wrong constructor for BaseGasDensity was called here - check inputType field");
		}

		double const rhRatio = calculateRatioRH(tdo, rh, pbo, specificGravity);
		po = (((pbo + (pso / 13.6)) - satPress * rh) * g + satPress * rh * rhRatio) / ((21.85 / (g * 29.98)) * (tdo + 459.7));
	}

	BaseGasDensity(double const dryBulbTemp, double const staticPressure, double const barometricPressure,
	               double const wetBulbTemp, GasType const gasType,
	               InputType const inputType, double const specificGravity, const double cpGas)
			: tdo(dryBulbTemp), pso(staticPressure), pbo(barometricPressure), g(specificGravity), gasType(gasType)
	{
		if (inputType != InputType::WetBulbTemp) throw std::runtime_error("The wrong constructor for BaseGasDensity was called - check inputType field");
		double const satPress = calculateSaturationPressure(tdo);
		double const rh = calculateRelativeHumidityFromWetBulb(tdo, wetBulbTemp, cpGas);
		double const rhRatio = calculateRatioRH(tdo, rh, pbo, specificGravity);
		po = (((pbo + (pso / 13.6)) - satPress * rh) * g + satPress * rh + rhRatio) / ((21.85 / (g * 29.98)) * (tdo + 459.7));
	}

	double getGasDensity() const {
		return po;
	}

private:

	double calculateSaturationPressure(double dryBulbTemp) const {
		double const C1 = -5674.5359, C2 = -0.51523058, C3 = -0.009677843, C4 = 0.00000062215701;
		double const C5 = 2.0747825 * std::pow(10, -9), C6 = -9.0484024 * std::pow(10, -13), C7 = 4.1635019, C8 = -5800.2206;
		double const C9 = -5.516256, C10 = -0.048640239, C11 = 0.000041764768, C12 = -0.000000014452093, C13 = 6.5459673;

		double const tKelvin = (dryBulbTemp + 459.67) *  0.555556;

		if (tKelvin < 273.15) {
			double const p = std::exp(C1 / tKelvin + C2 + tKelvin * C3 + tKelvin * tKelvin
			                                                           * (C4 + tKelvin * (C5 + C6 * tKelvin))
			                        + C7 * std::log(tKelvin));
			return p * (29.9216 / 101.325);
		}
		double const p = std::exp(C8 / tKelvin + C9 + tKelvin * (C10 + tKelvin * (C11 + tKelvin * C12))
		                        + C13 * std::log(tKelvin));

		return p * (29.9216 / 101.325);
	}

	double calculateRatioRH(const double dryBulbTemp, const double relativeHumidity, const double barometricPressure,
	                        const double specificGravity) const
	{
		auto const pw = (calculateSaturationPressure(dryBulbTemp) * relativeHumidity);
		return (18.02 / (specificGravity * 28.98)) * pw / (barometricPressure - pw);
	}

	double calculateRelativeHumidityFromWetBulb(const double dryBulbTemp, const double wetBulbTemp,
	                                            const double cpGas) const {
		double const pAtm = 29.9213 / pbo, nMol = 18.02 / (g * 28.98);
		double const psatDb = calculateSaturationPressure(dryBulbTemp);
		//	double const wSat = nMol * psatDb / (pAtm - psatDb);
		double const psatWb = calculateSaturationPressure(wetBulbTemp);
		double const wStar = nMol * psatWb / (pAtm - psatWb);
		double const w = ((1061 - (1 - 0.444) * wetBulbTemp) * wStar - cpGas * (dryBulbTemp - wetBulbTemp))
		               / (1061 + (0.444 * dryBulbTemp) - wetBulbTemp);

		double const pV = pAtm * w / (nMol + w);
		return pV / psatDb;
	}

	// dry bulb temp, reference static pressure, reference barometric pressure, gas density respectively
	const double tdo, pso, pbo;

	// gasDensity, specificGravity
	double po, g;
	const GasType gasType;

	friend class PlaneData;
	friend class Fan203;
};


class PlaneData {
public:
	// used to access private stuff from the nan bindings
	struct NodeBinding {
		struct Data {
			Data(const double density, const double velocity, const double volumeFlowRate, const double velocityPressure,
				 const double totalPressure)
			: gasDensity(density), gasVelocity(velocity), gasVolumeFlowRate(volumeFlowRate),
			  gasVelocityPressure(velocityPressure), gasTotalPressure(totalPressure) {}

			const double gasDensity = 0, gasVelocity = 0, gasVolumeFlowRate = 0, gasVelocityPressure = 0, gasTotalPressure = 0;
		};
		struct DataFlange : Data {
			DataFlange(const double density, const double velocity, const double volumeFlowRate, const double velocityPressure,
				 const double totalPressure, const double staticPressure)
					: Data(density, velocity, volumeFlowRate, velocityPressure, totalPressure),
					  staticPressure(staticPressure) {}

			const double staticPressure = 0;
		};
		struct Output {
			explicit Output(PlaneData const & planeData)
					: fanInletFlange(getDataFlange(planeData.fanInletFlange)),
					  fanOrEvaseOutletFlange(getDataFlange(planeData.fanOrEvaseOutletFlange)),
					  flowTraverse(getData(planeData.flowTraverse)),
					  inletMstPlane(getData(planeData.inletMstPlane)),
					  outletMstPlane(getData(planeData.outletMstPlane)),
					  addlTravPlanes(getDataTrav(planeData.addlTravPlanes))
			{}
			DataFlange fanInletFlange, fanOrEvaseOutletFlange;
			Data flowTraverse, inletMstPlane, outletMstPlane;
			std::vector<Data> addlTravPlanes;
		};

		static Output calculate(PlaneData & planeData, BaseGasDensity const & baseGasDensity) {
			planeData.calculate(baseGasDensity);
			return Output(planeData);
		}

	private:
		static Data getData(Planar const & plane) {
			return {plane.gasDensity, plane.gasVelocity, plane.gasVolumeFlowRate, plane.gasVelocityPressure, plane.gasTotalPressure};
		}
		static DataFlange getDataFlange(Planar const & plane) {
			return {plane.gasDensity, plane.gasVelocity, plane.gasVolumeFlowRate, plane.gasVelocityPressure, plane.gasTotalPressure, plane.staticPressure};
		}
		static std::vector<Data> getDataTrav(std::vector<TraversePlane> const & addlPlanes) {
			std::vector<Data> data;
			for (auto const & plane : addlPlanes) {
				data.push_back({plane.gasDensity, plane.gasVelocity, plane.gasVolumeFlowRate, plane.gasVelocityPressure, plane.gasTotalPressure});
			}
			return data;
		}
	};


	PlaneData(FlangePlane fanInletFlange, FlangePlane fanOrEvaseOutletFlange,
			  TraversePlane flowTraverse, std::vector<TraversePlane> addlTravPlanes,
			  MstPlane inletMstPlane, MstPlane outletMstPlane,
	          const double totalPressureLossBtwnPlanes1and4, const double totalPressureLossBtwnPlanes2and5,
	          bool const plane5upstreamOfPlane2)
			: fanInletFlange(std::move(fanInletFlange)), fanOrEvaseOutletFlange(std::move(fanOrEvaseOutletFlange)), flowTraverse(std::move(flowTraverse)),
			  addlTravPlanes(std::move(addlTravPlanes)), inletMstPlane(std::move(inletMstPlane)), outletMstPlane(std::move(outletMstPlane)),
			  plane5upstreamOfPlane2(plane5upstreamOfPlane2),
			  totalPressureLossBtwnPlanes1and4(totalPressureLossBtwnPlanes1and4),
			  totalPressureLossBtwnPlanes2and5(totalPressureLossBtwnPlanes2and5)
	{}

private:

	void establishFanInletOrOutletDensity(Planar & plane,
	                                      std::function<double (Planar const &, const double)> const & calcDensity,
	                                      double const mTotal, double const assumedDensity)
	{
		double calculatedDensity = assumedDensity;
		for (auto i = 0; i < 50; i++) {
			plane.gasDensity = calculatedDensity;
			plane.gasVolumeFlowRate = mTotal / plane.gasDensity;
			plane.gasVelocity = plane.gasVolumeFlowRate / plane.area;
			plane.gasVelocityPressure = plane.gasDensity * std::pow(plane.gasVelocity / 1096, 2);
			double fanInletOrOutletStaticPressure = plane.gasTotalPressure - plane.gasVelocityPressure;
			double fanInletOrOutletGasDensity = calcDensity(plane, fanInletOrOutletStaticPressure);

			calculatedDensity = fanInletOrOutletGasDensity;
			if (std::abs(fanInletOrOutletGasDensity - plane.gasDensity) < 0.0001) {
				plane.gasDensity = fanInletOrOutletGasDensity;
				plane.staticPressure = fanInletOrOutletStaticPressure;
				return;
			}
		}
		throw std::runtime_error("In PlaneData::establishFanInletOrOutletDensity - density iteration did not converge");
	}

	void calculate(BaseGasDensity const & bgd) {
		auto const calcDensity = [&bgd] (Planar const & plane, const double psx) {
			return bgd.po * (bgd.tdo + 460) * (psx + 13.63 * plane.barometricPressure) / ((plane.dryBulbTemperature + 460) * (bgd.pso + 13.63 * bgd.pbo));
		};

		flowTraverse.gasDensity = calcDensity(flowTraverse, flowTraverse.staticPressure);
		for (auto & p : addlTravPlanes) {
			p.gasDensity = calcDensity(p, p.staticPressure);
		}
		inletMstPlane.gasDensity = calcDensity(inletMstPlane, inletMstPlane.staticPressure);
		outletMstPlane.gasDensity = calcDensity(outletMstPlane, outletMstPlane.staticPressure);

		flowTraverse.gasVelocity = 1096 * std::sqrt(flowTraverse.pv3 / flowTraverse.gasDensity);
		flowTraverse.gasVolumeFlowRate = flowTraverse.gasVelocity * flowTraverse.area;

		double mTotal = flowTraverse.gasDensity * flowTraverse.gasVolumeFlowRate;
		for (auto & plane : addlTravPlanes) {
			plane.gasVelocity = 1096 * std::sqrt(plane.pv3 / plane.gasDensity);
			plane.gasVolumeFlowRate = plane.gasVelocity * plane.area;
			mTotal += plane.gasDensity * plane.gasVolumeFlowRate;
		}

		inletMstPlane.gasVolumeFlowRate = mTotal / inletMstPlane.gasDensity;
		inletMstPlane.gasVelocity = inletMstPlane.gasVolumeFlowRate / inletMstPlane.area;
		inletMstPlane.gasVelocityPressure = inletMstPlane.gasDensity * std::pow((inletMstPlane.gasVelocity / 1096), 2);
		inletMstPlane.gasTotalPressure = inletMstPlane.staticPressure + inletMstPlane.gasVelocityPressure;

		// step 7
		fanInletFlange.gasTotalPressure = inletMstPlane.gasTotalPressure - totalPressureLossBtwnPlanes1and4;

		// steps 8 - 13
		establishFanInletOrOutletDensity(fanInletFlange, calcDensity, mTotal, inletMstPlane.gasDensity);

		// calculating plane 2 inlet density and pressure
		outletMstPlane.gasVolumeFlowRate = mTotal / outletMstPlane.gasDensity;
		outletMstPlane.gasVelocity = outletMstPlane.gasVolumeFlowRate / outletMstPlane.area;
		outletMstPlane.gasVelocityPressure = outletMstPlane.gasDensity * std::pow(outletMstPlane.gasVelocity / 1096, 2);
		outletMstPlane.gasTotalPressure = outletMstPlane.staticPressure + outletMstPlane.gasVelocityPressure;

		// step 7
		fanOrEvaseOutletFlange.gasTotalPressure = outletMstPlane.gasTotalPressure;
		fanOrEvaseOutletFlange.gasTotalPressure +=
				(plane5upstreamOfPlane2) ? -totalPressureLossBtwnPlanes2and5 : totalPressureLossBtwnPlanes2and5;

		// step 8 - iteration
		establishFanInletOrOutletDensity(fanOrEvaseOutletFlange, calcDensity, mTotal, outletMstPlane.gasDensity);
	}

	FlangePlane fanInletFlange, fanOrEvaseOutletFlange;
	TraversePlane flowTraverse;
	std::vector<TraversePlane> addlTravPlanes;
	MstPlane inletMstPlane;
	MstPlane outletMstPlane;

	bool const plane5upstreamOfPlane2;
	const double totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5;

	friend class Fan203;
	friend struct NodeBinding;
};


class Fan203 {
public:
	Fan203(FanRatedInfo fanRatedInfo, PlaneData planeData, BaseGasDensity baseGasDensity, FanShaftPower fanShaftPower)
			: fanRatedInfo(fanRatedInfo), planeData(std::move(planeData)),
			  baseGasDensity(baseGasDensity), fanShaftPower(fanShaftPower)
	{
		this->planeData.calculate(this->baseGasDensity);
	};

	struct Results {
		Results(const double kpc, const double power, const double flow,
		        const double pressureTotal, const double pressureStatic,
		        const double staticPressureRise)
				: kpc(kpc), power(power),
				  flow(flow), pressureTotal(pressureTotal),
				  pressureStatic(pressureStatic), staticPressureRise(staticPressureRise)
		{}
		const double kpc, power, flow, pressureTotal;
		const double pressureStatic, staticPressureRise;
	};

	struct Output {
		Output(const double fanEfficiencyTotalPressure, const double fanEfficiencyStaticPressure,
		       const double fanEfficiencyStaticPressureRise, const Results asTested, const Results converted)
				: fanEfficiencyTotalPressure(fanEfficiencyTotalPressure), fanEfficiencyStaticPressure(fanEfficiencyStaticPressure),
				  fanEfficiencyStaticPressureRise(fanEfficiencyStaticPressureRise), asTested(asTested), converted(converted)
		{}

		const double fanEfficiencyTotalPressure, fanEfficiencyStaticPressure, fanEfficiencyStaticPressureRise;
		const Results asTested, converted;
	};

	Output calculate() {
		// TODO barometricPressure = barometric pressure, what to do if barometric pressure does vary between planes ? pg
		double const x = (planeData.fanOrEvaseOutletFlange.gasTotalPressure - planeData.fanInletFlange.gasTotalPressure)
		                 / (planeData.fanInletFlange.gasTotalPressure + 13.63 * planeData.fanInletFlange.barometricPressure);

		double isentropicExponent = 1.4; // TODO what value to use for GasTypes other than Air ?
		if (baseGasDensity.gasType == BaseGasDensity::GasType::AIR) isentropicExponent = 1.4;

		// TODO barometricPressure = barometric pressure, what to do if barometric pressure does vary between planes ? pg 61
		double const z = ((isentropicExponent - 1) / isentropicExponent)
		                 * ((6362 * fanShaftPower.getFanPowerInput() / planeData.fanInletFlange.gasVolumeFlowRate)
		                    / (planeData.fanInletFlange.gasTotalPressure + 13.63 * planeData.fanInletFlange.barometricPressure));

		double const kp = (std::log(1 + x) / x) * (z / (std::log(1 + z)));

		planeData.flowTraverse.gasTotalPressure =
				planeData.flowTraverse.staticPressure + planeData.flowTraverse.gasVelocityPressure;
		for (auto &p : planeData.addlTravPlanes) {
			p.gasTotalPressure = p.staticPressure + p.gasVelocityPressure;
		}

		double const fanTotalPressure = planeData.fanOrEvaseOutletFlange.gasTotalPressure
		                                - planeData.fanInletFlange.gasTotalPressure + fanShaftPower.getSEF();

		double const fanStaticPressure = planeData.fanOrEvaseOutletFlange.staticPressure
		                                 - planeData.fanInletFlange.gasTotalPressure + fanShaftPower.getSEF();

		double const staticPressureRise =
				planeData.fanOrEvaseOutletFlange.staticPressure - planeData.fanInletFlange.staticPressure +
				fanShaftPower.getSEF();

		double const kpFactorRatio = calculateCompressibilityFactor(x, z, isentropicExponent);

		// corrected variables
		double const qc = planeData.fanInletFlange.gasVolumeFlowRate * (fanRatedInfo.fanSpeedCorrected / fanRatedInfo.fanSpeed)
		                  * kpFactorRatio;

		double const ptc = fanTotalPressure * kpFactorRatio * std::pow(fanRatedInfo.fanSpeedCorrected / fanRatedInfo.fanSpeed, 2)
		                   * (fanRatedInfo.densityCorrected / planeData.fanInletFlange.gasDensity);

		double const psc = fanStaticPressure * kpFactorRatio * std::pow(fanRatedInfo.fanSpeedCorrected / fanRatedInfo.fanSpeed, 2)
		                   * (fanRatedInfo.densityCorrected / planeData.fanInletFlange.gasDensity);

		double const sprc =
				staticPressureRise * kpFactorRatio * std::pow(fanRatedInfo.fanSpeedCorrected / fanRatedInfo.fanSpeed, 2)
				* (fanRatedInfo.densityCorrected / planeData.fanInletFlange.gasDensity);

		double const hc = fanShaftPower.getFanPowerInput() * kpFactorRatio
		                  * std::pow(fanRatedInfo.fanSpeedCorrected / fanRatedInfo.fanSpeed, 3)
		                  * (fanRatedInfo.densityCorrected / planeData.fanInletFlange.gasDensity);

		double const kpc = kp / kpFactorRatio;

		double const efficiency = qc * kpc / (6362 * hc);

		return {
				ptc * efficiency * 100, psc * efficiency * 100, sprc * efficiency * 100,
				{
						kpFactorRatio, fanShaftPower.getFanPowerInput(), planeData.fanInletFlange.gasVolumeFlowRate, fanTotalPressure,
						fanStaticPressure, staticPressureRise
				},
				{
						kpc, hc, qc, ptc, psc, sprc
				}
		};
	}

private:

	double calculateCompressibilityFactor(const double x, const double z, const double isentropic) {
		double assumedKpOverKpc = 1.0;
		auto const & p1 = planeData.fanInletFlange;
		for (auto i = 0; i < 50; i++) {
			double const pt1c = p1.gasTotalPressure * std::pow(fanRatedInfo.fanSpeedCorrected / fanRatedInfo.fanSpeed, 2)
			                    * (fanRatedInfo.densityCorrected / p1.gasDensity) * assumedKpOverKpc;

			// TODO how to get isentropic exponent for gas at converted conditions? section 9.4.1 step 2
			double const zOverZc = ((pt1c + 13.63 * fanRatedInfo.pressureBarometricCorrected) / (p1.gasTotalPressure + 13.63 * p1.barometricPressure))
			                       * (p1.gasDensity /  fanRatedInfo.densityCorrected) * std::pow(fanRatedInfo.fanSpeed / fanRatedInfo.fanSpeedCorrected, 2)
			                       * ((isentropic - 1) / isentropic) * (isentropic / (isentropic - 1));

			double const zc = z  / zOverZc;

			double const ln1xc = std::log(1 + x) * ((std::log(1 + zc) / std::log(1 + z))) * ((isentropic - 1) / isentropic)
			                     * (isentropic / (isentropic - 1));

			double const xc = std::exp(ln1xc) - 1;

			double const kpOverKpc = (z / zc) * (xc / x) * (isentropic / (isentropic - 1)) * ((isentropic - 1) / isentropic);
			if (std::abs(kpOverKpc - assumedKpOverKpc) < 0.0000001) {
				return kpOverKpc;
			}
			assumedKpOverKpc = kpOverKpc;
		}
		throw std::runtime_error("compressibility factor ratio iteration did not converge");
	}

	FanRatedInfo const fanRatedInfo;
	PlaneData planeData;
	BaseGasDensity const baseGasDensity;
	FanShaftPower const fanShaftPower;
};

#endif //AMO_TOOLS_SUITE_FAN_H
