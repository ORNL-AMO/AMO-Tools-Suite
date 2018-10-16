#include "catch.hpp"
#include <ssmt/HeatExchanger.h>

TEST_CASE( "Test HeatExchanger 1", "[HeatExchanger]" ) {
    auto hotInlet = SteamSystemModelerTool::FluidProperties(3761, 4153, 527, 4.2382, 0, 0.001, 1 / 0.001, 1104.3, 2.828);
    auto coldInlet = SteamSystemModelerTool::FluidProperties(83327, 3510, 283.2, 0.1013, 0, 0.001, 1 / 0.001, 42.1, 0.151);
    auto he = HeatExchanger(hotInlet, coldInlet, 11.111111);

    auto output = he.calculate();

    CHECK(output.hotOutlet.pressure == Approx(4.2382));
    CHECK(output.hotOutlet.temperature == Approx(294.311111));
    CHECK(output.hotOutlet.specificEnthalpy == Approx(92.742848731));
    CHECK(output.hotOutlet.specificEntropy == Approx(0.3121054537));
    CHECK(output.hotOutlet.quality == Approx(0));
    CHECK(output.hotOutlet.specificVolume == Approx(0.0010001635));
    CHECK(output.hotOutlet.massFlow == Approx(3761.0));
    CHECK(output.hotOutlet.energyFlow == Approx(348.8058540774));

    CHECK(output.coldOutlet.pressure == Approx(0.1013));
    CHECK(output.coldOutlet.temperature == Approx(294.0495052176));
    CHECK(output.coldOutlet.specificEnthalpy == Approx(87.7770008031));
    CHECK(output.coldOutlet.specificEntropy == Approx(0.3093027213));
    CHECK(output.coldOutlet.quality == Approx(0));
    CHECK(output.coldOutlet.specificVolume == Approx(0.001));
    CHECK(output.coldOutlet.massFlow == Approx(83327));
    CHECK(output.coldOutlet.energyFlow == Approx(7314.1941459226));
}

TEST_CASE( "Test HeatExchanger 2", "[HeatExchanger]" ) {
    auto hotInlet = SteamSystemModelerTool::FluidProperties(1768, 982, 405.2, 0.2875, 0, 0.001, 1 / 0.001, 555.3, 1.657);
    auto coldInlet = SteamSystemModelerTool::FluidProperties(51922, 1581, 280.4, 0.1013, 0, 0.001, 1 / 0.001, 30.5, 0.110);
    auto he = HeatExchanger(hotInlet, coldInlet, 27.77777777777778);

    auto output = he.calculate();

    CHECK(output.hotOutlet.pressure == Approx(0.2875));
    CHECK(output.hotOutlet.temperature == Approx(308.1777777778));
    CHECK(output.hotOutlet.specificEnthalpy == Approx(147.0142483402));
    CHECK(output.hotOutlet.specificEntropy == Approx(0.5054463436));
    CHECK(output.hotOutlet.quality == Approx(0));
    CHECK(output.hotOutlet.specificVolume == Approx(0.001));
    CHECK(output.hotOutlet.massFlow == Approx(1768));
    CHECK(output.hotOutlet.energyFlow == Approx(259.9211910654));

    CHECK(output.coldOutlet.pressure == Approx(0.1013));
    CHECK(output.coldOutlet.temperature == Approx(283.6834425999));
    CHECK(output.coldOutlet.specificEnthalpy == Approx(44.3565118627));
    CHECK(output.coldOutlet.specificEntropy == Approx(0.158972121));
    CHECK(output.coldOutlet.quality == Approx(0));
    CHECK(output.coldOutlet.specificVolume == Approx(0.001));
    CHECK(output.coldOutlet.massFlow == Approx(51922));
    CHECK(output.coldOutlet.energyFlow == Approx(2303.0788089347));
}
