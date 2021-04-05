#include "catch.hpp"
#include <calculator/pump/FluidPower.h>

TEST_CASE( "Calculate Fluid Power for Pumps and Fans", "[FluidPower]" ) {
	CHECK(FluidPower(1.02, 1000, 280.0).calculate() == Approx(53.7836814443));
	CHECK(FluidPower(1.02, 1200, 280.0).calculate() == Approx(64.5404177332));

	CHECK(FluidPower(2000, 20, 25, 1.4, 0).calculate() == Approx(1.6416221314));
	CHECK(FluidPower(1200, 25, 35, 1.4, 0).calculate() == Approx(1.9699465577));
	CHECK(FluidPower(129691, -16.36, 1.1, 0.988, 0).calculate() == Approx(262.3349690747));
	CHECK(FluidPower(151961, -8.92, 2.28, 0.995, 0).calculate() == Approx(198.5721824055));
}
