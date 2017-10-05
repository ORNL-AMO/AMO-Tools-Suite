#include <catch.hpp>
#include "ssmt/Header.h"

TEST_CASE( "Calculate Header properties", "[Header][ssmt]") {
	auto qualityType = SteamProperties::ThermodynamicQuantity::TEMPERATURE;
	std::vector<Inlet> inlets = {
			Inlet(1.9332, qualityType, 579.8, 0.686), Inlet(2.8682, qualityType, 308.5, 0.5019)
	};

	auto header = Header(0.173, inlets);
	CHECK(header.getSpecificEnthalpy() == Approx(1820.064143168));

	inlets = {
			Inlet(1.9332, qualityType, 579.8, 0.686), Inlet(2.8682, qualityType, 308.5, 0.5019),
			Inlet(1.0348, qualityType, 458, 0.5633), Inlet(1.8438, qualityType, 475.8, 0.3082)
	};

	header.setInlets(inlets);
	CHECK(header.getSpecificEnthalpy() == Approx(1941.73683349));
	CHECK(header.getHeaderProperties().at("temperature") == Approx(388.8366691795));
	CHECK(header.getHeaderProperties().at("quality") == Approx(0.65771447961));

	header.setHeaderPressure(0.15);
	header.setHeaderPressure(0.173);
	CHECK(header.getHeaderProperties().at("quality") == Approx(0.65771447961));
}
