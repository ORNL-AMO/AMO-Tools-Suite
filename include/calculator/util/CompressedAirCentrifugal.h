//
// Created by 7bo on 10/12/2020.
// Calculate estimated power(kW) consumption and air flow(acfm) for a centrifugal compressors based on control type
//      1. Control type
//          a. Load / unload
//          b. Inlet Butterfly with BlowOff or Inlet Guide Vane with BlowOff
//          c. Inlet Guide Vane Modulation with Unloading or Butterfly Modulation with unloading
//      2. Using Input as
//          a. Capacity
//          b. Capacity%
//          c. Power
//          d. Power%
//               OR
//             Power% and BlowOff%
//          e. Volts, Amps, Power Factor(PF)
//               OR
//             Volts, Amps, Power Factor(PF) and BlowOff%
//

#ifndef AMO_TOOLS_SUITE_COMPRESSEDAIRCENTRIFUGAL_H
#define AMO_TOOLS_SUITE_COMPRESSEDAIRCENTRIFUGAL_H

#include "CurveFitVal.h"

class CompressedAirCentrifugalBase {
public:
    enum ControlType {
        LoadUnload,
        ModulationUnload,
        BlowOff
    };

    enum ComputeFrom {
        PercentagePower,
        PercentageCapacity,
        PowerMeasured,
        CapacityMeasured,
        PowerFactor
    };

    struct Output
    {
        Output(double kW_Calc, double C_Calc, double PerkW, double C_Per) : kW_Calc(kW_Calc), C_Calc(C_Calc), PerkW(PerkW), C_Per(C_Per){}

        Output() = default;
        double kW_Calc = 0, C_Calc = 0, PerkW = 0, C_Per = 0;
    };

    struct OutputBlowOff
    {
        OutputBlowOff(double kW_Calc, double C_Calc, double PerkW, double C_Per, double C_blow, double blowPer) : kW_Calc(kW_Calc), C_Calc(C_Calc), PerkW(PerkW), C_Per(C_Per), C_blow(C_blow), blowPer(blowPer){}

        OutputBlowOff() = default;
        double kW_Calc = 0, C_Calc = 0, PerkW = 0, C_Per = 0, C_blow = 0, blowPer = 0;
    };

    static double Round(double value) { return (float)((int)(value * 100 + .5)) / 100; }

protected:
    CompressedAirCentrifugalBase(const double kW_fl, const double C_fl) : kW_fl(kW_fl), C_fl(C_fl), C_fl_raw(C_fl) {}

    const double kW_fl, C_fl_raw;
    double C_fl;

private:
    virtual CompressedAirCentrifugalBase::OutputBlowOff calculateFromPerkW_BlowOff(double, double) {return OutputBlowOff();}
    virtual CompressedAirCentrifugalBase::OutputBlowOff calculateFromPerC_BlowOff(double) {return OutputBlowOff();}
    virtual CompressedAirCentrifugalBase::OutputBlowOff calculateFromkWMeasured_BlowOff(double, double) {return OutputBlowOff();}
    virtual CompressedAirCentrifugalBase::OutputBlowOff calculateFromCMeasured_BlowOff(double) {return OutputBlowOff();}
    virtual CompressedAirCentrifugalBase::OutputBlowOff calculateFromVIPFMeasured_BlowOff(double, double, double, double) {return OutputBlowOff();}

    virtual CompressedAirCentrifugalBase::Output calculateFromPerkW(double) {return Output();}
    virtual CompressedAirCentrifugalBase::Output calculateFromPerC(double) {return Output();}
    virtual CompressedAirCentrifugalBase::Output calculateFromkWMeasured(double) {return Output();}
    virtual CompressedAirCentrifugalBase::Output calculateFromCMeasured(double) {return Output();}
    virtual CompressedAirCentrifugalBase::Output calculateFromVIPFMeasured(double, double, double) {return Output();}

    virtual void AdjustDischargePressure(std::vector<double>, std::vector<double>, double, double) {}
};

class CompressedAirCentrifugal: public CompressedAirCentrifugalBase {
public:
    CompressedAirCentrifugal(const double kW_fl, const double C_fl) : CompressedAirCentrifugalBase(kW_fl, C_fl) {}
};

class CompressedAirCentrifugal_BlowOff: private CompressedAirCentrifugalBase{
public:
    double C_fl_Adjusted = 0;

    CompressedAirCentrifugal_BlowOff(const double kW_fl, const double C_fl, const double kW_blow, const double C_blow) : CompressedAirCentrifugalBase(kW_fl, C_fl), C_blow(C_blow), C_fl_Adjusted(C_fl)
    {
        CPer_blow = C_blow / C_fl;
        kWPer_blow = kW_blow / kW_fl;
    }

    CompressedAirCentrifugalBase::OutputBlowOff calculateFromPerkW_BlowOff(double PerkW, double blowPer) override;
    CompressedAirCentrifugalBase::OutputBlowOff calculateFromPerC_BlowOff(double C_Per) override;
    CompressedAirCentrifugalBase::OutputBlowOff calculateFromkWMeasured_BlowOff(double kW, double blowPer) override;
    CompressedAirCentrifugalBase::OutputBlowOff calculateFromCMeasured_BlowOff(double C) override;
    CompressedAirCentrifugalBase::OutputBlowOff calculateFromVIPFMeasured_BlowOff(double V, double I, double PF, double blowPer) override;

    void AdjustDischargePressure(std::vector<double> Capacity, std::vector<double> DischargePressure, double P_fl, double P_max = 0) override {
        if(P_fl > 0) {
            CurveFitVal curveFitValCap(DischargePressure, Capacity, 2);
            C_fl_Adjusted = C_fl = curveFitValCap.calculate(P_fl);

            CPer_blow = C_blow / C_fl;
        }
    }

private:
    double C_blow = 1;
    double CPer_blow = 1;
    double kWPer_blow = 0;
};

class CompressedAirCentrifugal_LoadUnload: private CompressedAirCentrifugalBase{
public:
    double C_fl_Adjusted = 0;

    CompressedAirCentrifugal_LoadUnload(const double kW_fl, const double C_fl, const double kW_nl) : CompressedAirCentrifugalBase(kW_fl, C_fl), C_fl_Adjusted(C_fl)
    {
        kWPer_nl = kW_nl / kW_fl;
    }

    CompressedAirCentrifugalBase::Output calculateFromPerkW(double PerkW) override;
    CompressedAirCentrifugalBase::Output calculateFromPerC(double C_Per) override;
    CompressedAirCentrifugalBase::Output calculateFromkWMeasured(double kW) override;
    CompressedAirCentrifugalBase::Output calculateFromCMeasured(double C) override;
    CompressedAirCentrifugalBase::Output calculateFromVIPFMeasured(double V, double I, double PF) override;

    void AdjustDischargePressure(std::vector<double> Capacity, std::vector<double> DischargePressure, double P_fl, double P_max = 0) override {
        if(P_fl > 0) {
            CurveFitVal curveFitValCap(DischargePressure, Capacity, 2);
            C_fl_Adjusted = C_fl = curveFitValCap.calculate(P_fl);
        }
    }

private:
    const double CPer_fl = 1;
    const double CPer_nl = 0;
    double kWPer_nl = 0;
};

class CompressedAirCentrifugal_ModulationUnload: private CompressedAirCentrifugalBase{
public:
    double C_fl_Adjusted = 0;
    double C_max_Adjusted = 0;

    CompressedAirCentrifugal_ModulationUnload(const double kW_fl, const double C_fl, const double kW_nl, const double C_max, const double kW_ul, const double C_ul): CompressedAirCentrifugalBase(kW_fl, C_fl), C_max(C_max), C_max_raw(C_max), C_ul(C_ul), C_fl_Adjusted(C_fl), C_max_Adjusted(C_max)
    {
        kWPer_nl = kW_nl / kW_fl;
        kWPer_ul = kW_ul / kW_fl;
        CPer_max = C_max / C_fl;
        CPer_ul = C_ul / C_fl;
        CPer_ulB = C_ul / C_max;
    }

    CompressedAirCentrifugalBase::Output calculateFromPerkW(double PerkW) override;
    CompressedAirCentrifugalBase::Output calculateFromPerC(double C_Per) override;
    CompressedAirCentrifugalBase::Output calculateFromkWMeasured(double kW) override;
    CompressedAirCentrifugalBase::Output calculateFromCMeasured(double C) override;
    CompressedAirCentrifugalBase::Output calculateFromVIPFMeasured(double V, double I, double PF) override;

    void AdjustDischargePressure(std::vector<double> Capacity, std::vector<double> DischargePressure, double P_fl, double P_max) override {
        if(P_fl > 0 || P_max > 0) {
            CurveFitVal curveFitValCap(DischargePressure, Capacity, 2);

            if(P_fl > 0) C_fl_Adjusted = C_fl = curveFitValCap.calculate(P_fl);
            if(P_max > 0) C_max_Adjusted = C_max = curveFitValCap.calculate(P_max);

            CPer_max = C_max / C_fl;
            CPer_ul = C_ul / C_fl;
            CPer_ulB = C_ul / C_max;
        }
    }

private:
    const double kWPer_max = 1, C_max_raw = 1, C_ul = 1;
    double kWPer_nl = 0;
    double kWPer_ul = 1;
    double C_max = 1;
    double CPer_max = 1;
    double CPer_ul = 1;
    double CPer_ulB = 1;
    const double CPer_nl = 0;
};
#endif //AMO_TOOLS_SUITE_COMPRESSEDAIRCENTRIFUGAL_H
