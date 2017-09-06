#include "catch.hpp"
#include <fsat/Fan.h>

TEST_CASE( "Fan", "Fan stuff") {
	FanRatedInfo fanRatedInfo(40, 1191, 1191, 1170, 0.05, 26.28, FanRatedInfo::DriveType::DIRECT);
	FanInletFlange fanInletFlange(143.63, 32.63, 2, 123, 26.57);
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange(70, 78, 132.7, 26.57);
	FlowTraverse flowTraverse(143.63, 32.63, 123.0, 26.57, -18.1);

	std::vector<AddlTravPlane> addlTravPlanes({
			                                          {143.63, 32.63, 123.0, 26.57, -17.0}
	                                          });

	InletMstPlane inletMstPlane(143.63, 32.63, 2, 123.0, 26.57, -17.55);
	OutletMstPlane outletMstPlane(55.42, 60.49, 132.7, 26.57, 1.8);

	auto planeData = PlaneData(fanInletFlange, fanOrEvaseOutletFlange, flowTraverse, addlTravPlanes, inletMstPlane,
	                           outletMstPlane, false, false);

	std::vector< std::vector< double > > traverseHoleData = {
			{
					0.701, 0.703, 0.668, 0.815, 0.979, 1.090, 1.155, 1.320, 1.578, 2.130
			},
			{
					0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865
			},
			{
					0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.883, 1.230, 1.210, 1.569
			}
	};

	VelocityPressureTraverseData vptd(VelocityPressureTraverseData::TubeType::STYPE, 0.87, traverseHoleData);

	BaseGasDensity baseGasDensity(123, -17.6, 26.57, 0.0547);

	auto fan = Fan(fanRatedInfo, planeData, vptd, baseGasDensity);


	auto test = 0;
}
