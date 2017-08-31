#include "catch.hpp"
#include <fsat/Fan.h>

TEST_CASE( "Fan", "Fan stuff") {

	std::unordered_map<std::string, Planar> planes = {
			{"fanInletFlange", Planar(143.63, 32.63, 2)},
			{"fanOrEvaseOutletFlange", Planar(70, 78)},
			{"flowTraverse", Planar(143.63, 32.63)},
			{"AddlTravPlane1", Planar(143.63, 32.63)},
			{"InletMstPlane", Planar(143.63, 32.63, 2)},
			{"OutletMstPlane", Planar(55.42, 60.49)}
	};


	FanRatedInfo fanRatedInfo(40, 1191, 1191, 1170, 0.05, 26.28, FanRatedInfo::DriveType::DIRECT);
	auto fan = Fan(fanRatedInfo, planes);




	auto test = 0;
}
