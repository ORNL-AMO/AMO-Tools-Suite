#include "catch.hpp"
#include <fsat/Fan.h>
#include <fsat/FanCurve.h>

TEST_CASE( "Fan", "Fan stuff") {
	FanRatedInfo fanRatedInfo(40, 1191, 1191, 1170, 0.05, 26.28, FanRatedInfo::DriveType::DIRECT);

	std::vector< std::vector< double > > traverseHoleData = {
			{
					0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130
			},
			{
					0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865
			},
			{
					0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569
			}
	};



	FanInletFlange fanInletFlange(143.63, 32.63, 2, 123, 26.57);
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange(70, 78, 132.7, 26.57);

	FlowTraverse flowTraverse(143.63, 32.63, 123.0, 26.57, -18.1, VelocityPressureTraverseData::TubeType::STYPE,
	                          std::sqrt(0.762), traverseHoleData);

	traverseHoleData = {
			{
					0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630
			},
			{
					0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596
			},
			{
					0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620
			}
	};

	std::vector<AddlTravPlane> addlTravPlanes({
			                                          {143.63, 32.63, 123.0, 26.57, -17.0,
					                                          VelocityPressureTraverseData::TubeType::STYPE, std::sqrt(0.762), traverseHoleData}
	                                          });

	InletMstPlane inletMstPlane(143.63, 32.63, 2, 123.0, 26.57, -17.55);
	OutletMstPlane outletMstPlane(55.42, 60.49, 132.7, 26.57, 1.8);

	auto planeData = PlaneData(fanInletFlange, fanOrEvaseOutletFlange, flowTraverse, addlTravPlanes, inletMstPlane,
	                           outletMstPlane, false, false, 0, 0.627, true);

	BaseGasDensity baseGasDensity(123, -17.6, 26.57, 0.0547, BaseGasDensity::GasType::AIR);

	auto fanShaftPower = FanShaftPower(true, false, 1750, 1200, 4160, 210, 4200, 205, 0.88, 95.0, 100, 100, FanRatedInfo::DriveType::DIRECT, 0);

	auto fan = Fan(fanRatedInfo, planeData, baseGasDensity, fanShaftPower);
	auto results = fan.calculate();

	auto const fanEfficiencyTp = results["fanEfficiencyTp"];
	auto const fanEfficiencySp = results["fanEfficiencySp"];
	auto const fanEfficiencySpr = results["fanEfficiencySpr"];
	auto const Qc = results["Qc"];
	auto const Ptc = results["Ptc"];
	auto const Psc = results["Psc"];
	auto const SPRc = results["SPRc"];
	auto const Hc = results["Hc"];
	auto const Kpc = results["Kpc"];

	CHECK(fanEfficiencyTp == Approx(53.607386));
	CHECK(fanEfficiencySp == Approx(49.206914));
	CHECK(fanEfficiencySpr == Approx(50.768875));
	// TODO add checks for other stuff besides efficiency
}

TEST_CASE( "FanCurve", "[Fan][FanCurve]") {
	FanCurve fc;

	// using row 2 appendix 1
	double q = 14410, ps = 22.5, h = 154, density = 0.0308, n = 1180, densityC = 0.0332, nC = 1187, pb = 29.36;
	double pbC = 29.36, pt1F = -0.93736, gamma = 1.4, gammaC = 1.4, a1 = 34, a2 = 12.7;
	// TODO estPt and estPtc should not be inputs
	FanCurveType curveType = FanCurveType::FanStaticPressure;
	fc.calculate(q, ps, h, density, n, densityC, nC, pb, pbC, pt1F, gamma, gammaC, a1, a2, curveType);
}
