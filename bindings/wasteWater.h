#ifndef AMO_TOOLS_SUITE_WASTEWATER_H
#define AMO_TOOLS_SUITE_WASTEWATER_H

#include <nan.h>
#include <node.h>
#include "wasteWater/WasteWaterTreatment.h"
#include <string>
#include <array>
#include <vector>
#include <exception>
#include <iostream>
#include "./NanDataConverters.h"

using namespace Nan;
using namespace v8;

// Local<Object> inp;
// Local<Object> r;

NAN_METHOD(WasteWaterTreatment)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double Temperature = getDouble("Temperature", inp);
    const double So = getDouble("So", inp);
    const double Volume = getDouble("Volume", inp);
    const double FlowRate = getDouble("FlowRate", inp);
    const double InertVSS = getDouble("InertVSS", inp);
    const double OxidizableN = getDouble("OxidizableN", inp);
    const double Biomass = getDouble("Biomass", inp);
    const double InfluentTSS = getDouble("InfluentTSS", inp);
    const double InertInOrgTSS = getDouble("InertInOrgTSS", inp);
    const double EffluentTSS = getDouble("EffluentTSS", inp);
    const double RASTSS = getDouble("RASTSS", inp);
    const double MLSSpar = getDouble("MLSSpar", inp);
    const double FractionBiomass = getDouble("FractionBiomass", inp);
    const double BiomassYeild = getDouble("BiomassYeild", inp);
    const double HalfSaturation = getDouble("HalfSaturation", inp);
    const double MicrobialDecay = getDouble("MicrobialDecay", inp);
    const double MaxUtilizationRate = getDouble("MaxUtilizationRate", inp);
    const double MaxDays = getDouble("MaxDays", inp);
    const double TimeIncrement = getDouble("TimeIncrement", inp);
    const double OperatingDO = getDouble("OperatingDO", inp);
    const double Alpha = getDouble("Alpha", inp);
    const double Beta = getDouble("Beta", inp);
    const double SOTR = getDouble("SOTR", inp);
    const double Aeration = getDouble("Aeration", inp);
    const double Elevation = getDouble("Elevation", inp);
    const double OperatingTime = getDouble("OperatingTime", inp);
    const int TypeAerators = getInteger("TypeAerators", inp);
    const double Speed = getDouble("Speed", inp);
    const double EnergyCostUnit = getDouble("EnergyCostUnit", inp);
    try
    {
        WasteWaterTreatment::Output output = WasteWaterTreatment::WasteWaterTreatment(Temperature,
                                                                                      So,
                                                                                      Volume,
                                                                                      FlowRate,
                                                                                      InertVSS,
                                                                                      OxidizableN,
                                                                                      Biomass,
                                                                                      InfluentTSS,
                                                                                      InertInOrgTSS,
                                                                                      EffluentTSS,
                                                                                      RASTSS,
                                                                                      MLSSpar,
                                                                                      FractionBiomass,
                                                                                      BiomassYeild,
                                                                                      HalfSaturation,
                                                                                      MicrobialDecay,
                                                                                      MaxUtilizationRate,
                                                                                      MaxDays,
                                                                                      TimeIncrement,
                                                                                      OperatingDO,
                                                                                      Alpha,
                                                                                      Beta,
                                                                                      SOTR,
                                                                                      Aeration,
                                                                                      Elevation,
                                                                                      OperatingTime,
                                                                                      TypeAerators,
                                                                                      Speed,
                                                                                      EnergyCostUnit)
                                                 .calculate();

        setR("TotalAverageDailyFlowRate", output.TotalAverageDailyFlowRate);
        setR("VolumeInService", output.VolumeInService);
        setR("InfluentBOD5Concentration", output.InfluentBOD5Concentration);
        setR("InfluentBOD5MassLoading", output.InfluentBOD5MassLoading);
        setR("SecWWOxidNLoad", output.SecWWOxidNLoad);
        setR("SecWWTSSLoad", output.SecWWTSSLoad);
        setR("FM_ratio", output.FM_ratio);
        setR("SolidsRetentionTime", output.SolidsRetentionTime);
        setR("MLSS", output.MLSS);
        setR("MLVSS", output.MLVSS);
        setR("TSSSludgeProduction", output.TSSSludgeProduction);
        setR("TSSInActivatedSludgeEffluent", output.TSSInActivatedSludgeEffluent);
        setR("TotalOxygenRequirements", output.TotalOxygenRequirements);
        setR("TotalOxygenReqWDenit", output.TotalOxygenReqWDenit);
        setR("TotalOxygenSupplied", output.TotalOxygenSupplied);
        setR("MixingIntensityInReactor", output.MixingIntensityInReactor);
        setR("RASFlowRate", output.RASFlowRate);
        setR("RASRecyclePercentage", output.RASRecyclePercentage);
        setR("WASFlowRate", output.WASFlowRate);
        setR("RASTSSConcentration", output.RASTSSConcentration);
        setR("TotalSludgeProduction", output.TotalSludgeProduction);
        setR("ReactorDetentionTime", output.ReactorDetentionTime);
        setR("VOLR", output.VOLR);
        setR("EffluentCBOD5", output.EffluentCBOD5);
        setR("EffluentTSS", output.EffluentTSS);
        setR("EffluentAmmonia_N", output.EffluentAmmonia_N);
        setR("EffluentNO3_N", output.EffluentNO3_N);
        setR("EffluentNO3_N_W_Denit", output.EffluentNO3_N_W_Denit);
        setR("AeEnergy", output.AeEnergy);
        setR("AeCost", output.AeCost);
        setR("FieldOTR", output.FieldOTR);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in WasteWaterTreatment - wasteWater.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}
#endif //AMO_TOOLS_SUITE_WASTEWATER_H