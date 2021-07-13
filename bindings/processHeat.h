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
#include "calculator/processHeat/WaterHeatingUsingSteam.h"
#include "calculator/processHeat/CascadeHeatHighToLow.h"
#include "calculator/processHeat/WaterHeatingUsingFlue.h"

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
        ThrowError(std::string("std::runtime_error thrown in Water ProcessHeat using Exhaust- calculator: " + what).c_str());
    }
}

NAN_METHOD(waterHeatingUsingSteam)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double pressureSteamIn = getDouble("pressureSteamIn", inp);
        const double flowSteamRate = getDouble("flowSteamRate", inp);
        const double temperatureWaterIn = getDouble("temperatureWaterIn", inp);
        const double pressureWaterOut = getDouble("pressureWaterOut", inp);
        const double flowWaterRate = getDouble("flowWaterRate", inp);
        const double tempMakeupWater = getDouble("tempMakeupWater", inp);
        const double presMakeupWater = getDouble("presMakeupWater", inp);
        const double effWaterHeater = getDouble("effWaterHeater", inp);
        const double effBoiler = getDouble("effBoiler", inp);
        const double operatingHours = getDouble("operatingHours", inp);

        auto output = WaterHeatingUsingSteam().calculate(pressureSteamIn,flowSteamRate,temperatureWaterIn,pressureWaterOut,flowWaterRate,tempMakeupWater,presMakeupWater,
                                                         effWaterHeater, effBoiler, operatingHours);

        setR("bpTempWarningFlag", output.bpTempWarningFlag);
        setR("tempWaterOut", output.tempWaterOut);
        setR("bpTempWaterOut", output.bpTempWaterOut);
        setR("enthalpySteamIn", output.enthalpySteamIn);
        setR("enthalpySteamOut", output.enthalpySteamOut);
        setR("enthalpyMakeUpWater", output.enthalpyMakeUpWater);
        setR("flowByPassSteam", output.flowByPassSteam);
        setR("energySavedDWH", output.energySavedDWH);
        setR("energySavedBoiler", output.energySavedBoiler);
        setR("waterSaved", output.waterSaved);
        setR("heatGainRate", output.heatGainRate);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Water ProcessHeat using Steam - calculator: " + what).c_str());
    }
}

NAN_METHOD(cascadeHeatHighToLow)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double priFiringRate = getDouble("priFiringRate", inp);
        const double priExhaustTemperature = getDouble("priExhaustTemperature", inp);
        const double priExhaustO2 = getDouble("priExhaustO2", inp);
        const double priCombAirTemperature = getDouble("priCombAirTemperature", inp);
        const double priOpHours = getDouble("priOpHours", inp);
        const double priFuelHV = getDouble("priFuelHV", inp);

        const double secFiringRate = getDouble("secFiringRate", inp);
        const double secExhaustTemperature = getDouble("secExhaustTemperature", inp);
        const double secCombAirTemperature = getDouble("secCombAirTemperature", inp);
        const double secOpHours = getDouble("secOpHours", inp);
        const double secFuelCost = getDouble("secFuelCost", inp);

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

        auto ch = CascadeHeatHighToLow(GasCompositions("Gas", CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2),
                                       priFiringRate, priExhaustTemperature, priExhaustO2, priCombAirTemperature, priOpHours, priFuelHV,
                                       secFiringRate, secExhaustTemperature, secCombAirTemperature, secOpHours, secFuelCost);
        auto output = ch.calculate();

        setR("priFlueVolume", output.priFlueVolume);
        setR("hxEnergyRate", output.hxEnergyRate);
        setR("eqEnergySupply", output.eqEnergySupply);
        setR("effOpHours", output.effOpHours);
        setR("energySavings", output.energySavings);
        setR("costSavings", output.costSavings);
        setR("hourlySavings", output.hourlySavings);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Cascade Heat HighToLow ProcessHeat - calculator: " + what).c_str());
    }
}

NAN_METHOD(waterHeatingUsingFlue)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double tempFlueGas = getDouble("tempFlueGas", inp);
        const double percO2 = getDouble("percO2", inp);
        const double tempCombAir = getDouble("tempCombAir", inp);
        const double moistCombAir = getDouble("moistCombAir", inp);
        const double ratingBoiler = getDouble("ratingBoiler", inp);
        const double prSteam = getDouble("prSteam", inp);
        const double tempAmbientAir = getDouble("tempAmbientAir", inp);
        const double tempSteam = getDouble("tempSteam", inp);
        const double tempFW = getDouble("tempFW", inp);
        const double percBlowDown = getDouble("percBlowDown", inp);
        const double effHX = getDouble("effHX", inp);
        const double opHours = getDouble("opHours", inp);
        const double costFuel = getDouble("costFuel", inp);
        const double hhvFuel = getDouble("hhvFuel", inp);
        const int condSteam = getInteger("condSteam", inp);

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

        auto output = WaterHeatingUsingFlue().calculate(GasCompositions("Gas", CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2),
                                                      tempFlueGas, percO2, tempCombAir, moistCombAir, ratingBoiler, prSteam, tempAmbientAir,
                                                      tempSteam, tempFW, percBlowDown, effHX, opHours, costFuel, hhvFuel, (WaterHeatingUsingFlue::SteamCondition)condSteam);

        setR("tempSteamSat", output.tempSteamSat);
        setR("flowFlueGas", output.flowFlueGas);
        setR("effBoiler", output.effBoiler);
        setR("enthalpySteam", output.enthalpySteam);
        setR("enthalpyFW", output.enthalpyFW);
        setR("flowSteam", output.flowSteam);
        setR("flowFW", output.flowFW);
        setR("specheatFG", output.specheatFG);
        setR("heatCapacityFG", output.heatCapacityFG);
        setR("specheatFW", output.specheatFW);
        setR("heatCapacityFW", output.heatCapacityFW);
        setR("heatCapacityMin", output.heatCapacityMin);
        setR("ratingHeatRecFW", output.ratingHeatRecFW);
        setR("tempFlueGasOut", output.tempFlueGasOut);
        setR("tempFWOut", output.tempFWOut);
        setR("energySavingsBoiler", output.energySavingsBoiler);
        setR("costSavingsBoiler", output.costSavingsBoiler);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Water Heating Using Flue ProcessHeat - calculator: " + what).c_str());
    }
}