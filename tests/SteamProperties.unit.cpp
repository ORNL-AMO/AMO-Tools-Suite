//
// Created by Preston Shires on 7/19/17.
//

#include "catch.hpp"
#include <ssmt/SteamProperties.h>

TEST_CASE( "Calculate Heat Loss for liquid cooling Losses ethylene glycon", "[Heat Loss][Ethylene Glycon][Liquid]") {
	auto properties = SteamProperties(SteamProperties::ThermodynamicQuantity::TEMPERATURE);
//	properties.calculate(500.0, 1000.0);

}
