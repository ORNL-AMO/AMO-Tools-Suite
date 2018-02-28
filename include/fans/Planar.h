#ifndef AMO_TOOLS_SUITE_PLANAR_H
#define AMO_TOOLS_SUITE_PLANAR_H

#include <vector>
#include <cmath>

// to be inherited by planes 3 and 3a, 3b
class VelocityPressureTraverseData {
protected:
	// protected constructor to be used only during the construction of its derived classes
	VelocityPressureTraverseData(double pitotTubeCoefficient, std::vector< std::vector< double > > traverseHoleData);

	const double pitotTubeCoefficient;
	double pv3 = 0, percent75Rule = 0;

	std::vector< std::vector< double > > traverseHoleData;

	friend class PlaneData;
};

class Planar {
protected:
	Planar(double area, double tdx, double pbx, double psx);

	const double dryBulbTemperature, barometricPressure, area;
	double gasDensity = 0, gasVelocity = 0, gasVolumeFlowRate = 0, gasVelocityPressure = 0, gasTotalPressure = 0;
	double staticPressure = 0;

	friend class PlaneData;
	friend class Fan;
};

class FanInletFlange : public Planar {
public:
	FanInletFlange(double area, double tdx, double pbx);
};

class FanOrEvaseOutletFlange : public Planar {
public:
	FanOrEvaseOutletFlange(double area, double tdx, double pbx);
};


class FlowTraverse : public Planar, public VelocityPressureTraverseData {
public:
	FlowTraverse(double area, double tdx, double pbx, double psx, double pitotTubeCoefficient,
	             std::vector< std::vector< double > > traverseHoleData);
};

class AddlTravPlane : public Planar, public VelocityPressureTraverseData {
public:
	AddlTravPlane(double area, double tdx, double pbx, double psx, double pitotTubeCoefficient,
	              std::vector< std::vector< double > > traverseHoleData);
};

class InletMstPlane : public Planar {
public:
	InletMstPlane(double area, double tdx, double pbx, double psx);
};

class OutletMstPlane : public Planar {
public:
	OutletMstPlane(double area, double tdx, double pbx, double psx);
};

#endif //AMO_TOOLS_SUITE_PLANAR_H
