#ifndef AMO_TOOLS_SUITE_FAN_H
#define AMO_TOOLS_SUITE_FAN_H

#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>

// TODO consider deleting class member variables rectLength, width, diameter etc if they are used ONLY in area calculations
// TODO deletions are looking more likely
class Planar {
protected:

	Planar(const double circularDuctDiameter, const double tdx, const double pbx)
			: tdx(tdx), pbx(pbx), area(((3.14159265358979 / 4) * (circularDuctDiameter * circularDuctDiameter)) / 144.0)
	{}

	Planar(const double rectLength, const double rectWidth, const double tdx, const double pbx)
			: tdx(tdx), pbx(pbx), area((rectLength * rectWidth) / 144.0)
	{}

	Planar(const double rectLength, const double rectWidth, unsigned const noInletBoxes, const double tdx,
	       const double pbx)
			: tdx(tdx), pbx(pbx), area((rectLength * rectWidth * noInletBoxes) / 144.0)
	{}

//	where tdx = dryBulbTemperature and pbx = barometric pressure
	const double tdx, pbx;
	double area = 0, gasDensity = 0, gasVelocity = 0, gasVolumeFlowRate = 0, gasVelocityPressure = 0, gasTotalPressure = 0;

	friend class PlaneData;
};

class FanInletFlange : public Planar {
public:
	FanInletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
			: Planar(circularDuctDiameter, tdx, pbx) {}

	FanInletFlange(const double rectLength, const double rectWidth, const double tdx, const double pbx)
			: Planar(rectLength, rectWidth, tdx, pbx) {}

	FanInletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	               const double tdx, const double pbx)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx)
	{}

private:

	// TODO consider getting rid of these vairables if they are unused later in the calcs, could just be localized
	double fanInletStaticPressure = 0, fanInletGasDensity = 0;
	friend class PlaneData;
};

class FanOrEvaseOutletFlange : private Planar {
public:
	FanOrEvaseOutletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
			: Planar(circularDuctDiameter, tdx, pbx) {}

	FanOrEvaseOutletFlange(const double rectLength, const double rectWidth, const double tdx,
	               const double pbx) : Planar(rectLength, rectWidth, tdx, pbx) {}

	FanOrEvaseOutletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	               const double tdx, const double pbx)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx)
	{}
};

// to be inherited by planes 3 and 3a, 3b
class VelocityPressureTraverseData {
public:
	enum class TubeType {
		STANDARD,
		STYPE
	};

protected:

	// protected constructor to be used only during the construction of its derived classes
	VelocityPressureTraverseData(const TubeType pitotTubeType, const double pitotTubeCoefficient,
	                             std::vector< std::vector< double > > & traverseHoleData)
			: pitotTubeType(pitotTubeType), pitotTubeCoefficient(pitotTubeCoefficient),
			  traverseHoleData(std::move(traverseHoleData))
	{
		auto maxPv3r = 0.0;
		auto sumPv3r = 0.0;
		for (auto & row : this->traverseHoleData) {
			for (auto & val : row) {
				if (val <= 0) {
					val = 0;
					continue;
				}
				val *= std::pow(pitotTubeCoefficient, 2);
				if (val > maxPv3r) maxPv3r = val;
				sumPv3r += std::sqrt(val);
			}
		}

		pv3 = std::pow(sumPv3r / (this->traverseHoleData.size() * this->traverseHoleData[0].size()), 2);
		size_t count = 0;
		for (auto & row : this->traverseHoleData) {
			for (auto & val : row) {
				if (val > (0.1 * maxPv3r)) count++;
			}
		}

		percent75Rule = count / static_cast<double>(this->traverseHoleData.size() * this->traverseHoleData[0].size());
	};

	const TubeType pitotTubeType;
	const double pitotTubeCoefficient;
	double pv3 = 0, percent75Rule = 0;

	std::vector< std::vector< double > > traverseHoleData;

	friend class PlaneData;
};

class FlowTraverse : public Planar, public VelocityPressureTraverseData {
public:
	FlowTraverse(const double circularDuctDiameter, const double tdx, const double pbx,
	             const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
	             std::vector< std::vector< double > > & traverseHoleData)
			: Planar(circularDuctDiameter, tdx, pbx),
			  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData),
			  psx(psx)
	{}

	FlowTraverse(const double rectLength, const double rectWidth, const double tdx,
	                       const double pbx, const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
	             std::vector< std::vector< double > > & traverseHoleData)
			: Planar(rectLength, rectWidth, tdx, pbx),
			  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData),
			  psx(psx)
	{}

	FlowTraverse(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	                       const double tdx, const double pbx, const double psx, const TubeType tubeType,
	             const double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx),
			  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData),
			  psx(psx)
	{}

	double getPsx() { return psx; }

private:
	const double psx;
};

class AddlTravPlane : public Planar, public VelocityPressureTraverseData {
public:
	AddlTravPlane(const double circularDuctDiameter, const double tdx, const double pbx,
	             const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
	             std::vector< std::vector< double > > & traverseHoleData)
			: Planar(circularDuctDiameter, tdx, pbx),
			  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData),
			  psx(psx)
	{}

	AddlTravPlane(const double rectLength, const double rectWidth, const double tdx,
	             const double pbx, const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
	             std::vector< std::vector< double > > & traverseHoleData)
			: Planar(rectLength, rectWidth, tdx, pbx),
			  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData),
			  psx(psx)
	{}

	AddlTravPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	             const double tdx, const double pbx, const double psx, const TubeType tubeType,
	             const double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx),
			  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData),
			  psx(psx)
	{}

	double getPsx() const { return psx; }

private:
	const double psx;
};

class InletMstPlane : public Planar {
public:
	InletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx,
	             const double psx)
			: Planar(circularDuctDiameter, tdx, pbx), psx(psx) {}

	InletMstPlane(const double rectLength, const double rectWidth, const double tdx,
	             const double pbx, const double psx)
			: Planar(rectLength, rectWidth, tdx, pbx), psx(psx) {}

	InletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	             const double tdx, const double pbx, const double psx)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx), psx(psx)
	{}

	double getPsx() { return psx; }

private:
	const double psx;
};

class OutletMstPlane : public Planar {
public:
	OutletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx,
	             const double psx)
			: Planar(circularDuctDiameter, tdx, pbx), psx(psx) {}

	OutletMstPlane(const double rectLength, const double rectWidth, const double tdx,
	             const double pbx, const double psx)
			: Planar(rectLength, rectWidth, tdx, pbx), psx(psx) {}

	OutletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	             const double tdx, const double pbx, const double psx)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx), psx(psx)
	{}

	double getPsx() { return psx; }

private:
	const double psx;
};


class FanRatedInfo {
public:
	enum class DriveType {
		DIRECT,
		BELT
	};

	// this currently does not take the field SystemDamperPosition, as it is used "only for reference purposes" as per
	// page 8 in the algorithm document
	FanRatedInfo(double const fanDamperPosition, double const fanSpeed, double const motorSpeed, double const nc,
	             double const pc, double const pbc, DriveType const driveType) :
			fanDamperPosition(fanDamperPosition / 100.0), fanSpeed(fanSpeed), motorSpeed(motorSpeed),
			nc(nc), pc(pc), pbc(pbc), driveType(driveType)
	{};

private:
	double const fanDamperPosition, fanSpeed, motorSpeed, nc, pc, pbc;
	DriveType const driveType;

};


class BaseGasDensity {
public:

	enum class GasType {
		AIR,
		STANDARDAIR,
		OTHERGAS
	};

	// used for method 1
	BaseGasDensity(const double tdo, const double pso, const double pbo, const double po)
			: tdo(tdo), pso(pso), pbo(pbo), po(po) {}

	// TODO incomplete, po (density) shouldn't be an input in either of the constructors below bc it needs to be calculated
//	// used for method 2 without wet bulb temperature as "data to establish gas humidity"
//	BaseGasDensity(const double tdo, const double pso, const double pbo, const double po, const double g,
//	               const double two)
//			: tdo(tdo), pso(pso), pbo(pbo), po(po), g(g), two(two) {}

//	// used for method 2 with wet bulb temp being used for "data to establish gas humidity"
//	BaseGasDensity(const double tdo, const double pso, const double pbo, const double po, const double g,
//	               const double percentRH)
//			: tdo(tdo), pso(pso), pbo(pbo), po(po), g(g), percentRH(percentRH) {}

private:

//	double calcWaterVaporDensityToDryAirDensityRatio(const double pws) {
//		return 0.6214 + (percentRH * std::pow(pws, 1 / 1.42)) / 1130;
//	}
//
//	double calcBaseGasDensity(const double p, const double pws) {
//		return ((p - pws * percentRH) * g + pws * percentRH * calcWaterVaporDensityToDryAirDensityRatio(pws))
//		       / (0.7543 * (tdo + 459.7));
//	}

	const double tdo, pso, pbo, po;

	friend class PlaneData;

//	const double g = 0, two = 0, percentRH = 0, tdp = 0;
};


class PlaneData {
public:
	// TODO add "global" stuff for planes here maybe.
	PlaneData(FanInletFlange & fanInletFlange, FanOrEvaseOutletFlange & fanOrEvaseOutletFlange,
	          FlowTraverse & flowTraverse, std::vector<AddlTravPlane> & addlTravPlanes, InletMstPlane & inletMstPlane,
	          OutletMstPlane & outletMstPlane, bool const variationsInPlanarBarometricPressure,
	          bool const estimatePlaneTemp, const double totalPressureLossBtwnPlanes1and4, const double totalPressureLossBtwnPlanes2and5)
			: fanInletFlange(fanInletFlange), fanOrEvaseOutletFlange(fanOrEvaseOutletFlange), flowTraverse(flowTraverse),
			  addlTravPlanes(addlTravPlanes), inletMstPlane(inletMstPlane), outletMstPlane(outletMstPlane),
			  variationsInPlanarBarometricPressure(variationsInPlanarBarometricPressure), estimatePlaneTemp(estimatePlaneTemp),
			  totalPressureLossBtwnPlanes1and4(totalPressureLossBtwnPlanes1and4), totalPressureLossBtwnPlanes2and5(totalPressureLossBtwnPlanes2and5) {}

private:
//	void calculatePlanes3through5density(BaseGasDensity & bgd) {
//		auto const calcDensity = [&bgd] (Planar & plane, const double psx) {
//			plane.gasDensity = bgd.po * (bgd.tdo + 460) * (psx + 13.63 * plane.pbx)
//			                   / ((plane.tdx + 460) * (bgd.pso + 13.63 * bgd.pbo));
//		};
//
//		calcDensity(flowTraverse, flowTraverse.getPsx());
//
//		for (auto & plane : addlTravPlanes) {
//			calcDensity(plane, plane.getPsx());
//		}
//
//		calcDensity(inletMstPlane, inletMstPlane.getPsx());
//		calcDensity(outletMstPlane, outletMstPlane.getPsx());
//	}

	void calculate(BaseGasDensity const & bgd) {
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

		// step 8
		fanInletFlange.gasDensity = inletMstPlane.gasDensity;

		// step 9
		fanInletFlange.gasVolumeFlowRate = mTotal / fanInletFlange.gasDensity;
		fanInletFlange.gasVelocity = fanInletFlange.gasVolumeFlowRate / fanInletFlange.area;
		fanInletFlange.gasVelocityPressure = fanInletFlange.gasDensity * std::pow(fanInletFlange.gasVelocity / 1096, 2);
		fanInletFlange.fanInletStaticPressure = fanInletFlange.gasTotalPressure - fanInletFlange.gasVelocityPressure;
		fanInletFlange.fanInletGasDensity = calcDensity(fanInletFlange, fanInletFlange.fanInletStaticPressure);

		// step 14 - iteration begins
		// stuff
	}

	FanInletFlange fanInletFlange;
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange;
	FlowTraverse flowTraverse;
	std::vector<AddlTravPlane> addlTravPlanes;
	InletMstPlane inletMstPlane;
	OutletMstPlane outletMstPlane;

	bool const variationsInPlanarBarometricPressure, estimatePlaneTemp;
	const double totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5;

	friend class Fan;
};



class Fan {
public:
	Fan(FanRatedInfo & fanRatedInfo, PlaneData & planeData, BaseGasDensity & baseGasDensity)
			: fanRatedInfo(fanRatedInfo), planeData(std::move(planeData)), baseGasDensity(baseGasDensity)
	{
//		this->planeData.calculatePlanes3through5density(baseGasDensity);
		this->planeData.calculate(this->baseGasDensity);
	};

private:
	FanRatedInfo const fanRatedInfo;
	PlaneData planeData;
	BaseGasDensity const baseGasDensity;
};

#endif //AMO_TOOLS_SUITE_FAN_H
