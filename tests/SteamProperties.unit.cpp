//
// Created by Preston Shires on 7/19/17.
//

#include "catch.hpp"
#include <ssmt/SteamProperties.h>

TEST_CASE( "steam properties calculate", "[idk]") {
	auto properties = SteamProperties(SteamProperties::ThermodynamicQuantity::TEMPERATURE);
	auto rv = properties.calculate(1000.0, 500.0);

	for ( auto const it : rv ) {
		std::string key = it.first;
		double val = it.second;
		auto breakPointHere = 0;
	}
}
