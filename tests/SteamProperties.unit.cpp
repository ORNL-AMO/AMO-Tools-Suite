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
	auto sp = SteamProperties(25.58, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 650);
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

	result = sp.waterPropertiesPressureTemperature(80, 300);
	CHECK( result["specificEnthalpy"] == Approx(184.142828));
	CHECK( result["specificEntropy"] == Approx(0.368563852));
	CHECK( result["specificVolume"] == Approx(0.000971181));

	result = sp.waterPropertiesPressureTemperature(80, 500);
	CHECK( result["specificEnthalpy"] == Approx(1005.1696722456));
	CHECK( result["specificEntropy"] == Approx(2.4609385983));
	CHECK( result["specificVolume"] == Approx(0.00112629));

	// region 2 areas
	result = sp.waterPropertiesPressureTemperature(0.0035, 300);
	CHECK( result["specificEnthalpy"] == Approx(2549.9));
	CHECK( result["specificEntropy"] == Approx(8.5223896673));
	CHECK( result["specificVolume"] == Approx(39.491));

	result = sp.waterPropertiesPressureTemperature(0.0035, 700);
	CHECK( result["specificEnthalpy"] == Approx(3335.7));
	CHECK( result["specificEntropy"] == Approx(10.175));
	CHECK( result["specificVolume"] == Approx(92.302));

	result = sp.waterPropertiesPressureTemperature(30, 700);
	CHECK( result["specificEnthalpy"] == Approx(2631.4947448448));
	CHECK( result["specificEntropy"] == Approx(5.1754029823));
	CHECK( result["specificVolume"] == Approx(0.0054294662));

	result = sp.waterPropertiesPressureTemperature(1, 450);
	CHECK( result["specificEnthalpy"] == Approx(749.3284821858));
	CHECK( result["specificEntropy"] == Approx(2.108854683));
	CHECK( result["specificVolume"] == Approx(0.0011231015));

	result = sp.waterPropertiesPressureTemperature(1, 440);
	CHECK( result["specificEnthalpy"] == Approx(705.5753461629));
	CHECK( result["specificEntropy"] == Approx(2.0105303763));
	CHECK( result["specificVolume"] == Approx(0.0011101036));

	result = sp.waterPropertiesPressureTemperature(1.5, 450);
	CHECK( result["specificEnthalpy"] == Approx(749.5873697011));
	CHECK( result["specificEntropy"] == Approx(2.1081823281));
	CHECK( result["specificVolume"] == Approx(0.0011226877));

	// region 3 areas
	result = sp.waterPropertiesPressureTemperature(25.6, 650);
	CHECK( result["specificEnthalpy"] == Approx(1863.1063178273));
	CHECK( result["specificEntropy"] == Approx(4.0537243346));
	CHECK( result["specificVolume"] == Approx(0.002));

	result = sp.waterPropertiesPressureTemperature(22.293064, 650);
	CHECK( result["specificEnthalpy"] == Approx(2375.12401));
	CHECK( result["specificEntropy"] == Approx(4.8543880077));
	CHECK( result["specificVolume"] == Approx(0.0050000005));

	result = sp.waterPropertiesPressureTemperature(78.3, 750);
	CHECK( result["specificEnthalpy"] == Approx(2258.7326650989));
	CHECK( result["specificEntropy"] == Approx(4.4698035205));
	CHECK( result["specificVolume"] == Approx(0.0020001543));
}

TEST_CASE( "waterPropertiesPressureSpecificEnthalpy", "[waterPropertiesPressureEnthalpy]") {
	auto sp = SteamProperties(50, SteamProperties::ThermodynamicQuantity::ENTHALPY, 60);
	auto result = sp.calculate();
	CHECK( result["pressure"] == Approx(50));
	CHECK( result["temperature"] == Approx(275.8506041107));
	CHECK( result["specificVolume"] == Approx(0.0009770201));
	CHECK( result["specificEnthalpy"] == Approx(60.0));
	CHECK( result["specificEntropy"] == Approx(0.0385834579));
}

TEST_CASE( "waterPropertiesPressureSpecificEnthalpy2", "[waterPropertiesPressureEnthalpy2]") {
	auto sp = SteamProperties(50, SteamProperties::ThermodynamicQuantity::ENTHALPY, 1000);
	auto result = sp.calculate();
	CHECK( result["pressure"] == Approx(50));
	CHECK( result["temperature"] == Approx(501.9871417891));
	CHECK( result["specificVolume"] == Approx( 0.0011538465));
	CHECK( result["specificEnthalpy"] == Approx(1000.0));
	CHECK( result["specificEntropy"] == Approx(2.5188578322));
}

TEST_CASE( "waterPropertiesPressureSpecificEnthalpy3", "[waterPropertiesPressureEnthalpy3]") {
	auto sp = SteamProperties(10, SteamProperties::ThermodynamicQuantity::ENTHALPY, 3000);
	auto result = sp.calculate();
	CHECK( result["pressure"] == Approx(10));
	CHECK( result["temperature"] == Approx( 643.4889623134 ));
	CHECK( result["specificVolume"] == Approx( 0.024188001 ));
	CHECK( result["specificEnthalpy"] == Approx(3000.0100018335));
	CHECK( result["specificEntropy"] == Approx(6.0659344202));
}

TEST_CASE( "waterPropertiesPressureSpecificEntropy", "[waterPropertiesPressureEntropy]") {
	auto sp = SteamProperties(50, SteamProperties::ThermodynamicQuantity::ENTROPY, 3);
	auto result = sp.calculate();
	CHECK( result["pressure"] == Approx(50));
	CHECK( result["temperature"] == Approx( 558.6087938578 ));
	CHECK( result["specificVolume"] == Approx( 0.0012546044 ));
	CHECK( result["specificEnthalpy"] == Approx(1255.054208238 ));
	CHECK( result["specificEntropy"] == Approx( 3.0 ));
}

TEST_CASE( "waterPropertiesPressureSpecificQuality", "[waterPropertiesPressureQuality]") {
	auto sp = SteamProperties(15, SteamProperties::ThermodynamicQuantity::QUALITY, 0.5);
	auto result = sp.calculate();
	CHECK( result["pressure"] == Approx(15));
	CHECK( result["temperature"] == Approx(  615.307871249 ));
	CHECK( result["specificVolume"] == Approx(0.0059985271));
	CHECK( result["specificEnthalpy"] == Approx( 2110.5082722126 ));
	CHECK( result["specificEntropy"] == Approx( 4.497623181 ));
}

TEST_CASE( "Calculate Steam Properties using Pressure and Enthalpy", "[waterPropertiesPressureEnthalpy]") {
    auto sp = SteamProperties(3, SteamProperties::ThermodynamicQuantity::ENTHALPY, 500);
    auto result1 = sp.calculate();
    CHECK( result1["pressure"] == Approx(3));
    CHECK( result1["temperature"] == Approx( 391.791991375 ));
    CHECK( result1["specificVolume"] == Approx(0.0010575419));
    CHECK( result1["specificEnthalpy"] == Approx(500 ));
    CHECK( result1["specificEntropy"] == Approx(1.5106138266 ));

    auto result2 = sp.waterPropertiesPressureEnthalpy(80, 500);
    CHECK( result2["pressure"] == Approx(80));
    CHECK( result2["temperature"] == Approx(378.1241736021));
    CHECK( result2["specificVolume"] == Approx(.001));
    CHECK( result2["specificEnthalpy"] == Approx( 500 ));
    CHECK( result2["specificEntropy"] == Approx(1.304));

    auto result3 = sp.waterPropertiesPressureEnthalpy(80, 1500);
    CHECK( result3["pressure"] == Approx(80));
    CHECK( result3["temperature"] == Approx(611.0580090037));
    CHECK( result3["specificVolume"] == Approx(0.0013215616));
    CHECK( result3["specificEnthalpy"] == Approx( 1500 ));
    CHECK( result3["specificEntropy"] == Approx( 3.3530707604 ));

	auto result4 = sp.waterPropertiesPressureEnthalpy(0.001, 3000);
	CHECK( result4["pressure"] == Approx(0.001));
	CHECK( result4["temperature"] == Approx(534.433241));
	CHECK( result4["specificVolume"] == Approx(246.6488133525));
	CHECK( result4["specificEnthalpy"] == Approx( 3000 ));
	CHECK( result4["specificEntropy"] == Approx(10.2066379788));

	auto result5 = sp.waterPropertiesPressureEnthalpy(3, 3000);
	CHECK( result5["pressure"] == Approx(3));
	CHECK( result5["temperature"] == Approx(575.37337));
	CHECK( result5["specificVolume"] == Approx(0.0816111351));
	CHECK( result5["specificEnthalpy"] == Approx( 3000 ));
	CHECK( result5["specificEntropy"] == Approx(6.5510505695));

    // the enthalpy is out of range for this test
//	auto result6 = sp.calculate(3, 4000);
//	CHECK( result6["pressure"] == Approx(3));
//	CHECK( result6["temperature"] == Approx(1010.77577));
//	CHECK( result6["specificVolume"] == Approx(0.0));
//	CHECK( result6["specificEnthalpy"] == Approx( 4000 ));
//	CHECK( result6["specificEntropy"] == Approx( 0.0 ));

	auto result7 = sp.waterPropertiesPressureEnthalpy(5, 3500);
	CHECK( result7["pressure"] == Approx(5));
	CHECK( result7["temperature"] == Approx(801.299102));
	CHECK( result7["specificVolume"] == Approx(0.0714748469));
	CHECK( result7["specificEnthalpy"] == Approx(3500));
	CHECK( result7["specificEntropy"] == Approx(7.0610476389));


	//this enthalpy is out of the acceptable range for this test
//	auto result8 = sp.calculate(5, 4000);
//	CHECK( result8["pressure"] == Approx(5));
//	CHECK( result8["temperature"] == Approx(1015.31583));
//	CHECK( result8["specificVolume"] == Approx(0.0714748469));
//	CHECK( result8["specificEnthalpy"] == Approx(4000));
//	CHECK( result8["specificEntropy"] == Approx(7.0610476389));


	auto result9 = sp.waterPropertiesPressureEnthalpy(25, 3500);
	CHECK( result9["pressure"] == Approx(25));
	CHECK( result9["temperature"] == Approx(875.279054));
	CHECK( result9["specificVolume"] == Approx(0.0141966031));
	CHECK( result9["specificEnthalpy"] == Approx(3500));
	CHECK( result9["specificEntropy"] == Approx(6.3710455092));

	auto result10 = sp.waterPropertiesPressureEnthalpy(40, 2700);
	CHECK( result10["pressure"] == Approx(40));
	CHECK( result10["temperature"] == Approx(743.0656225993));
	CHECK( result10["specificVolume"] == Approx(0.0045639484));
	CHECK( result10["specificEnthalpy"] == Approx(2700));
	CHECK( result10["specificEntropy"] == Approx(5.2016434761));

	auto result11 = sp.waterPropertiesPressureEnthalpy(60, 2700);
	CHECK( result11["pressure"] == Approx(60));
	CHECK( result11["temperature"] == Approx(791.1146921709));
	CHECK( result11["specificVolume"] == Approx(0.003319241));
	CHECK( result11["specificEnthalpy"] == Approx(2700));
	CHECK( result11["specificEntropy"] == Approx(5.1013392134));

	auto result12 = sp.waterPropertiesPressureEnthalpy(60, 3200);
	CHECK( result12["pressure"] == Approx(60));
	CHECK( result12["temperature"] == Approx(882.7697090377));
	CHECK( result12["specificVolume"] == Approx(0.0049873395));
	CHECK( result12["specificEnthalpy"] == Approx(3200));
	CHECK( result12["specificEntropy"] == Approx(5.7018594072));


}

TEST_CASE( "Calculate Steam Properties using Pressure and Entropy", "[waterPropertiesPressureEntropy]") {
    auto sp = SteamProperties(3, SteamProperties::ThermodynamicQuantity::ENTROPY, 0.5);
    auto result1 = sp.calculate();
    CHECK(result1["pressure"] == Approx(3));
    CHECK(result1["temperature"] == Approx(307.842258));
    CHECK(result1["specificVolume"] == Approx(0.0010046046));
    CHECK(result1["specificEnthalpy"] == Approx(148.0634883148));
    CHECK(result1["specificEntropy"] == Approx(0.5));

    auto result2 = sp.waterPropertiesPressureEntropy(80, 0.5);
    CHECK( result2["pressure"] == Approx(80));
    CHECK( result2["temperature"] == Approx(309.979785));
    CHECK( result2["specificVolume"] == Approx(0.0009747722));
    CHECK( result2["specificEnthalpy"] == Approx(224.2263328394));
    CHECK( result2["specificEntropy"] == Approx(0.5));

    auto result3 = sp.waterPropertiesPressureEntropy(80, 3);
    CHECK( result3["pressure"] == Approx(80));
    CHECK( result3["temperature"] == Approx(565.9070416669));
    CHECK( result3["specificVolume"] == Approx(0.0012263315));
    CHECK( result3["specificEnthalpy"] == Approx(1292.2544898841));
    CHECK( result3["specificEntropy"] == Approx(3));

    auto result4 = sp.waterPropertiesPressureEntropy(8, 6);
    CHECK( result4["pressure"] == Approx(8));
    CHECK( result4["temperature"] == Approx(600.48404));
    CHECK( result4["specificVolume"] == Approx(0.0276660137));
    CHECK( result4["specificEnthalpy"] == Approx(2907.378739685));
    CHECK( result4["specificEntropy"] == Approx(6));

    auto result5 = sp.waterPropertiesPressureEntropy(90, 6);
    CHECK( result5["pressure"] == Approx(90));
    CHECK( result5["temperature"] == Approx(1038.01126));
    CHECK( result5["specificVolume"] == Approx(0.00454352));
    CHECK( result5["specificEnthalpy"] == Approx(3628.089478129));
    CHECK( result5["specificEntropy"] == Approx(6));

    auto result6 = sp.waterPropertiesPressureEntropy(20, 5.75);
    CHECK( result6["pressure"] == Approx(20));
    CHECK( result6["temperature"] == Approx(697.992849));
    CHECK( result6["specificVolume"] == Approx(0.0114675187));
    CHECK( result6["specificEnthalpy"] == Approx(2952.1269382186));
    CHECK( result6["specificEntropy"] == Approx(5.75));

    auto result7 = sp.waterPropertiesPressureEntropy(80, 5.25);
    CHECK( result7["pressure"] == Approx(80));
    CHECK( result7["temperature"] == Approx(854.011484));
    CHECK( result7["specificVolume"] == Approx(0.0031462467));
    CHECK( result7["specificEnthalpy"] == Approx(2886.747071315));
    CHECK( result7["specificEntropy"] == Approx(5.25));

    auto result8 = sp.waterPropertiesPressureEntropy(80, 5.75);
    CHECK( result8["pressure"] == Approx(80));
    CHECK( result8["temperature"] == Approx(949.017998));
    CHECK( result8["specificVolume"] == Approx(0.0042610579));
    CHECK( result8["specificEnthalpy"] == Approx(3335.9653473966));
    CHECK( result8["specificEntropy"] == Approx(5.75));
}


