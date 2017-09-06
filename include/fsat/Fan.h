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

	Planar(const double circularDuctDiameter, const double tdx, const double pbx) :
			shape(Shape::CIRCULAR), tdx(tdx), pbx(pbx),
			area(((3.14159265358979 / 4) * (circularDuctDiameter * circularDuctDiameter)) / 144.0)
	{}

	Planar(const double rectLength, const double rectWidth, const double tdx, const double pbx) :
			shape(Shape::RECTANGULAR), tdx(tdx),
			pbx(pbx), area((rectLength * rectWidth) / 144.0)
	{}

	Planar(const double rectLength, const double rectWidth, unsigned const noInletBoxes, const double tdx,
	       const double pbx) :
			shape(Shape::RECTANGULAR), tdx(tdx),
			pbx(pbx), area((rectLength * rectWidth * noInletBoxes) / 144.0)
	{}

	enum class Shape {
		RECTANGULAR,
		CIRCULAR
	};

//	const double rectLength = 0, rectWidth = 0, dryBulbTemp = 0, pbx = 0;
//	const unsigned noInletBoxes = 0; // TODO should delete this variable along with all others besides area?

//	where tdx = dryBulbTemperature and pbx = barometric pressure
	const double tdx, pbx;
	const Shape shape; // TODO should probably delete this one too
	double area = 0, gasDensity = 0;

	friend class PlaneData;
};

class FanInletFlange : private Planar {
public:
	FanInletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
			: Planar(circularDuctDiameter, tdx, pbx) {}

	FanInletFlange(const double rectLength, const double rectWidth, const double tdx, const double pbx)
			: Planar(rectLength, rectWidth, tdx, pbx) {}

	FanInletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	               const double tdx, const double pbx)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx)
	{}
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

class FlowTraverse : public Planar {
public:
	FlowTraverse(const double circularDuctDiameter, const double tdx, const double pbx,
	             const double psx)
			: Planar(circularDuctDiameter, tdx, pbx), psx(psx) {}

	FlowTraverse(const double rectLength, const double rectWidth, const double tdx,
	                       const double pbx, const double psx)
			: Planar(rectLength, rectWidth, tdx, pbx), psx(psx) {}

	FlowTraverse(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	                       const double tdx, const double pbx, const double psx)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx), psx(psx)
	{}

	double getPsx() { return psx; }

private:
	const double psx;
};

class AddlTravPlane : public Planar {
public:
	AddlTravPlane(const double circularDuctDiameter, const double tdx, const double pbx,
	             const double psx)
			: Planar(circularDuctDiameter, tdx, pbx), psx(psx) {}

	AddlTravPlane(const double rectLength, const double rectWidth, const double tdx,
	             const double pbx, const double psx)
			: Planar(rectLength, rectWidth, tdx, pbx), psx(psx) {}

	AddlTravPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	             const double tdx, const double pbx, const double psx)
			: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx), psx(psx)
	{}

	double getPsx() { return psx; }

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
	          OutletMstPlane & outletMstPlane, bool const variationsInPlanarBarometricPressure, bool const estimatePlaneTemp)
			: fanInletFlange(fanInletFlange), fanOrEvaseOutletFlange(fanOrEvaseOutletFlange), flowTraverse(flowTraverse),
			  addlTravPlanes(addlTravPlanes), inletMstPlane(inletMstPlane), outletMstPlane(outletMstPlane),
			  variationsInPlanarBarometricPressure(variationsInPlanarBarometricPressure), estimatePlaneTemp(estimatePlaneTemp) {}

private:
	bool const variationsInPlanarBarometricPressure, estimatePlaneTemp;

	void calculatePlanes3through5Densities(BaseGasDensity & bgd) {
		auto const calcDensity = [&bgd] (Planar & plane, const double psx) {
			plane.gasDensity = bgd.po * (bgd.tdo + 460) * (psx + 13.63 * plane.pbx)
			                   / ((plane.tdx + 460) * (bgd.pso + 13.63 * bgd.pbo));
		};

		calcDensity(flowTraverse, flowTraverse.getPsx());

		for (auto & plane : addlTravPlanes) {
			calcDensity(plane, plane.getPsx());
		}

		calcDensity(inletMstPlane, inletMstPlane.getPsx());
		calcDensity(outletMstPlane, outletMstPlane.getPsx());
	}

	FanInletFlange fanInletFlange;
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange;
	FlowTraverse flowTraverse;
	std::vector<AddlTravPlane> addlTravPlanes;
	InletMstPlane inletMstPlane;
	OutletMstPlane outletMstPlane;

	friend class Fan;
};

class VelocityPressureTraverseData {
public:
	enum class TubeType {
		STANDARD,
		STYPE
	};

	// TODO pretty sure the constructor body here needs to be repeated for 3+ planes w/ different input data
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

private:
	const TubeType pitotTubeType;
	const double pitotTubeCoefficient;
	double pv3, percent75Rule;

//	const unsigned noTraverseHoles, noInsertionPoints; // TODO these need to go away, these dimensions will almost surely be defined in the UI, all we need is a vector here
	std::vector< std::vector< double > > traverseHoleData;
};


class Fan {
public:
	Fan(FanRatedInfo & fanRatedInfo, PlaneData & planeData, VelocityPressureTraverseData & velocityPressureTraverseData,
	    BaseGasDensity & baseGasDensity)
			: fanRatedInfo(fanRatedInfo), planeData(std::move(planeData)),
			  velocityPressureTraverseData(std::move(velocityPressureTraverseData)), baseGasDensity(baseGasDensity)
	{
		this->planeData.calculatePlanes3through5Densities(baseGasDensity);
	};

private:
	FanRatedInfo const fanRatedInfo;
	PlaneData planeData;
	VelocityPressureTraverseData const velocityPressureTraverseData;
	BaseGasDensity const baseGasDensity;
};

#endif //AMO_TOOLS_SUITE_FAN_H
