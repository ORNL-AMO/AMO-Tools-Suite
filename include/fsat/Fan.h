#ifndef AMO_TOOLS_SUITE_FAN_H
#define AMO_TOOLS_SUITE_FAN_H

#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <stdexcept>
#include "Planar.h"
#include "FanShaftPower.h"

class FanRatedInfo;
class Planar;
class FanInletFlange;
class FanOrEvaseOutletFlange;
class FlowTraverse;
class AddlTravPlane;
class InletMstPlane;
class OutletMstPlane;

class BaseGasDensity {
public:

	enum class GasType {
		AIR,
		STANDARDAIR,
		OTHERGAS
	};

	// used for method 1
	BaseGasDensity(double tdo, double pso, double pbo, double po, GasType gasType);

	// TODO incomplete, po (density) shouldn't be an input in either of the constructors below bc it needs to be calculated
//	// used for method 2 without wet bulb temperature as "data to establish gas humidity"
//	BaseGasDensity(double tdo, double pso, double pbo, double po, double g,
//	               double two)
//			: tdo(tdo), pso(pso), pbo(pbo), po(po), g(g), two(two) {}

//	// used for method 2 with wet bulb temp being used for "data to establish gas humidity"
//	BaseGasDensity(double tdo, double pso, double pbo, double po, double g,
//	               double percentRH)
//			: tdo(tdo), pso(pso), pbo(pbo), po(po), g(g), percentRH(percentRH) {}

private:

//	double calcWaterVaporDensityToDryAirDensityRatio(double pws) {
//		return 0.6214 + (percentRH * std::pow(pws, 1 / 1.42)) / 1130;
//	}
//
//	double calcBaseGasDensity(double p, double pws) {
//		return ((p - pws * percentRH) * g + pws * percentRH * calcWaterVaporDensityToDryAirDensityRatio(pws))
//		       / (0.7543 * (tdo + 459.7));
//	}

	const double tdo, pso, pbo, po;
	const GasType gasType;

	friend class PlaneData;
	friend class Fan;

//	const double g = 0, two = 0, percentRH = 0, tdp = 0;
};


class PlaneData {
public:
	PlaneData(FanInletFlange & fanInletFlange, FanOrEvaseOutletFlange & fanOrEvaseOutletFlange,
	          FlowTraverse & flowTraverse, std::vector<AddlTravPlane> & addlTravPlanes, InletMstPlane & inletMstPlane,
	          OutletMstPlane & outletMstPlane, bool variationsInPlanarBarometricPressure,
	          bool estimatePlaneTemp, double totalPressureLossBtwnPlanes1and4,
	          double totalPressureLossBtwnPlanes2and5, bool plane5upstreamOfPlane2);

private:

	void establishFanInletOrOutletDensity(Planar & plane,
	                                      std::function<double (Planar const &, const double)> const & calcDensity,
	                                      double mTotal, double assumedDensity);

	void calculate(BaseGasDensity const & bgd);


	FanInletFlange fanInletFlange;
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange;
	FlowTraverse flowTraverse;
	std::vector<AddlTravPlane> addlTravPlanes;
	InletMstPlane inletMstPlane;
	OutletMstPlane outletMstPlane;

	bool const variationsInPlanarBarometricPressure, estimatePlaneTemp, plane5upstreamOfPlane2;
	const double totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5;

	friend class Fan;
};


class Fan {
public:
	Fan(FanRatedInfo & fanRatedInfo, PlaneData & planeData, BaseGasDensity & baseGasDensity,
	    FanShaftPower & fanShaftPower);

	std::unordered_map<std::string, double> calculate();

private:

	double calculateCompressibilityFactor(double x, double z, double kp, double isentropicExponent);

	FanRatedInfo const fanRatedInfo;
	PlaneData planeData;
	BaseGasDensity const baseGasDensity;
	FanShaftPower const fanShaftPower;
};

#endif //AMO_TOOLS_SUITE_FAN_H
