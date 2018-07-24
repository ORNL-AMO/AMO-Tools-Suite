#ifndef AMO_TOOLS_SUITE_FANCURVE_H
#define AMO_TOOLS_SUITE_FANCURVE_H

#include <vector>

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
	enum class CalculationType {
		BaseCurve,
		RatedPoint,
		BaseOperatingPoint
	};

	struct BaseCurve {
		// pressure here is pressureBox, determined by Curve Type
		BaseCurve(const double flow, const double pressure, const double power)
				: flow(flow),
				  pressure(pressure),
				  power(power)
		{};

		const double flow, pressure, power;
		friend class FanCurveData;
	};

	struct RatedPoint : public BaseCurve {
		// pressure here is pressureBox, determined by Curve Type
		RatedPoint(const double flow, const double pressure, const double power, const double density,
		           const double speed, const double speedCorrected)
				: BaseCurve(flow, pressure, power),
				  density(density),
				  speed(speed),
				  speedCorrected(speedCorrected)
		{};

		const double density, speed, speedCorrected;
		friend class FanCurveData;
	};

	struct BaseOperatingPoint : public RatedPoint {
		// pressure here is pressureBox, determined by Curve Type
		BaseOperatingPoint(const double flow, const double pressure, const double power, const double density,
		                   const double speed, const double speedCorrected, const double pressureBarometric,
		                   const bool usePt1Factor, const double pt1 = 0)
				: RatedPoint(flow, pressure, power, density, speed, speedCorrected),
				  pressureBarometric(pressureBarometric), usePt1Factor(usePt1Factor), pt1(pt1)
		{};

		const double pressureBarometric;
		bool usePt1Factor;
		const double pt1;
		friend class FanCurveData;
	};

	FanCurveData(FanCurveType const curveType, std::vector<BaseCurve> baseCurveData)
			: curveType(curveType),
			  baseCurveData(std::move(baseCurveData)),
			  calcType(CalculationType::BaseCurve)
	{}

	FanCurveData(FanCurveType const curveType, std::vector<RatedPoint> ratedPointData)
			: curveType(curveType),
			  ratedPointData(std::move(ratedPointData)),
			  calcType(CalculationType::RatedPoint)
	{}

	FanCurveData(FanCurveType const curveType, std::vector<BaseOperatingPoint> baseOperatingPointData)
			: curveType(curveType),
			  baseOperatingPointData(std::move(baseOperatingPointData)),
			  calcType(CalculationType::BaseOperatingPoint)
	{}

private:
	FanCurveType curveType;
	std::vector<BaseCurve> baseCurveData;
	std::vector<RatedPoint> ratedPointData;
	std::vector<BaseOperatingPoint> baseOperatingPointData;

	CalculationType calcType;

	friend class FanCurve;
};

class FanCurve {
public:
	FanCurve(const double density, const double densityCorrected, const double speed, const double speedCorrected,
	         const double pressureBarometric, const double pressureBarometricCorrected, const double pt1Factor,
	         const double gamma, const double gammaCorrected, const double area1, const double area2, FanCurveData data)
			: density(density),
			  densityCorrected(densityCorrected),
			  speed(speed),
			  speedCorrected(speedCorrected),
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

private:
	std::vector<ResultData> calculateBaseCurve();
	std::vector<ResultData> calculateBaseOperatingPoint();
	std::vector<ResultData> calculateRatedPoint();

	double density, densityCorrected, speed, speedCorrected, pressureBarometric, pressureBarometricCorrected;
	double pt1Factor, gamma, gammaCorrected, area1, area2;

	FanCurveData curveData;
};

#endif //AMO_TOOLS_SUITE_FANCURVE_H
