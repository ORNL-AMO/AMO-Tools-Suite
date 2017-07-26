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

//TEST_CASE( "region 2 - 2", "[region 2 ]") {
//	auto result = SteamSystemModelerTool::region2(14192.912751330714, 50);
//	CHECK( result["pressure"] == Approx(25.58));
//	CHECK( result["temperature"] == Approx(679.50438021013));
//	CHECK( result["specificVolume"] == Approx(0.006211616555293));
//	CHECK( result["density"] == Approx(160.98868806509));
//	CHECK( result["specificEnthalpy"] == Approx(2621.5406472142));
//	CHECK( result["specificEntropy"] == Approx(5.198131771144));
//}

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

	result = sp.waterPropertiesPressureTemperature(3, 300);
	CHECK( result["specificVolume"] == Approx(0.001));
	CHECK( result["specificEnthalpy"] == Approx(115.3312730214));
	CHECK( result["specificEntropy"] == Approx(0.3922947924));

	result = sp.waterPropertiesPressureTemperature(3, 500);
	CHECK( result["specificEnthalpy"] == Approx(975.542239097));
	CHECK( result["specificEntropy"] == Approx(2.5804191201));
	CHECK( result["specificVolume"] == Approx(0.001202418));
}

TEST_CASE( "waterPropertiesPressureSpecificEnthalpy", "[waterPropertiesPressureEnthalpy]") {
	auto sp = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTHALPY);
	auto result = sp.waterPropertiesPressureEnthalpy(50, 60);
	CHECK( result["pressure"] == Approx(50));
	CHECK( result["temperature"] == Approx(275.8506041107));
	CHECK( result["specificVolume"] == Approx(0.0009770201));
	CHECK( result["specificEnthalpy"] == Approx(60.0));
	CHECK( result["specificEntropy"] == Approx(0.0385834579));
}

TEST_CASE( "waterPropertiesPressureSpecificEnthalpy2", "[waterPropertiesPressureEnthalpy2]") {
	auto sp = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTHALPY);
	auto result = sp.waterPropertiesPressureEnthalpy(50, 1000);
	CHECK( result["pressure"] == Approx(50));
	CHECK( result["temperature"] == Approx(501.9871417891));
	CHECK( result["specificVolume"] == Approx( 0.0011538465));
	CHECK( result["specificEnthalpy"] == Approx(1000.0));
	CHECK( result["specificEntropy"] == Approx(2.5188578322));
}

TEST_CASE( "waterPropertiesPressureSpecificEnthalpy3", "[waterPropertiesPressureEnthalpy3]") {
	auto sp = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTHALPY);
	auto result = sp.waterPropertiesPressureEnthalpy(10, 3000);
	CHECK( result["pressure"] == Approx(10));
	CHECK( result["temperature"] == Approx( 643.4889623134 ));
	CHECK( result["specificVolume"] == Approx( 0.024188001 ));
	CHECK( result["specificEnthalpy"] == Approx(3000.0100018335));
	CHECK( result["specificEntropy"] == Approx(6.0659344202));
}

TEST_CASE( "waterPropertiesPressureSpecificEntropy", "[waterPropertiesPressureEntropy]") {
	auto sp = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTROPY);
	auto result = sp.calculate(50, 3);
	CHECK( result["pressure"] == Approx(50));
	CHECK( result["temperature"] == Approx( 558.6087938578 ));
	CHECK( result["specificVolume"] == Approx( 0.0012546044 ));
	CHECK( result["specificEnthalpy"] == Approx(1255.054208238 ));
	CHECK( result["specificEntropy"] == Approx( 3.0 ));
}

TEST_CASE( "waterPropertiesPressureSpecificQuality", "[waterPropertiesPressureQuality]") {
	auto sp = SteamProperties(SteamProperties::ThermodynamicQuantity::QUALITY);
	auto result = sp.calculate(15, 0.5);
	CHECK( result["pressure"] == Approx(15));
	CHECK( result["temperature"] == Approx(  615.307871249 ));
	CHECK( result["specificVolume"] == Approx(0.0059985271));
	CHECK( result["specificEnthalpy"] == Approx( 2110.5082722126 ));
	CHECK( result["specificEntropy"] == Approx( 4.497623181 ));
}




