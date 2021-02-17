#include <nan.h>
#include <node.h>
#include <string>
#include <array>
#include <vector>
#include <exception>
#include <iostream>
#include "./NanDataConverters.h"
#include "calculator/processHeat/AirHeatingUsingExhaust.h"
#include "calculator/processHeat/WaterHeatingUsingExhaust.h"

using namespace Nan;
using namespace v8;

NAN_METHOD(airHeatingUsingExhaust)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double flueTemperature = getDouble("flueTemperature", inp);
        const double excessAir = getDouble("excessAir", inp);
        const double fireRate = getDouble("fireRate", inp);
        const double airflow = getDouble("airflow", inp);
        const double inletTemperature = getDouble("inletTemperature", inp);
        const double heaterEfficiency = getDouble("heaterEfficiency", inp);
        const double hxEfficiency = getDouble("hxEfficiency", inp);
        const double operatingHours = getDouble("operatingHours", inp);
        const std::string substance = getString("substance", inp);

        AirHeatingUsingExhaust::Output output;
        if(getBool("gasFuelType")) {
            const double CH4 = getDouble("CH4", inp);
            const double C2H6 = getDouble("C2H6", inp);
            const double N2 = getDouble("N2", inp);
            const double H2 = getDouble("H2", inp);
            const double C3H8 = getDouble("C3H8", inp);
            const double C4H10_CnH2n = getDouble("C4H10_CnH2n", inp);
            const double H2O = getDouble("H2O", inp);
            const double CO = getDouble("CO", inp);
            const double CO2 = getDouble("CO2", inp);
            const double SO2 = getDouble("SO2", inp);
            const double O2 = getDouble("O2", inp);

            auto airHeat = AirHeatingUsingExhaust(GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2));
            output = AirHeatingUsingExhaust(airHeat).calculate(flueTemperature,excessAir,fireRate,airflow,inletTemperature,heaterEfficiency,hxEfficiency,operatingHours);
        } else {
            const double carbon = getDouble("carbon", inp);
            const double hydrogen = getDouble("hydrogen", inp);
            const double sulphur = getDouble("sulphur", inp);
            const double inertAsh = getDouble("inertAsh", inp);
            const double o2 = getDouble("o2", inp);
            const double moisture = getDouble("moisture", inp);
            const double nitrogen = getDouble("nitrogen", inp);

            auto airHeat = AirHeatingUsingExhaust(SolidLiquidFlueGasMaterial(substance, carbon, hydrogen, sulphur, inertAsh, o2, moisture, nitrogen));
            output = AirHeatingUsingExhaust(airHeat).calculate(flueTemperature,excessAir,fireRate,airflow,inletTemperature,heaterEfficiency,hxEfficiency,operatingHours);
        }

        setR("hxColdAir", output.hxColdAir);
        setR("hxOutletExhaust", output.hxOutletExhaust);
        setR("energySavings", output.energySavings);
        setR("heatCapacityFlue", output.heatCapacityFlue);
        setR("heatCapacityAir", output.heatCapacityAir);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Air ProcessHeat - calculator: " + what).c_str());
    }
}

NAN_METHOD(waterHeatingUsingExhaust)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double availableHeat = getDouble("availableHeat", inp);
        const double heatInput = getDouble("heatInput", inp);
        const double hxEfficiency = getDouble("hxEfficiency", inp);
        const double chillerInTemperature = getDouble("chillerInTemperature", inp);
        const double chillerOutTemperature = getDouble("chillerOutTemperature", inp);
        const double copChiller = getDouble("copChiller", inp);
        const double chillerEfficiency = getDouble("chillerEfficiency", inp);
        const double copCompressor = getDouble("copCompressor", inp);

        auto output = WaterHeatingUsingExhaust().calculate(availableHeat,heatInput,hxEfficiency,chillerInTemperature,chillerOutTemperature,copChiller,chillerEfficiency,copCompressor);

        setR("recoveredHeat", output.recoveredHeat);
        setR("hotWaterFlow", output.hotWaterFlow);
        setR("tonsRefrigeration", output.tonsRefrigeration);
        setR("capacityChiller", output.capacityChiller);
        setR("electricalEnergy", output.electricalEnergy);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Water ProcessHeat - calculator: " + what).c_str());
    }
}
