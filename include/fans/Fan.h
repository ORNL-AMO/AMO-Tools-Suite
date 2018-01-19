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

	enum class InputType {
		DEW,
		RH,
		WET
	};

	// used for method 1
	BaseGasDensity(double tdo, double pso, double pbo, double po, GasType gasType);

	// TODO ensure correctness
//	BaseGasDensity(double tdo, double pso, double pbo, double relativeHumidityOrDewPointTempOrHumidityRatio,
//	               GasType gasType, InputType inputType, double specificGravity);
//
//	BaseGasDensity(double tdo, double pso, double pbo, double wetBulbTemp,
//	               GasType gasType, InputType inputType, double specificGravity, double cpGas);

private:

	double calculateSaturationPressure(double dryBulbTemp) const;

	double calculateRatioRH(double dryBulbTemp, double relativeHumidity, double barometricPressure,
	                        double specificGravity) const;

	double calculateRelativeHumidityFromWetBulb(double dryBulbTemp, double wetBulbTemp, double cpGas) const;

	// dry bulb temp, reference static pressure, reference barometric pressure, gas density respectively
	const double tdo, pso, pbo;

	// gasDensity, specificGravity
	double po, g;
	const GasType gasType;

	friend class PlaneData;
	friend class Fan;
};


class PlaneData {
public:
	PlaneData(FanInletFlange fanInletFlange, FanOrEvaseOutletFlange fanOrEvaseOutletFlange,
	          FlowTraverse flowTraverse, std::vector<AddlTravPlane> addlTravPlanes, InletMstPlane inletMstPlane,
	          OutletMstPlane outletMstPlane, double totalPressureLossBtwnPlanes1and4,
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

	bool const plane5upstreamOfPlane2;
	const double totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5;

	friend class Fan;
};


class Fan {
public:
	Fan(FanRatedInfo fanRatedInfo, PlaneData planeData, BaseGasDensity baseGasDensity, FanShaftPower fanShaftPower);

	std::unordered_map<std::string, double> calculate();

private:

	double calculateCompressibilityFactor(double x, double z, double isentropicExponent);

	FanRatedInfo const fanRatedInfo;
	PlaneData planeData;
	BaseGasDensity const baseGasDensity;
	FanShaftPower const fanShaftPower;
};

#endif //AMO_TOOLS_SUITE_FAN_H
