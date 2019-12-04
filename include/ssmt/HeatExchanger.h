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

    friend std::ostream &operator<<(std::ostream &stream, const HeatExchanger::Output &output) {
        stream << "HeatExchanger::Output["
               << "hotOutlet=" << output.hotOutlet
               << ", coldOutlet=" << output.coldOutlet
               << "]";
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<HeatExchanger::Output> &turbine) {
        if (turbine == nullptr) {
            stream << "HeatExchanger::Output[nullptr]";
        } else {
            stream << *turbine;
        }
        return stream;
    }

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
                hotInlet.massFlow, hotInlet.massFlow * sp.specificEnthalpy, sp
        );

        double heatExchanged = hotInlet.energyFlow - hotOutletTest.energyFlow;
        // TODO this should be rearranged to not perform a useless calculation
        sp = SteamProperties(
                coldInlet.pressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                (coldInlet.energyFlow + heatExchanged) / coldInlet.massFlow
        ).calculate();

        auto coldOutletTest = SteamSystemModelerTool::FluidProperties(
                coldInlet.massFlow, coldInlet.massFlow * sp.specificEnthalpy, sp
        );

        if (fabs((hotOutletTest.temperature - coldInlet.temperature) - approachTemp) > .0001) {
            sp = SteamProperties(
                    coldInlet.pressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                    hotInlet.temperature - approachTemp
            ).calculate();

            coldOutletTest = SteamSystemModelerTool::FluidProperties(
                    coldInlet.massFlow, coldInlet.massFlow * sp.specificEnthalpy, sp
            );

            heatExchanged = coldOutletTest.energyFlow - coldInlet.energyFlow;
            sp = SteamProperties(
                    hotInlet.pressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                    (hotInlet.energyFlow - heatExchanged) / hotInlet.massFlow
            ).calculate();

            hotOutletTest = SteamSystemModelerTool::FluidProperties(
                    hotInlet.massFlow, hotInlet.massFlow * sp.specificEnthalpy, sp
            );
        }
        return {hotOutletTest, coldOutletTest};
    }
private:
    SteamSystemModelerTool::FluidProperties hotInlet, coldInlet;
    const double approachTemp;
};

#endif //AMO_TOOLS_SUITE_HEATEXCHANGER_H
