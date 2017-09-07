#include "catch.hpp"
#include <fsat/Fan.h>

TEST_CASE( "Fan", "Fan stuff") {
	FanRatedInfo fanRatedInfo(40, 1191, 1191, 1170, 0.05, 26.28, FanRatedInfo::DriveType::DIRECT);

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



	FanInletFlange fanInletFlange(143.63, 32.63, 2, 123, 26.57);
	FanOrEvaseOutletFlange fanOrEvaseOutletFlange(70, 78, 132.7, 26.57);

	FlowTraverse flowTraverse(143.63, 32.63, 123.0, 26.57, -18.1, VelocityPressureTraverseData::TubeType::STYPE, 0.87,
	                          traverseHoleData);

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
					                                          VelocityPressureTraverseData::TubeType::STYPE, 0.87, traverseHoleData}
	                                          });

	InletMstPlane inletMstPlane(143.63, 32.63, 2, 123.0, 26.57, -17.55);
	OutletMstPlane outletMstPlane(55.42, 60.49, 132.7, 26.57, 1.8);

	auto planeData = PlaneData(fanInletFlange, fanOrEvaseOutletFlange, flowTraverse, addlTravPlanes, inletMstPlane,
	                           outletMstPlane, false, false, 0, 0.627);


	BaseGasDensity baseGasDensity(123, -17.6, 26.57, 0.0547);

	auto fan = Fan(fanRatedInfo, planeData, baseGasDensity);


	auto test = 0;
}
