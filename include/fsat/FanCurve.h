#ifndef AMO_TOOLS_SUITE_FANCURVE_H
#define AMO_TOOLS_SUITE_FANCURVE_H

class CurveConditions {
public:
	CurveConditions(double density, double rpm, double barometricPressure, double isentropicExponent);

private:
	double density, rpm, barometricPressure, isentropicExponent;
};

class FanCurve {
public:
	enum class FanCurveType {
		FanStaticPressure,
		FanTotalPressure,
		StaticPressureRise
	};
	FanCurve(double flow, double pressure, double horsepower, double density, double rpm, FanCurveType curveType);

private:
	CurveConditions base, optimized;
};

#endif //AMO_TOOLS_SUITE_FANCURVE_H
