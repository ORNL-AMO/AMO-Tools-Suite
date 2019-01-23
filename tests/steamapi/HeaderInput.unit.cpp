#include <iostream>
#include "catch.hpp"
#include "ssmt/api/HeaderInput.h"

void verifyHeader(const HeaderWithHighestPressure &actualHeader, const HeaderWithHighestPressure &expectedHeader) {
    CHECK(actualHeader.getCondensateReturnTemperature() == expectedHeader.getCondensateReturnTemperature());
    CHECK(actualHeader.getCondensationRecoveryRate() == expectedHeader.getCondensationRecoveryRate());
    CHECK(actualHeader.getHeatLoss() == expectedHeader.getHeatLoss());
    CHECK(actualHeader.getPressure() == expectedHeader.getPressure());
    CHECK(actualHeader.getProcessSteamUsage() == expectedHeader.getProcessSteamUsage());
    CHECK(actualHeader.isFlashCondensate() == expectedHeader.isFlashCondensate());
}

void verifyHeader(std::shared_ptr<HeaderNotHighestPressure> actualHeader, std::shared_ptr<HeaderNotHighestPressure> expectedHeader) {
    CHECK(actualHeader->getCondensationRecoveryRate() == expectedHeader->getCondensationRecoveryRate());
    CHECK(actualHeader->getDesuperheatSteamTemperature() == expectedHeader->getDesuperheatSteamTemperature());
    CHECK(actualHeader->getHeatLoss() == expectedHeader->getHeatLoss());
    CHECK(actualHeader->getPressure() == expectedHeader->getPressure());
    CHECK(actualHeader->getProcessSteamUsage() == expectedHeader->getProcessSteamUsage());
    CHECK(actualHeader->isDesuperheatSteamIntoNextHighest() == expectedHeader->isDesuperheatSteamIntoNextHighest());
    CHECK(actualHeader->isFlashCondensate() == expectedHeader->isFlashCondensate());
}

TEST_CASE("HeaderInputConstructor All Args", "[Header input constructor]") {
    auto high = HeaderWithHighestPressure(1, 1, 1, 1, 1, true);
    auto medium = std::make_shared<HeaderNotHighestPressure>(2, 2, 2, 2, true, true, 2);
    auto low = std::make_shared<HeaderNotHighestPressure>(3, 3, 3, 3, true, true, 3);

    auto actual = HeaderInput(high, medium, low);
    auto actualHigh = actual.getHighPressureHeader();
    auto actualMedium = actual.getMediumPressureHeader();
    auto actualLow = actual.getLowPressureHeader();

    verifyHeader(actualHigh, high);
    verifyHeader(actualMedium, medium);
    verifyHeader(actualLow, low);
}

TEST_CASE("HeaderInputConstructor Required Args Only", "[Header input constructor]") {
    auto high = HeaderWithHighestPressure(1, 1, 1, 1, 1, true);
    auto medium = std::shared_ptr<HeaderNotHighestPressure>(nullptr);
    auto low = std::shared_ptr<HeaderNotHighestPressure>(nullptr);

    auto actual = HeaderInput(high, medium, low);
    auto actualHigh = actual.getHighPressureHeader();
    auto actualMedium = actual.getMediumPressureHeader();
    auto actualLow = actual.getLowPressureHeader();

    verifyHeader(actualHigh, high);
    CHECK(actualMedium == medium);
    CHECK(actualLow == low);
}
