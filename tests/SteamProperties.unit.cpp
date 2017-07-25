//
// Created by Preston Shires on 7/19/17.
//

#include "catch.hpp"
#include <ssmt/SteamProperties.h>
#include <ssmt/SteamSystemModelerTool.h>

TEST_CASE( "steam properties calculate", "[idk]") {
	auto properties = SteamProperties(SteamProperties::ThermodynamicQuantity::TEMPERATURE);
	auto rv = properties.calculate(1000.0, 500.0);

	for ( auto const it : rv ) {
		std::string key = it.first;
		double val = it.second;
		auto breakPointHere = 0;
	}
}

TEST_CASE( "Calculate the Steam Properties Using Temperature", "[Steam Properties][ssmt][Calculator]") {
	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::TEMPERATURE).calculate(50, 300);
	CHECK( test["pressure"] == Approx(50.0));
	CHECK( test["temperature"] == Approx(300));
	CHECK( test["specificEnthalpy"] == Approx(157.7656843556));
	CHECK( test["specificEntropy"] == Approx(0.3783149091));
	CHECK( test["quality"] == Approx(0));
	CHECK( test["specificVolume"] == Approx(0.0009824691));
}

TEST_CASE( "Calculate the Steam Properties Using Specific Enthalpy", "[Steam Properties][ssmt][Calculator]") {
	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTHALPY).calculate(50, 60);
	CHECK( test["pressure"] == Approx(50.0));
	CHECK( test["temperature"] == Approx(275.8561282609));
	CHECK( test["specificEnthalpy"] == Approx(60.0));
	CHECK( test["specificEntropy"] == Approx(0.0386641323));
	CHECK( test["quality"] == Approx(0));
	CHECK( test["specificVolume"] == Approx(0.0009770201));
}

//TEST_CASE( "Calculate the Steam Properties Using Specific Entropy", "[Steam Properties][ssmt][Calculator]") {
//	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::ENTROPY).calculate(50, 4);
//	CHECK( test["pressure"] == Approx(50.0));
//	CHECK( test["temperature"] == Approx(672.9));
//	CHECK( test["specificEnthalpy"] == Approx(1872.4));
//	CHECK( test["specificEntropy"] == Approx(4.0));
//	CHECK( test["quality"] == Approx(0));
//	CHECK( test["specificVolume"] == Approx(0.002));
//}

TEST_CASE( "Calculate the Steam Properties Using Specific Quality", "[Steam Properties][ssmt][Calculator]") {
	std::unordered_map <std::string, double> test = SteamProperties(SteamProperties::ThermodynamicQuantity::QUALITY).calculate(20, 0.6);
	CHECK( test["pressure"] == Approx(20.0));
	CHECK( test["temperature"] == Approx(638.9));
	CHECK( test["specificEnthalpy"] == Approx(2183.8485753012));
	CHECK( test["specificEntropy"] == Approx(4.5737534333));
	CHECK( test["quality"] == Approx(0.6));
	CHECK( test["specificVolume"] == Approx(0.0043775714));
}

TEST_CASE( "Ctest", "[Steam Properties][ssmt][Calculator]") {
	Point test = SteamSystemModelerTool::generatePoint(3, SteamSystemModelerTool::Key::ENTHALPY, 5, 8);
	CHECK( test.getX() == Approx(20.0));

}

TEST_CASE( "test", "[Steam Properties][ssmt][Calculator]") {
    CHECK( SteamSystemModelerTool::backwardPressureEnthalpyRegion2B(25, 3849.1) == Approx(275.9));
}

