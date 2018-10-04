#ifndef AMO_TOOLS_SUITE_HEATEXCHANGER_H
#define AMO_TOOLS_SUITE_HEATEXCHANGER_H

#include <stdexcept>
#include "SteamProperties.h"
#include "Header.h"

//class HeatExchanger {
//public:
//    struct Output {
//        Output(SteamProperties hotOutlet, SteamProperties coldOutlet)
//                : hotOutlet(hotOutlet), coldOutlet(coldOutlet)
//        {}
//        SteamProperties hotOutlet, coldOutlet;
//    };
//    /**
//     * Constructor for the HeatExchanger calculator
//     * @param hotInlet const Inlet, must be thermodynamic quantity of temperature or else exception will be thrown
//     * @param coldInlet const Inlet, must be thermodynamic quantity of temperature or else exception will be thrown
//     * @param approachTemp double, default of 20 K
//     * */
//    HeatExchanger(const Inlet hotInlet, const Inlet coldInlet, const double approachTemp = 20)
//            : hotInlet(hotInlet), coldInlet(coldInlet), approachTemp(approachTemp) {
//        if (hotInlet.getQuantityType() != SteamProperties::ThermodynamicQuantity::TEMPERATURE
//            || coldInlet.getQuantityType() != SteamProperties::ThermodynamicQuantity::TEMPERATURE) {
//            throw std::runtime_error("HeatExchanger.h - You must instantiate the Inlet input classes with the ThermodynamicQuantity TEMPERATURE");
//        }
//    }
//
//    Output calculate() {
//        const double maxTempDiff = hotInlet.getQuantityValue() - coldInlet.getQuantityValue();
//        auto hotOutletTest = SteamProperties(
//                hotInlet.getPressure(), SteamProperties::ThermodynamicQuantity::TEMPERATURE, hotInlet.getQuantityValue()
//        ).calculate();
//
//        double heatExchanged = hotInlet.getInletEnergyFlow() - hotOutletTest.internalEnergy;
//        // TODO this should be rearranged to not perform a useless calculation
//        auto coldOutletTest = SteamProperties(
//                coldInlet.getPressure(), SteamProperties::ThermodynamicQuantity::ENTHALPY,
//                (coldInlet.getInletEnergyFlow() + heatExchanged) / coldInlet.getMassFlow() * 1000
//        ).calculate();
//
//        if ((hotOutletTest.temperature - coldInlet.getQuantityValue()) > approachTemp) {
//            coldOutletTest = SteamProperties(
//                    coldInlet.getPressure(), SteamProperties::ThermodynamicQuantity::TEMPERATURE,
//                    hotInlet.getQuantityValue() - approachTemp
//            ).calculate();
//
//            heatExchanged = coldOutletTest.internalEnergy - coldInlet.getInletEnergyFlow();
//            hotOutletTest = SteamProperties(
//                    hotInlet.getPressure(), SteamProperties::ThermodynamicQuantity::ENTHALPY,
//                    (hotInlet.getInletEnergyFlow() - heatExchanged) / hotInlet.getMassFlow() * 1000;
//            ).calculate();
//        }
//        return {hotOutletTest, coldOutletTest};
//    }
//private:
//    Inlet hotInlet, coldInlet;
//    const double approachTemp;
//};

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
                  const double approachTemp = 20)
            : hotInlet(hotInlet), coldInlet(coldInlet), approachTemp(approachTemp)
    {}

    Output calculate() {
        const double maxTempDiff = hotInlet.temperature - coldInlet.temperature;
        auto sp = SteamProperties(
                hotInlet.pressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                coldInlet.temperature + approachTemp
        ).calculate();

        auto hotOutletTest = SteamSystemModelerTool::FluidProperties(hotInlet.massFlow, sp.internalEnergy, sp);

        double heatExchanged = hotInlet.internalEnergy - hotOutletTest.internalEnergy;
        // TODO this should be rearranged to not perform a useless calculation
        sp = SteamProperties(
                coldInlet.pressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                (coldInlet.internalEnergy + heatExchanged) / coldInlet.massFlow * 1000
        ).calculate();

        auto coldOutletTest = SteamSystemModelerTool::FluidProperties(coldInlet.massFlow, sp.internalEnergy, sp);

        if ((hotOutletTest.temperature - coldInlet.temperature) > approachTemp) {
            sp = SteamProperties(
                    coldInlet.pressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                    hotInlet.temperature - approachTemp
            ).calculate();

            coldOutletTest = SteamSystemModelerTool::FluidProperties(coldInlet.massFlow, sp.internalEnergy, sp);

            heatExchanged = coldOutletTest.internalEnergy - coldInlet.internalEnergy;
            sp = SteamProperties(
                    hotInlet.pressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                    (hotInlet.internalEnergy - heatExchanged) / hotInlet.massFlow * 1000
            ).calculate();

            hotOutletTest = SteamSystemModelerTool::FluidProperties(hotInlet.massFlow, sp.internalEnergy, sp);
        }
        return {hotOutletTest, coldOutletTest};
    }
private:
    SteamSystemModelerTool::FluidProperties hotInlet, coldInlet;
    const double approachTemp;
};

#endif //AMO_TOOLS_SUITE_HEATEXCHANGER_H
