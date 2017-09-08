#include "catch.hpp"
#include <ssmt/SteamProperties.h>
#include <ssmt/SteamSystemModelerTool.h>

//TEST_CASE( "region 1", "[region 1]") {
//	auto result = SteamSystemModelerTool::region1(300, 15);
//	CHECK( result["pressure"] == Approx(15.0));
//	CHECK( result["temperature"] == Approx(300));
//	CHECK( result["specificEnthalpy"] == Approx(126.3055708813));
//	CHECK( result["specificEntropy"] == Approx(0.3888958577));
//	CHECK( result["quality"] == Approx(0));
//	CHECK( result["specificVolume"] == Approx(0.0009968749));
//
//	result = SteamSystemModelerTool::region1(SteamSystemModelerTool::TEMPERATURE_Tp, 25.58);
//	CHECK( result["pressure"] == Approx(25.58));
//	CHECK( result["temperature"] == Approx(623.15));
//	CHECK( result["specificEnthalpy"] == Approx(1621.84698));
//	CHECK( result["specificEntropy"] == Approx(3.6756));
//	CHECK( result["specificVolume"] == Approx(0.001592707));
//	CHECK( result["density"] == Approx(627.8616834));
//}
//
//TEST_CASE( "region3Density", "[region3Density]") {
//	auto result = SteamSystemModelerTool::region3Density(627.8616834, 650);
//	CHECK( result["pressure"] == Approx(46.90039363463));
//	CHECK( result["temperature"] == Approx(650));
//	CHECK( result["specificVolume"] == Approx(0.0015927074805465));
//	CHECK( result["density"] == Approx(627.86168346299));
//	CHECK( result["specificEnthalpy"] == Approx(1734.6938311862));
//	CHECK( result["specificEntropy"] == Approx(3.7995608137168));
//	CHECK( result["internalEnergy"] == Approx(1659.9952234038));
//}
//
//TEST_CASE( "boundaryByPressureRegion3to2", "[boundaryByPressureRegion3to2]") {
//	auto result = SteamSystemModelerTool::boundaryByPressureRegion3to2(25.58);
//	CHECK( result == Approx(679.50438021013));
//}
//
//TEST_CASE( "region 2", "[region 2]") {
//	auto result = SteamSystemModelerTool::region2(679.50438021013, 25.58);
//	CHECK( result["pressure"] == Approx(25.58));
//	CHECK( result["temperature"] == Approx(679.50438021013));
//	CHECK( result["specificVolume"] == Approx(0.006211616555293));
//	CHECK( result["density"] == Approx(160.98868806509));
//	CHECK( result["specificEnthalpy"] == Approx(2621.5406472142));
//	CHECK( result["specificEntropy"] == Approx(5.198131771144));
//}
//
//TEST_CASE( "region 3", "[region 3]") {
//	auto result = SteamSystemModelerTool::region3(650, 25.58);
//	CHECK( result["density"] == Approx(499.93601366213));
//	CHECK( result["specificVolume"] == Approx(0.0020002559781097));
//	CHECK( result["internalEnergy"] == Approx(1812.3374452641));
//	CHECK( result["specificEnthalpy"] == Approx(1863.5039931841));
//	CHECK( result["specificEntropy"] == Approx(4.0543976678954));
//}

TEST_CASE( "waterPropertiesPressureTemperature", "[waterPropertiesPressureTemp]") {
	auto const quality = SteamProperties::ThermodynamicQuantity::TEMPERATURE;
	auto result = SteamProperties(25.58, quality, 650).calculate();
	CHECK( result["density"] == Approx(499.93601366213));
	CHECK( result["specificVolume"] == Approx(0.0020002559781097));
	CHECK( result["internalEnergy"] == Approx(1812.3374452641));
	CHECK( result["specificEnthalpy"] == Approx(1863.5039931841));
	CHECK( result["specificEntropy"] == Approx(4.0543976678954));

	result = SteamProperties(3, quality, 300).calculate();
	CHECK( result["specificVolume"] == Approx(0.001));
	CHECK( result["specificEnthalpy"] == Approx(115.3312730214));
	CHECK( result["specificEntropy"] == Approx(0.3922947924));

	result = SteamProperties(3, quality, 500).calculate();
	CHECK( result["specificEnthalpy"] == Approx(975.542239097));
	CHECK( result["specificEntropy"] == Approx(2.5804191201));
	CHECK( result["specificVolume"] == Approx(0.001202418));

	result = SteamProperties(80, quality, 300).calculate();
	CHECK( result["specificEnthalpy"] == Approx(184.142828));
	CHECK( result["specificEntropy"] == Approx(0.368563852));
	CHECK( result["specificVolume"] == Approx(0.000971181));

	result = SteamProperties(80, quality, 500).calculate();
	CHECK( result["specificEnthalpy"] == Approx(1005.1696722456));
	CHECK( result["specificEntropy"] == Approx(2.4609385983));
	CHECK( result["specificVolume"] == Approx(0.00112629));

	// region 2 areas
	result = SteamProperties(0.0035, quality, 300).calculate();
	CHECK( result["specificEnthalpy"] == Approx(2549.9));
	CHECK( result["specificEntropy"] == Approx(8.5223896673));
	CHECK( result["specificVolume"] == Approx(39.491));

	result = SteamProperties(0.0035, quality, 700).calculate();
	CHECK( result["specificEnthalpy"] == Approx(3335.7));
	CHECK( result["specificEntropy"] == Approx(10.175));
	CHECK( result["specificVolume"] == Approx(92.302));

	result = SteamProperties(30, quality, 700).calculate();
	CHECK( result["specificEnthalpy"] == Approx(2631.4947448448));
	CHECK( result["specificEntropy"] == Approx(5.1754029823));
	CHECK( result["specificVolume"] == Approx(0.0054294662));

	result = SteamProperties(1, quality, 450).calculate();
	CHECK( result["specificEnthalpy"] == Approx(749.3284821858));
	CHECK( result["specificEntropy"] == Approx(2.108854683));
	CHECK( result["specificVolume"] == Approx(0.0011231015));

	result = SteamProperties(1, quality, 440).calculate();
	CHECK( result["specificEnthalpy"] == Approx(705.5753461629));
	CHECK( result["specificEntropy"] == Approx(2.0105303763));
	CHECK( result["specificVolume"] == Approx(0.0011101036));

	result = SteamProperties(1.5, quality, 450).calculate();
	CHECK( result["specificEnthalpy"] == Approx(749.5873697011));
	CHECK( result["specificEntropy"] == Approx(2.1081823281));
	CHECK( result["specificVolume"] == Approx(0.0011226877));

	// region 3 areas
	result = SteamProperties(25.6, quality, 650).calculate();
	CHECK( result["specificEnthalpy"] == Approx(1863.1063178273));
	CHECK( result["specificEntropy"] == Approx(4.0537243346));
	CHECK( result["specificVolume"] == Approx(0.002));

	result = SteamProperties(22.293064, quality, 650).calculate();
	CHECK( result["specificEnthalpy"] == Approx(2375.12401));
	CHECK( result["specificEntropy"] == Approx(4.8543880077));
	CHECK( result["specificVolume"] == Approx(0.0050000005));

	result = SteamProperties(78.3, quality, 750).calculate();
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
	auto const quality = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    auto result = SteamProperties(3, quality, 500).calculate();
    CHECK( result["pressure"] == Approx(3));
    CHECK( result["temperature"] == Approx( 391.791991375 ));
    CHECK( result["specificVolume"] == Approx(0.0010575419));
    CHECK( result["specificEnthalpy"] == Approx(500 ));
    CHECK( result["specificEntropy"] == Approx(1.5106138266 ));

	result = SteamProperties(80, quality, 500).calculate();
    CHECK( result["pressure"] == Approx(80));
    CHECK( result["temperature"] == Approx(378.1241736021));
    CHECK( result["specificVolume"] == Approx(.001));
    CHECK( result["specificEnthalpy"] == Approx( 500 ));
    CHECK( result["specificEntropy"] == Approx(1.304));

	result = SteamProperties(80, quality, 1500).calculate();
    CHECK( result["pressure"] == Approx(80));
    CHECK( result["temperature"] == Approx(611.0580090037));
    CHECK( result["specificVolume"] == Approx(0.0013215616));
    CHECK( result["specificEnthalpy"] == Approx( 1500 ));
    CHECK( result["specificEntropy"] == Approx( 3.3530707604 ));

	result = SteamProperties(0.001, quality, 3000).calculate();
	CHECK( result["pressure"] == Approx(0.001));
	CHECK( result["temperature"] == Approx(534.433241));
	CHECK( result["specificVolume"] == Approx(246.6488133525));
	CHECK( result["specificEnthalpy"] == Approx( 3000 ));
	CHECK( result["specificEntropy"] == Approx(10.2066379788));

	result = SteamProperties(3, quality, 3000).calculate();
	CHECK( result["pressure"] == Approx(3));
	CHECK( result["temperature"] == Approx(575.37337));
	CHECK( result["specificVolume"] == Approx(0.0816111351));
	CHECK( result["specificEnthalpy"] == Approx( 3000 ));
	CHECK( result["specificEntropy"] == Approx(6.5510505695));

	result = SteamProperties(5, quality, 3500).calculate();
	CHECK( result["pressure"] == Approx(5));
	CHECK( result["temperature"] == Approx(801.299102));
	CHECK( result["specificVolume"] == Approx(0.0714748469));
	CHECK( result["specificEnthalpy"] == Approx(3500));
	CHECK( result["specificEntropy"] == Approx(7.0610476389));

	result = SteamProperties(25, quality, 3500).calculate();
	CHECK( result["pressure"] == Approx(25));
	CHECK( result["temperature"] == Approx(875.279054));
	CHECK( result["specificVolume"] == Approx(0.0141966031));
	CHECK( result["specificEnthalpy"] == Approx(3500));
	CHECK( result["specificEntropy"] == Approx(6.3710455092));

	result = SteamProperties(40, quality, 2700).calculate();
	CHECK( result["pressure"] == Approx(40));
	CHECK( result["temperature"] == Approx(743.0656225993));
	CHECK( result["specificVolume"] == Approx(0.0045639484));
	CHECK( result["specificEnthalpy"] == Approx(2700));
	CHECK( result["specificEntropy"] == Approx(5.2016434761));

	result = SteamProperties(60, quality, 2700).calculate();
	CHECK( result["pressure"] == Approx(60));
	CHECK( result["temperature"] == Approx(791.1146921709));
	CHECK( result["specificVolume"] == Approx(0.003319241));
	CHECK( result["specificEnthalpy"] == Approx(2700));
	CHECK( result["specificEntropy"] == Approx(5.1013392134));

	result = SteamProperties(60, quality, 3200).calculate();
	CHECK( result["pressure"] == Approx(60));
	CHECK( result["temperature"] == Approx(882.7697090377));
	CHECK( result["specificVolume"] == Approx(0.0049873395));
	CHECK( result["specificEnthalpy"] == Approx(3200));
	CHECK( result["specificEntropy"] == Approx(5.7018594072));
}

TEST_CASE( "Calculate Steam Properties using Pressure and Entropy", "[waterPropertiesPressureEntropy]") {
	auto const quality = SteamProperties::ThermodynamicQuantity::ENTROPY;
    auto result = SteamProperties(3, quality, 0.5).calculate();
    CHECK(result["pressure"] == Approx(3));
    CHECK(result["temperature"] == Approx(307.842258));
    CHECK(result["specificVolume"] == Approx(0.0010046046));
    CHECK(result["specificEnthalpy"] == Approx(148.0634883148));
    CHECK(result["specificEntropy"] == Approx(0.5));

	result = SteamProperties(80, quality, 0.5).calculate();
    CHECK( result["pressure"] == Approx(80));
    CHECK( result["temperature"] == Approx(309.979785));
    CHECK( result["specificVolume"] == Approx(0.0009747722));
    CHECK( result["specificEnthalpy"] == Approx(224.2263328394));
    CHECK( result["specificEntropy"] == Approx(0.5));

	result = SteamProperties(80, quality, 3).calculate();
    CHECK( result["pressure"] == Approx(80));
    CHECK( result["temperature"] == Approx(565.9070416669));
    CHECK( result["specificVolume"] == Approx(0.0012263315));
    CHECK( result["specificEnthalpy"] == Approx(1292.2544898841));
    CHECK( result["specificEntropy"] == Approx(3));

	result = SteamProperties(8, quality, 6).calculate();
    CHECK( result["pressure"] == Approx(8));
    CHECK( result["temperature"] == Approx(600.48404));
    CHECK( result["specificVolume"] == Approx(0.0276660137));
    CHECK( result["specificEnthalpy"] == Approx(2907.378739685));
    CHECK( result["specificEntropy"] == Approx(6));

	result = SteamProperties(90, quality, 6).calculate();
    CHECK( result["pressure"] == Approx(90));
    CHECK( result["temperature"] == Approx(1038.01126));
    CHECK( result["specificVolume"] == Approx(0.00454352));
    CHECK( result["specificEnthalpy"] == Approx(3628.089478129));
    CHECK( result["specificEntropy"] == Approx(6));

	result = SteamProperties(20, quality, 5.75).calculate();
    CHECK( result["pressure"] == Approx(20));
    CHECK( result["temperature"] == Approx(697.992849));
    CHECK( result["specificVolume"] == Approx(0.0114675187));
    CHECK( result["specificEnthalpy"] == Approx(2952.1269382186));
    CHECK( result["specificEntropy"] == Approx(5.75));

	result = SteamProperties(80, quality, 5.25).calculate();
    CHECK( result["pressure"] == Approx(80));
    CHECK( result["temperature"] == Approx(854.011484));
    CHECK( result["specificVolume"] == Approx(0.0031462467));
    CHECK( result["specificEnthalpy"] == Approx(2886.747071315));
    CHECK( result["specificEntropy"] == Approx(5.25));

	result = SteamProperties(80, quality, 5.75).calculate();
    CHECK( result["pressure"] == Approx(80));
    CHECK( result["temperature"] == Approx(949.017998));
    CHECK( result["specificVolume"] == Approx(0.0042610579));
    CHECK( result["specificEnthalpy"] == Approx(3335.9653473966));
    CHECK( result["specificEntropy"] == Approx(5.75));
}
