#ifndef AMO_TOOLS_SUITE_FANCURVE_H
#define AMO_TOOLS_SUITE_FANCURVE_H

#include <vector>

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

class ResultData {
public:
	ResultData(const double flow, const double pressure, const double power, const double efficiency)
			: flow(flow),
			  pressure(pressure),
			  power(power),
			  efficiency(efficiency)
	{};

	const double flow, pressure, power, efficiency;
};

class FanCurveData {
public:
	class Row {
	public:
		Row(const double flow, const double pressure, const double power)
				: flow(flow),
				  pressure(pressure),
				  power(power)
		{};

		const double flow, pressure, power;

		friend class FanCurveData;
	};

	FanCurveData(FanCurveType curveType, std::vector<Row> data)
			: curveType(curveType),
			  data(std::move(data)) {}

private:
	FanCurveType curveType;
	std::vector<Row> data;

	friend class FanCurve;
};

class FanCurve {
public:
	FanCurve(double density, double efficiency, double densityCorrected, double efficiencyCorrected,
	                  double pressureBarometric, double pressureBarometricCorrected, double pt1Factor, double gamma,
	                  double gammaCorrected, double area1, double area2, FanCurveData data)
			: density(density),
			  efficiency(efficiency),
			  densityCorrected(densityCorrected),
			  efficiencyCorrected(efficiencyCorrected),
			  pressureBarometric(pressureBarometric),
			  pressureBarometricCorrected(pressureBarometricCorrected),
			  pt1Factor(pt1Factor),
			  gamma(gamma),
			  gammaCorrected(gammaCorrected),
			  area1(area1),
			  area2(area2),
			  curveData(std::move(data))
	{};

	std::vector<ResultData> calculate();

//	void calculate(double flow, double pressure, double power, double density, double n, double densityC, double nC, double pb,
//	               double pbC, double pt1F, double gamma, double gammaC, double a1, double a2, FanCurveType curveType);

private:
	double density, efficiency, densityCorrected, efficiencyCorrected, pressureBarometric, pressureBarometricCorrected;
	double pt1Factor, gamma, gammaCorrected, area1, area2;

	FanCurveData curveData;
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
