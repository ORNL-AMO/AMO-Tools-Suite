#ifndef AMO_TOOLS_SUITE_FANCURVE_H
#define AMO_TOOLS_SUITE_FANCURVE_H

//class CurveConditions {
//public:
//	CurveConditions(double density, double rpm, double barometricPressure, double isentropicExponent);
//
//private:
//	double density, rpm, barometricPressure, isentropicExponent;
//};

enum class FanCurveType {
	FanStaticPressure,
	FanTotalPressure,
	StaticPressureRise
};

class FanCurve {
	void calculate(double q, double p, double h, double density, double n, double densityC, double nC, double pb,
	               double pbC, double pt1F, double gamma, double gammaC, double a1, double a2, FanCurveType curveType,
	               double kp, double kpC, double estPt, double estPtc, double q1, double q2, double density1,
	               double density2);
};

//class FanCurve {
//public:
//	enum class FanCurveType {
//		FanStaticPressure,
//		FanTotalPressure,
//		StaticPressureRise
//	};
//	FanCurve(double flow, double pressure, double horsepower, double density, double rpm, FanCurveType curveType);
//
//private:
//	CurveConditions base, optimized;
//	double flow, pressure, horsepower, density, rpm, isentropicExponent;
//};

#endif //AMO_TOOLS_SUITE_FANCURVE_H
