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

	Planar(const double circularDuctDiameter, const double dryBulbTemp, const double barometricPressure) :
			shape(Shape::CIRCULAR), dryBulbTemp(dryBulbTemp), barometricPressure(barometricPressure),
			area(((3.14159265358979 / 4) * (circularDuctDiameter * circularDuctDiameter)) / 144.0)
	{}

	Planar(const double rectLength, const double rectWidth, const double dryBulbTemp, const double barometricPressure) :
			rectLength(rectLength), rectWidth(rectWidth), shape(Shape::RECTANGULAR), dryBulbTemp(dryBulbTemp),
			barometricPressure(barometricPressure), area((rectLength * rectWidth) / 144.0)
	{}

	Planar(const double rectLength, const double rectWidth, unsigned const noInletBoxes, const double dryBulbTemp,
	       const double barometricPressure) :
			rectLength(rectLength), rectWidth(rectWidth), shape(Shape::RECTANGULAR), dryBulbTemp(dryBulbTemp),
			barometricPressure(barometricPressure), area((rectLength * rectWidth * noInletBoxes) / 144.0)
	{}

	enum class Shape {
		RECTANGULAR,
		CIRCULAR
	};

	const double rectLength = 0, rectWidth = 0, dryBulbTemp = 0, barometricPressure = 0;
	const unsigned noInletBoxes = 0; // TODO should delete this variable along with all others besides area?
	const Shape shape;
	double area = 0;
};

class FanInletFlange : private Planar {
public:
	FanInletFlange(const double circularDuctDiameter, const double dryBulbTemp, const double barometricPressure)
			: Planar(circularDuctDiameter, dryBulbTemp, barometricPressure) {}

	FanInletFlange(const double rectLength, const double rectWidth, const double dryBulbTemp,
	               const double barometricPressure) : Planar(rectLength, rectWidth, dryBulbTemp, barometricPressure) {}

	FanInletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	               const double dryBulbTemp, const double barometricPressure)
			: Planar(rectLength, rectWidth, noInletBoxes, dryBulbTemp, barometricPressure)
	{}
};

class FanOrEvaseOutletFlange : private Planar {
public:
	FanOrEvaseOutletFlange(const double circularDuctDiameter, const double dryBulbTemp, const double barometricPressure)
			: Planar(circularDuctDiameter, dryBulbTemp, barometricPressure) {}

	FanOrEvaseOutletFlange(const double rectLength, const double rectWidth, const double dryBulbTemp,
	               const double barometricPressure) : Planar(rectLength, rectWidth, dryBulbTemp, barometricPressure) {}

	FanOrEvaseOutletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	               const double dryBulbTemp, const double barometricPressure)
			: Planar(rectLength, rectWidth, noInletBoxes, dryBulbTemp, barometricPressure)
	{}
};

class FlowTraverse : private Planar {
public:
	FlowTraverse(const double circularDuctDiameter, const double dryBulbTemp, const double barometricPressure,
	             const double staticPressure)
			: Planar(circularDuctDiameter, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	FlowTraverse(const double rectLength, const double rectWidth, const double dryBulbTemp,
	                       const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	FlowTraverse(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	                       const double dryBulbTemp, const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, noInletBoxes, dryBulbTemp, barometricPressure), staticPressure(staticPressure)
	{}

private:
	const double staticPressure;
};

class AddlTravPlane : private Planar {
public:
	AddlTravPlane(const double circularDuctDiameter, const double dryBulbTemp, const double barometricPressure,
	             const double staticPressure)
			: Planar(circularDuctDiameter, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	AddlTravPlane(const double rectLength, const double rectWidth, const double dryBulbTemp,
	             const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	AddlTravPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	             const double dryBulbTemp, const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, noInletBoxes, dryBulbTemp, barometricPressure), staticPressure(staticPressure)
	{}

private:
	const double staticPressure;
};

class InletMstPlane : private Planar {
public:
	InletMstPlane(const double circularDuctDiameter, const double dryBulbTemp, const double barometricPressure,
	             const double staticPressure)
			: Planar(circularDuctDiameter, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	InletMstPlane(const double rectLength, const double rectWidth, const double dryBulbTemp,
	             const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	InletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	             const double dryBulbTemp, const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, noInletBoxes, dryBulbTemp, barometricPressure), staticPressure(staticPressure)
	{}

private:
	const double staticPressure;
};

class OutletMstPlane : private Planar {
public:
	OutletMstPlane(const double circularDuctDiameter, const double dryBulbTemp, const double barometricPressure,
	             const double staticPressure)
			: Planar(circularDuctDiameter, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	OutletMstPlane(const double rectLength, const double rectWidth, const double dryBulbTemp,
	             const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, dryBulbTemp, barometricPressure), staticPressure(staticPressure) {}

	OutletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
	             const double dryBulbTemp, const double barometricPressure, const double staticPressure)
			: Planar(rectLength, rectWidth, noInletBoxes, dryBulbTemp, barometricPressure), staticPressure(staticPressure)
	{}

private:
	const double staticPressure;
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
	const double barometricPressure = 0; // TODO should this be here? barometric pres. in the example is individually inputted


	FanInletFlange fanInletFlange;
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange;
	FlowTraverse flowTraverse;
	std::vector<AddlTravPlane> addlTravPlanes;
	InletMstPlane inletMstPlane;
	OutletMstPlane outletMstPlane;
};

class VelocityPressureTraverseData {
public:
	enum class TubeType {
		STANDARD,
		STYPE
	};

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
	double pv3 = 0, percent75Rule = 0;

//	const unsigned noTraverseHoles, noInsertionPoints; // TODO these need to go away, these dimensions will almost surely be defined in the UI, all we need is a vector here
	std::vector< std::vector< double > > traverseHoleData;
};


class Fan {
public:
	Fan(FanRatedInfo & fanRatedInfo, PlaneData & planeData, VelocityPressureTraverseData & velocityPressureTraverseData)
			: fanRatedInfo(fanRatedInfo), planeData(std::move(planeData)),
			  velocityPressureTraverseData(std::move(velocityPressureTraverseData))
	{};

private:
	FanRatedInfo const fanRatedInfo;
	PlaneData const planeData;
	VelocityPressureTraverseData const velocityPressureTraverseData;
};

#endif //AMO_TOOLS_SUITE_FAN_H
