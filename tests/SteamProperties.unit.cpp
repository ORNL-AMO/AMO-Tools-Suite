//
// Created by Preston Shires on 7/19/17.
//

#include "catch.hpp"
#include <ssmt/SteamProperties.h>
#include <ssmt/SteamSystemModelerTool.h>

TEST_CASE( "region 1", "[region 1]") {
	auto result = SteamSystemModelerTool::region1(300, 15);
	CHECK( result["pressure"] == Approx(15.0));
	CHECK( result["temperature"] == Approx(300));
	CHECK( result["specificEnthalpy"] == Approx(126.3055708813));
	CHECK( result["specificEntropy"] == Approx(0.3888958577));
	CHECK( result["quality"] == Approx(0));
	CHECK( result["specificVolume"] == Approx(0.0009968749));

	result = SteamSystemModelerTool::region1(SteamSystemModelerTool::TEMPERATURE_Tp, 25.58);
	CHECK( result["pressure"] == Approx(25.58));
	CHECK( result["temperature"] == Approx(623.15));
	CHECK( result["specificEnthalpy"] == Approx(1621.84698));
	CHECK( result["specificEntropy"] == Approx(3.6756));
	CHECK( result["specificVolume"] == Approx(0.001592707));
	CHECK( result["density"] == Approx(627.8616834));
}

TEST_CASE( "region3Density", "[region3Density]") {
	auto result = SteamSystemModelerTool::region3Density(627.8616834, 650);
	CHECK( result["pressure"] == Approx(46.90039363463));
	CHECK( result["temperature"] == Approx(650));
	CHECK( result["specificVolume"] == Approx(0.0015927074805465));
	CHECK( result["density"] == Approx(627.86168346299));
	CHECK( result["specificEnthalpy"] == Approx(1734.6938311862));
	CHECK( result["specificEntropy"] == Approx(3.7995608137168));
	CHECK( result["internalEnergy"] == Approx(1659.9952234038));
}

TEST_CASE( "boundaryByPressureRegion3to2", "[boundaryByPressureRegion3to2]") {
	auto result = SteamSystemModelerTool::boundaryByPressureRegion3to2(25.58);
	CHECK( result == Approx(679.50438021013));
}

TEST_CASE( "region 2", "[region 2]") {
	auto result = SteamSystemModelerTool::region2(679.50438021013, 25.58);
	CHECK( result["pressure"] == Approx(25.58));
	CHECK( result["temperature"] == Approx(679.50438021013));
	CHECK( result["specificVolume"] == Approx(0.006211616555293));
	CHECK( result["density"] == Approx(160.98868806509));
	CHECK( result["specificEnthalpy"] == Approx(2621.5406472142));
	CHECK( result["specificEntropy"] == Approx(5.198131771144));
}

TEST_CASE( "region 3", "[region 3]") {
	auto result = SteamSystemModelerTool::region3(650, 25.58);
	CHECK( result["density"] == Approx(499.93601366213));
	CHECK( result["specificVolume"] == Approx(0.0020002559781097));
	CHECK( result["internalEnergy"] == Approx(1812.3374452641));
	CHECK( result["specificEnthalpy"] == Approx(1863.5039931841));
	CHECK( result["specificEntropy"] == Approx(4.0543976678954));
}

TEST_CASE( "waterPropertiesPressureTemperature", "[waterPropertiesPressureTemp]") {
	auto sp = SteamProperties(SteamProperties::ThermodynamicQuantity::TEMPERATURE);
	auto result = sp.waterPropertiesPressureTemperature(25.58, 650);
	CHECK( result["density"] == Approx(499.93601366213));
	CHECK( result["specificVolume"] == Approx(0.0020002559781097));
	CHECK( result["internalEnergy"] == Approx(1812.3374452641));
	CHECK( result["specificEnthalpy"] == Approx(1863.5039931841));
	CHECK( result["specificEntropy"] == Approx(4.0543976678954));
}


//// region 1
//TEST_CASE( "Calculate the Steam Properties Using Temperature", "[Steam Properties][ssmt][Calculator]") {
//	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::TEMPERATURE).calculate(50, 300);
//	CHECK( test["pressure"] == Approx(50.0));
//	CHECK( test["temperature"] == Approx(300));
//	CHECK( test["specificEnthalpy"] == Approx(157.7656843556));
//	CHECK( test["specificEntropy"] == Approx(0.3783149091));
//	CHECK( test["quality"] == Approx(0));
//	CHECK( test["specificVolume"] == Approx(0.0009824691));
//}
//
//// idk what region this is right now
//TEST_CASE( "Calculate the Steam Properties Using Specific Enthalpy", "[Steam Properties][ssmt][Calculator]") {
//	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTHALPY).calculate(50, 60);
//	CHECK( test["pressure"] == Approx(50.0));
//	CHECK( test["temperature"] == Approx(275.8561282609));
//	CHECK( test["specificEnthalpy"] == Approx(60.0222543089));
//	CHECK( test["specificEntropy"] == Approx(0.0386641323));
//	CHECK( test["quality"] == Approx(0));
//	CHECK( test["specificVolume"] == Approx(0.0009770201));
//}
//
//// region 3
//TEST_CASE( "Calculate the Steam Properties Using Specific Entropy", "[Steam Properties][ssmt][Calculator]") {
//	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTROPY).calculate(50, 4);
//	CHECK( test["pressure"] == Approx(50.0));
//	CHECK( test["temperature"] == Approx(672.9));
//	CHECK( test["specificEnthalpy"] == Approx(1872.4));
//	CHECK( test["specificEntropy"] == Approx(4.0));
//	CHECK( test["quality"] == Approx(0));
//	CHECK( test["specificVolume"] == Approx(0.002));
//}
//
//TEST_CASE( "Calculate the Steam Properties Using Specific Quality", "[Steam Properties][ssmt][Calculator]") {
//	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::QUALITY).calculate(20, 0.6);
//	CHECK( test["pressure"] == Approx(20.0));
//	CHECK( test["temperature"] == Approx(638.9));
//	CHECK( test["specificEnthalpy"] == Approx(2183.8485753012));
//	CHECK( test["specificEntropy"] == Approx(4.5737534333));
//	CHECK( test["quality"] == Approx(0.6));
//	CHECK( test["specificVolume"] == Approx(0.0043775714));
//}
//
//TEST_CASE( "Ctest", "[Steam Properties][ssmt][Calculator]") {
//	Point test = SteamSystemModelerTool::generatePoint(3, SteamSystemModelerTool::Key::ENTHALPY, 5, 14);
//	CHECK( test.getX() == Approx(20.0));
//
//}

//TEST_CASE( "test", "[Steam Properties][ssmt][Calculator]") {
//    CHECK( SteamSystemModelerTool::backwardPressureEnthalpyRegion2B(25, 3849.1) == Approx(275.9));
//}

