#ifndef AMO_TOOLS_SUITE_HEATEXCHANGER_H
#define AMO_TOOLS_SUITE_HEATEXCHANGER_H

#include <stdexcept>
#include "SteamProperties.h"
#include "Header.h"

class HeatExchanger {
public:
    struct Output {
        Output(SteamSystemModelerTool::FluidProperties hotOutlet, SteamSystemModelerTool::FluidProperties coldOutlet)
                : hotOutlet(hotOutlet), coldOutlet(coldOutlet)
        {}
        SteamSystemModelerTool::FluidProperties hotOutlet, coldOutlet;
    };
    /**
     * Constructor for the HeatExchanger calculator
     * @param hotInlet const Inlet, must be thermodynamic quantity of temperature or else exception will be thrown
     * @param coldInlet const Inlet, must be thermodynamic quantity of temperature or else exception will be thrown
     * @param approachTemp double, default of 20 K
     * */
    HeatExchanger(const SteamSystemModelerTool::FluidProperties hotInlet,
                  const SteamSystemModelerTool::FluidProperties coldInlet,
                  const double approachTemp = 20
    )
            : hotInlet(hotInlet), coldInlet(coldInlet), approachTemp(approachTemp)
    {}

    Output calculate() {
        auto sp = SteamProperties(
                hotInlet.pressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                coldInlet.temperature + approachTemp
        ).calculate();

        auto hotOutletTest = SteamSystemModelerTool::FluidProperties(
                hotInlet.massFlow, hotInlet.massFlow * sp.specificEnthalpy / 1000, sp
        );

        double heatExchanged = hotInlet.energyFlow - hotOutletTest.energyFlow;
        // TODO this should be rearranged to not perform a useless calculation
        sp = SteamProperties(
                coldInlet.pressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                (coldInlet.energyFlow + heatExchanged) / coldInlet.massFlow * 1000
        ).calculate();

        auto coldOutletTest = SteamSystemModelerTool::FluidProperties(
                coldInlet.massFlow, coldInlet.massFlow * sp.specificEnthalpy / 1000, sp
        );

        if ((hotOutletTest.temperature - coldInlet.temperature) > approachTemp) {
            sp = SteamProperties(
                    coldInlet.pressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                    hotInlet.temperature - approachTemp
            ).calculate();

            coldOutletTest = SteamSystemModelerTool::FluidProperties(
                    coldInlet.massFlow, coldInlet.massFlow * sp.specificEnthalpy / 1000, sp
            );

            heatExchanged = coldOutletTest.energyFlow - coldInlet.energyFlow;
            sp = SteamProperties(
                    hotInlet.pressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                    (hotInlet.energyFlow - heatExchanged) / hotInlet.massFlow * 1000
            ).calculate();

            hotOutletTest = SteamSystemModelerTool::FluidProperties(
                    hotInlet.massFlow, hotInlet.massFlow * sp.specificEnthalpy / 1000, sp
            );
        }
        return {hotOutletTest, coldOutletTest};
    }
private:
    SteamSystemModelerTool::FluidProperties hotInlet, coldInlet;
    const double approachTemp;
};

#endif //AMO_TOOLS_SUITE_HEATEXCHANGER_H
