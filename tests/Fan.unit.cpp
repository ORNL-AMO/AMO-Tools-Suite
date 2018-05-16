#include "catch.hpp"
#include <fans/Fan203.h>
#include <fans/FanEnergyIndex.h>
#include <fans/FanCurve.h>

TEST_CASE( "FanEnergyIndex", "[FanEnergyIndex]") {
	CHECK(Approx(FanEnergyIndex(129691, -16, 1, 0.07024, 450).calculateEnergyIndex()) == 0.9678686743);
	CHECK(Approx(FanEnergyIndex(80364, -9, 1, 0.07024, 150).calculateEnergyIndex()) == 1.0776769184);
}

TEST_CASE( "Fan203", "[Fan203]") {
	FanRatedInfo fanRatedInfo(1191, 1191, 1170, 0.05, 26.28);

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

	const double area = (143.63 * 32.63 * 2) / 144.0;
	FlangePlane fanInletFlange(area, 123, 26.57);
	FlangePlane fanOrEvaseOutletFlange(70 * 78 / 144.0, 132.7, 26.57);

	TraversePlane flowTraverse(143.63 * 32.63 / 144.0, 123.0, 26.57, -18.1, std::sqrt(0.762), traverseHoleData);

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

	std::vector<TraversePlane> addlTravPlanes({
			                                          {143.63 * 32.63 / 144.0, 123.0, 26.57, -17.0, std::sqrt(0.762), traverseHoleData}
	                                          });

	MstPlane inletMstPlane(area, 123.0, 26.57, -17.55);
	MstPlane outletMstPlane(55.42 * 60.49 / 144.0, 132.7, 26.57, 1.8);

	auto planeData = PlaneData(fanInletFlange, fanOrEvaseOutletFlange, flowTraverse, addlTravPlanes, inletMstPlane,
	                           outletMstPlane, 0, 0.627, true);

	BaseGasDensity baseGasDensity(123, -17.6, 26.57, 0.0547, BaseGasDensity::GasType::AIR);

	auto const motorShaftPower = FanShaftPower::calculateMotorShaftPower(4200, 205, 0.88) / 746.0;
	auto fanShaftPower = FanShaftPower(motorShaftPower, 95.0, 100, 100, 0);

	auto fan = Fan203(fanRatedInfo, planeData, baseGasDensity, fanShaftPower);
	auto results = fan.calculate();

	CHECK(results.fanEfficiencyTotalPressure == Approx(53.607386));
	CHECK(results.fanEfficiencyStaticPressure == Approx(49.206914));
	CHECK(results.fanEfficiencyStaticPressureRise == Approx(50.768875));
	// TODO add checks for other stuff besides efficiency
}

TEST_CASE( "FanCurve", "[Fan203][FanCurve]") {
	// using row 2 appendix 1
	double density = 0.0308, n = 1180, densityC = 0.0332, nC = 1187, pb = 29.36;
	double pbC = 29.36, pt1F = -0.93736, gamma = 1.4, gammaC = 1.4, a1 = 34, a2 = 12.7;
	FanCurveType curveType = FanCurveType::FanStaticPressure;

	std::vector<FanCurveData::BaseCurve> baseCurveData = {
			{0, 22.3, 115},
			{14410, 22.5, 154},
			{28820, 22.3, 194},
			{43230, 21.8, 241},
			{57640, 21.2, 293},
			{72050, 20.3, 349},
			{86460, 19.3, 406},
			{100871, 18, 462},
			{115281, 16.5, 515},
			{129691, 14.8, 566},
			{144101, 12.7, 615},
			{158511, 10.2, 667},
			{172921, 7.3, 725},
			{187331, 3.7, 789},
			{201741, -0.8, 861}
	};

	FanCurve fc(density, densityC, n, nC, pb, pbC, pt1F, gamma, gammaC, a1, a2, FanCurveData(curveType, baseCurveData));
	auto const results = fc.calculate();

	auto const compareRows = [](ResultData const & row, ResultData const & expected) {
		CHECK(row.flow == Approx(expected.flow));
		CHECK(row.pressure == Approx(expected.pressure));
		CHECK(row.power == Approx(expected.power));
		CHECK(row.efficiency == Approx(expected.efficiency));
	};

//	ResultData(const double flow, const double pressure, const double power, const double efficiency)
	std::vector<ResultData> expected = {
			{0, 24.3237008519,  126.1802380783, 0},
			{14500.8543591511,  24.5509446301, 169.0344096605, 0.3296327776},
			{29026.8029521096,  24.3537683159, 213.1237007012, 0.5140168074},
			{43549.7454585634,  23.8129367203, 264.8147787583, 0.6053657684},
			{58070.0734274583,  23.1590288007, 321.9740080602, 0.6451968788},
			{72585.9393038736,  22.1753576429, 383.5029716631, 0.6484847133},
			{87098.9706713126,  21.0819694298, 446.1168381298, 0.6362806595},
			{101607.8897959761, 19.6602795889, 507.6073147301, 0.6089335382},
			{116111.3789740286, 18.0200947791, 565.7819229037, 0.5728692768},
			{130609.5615402702, 16.1615468983, 621.7364859870, 0.5266325641},
			{145098.2298738518, 13.8661188861, 675.4528304721, 0.4628825027},
			{159574.7652742440, 11.1342523247, 732.4119689902, 0.3778769228},
			{174035.6935709888, 7.96653610850, 795.8906212688, 0.2721540841},
			{188477.2686633575, 4.03652020770, 865.8668678138, 0.1378022756},
			{202889.8046137204, -0.8723928962, 944.4826765914, -0.029540604}
	};

	for (std::size_t i = 0; i < results.size(); i++) {
		compareRows(results[i], expected[i]);
	}

	// TODO make this better by not using the same density, speed and speedCorrected for each entry?
//	RatedPoint(const double flow, const double pressure, const double power, const double density,
//				const double speed, const double speedCorrected)
	std::vector<FanCurveData::RatedPoint> ratedPointData = {
			{0, 22.3, 115, density, n, nC},
			{14410, 22.5, 154, density, n, nC},
			{28820, 22.3, 194, density, n, nC},
			{43230, 21.8, 241, density, n, nC},
			{57640, 21.2, 293, density, n, nC},
			{72050, 20.3, 349, density, n, nC},
			{86460, 19.3, 406, density, n, nC},
			{100871, 18, 462, density, n, nC},
			{115281, 16.5, 515, density, n, nC},
			{129691, 14.8, 566, density, n, nC},
			{144101, 12.7, 615, density, n, nC},
			{158511, 10.2, 667, density, n, nC},
			{172921, 7.3, 725, density, n, nC},
			{187331, 3.7, 789, density, n, nC},
			{201741, -0.8, 861, density, n, nC}
	};

	FanCurve fc2(density, densityC, n, nC, pb, pbC, pt1F, gamma, gammaC, a1, a2, FanCurveData(curveType, ratedPointData));
	auto const results2 = fc2.calculate();
	for (std::size_t i = 0; i < results2.size(); i++) {
		compareRows(results2[i], expected[i]);
	}
}
