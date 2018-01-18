#ifndef AMO_TOOLS_SUITE_PLANAR_H
#define AMO_TOOLS_SUITE_PLANAR_H

#include <vector>
#include <cmath>

// to be inherited by planes 3 and 3a, 3b
class VelocityPressureTraverseData {
protected:

	// protected constructor to be used only during the construction of its derived classes
	VelocityPressureTraverseData(double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData);

	const double pitotTubeCoefficient;
	double pv3 = 0, percent75Rule = 0;

	std::vector< std::vector< double > > traverseHoleData;

	friend class PlaneData;
};

class Planar {
protected:

	Planar(double circularDuctDiameter, double tdx, double pbx, double psx);

//	Planar(double rectLength, double rectWidth, double tdx, double pbx, double psx);

	Planar(double rectLength, double rectWidth, double tdx, double pbx, double psx, unsigned noInletBoxes = 1);

//	where tdx = dryBulbTemperature and pbx = barometric pressure
	const double tdx, pbx, area;
	double gasDensity = 0, gasVelocity = 0, gasVolumeFlowRate = 0, gasVelocityPressure = 0, gasTotalPressure = 0;
	double psx = 0;

	friend class PlaneData;
	friend class Fan;
};

class FanInletFlange : public Planar {
public:
	FanInletFlange(double circularDuctDiameter, double tdx, double pbx);

//	FanInletFlange(double rectLength, double rectWidth, double tdx, double pbx);

	FanInletFlange(double rectLength, double rectWidth, double tdx, double pbx, unsigned noInletBoxes = 1);
};

class FanOrEvaseOutletFlange : public Planar {
public:
	FanOrEvaseOutletFlange(double circularDuctDiameter, double tdx, double pbx);

//	FanOrEvaseOutletFlange(double rectLength, double rectWidth, double tdx, double pbx);

	FanOrEvaseOutletFlange(double rectLength, double rectWidth, double tdx, double pbx, unsigned noInletBoxes = 1);
};


class FlowTraverse : public Planar, public VelocityPressureTraverseData {
public:
	FlowTraverse(double circularDuctDiameter, double tdx, double pbx,
	             double psx, double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData);

//	FlowTraverse(double rectLength, double rectWidth, double tdx,
//	             double pbx, double psx, double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData);

	FlowTraverse(double rectLength, double rectWidth, double tdx, double pbx, double psx, double pitotTubeCoefficient,
	             std::vector< std::vector< double > > & traverseHoleData, unsigned noInletBoxes = 1);
};

class AddlTravPlane : public Planar, public VelocityPressureTraverseData {
public:
	AddlTravPlane(double circularDuctDiameter, double tdx, double pbx,
	              double psx, double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData);

//	AddlTravPlane(double rectLength, double rectWidth, double tdx,
//	              double pbx, double psx, double pitotTubeCoefficient,
//	              std::vector< std::vector< double > > & traverseHoleData);

	AddlTravPlane(double rectLength, double rectWidth, double tdx, double pbx, double psx, double pitotTubeCoefficient,
	              std::vector< std::vector< double > > & traverseHoleData, unsigned noInletBoxes = 1);
};

class InletMstPlane : public Planar {
public:
	InletMstPlane(double circularDuctDiameter, double tdx, double pbx, double psx);

//	InletMstPlane(double rectLength, double rectWidth, double tdx, double pbx, double psx);

	InletMstPlane(double rectLength, double rectWidth, double tdx, double pbx, double psx, unsigned noInletBoxes = 1);
};

class OutletMstPlane : public Planar {
public:
	OutletMstPlane(double circularDuctDiameter, double tdx, double pbx, double psx);

//	OutletMstPlane(double rectLength, double rectWidth, double tdx, double pbx,
//	               double psx);

	OutletMstPlane(double rectLength, double rectWidth, double tdx, double pbx, double psx, unsigned noInletBoxes = 1);
};


#endif //AMO_TOOLS_SUITE_PLANAR_H
