#include <catch.hpp>
#include "calculator/util/CurveFitVal.h"

TEST_CASE( "CurveFitVal", "[CurveFitVal]") {
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.25).calculate() == Approx(0.93));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.5).calculate() == Approx(0.94));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.75).calculate() == Approx(0.95));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 1).calculate() == Approx(0.956));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 1.25).calculate() == Approx(0.949));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.15).calculate() == Approx(0.925944));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.35).calculate() == Approx(0.933952));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.45).calculate() == Approx(0.93796));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.55).calculate() == Approx(0.942056));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.65).calculate() == Approx(0.946144));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.85).calculate() == Approx(0.953272));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 0.95).calculate() == Approx(0.95548));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 1.15).calculate() == Approx(0.954144));
	CHECK(CurveFitVal({.25, .50, .75, 1.00, 1.25}, {0.93, 0.94, 0.95, 0.956, 0.949}, 4, 1.5).calculate() == Approx(0.915));
}