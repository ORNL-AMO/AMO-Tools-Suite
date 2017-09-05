#ifndef AMO_TOOLS_SUITE_FAN_H
#define AMO_TOOLS_SUITE_FAN_H

#include <string>
#include <unordered_map>
#include <cmath>

// TODO consider deleting class member variables rectLength, width, diameter etc if they are used ONLY in area calculations
// no need to have them sitting around if everything we need comes from the constructor input.
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
	// TODO add "global" stuff for planes here maybe.
	PlaneData(FanInletFlange & fanInletFlange, FanOrEvaseOutletFlange & fanOrEvaseOutletFlange, FlowTraverse & flowTraverse,
	          AddlTravPlane & addlTravPlane, InletMstPlane & inletMstPlane, OutletMstPlane & outletMstPlane)
			: fanInletFlange(fanInletFlange), fanOrEvaseOutletFlange(fanOrEvaseOutletFlange), flowTraverse(flowTraverse),
			  addlTravPlane(addlTravPlane), inletMstPlane(inletMstPlane), outletMstPlane(outletMstPlane) {}

	FanInletFlange fanInletFlange;
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange;
	FlowTraverse flowTraverse;
	AddlTravPlane addlTravPlane;
	InletMstPlane inletMstPlane;
	OutletMstPlane outletMstPlane;
};


class Fan {
public:
	// TODO working constructor, consider using std::move on PlaneData
	Fan(FanRatedInfo & fanRatedInfo, PlaneData & planeData) :
			fanRatedInfo(fanRatedInfo), PlaneData(planeData)
	{}

private:
	FanRatedInfo const fanRatedInfo;
};

#endif //AMO_TOOLS_SUITE_FAN_H
