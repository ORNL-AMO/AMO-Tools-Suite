#include <cmath>
#include "calculator/util/Conversion.h"

double Conversion::fractionToPercent() {
    return x * 100.0;
}

double Conversion::percentToFraction() {
    return x / 100.0;
}

double Conversion::manualConversion(double factor) {
    return x * factor;
}