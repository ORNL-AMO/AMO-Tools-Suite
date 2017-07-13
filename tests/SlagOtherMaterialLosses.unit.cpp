#include "catch.hpp"
#include <calculator/losses/SlagOtherMaterialLosses.h>
#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>

TEST_CASE( "Calculate SlagOtherMaterialLosses Heat Loss", "[Heat Loss]" ) {
	auto sqlite = SQLite(":memory:", true);
	auto aluminum = sqlite.getSolidLoadChargeMaterialById(1);
	auto slag = SlagOtherMaterialLosses(3, 500, 550, aluminum.getSpecificHeatSolid(), 1.0);
	REQUIRE(slag.getHeatLoss() == Approx(37.1865297349));

	auto bismuth = sqlite.getSolidLoadChargeMaterialById(4);
	slag = SlagOtherMaterialLosses(10, 725, 850, bismuth.getSpecificHeatSolid(), 0.8);
	REQUIRE(slag.getHeatLoss() == Approx(32.9591593026));
}