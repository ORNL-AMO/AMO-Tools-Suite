//
// Created by 7bo on 11/17/2020.
// Estimate maximum air flow that can be heated by using exhaust gas heat
// of flue gases from a furnace or oven or a boiler
//

#ifndef AMO_TOOLS_SUITE_AIRHEATINGUSINGEXHAUST_H
#define AMO_TOOLS_SUITE_AIRHEATINGUSINGEXHAUST_H

#include "../losses/GasFlueGasMaterial.h"
#include "../losses/SolidLiquidFlueGasMaterial.h"

class AirHeatingUsingExhaust {
public:
    struct Output
    {
        Output(double hxColdAir, double hxOutletExhaust, double energySavings, double heatCapacityFlue, double heatCapacityAir) :
        hxColdAir(hxColdAir), hxOutletExhaust(hxOutletExhaust), energySavings(energySavings), heatCapacityFlue(heatCapacityFlue), heatCapacityAir(heatCapacityAir) {}

        Output() = default;
        double hxColdAir = 0, hxOutletExhaust = 0, energySavings = 0, heatCapacityFlue = 0, heatCapacityAir = 0;
    };

    AirHeatingUsingExhaust(GasCompositions gasCompositions) {
        fuelHeatingValue = gasCompositions.getHeatingValueVolume();
        stoichAir = gasCompositions.getStoichometricAir();
    }

    AirHeatingUsingExhaust(SolidLiquidFlueGasMaterial solidLiquidFlueGasMaterial) {
        fuelHeatingValue = solidLiquidFlueGasMaterial.getHeatingValueFuel();
        stoichAir = solidLiquidFlueGasMaterial.getStoichAirFuel();
    }

    AirHeatingUsingExhaust::Output calculate(const double flueTemperature, const double excessAir, const double fireRate,
                                             const double airflow, const double inletTemperature,
                                             const double heaterEfficiency, const double hxEfficiency, const double operatingHours);

private:
    double fuelHeatingValue = 1;
    double stoichAir = 0;
};

#endif //AMO_TOOLS_SUITE_AIRHEATINGUSINGEXHAUST_H
