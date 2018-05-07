#include "catch.hpp"
#include <fans/CompressibilityFactor.h>

TEST_CASE( "Calculate Compressibility Factor", "[Fans][Compressibility]") {
	CHECK(CompressibilityFactor(300, -8.5, 3, 29, 1000, 1.4).calculate() == Approx(1.5795535958));
	CHECK(CompressibilityFactor(566, -16.36, 1.1, 29.36, 129691, 1.4).calculate() == Approx(0.9879934727));
	CHECK(CompressibilityFactor(623, -8.92, 2.28, 29.36, 151961, 1.4).calculate() == Approx(0.9953146218));
}