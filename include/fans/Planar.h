#ifndef AMO_TOOLS_SUITE_PLANAR_H
#define AMO_TOOLS_SUITE_PLANAR_H

#include <vector>
#include <cmath>

// to be inherited by planes 3 and 3a, 3b
class VelocityPressureTraverseData {
public:
	double getPv3Value() const {
		return pv3;
	}

	double get75percentRule() const {
		return percent75Rule;
	}
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

class FanFlange : public Planar {
public:
	FanFlange(double area, double tdx, double pbx);
};

class TraversePlane : public Planar, public VelocityPressureTraverseData {
public:
	TraversePlane(double area, double tdx, double pbx, double psx, double pitotTubeCoefficient,
				  std::vector< std::vector< double > > traverseHoleData);
};

class MstPlane : public Planar {
public:
	MstPlane(double area, double tdx, double pbx, double psx);
};

#endif //AMO_TOOLS_SUITE_PLANAR_H
