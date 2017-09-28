#include <catch.hpp>
#include "ssmt/Turbine.h"


TEST_CASE( "Turbine", "[Turbine]") {

	auto t = Turbine(Turbine::Solve::OutletProperties, 4.2112, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 888, Turbine::TurbineProperty::MassFlow, 40.1, 94.2, 15844, 3.4781);
	CHECK( t.getInletProperties().at("specificEnthalpy") == Approx(3707.3971175332));
	CHECK( t.getInletProperties().at("specificEntropy") == Approx(7.384097768));
	CHECK( t.getInletEnergyFlow() == Approx(58739999.9301967993));
	CHECK( t.getEnergyOut() == Approx(479149.9032211461));
	CHECK( t.getPowerOut() == Approx(451359.208834319));

	t = Turbine(Turbine::Solve::OutletProperties, 4.2112, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 888, Turbine::TurbineProperty::PowerOut, 40.1, 94.2, 1000, 3.4781);
	CHECK( t.getInletProperties().at("specificEnthalpy") == Approx(3707.3971175332));
	CHECK( t.getInletProperties().at("specificEntropy") == Approx(7.384097768));
	CHECK( t.getInletEnergyFlow() == Approx(130140));

	CHECK( t.getOutletProperties().at("specificEnthalpy") == Approx(3677.1553917556));
	CHECK( t.getOutletProperties().at("specificEntropy") == Approx(7.4364791785));
	CHECK( t.getOutletEnergyFlow() == Approx(129079));
	CHECK( t.getMassFlow() == Approx(35.1028619554));
	CHECK( t.getEnergyOut() == Approx(1061.5711252654));
	CHECK( t.getPowerOut() == Approx(1000));
}