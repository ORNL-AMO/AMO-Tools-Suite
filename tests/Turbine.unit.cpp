#include <catch.hpp>
#include "ssmt/Turbine.h"


TEST_CASE( "Turbine", "[Turbine]") {

	auto t = Turbine(Turbine::Solve::OutletProperties, 4.2112, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 888,
	                 Turbine::TurbineProperty::MassFlow, 40.1, 94.2, 15844, 3.4781);
	CHECK( t.getInletProperties().specificEnthalpy == Approx(3707.3971175332));
	CHECK( t.getInletProperties().specificEntropy == Approx(7.384097768));
	CHECK( t.getInletEnergyFlow() == Approx(58739999.9301967993));
	CHECK( t.getEnergyOut() == Approx(479149.9032));
	CHECK( t.getPowerOut() == Approx(451359.2088));

	t = Turbine(Turbine::Solve::OutletProperties, 4.2112, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 888,
	            Turbine::TurbineProperty::PowerOut, 40.1, 94.2, 1000, 3.4781);
	CHECK( t.getInletProperties().specificEnthalpy == Approx(3707.3971175332));
	CHECK( t.getInletProperties().specificEntropy == Approx(7.384097768));
	CHECK( t.getInletEnergyFlow() == Approx(130140));

	CHECK( t.getOutletProperties().specificEnthalpy == Approx(3677.1553917556));
	CHECK( t.getOutletProperties().specificEntropy == Approx(7.4364791785));
	CHECK( t.getOutletEnergyFlow() == Approx(129079));
	CHECK( t.getMassFlow() == Approx(35.1028619554));
	CHECK( t.getEnergyOut() == Approx(1061.5711252654));
	CHECK( t.getPowerOut() == Approx(1000));


	t = Turbine(Turbine::Solve::IsentropicEfficiency, 5.3511, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
	            824.7, Turbine::TurbineProperty::MassFlow, 88.1, 28581, 0.5846,
	            SteamProperties::ThermodynamicQuantity::TEMPERATURE, 623.8);

	CHECK( t.getInletProperties().specificEnthalpy == Approx(3551));
	CHECK( t.getInletProperties().specificEntropy == Approx(7.0935165312));
	CHECK( t.getInletEnergyFlow() == Approx(101491776.0236083418));

	CHECK( t.getOutletProperties().specificEnthalpy == Approx(3167.7566746314));
	CHECK( t.getOutletProperties().specificEntropy == Approx(7.5625702284));
	CHECK( t.getOutletEnergyFlow() == Approx(90537653.5176413357));
	CHECK( t.getMassFlow() == Approx(28581.0));
	CHECK( t.getEnergyOut() == Approx(10954122.5059));
	CHECK( t.getPowerOut() == Approx(9650581.9278));

	t = Turbine(Turbine::Solve::IsentropicEfficiency, 5.3511, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
	            824.7, Turbine::TurbineProperty::PowerOut, 88.1, 1000, 0.5846,
	            SteamProperties::ThermodynamicQuantity::TEMPERATURE, 623.8);

	CHECK( t.getInletProperties().specificEnthalpy == Approx(3551));
	CHECK( t.getInletProperties().specificEntropy == Approx(7.0935165312));
	CHECK( t.getInletEnergyFlow() == Approx(10516.6482999));

	CHECK( t.getOutletProperties().specificEnthalpy == Approx(3167.7566746314));
	CHECK( t.getOutletProperties().specificEntropy == Approx(7.5625702284));
	CHECK( t.getOutletEnergyFlow() == Approx(9381.57452));
	CHECK( t.getMassFlow() == Approx(2.9615830645));
	CHECK( t.getEnergyOut() == Approx(1135.0737797957));
	CHECK( t.getPowerOut() == Approx(1000));
}
