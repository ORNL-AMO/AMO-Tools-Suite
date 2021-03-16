/**
 * @file
 * @brief Calculate estimated power(kW) consumption and air flow(acfm) for a compressor based on control type.
 *
 *      1. Compressor type
 *          a. Centrifugal
 *          b. Screw
 *          c. Reciprocating
 *      2. Control type
 *          a. Load / unload
 *          b. Inlet Butterfly with BlowOff or Inlet Guide Vane with BlowOff
 *          c. Inlet Guide Vane Modulation with Unloading or Butterfly Modulation with unloading Or Inlet Modulation with unloading
 *          d. Inlet Modulation with out unloading
 *          e. Start Stop
 *          f. Variable displacement with unloading
 *      3. Stage : Single / Two / Multiple
 *      4. Lubricant : Injected / Free
 *      5. Using Input as
 *          a. Capacity
 *          b. Capacity%
 *          c. Power
 *          d. Power%
 *               OR
 *             Power% and BlowOff%
 *          e. Volts, Amps, Power Factor(PF)
 *               OR
 *             Volts, Amps, Power Factor(PF) and BlowOff%
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_COMPRESSORS_H
#define AMO_TOOLS_SUITE_COMPRESSORS_H

#include <math.h>
#include <stdexcept>
#include "CurveFitVal.h"

class CompressorsBase {
public:
    enum CompressorType {
        Centrifugal,
        Screw,
        Reciprocating
    };

    enum ControlType {
        LoadUnload,
        ModulationUnload,
        BlowOff,
        ModulationWOUnload,
        StartStop,
        VariableDisplacementUnload,
        MultiStepUnloading,
        VFD
    };

    enum Stage {
        Single,
        Two,
        Multiple
    };

    enum Lubricant {
        Injected,
        Free,
        None
    };

    enum Modulation{
        Throttle,
        VariableDisplacement
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

public:
    double C_fl_Adjusted;
    double kW_fl_Adjusted;
    double C_max_Adjusted;
    double kW_max_Adjusted;

protected:
    CompressorsBase(const double kW_fl, const double C_fl) : kW_fl(kW_fl), C_fl(C_fl), C_fl_raw(C_fl), kW_fl_raw(kW_fl), kW_fl_Adjusted(kW_fl), C_fl_Adjusted(C_fl), C_max_Adjusted(0), kW_max_Adjusted(0) { }

    const double C_fl_raw, kW_fl_raw;
    double kW_fl, C_fl;

private:
    virtual CompressorsBase::OutputBlowOff calculateFromPerkW_BlowOff(double, double) {return OutputBlowOff();}
    virtual CompressorsBase::OutputBlowOff calculateFromPerC_BlowOff(double) {return OutputBlowOff();}
    virtual CompressorsBase::OutputBlowOff calculateFromkWMeasured_BlowOff(double, double) {return OutputBlowOff();}
    virtual CompressorsBase::OutputBlowOff calculateFromCMeasured_BlowOff(double) {return OutputBlowOff();}
    virtual CompressorsBase::OutputBlowOff calculateFromVIPFMeasured_BlowOff(double, double, double, double) {return OutputBlowOff();}

    virtual CompressorsBase::Output calculateFromPerkW(double) {return Output();}
    virtual CompressorsBase::Output calculateFromPerC(double) {return Output();}
    virtual CompressorsBase::Output calculateFromkWMeasured(double) {return Output();}
    virtual CompressorsBase::Output calculateFromCMeasured(double) {return Output();}
    virtual CompressorsBase::Output calculateFromVIPFMeasured(double, double, double) {return Output();}

    virtual void AdjustDischargePressure(std::vector<double>, std::vector<double>, double, double) {}

protected:
    static double Round(double value) { return (float)((int)(value * 100 + .5)) / 100; }

    void PressureInletCorrection(CompressorType CompType, const double capacity, const double full_load_bhp, const double poly_exponent, const double P_ratedDischarge,
                                 const double P_RatedIn, const double Eff, const double P_fl, const double P_max, const double P_in, const bool PresAdj, const double P_atm)
    {
        double kW = 0, Cap = 0;

        PressureInletCorrection(Cap, kW, CompType, capacity, full_load_bhp, poly_exponent, P_ratedDischarge, P_RatedIn, Eff, P_fl, P_in, PresAdj, P_atm);
        kW_fl_Adjusted = kW_fl = kW;
        C_fl_Adjusted = C_fl = Cap;

        PressureInletCorrection(Cap, kW, CompType, capacity, full_load_bhp, poly_exponent, P_ratedDischarge, P_RatedIn, Eff, P_max, P_in, PresAdj, P_atm);
        kW_max_Adjusted = kW;
        C_max_Adjusted = Cap;
    }

private:
    void PressureInletCorrection(double &cap, double &kW, CompressorType CompType, const double capacity, const double full_load_bhp, const double poly_exponent, const double P_ratedDischarge,
                                 const double P_RatedIn, const double Eff, const double dischargePres, const double P_in, const bool PresAdj, const double P_atm)
    {
        if(CompType == CompressorType::Centrifugal) return;

        double Pres_kW = 1, Pres_Flow = 1;
        if(PresAdj) {
            Pres_kW = -0.0000577 * pow(P_atm, 3) + 0.000251 * pow(P_atm, 2) + 0.0466 * P_atm + 0.4442;
            Pres_Flow = 0.000258 * pow(P_atm, 3) - 0.0116 * pow(P_atm, 2) + 0.176 * P_atm + 0.09992;
        }

        kW = Round(Pres_kW * (P_atm / P_in) * full_load_bhp * 0.746 / Eff *
                   PressureInletCorrection_PressRatio(poly_exponent, (P_ratedDischarge + P_RatedIn) / P_RatedIn, dischargePres, CompType == CompressorType::Screw ? P_RatedIn : P_atm));
        cap = Round(Pres_Flow * capacity * (1 - 0.00075 * (dischargePres - P_ratedDischarge)));
    }

    double PressureInletCorrection_PressRatio(double poly_exponent, double PressRatio1, double OpPress, double P_PressRatio2) {
        double PressRatio2  = (OpPress + P_PressRatio2) / P_PressRatio2;
        double PolyPower = ((poly_exponent - 1) / poly_exponent);
        return (pow(PressRatio2, PolyPower) - 1) / (pow(PressRatio1, PolyPower) - 1);
    }
};

class Compressors: public CompressorsBase {
public:
    Compressors(const double kW_fl, const double C_fl) : CompressorsBase(kW_fl, C_fl) {}
};


class Compressors_Centrifugal_BlowOff: public CompressorsBase{
public:
    /**
     *
     * @param kW_fl double, units kW
     * @param C_fl double, units acfm
     * @param kW_blow double, units kW
     * @param C_blow double, units acfm
     *
     */
    Compressors_Centrifugal_BlowOff(const double kW_fl, const double C_fl, const double kW_blow, const double C_blow) : CompressorsBase(kW_fl, C_fl), C_blow(C_blow)
    {
        CPer_blow = C_blow / C_fl;
        kWPer_blow = kW_blow / kW_fl;
    }

    /**
     *
     * @param PerkW double
     * @param blowPer double
     * @return
     * @param kW_Calc double, units kW
     * @param C_Calc double, units acfm
     * @param PerkW double, units percentage / fraction
     * @param C_Per double, units percentage / fraction
     * @param C_blow double, units acfm
     * @param blowPer double, units percentage / fraction
     *
    */
    CompressorsBase::OutputBlowOff calculateFromPerkW_BlowOff(double PerkW, double blowPer) override;

    /**
     *
     * @param C_Per double, units percentage / fraction
     * @return
     * @param kW_Calc double, units kW
     * @param C_Calc double, units acfm
     * @param PerkW double, units percentage / fraction
     * @param C_Per double, units percentage / fraction
     * @param C_blow double, units acfm
     * @param blowPer double, units percentage / fraction
     *
    */
    CompressorsBase::OutputBlowOff calculateFromPerC_BlowOff(double C_Per) override;

    /**
     *
     * @param kW double, units kW
     * @param blowPer double, units percentage / fraction
     * @return
     * @param kW_Calc double, units kW
     * @param C_Calc double, units acfm
     * @param PerkW double, units percentage / fraction
     * @param C_Per double, units percentage / fraction
     * @param C_blow double, units acfm
     * @param blowPer double, units percentage / fraction
     *
    */
    CompressorsBase::OutputBlowOff calculateFromkWMeasured_BlowOff(double kW, double blowPer) override;

    /**
     *
     * @param C, capacity double, units acfm
     * @return
     * @param kW_Calc double, units kW
     * @param C_Calc double, units acfm
     * @param PerkW double, units percentage / fraction
     * @param C_Per double, units percentage / fraction
     * @param C_blow double, units acfm
     * @param blowPer double, units percentage / fraction
     *
    */
    CompressorsBase::OutputBlowOff calculateFromCMeasured_BlowOff(double C) override;
    /**
     *
     * @param V, Voltage double
     * @param I, Current double, amps
     * @param PF, Power Factor double, percentage / fraction
     * @param blowPer double, percentage / fraction
     * @return
     * @param kW_Calc double, units kW
     * @param C_Calc double, units acfm
     * @param PerkW double, units percentage / fraction
     * @param C_Per double, units percentage / fraction
     * @param C_blow double, units acfm
     * @param blowPer double, units percentage / fraction
     *
     */
    CompressorsBase::OutputBlowOff calculateFromVIPFMeasured_BlowOff(double V, double I, double PF, double blowPer) override;

    /**
     *
     * @param Capacity, array of doubles Capacity at full load, max and min
     * @param DischargePressure, array of doubles DischargePressure at full load, max and min
     * @param P_fl double
     * @param P_max double, not required for this control type
     *      Units for power kW and Capacity acfm
     *
     */
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

class Compressors_Centrifugal_LoadUnload: public CompressorsBase{
public:
    /**
     *
     * @param kW_fl double
     * @param C_fl double
     * @param kW_nl double
     *      Units for power kW and Capacity acfm
     *
     */
    Compressors_Centrifugal_LoadUnload(const double kW_fl, const double C_fl, const double kW_nl) : CompressorsBase(kW_fl, C_fl)
    {
        kWPer_nl = kW_nl / kW_fl;
    }

    /**
     *
     * @param PerkW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerkW(double PerkW) override;

    /**
     *
     * @param C_Per double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerC(double C_Per) override;

    /**
     *
     * @param kW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromkWMeasured(double kW) override;

    /**
     *
     * @param C double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromCMeasured(double C) override;

    /**
     *
     * @param V, Voltage double
     * @param I, Current double
     * @param PF, Power Factor double
     * @param blowPer double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromVIPFMeasured(double V, double I, double PF) override;

    /**
     *
     * @param Capacity, array of doubles Capacity at full load, max and min
     * @param DischargePressure, array of doubles DischargePressure at full load, max and min
     * @param P_fl double
     * @param P_max double, not required for this control type
     *      Units for power kW and Capacity acfm
     *
     */
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

class Compressors_Centrifugal_ModulationUnload: public CompressorsBase{
public:
    /**
     *
     * @param kW_fl double
     * @param C_fl double
     * @param kW_nl double
     * @param C_max double
     * @param kW_ul double
     * @param C_ul double
     *      Units for power kW and Capacity acfm
     *
     */
    Compressors_Centrifugal_ModulationUnload(const double kW_fl, const double C_fl, const double kW_nl, const double C_max, const double kW_ul, const double C_ul): CompressorsBase(kW_fl, C_fl), C_max(C_max), C_max_raw(C_max), C_ul(C_ul)
    {
        C_max_Adjusted = C_max;

        kWPer_nl = kW_nl / kW_fl;
        kWPer_ul = kW_ul / kW_fl;
        CPer_max = C_max / C_fl;
        CPer_ul = C_ul / C_fl;
        CPer_ulB = C_ul / C_max;
    }

    /**
     *
     * @param PerkW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerkW(double PerkW) override;

    /**
     *
     * @param C_per double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerC(double C_Per) override;
    /**
     *
     * @param kW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromkWMeasured(double kW) override;

    /**
     *
     * @param C double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromCMeasured(double C) override;

    /**
     *
     * @param V, Voltage double
     * @param I, Current double
     * @param PF, Power Factor double
     * @param blowPer double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromVIPFMeasured(double V, double I, double PF) override;

    /**
     *
     * @param Capacity, array of doubles Capacity at full load, max and min
     * @param DischargePressure, array of doubles DischargePressure at full load, max and min
     * @param P_fl double
     * @param P_max double
     *      Units for power kW and Capacity acfm
     *
     */
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


class Compressors_ModulationWOUnload: public CompressorsBase{
public:
    /**
     *
     * @param kW_fl double
     * @param C_fl double
     * @param kW_nl double
     * @param CompType double
     *      Units for power kW and Capacity acfm
     *
     */
    Compressors_ModulationWOUnload(const double kW_fl, const double C_fl, const double kW_nl, const CompressorType CompType = CompressorType::Screw): CompressorsBase(kW_fl, C_fl), kW_nl(kW_nl), CompType(CompType)
    {
        mod_exp = 1;
        lf_nl = kW_nl / kW_fl;
    }

    /**
     *
     * @param PerkW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerkW(double PerkW) override;

    /**
     *
     * @param C_Per double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerC(double C_Per) override;

    /**
     *
     * @param kW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromkWMeasured(double kW) override;

    /**
     *
     * @param C double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromCMeasured(double C) override;

    /**
     *
     * @param V, Voltage double
     * @param I, Current double
     * @param PF, Power Factor double
     * @param blowPer double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromVIPFMeasured(double V, double I, double PF) override;

    /**
     *
     * @param capacity double
     * @param full_load_bhp double
     * @param poly_exponent double
     * @param P_ratedDischarge double
     * @param P_RatedIn double
     * @param Eff double
     * @param P_fl double
     * @param P_max double
     * @param P_in double
     * @param PresAdj double
     * @param P_atm double
     *      Units for power kW and Capacity acfm
     *
     */
    void Pressure_InletCorrection(const double capacity, const double full_load_bhp, const double poly_exponent, const double P_ratedDischarge, const double P_RatedIn,
                                  const double Eff, const double P_fl, const double P_max, const double P_in, const bool PresAdj, const double P_atm = 14.69) {
        PressureInletCorrection(CompType, capacity, full_load_bhp, poly_exponent, P_ratedDischarge, P_RatedIn, Eff, P_fl, P_max, P_in, PresAdj, P_atm);
    }

private:
    const double kW_nl = 1;
    double lf_nl = 0;
    double mod_exp = 1;
    CompressorType CompType;
};

class Compressors_StartStop: public CompressorsBase{
public:
    /**
     *
     * @param kW_fl double
     * @param C_fl double
     * @param kWPer_max double
     * @param kWPer_fl double
     *      Units for power kW and Capacity acfm
     *
     */
    Compressors_StartStop(const double kW_fl, const double C_fl, const double kWPer_max, const double kWPer_fl): CompressorsBase(kW_fl, C_fl), kWPer_max(kWPer_max), kWPer_fl(kWPer_fl)
    {
        kW_max = kWPer_max * kW_fl;
    }

    /**
     *
     * @param PerkW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerkW(double PerkW) override;

    /**
     *
     * @param C_Per double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerC(double C_Per) override;

    /**
     *
     * @param kW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromkWMeasured(double kW) override;

    /**
     *
     * @param C double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromCMeasured(double C) override;

    /**
     *
     * @param V, Voltage double
     * @param I, Current double
     * @param PF, Power Factor double
     * @param blowPer double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromVIPFMeasured(double V, double I, double PF) override;

    /**
     *
     * @param capacity double
     * @param full_load_bhp double
     * @param poly_exponent double
     * @param P_ratedDischarge double
     * @param P_RatedIn double
     * @param Eff double
     * @param P_fl double
     * @param P_max double
     * @param P_in double
     * @param PresAdj double
     * @param P_atm double
     *      Units for power kW and Capacity acfm
     *
     */
    void Pressure_InletCorrection(const double capacity, const double full_load_bhp, const double poly_exponent, const double P_ratedDischarge, const double P_RatedIn,
                                  const double Eff, const double P_fl, const double P_max, const double P_in, const bool PresAdj, const double P_atm = 14.69) {
        PressureInletCorrection(CompressorType::Screw, capacity, full_load_bhp, poly_exponent, P_ratedDischarge, P_RatedIn, Eff, P_fl, P_max, P_in, PresAdj, P_atm);

        kW_max = kWPer_max * kW_fl;
        //???? kW_max = kW_max_Adjusted;
    }

private:
    const double kWPer_max = 1, kWPer_fl = 1;
    double kW_max;
};

class Compressors_LoadUnload: public CompressorsBase{
public:
    /**
     *
     * @param kW_fl double
     * @param C_fl double
     * @param kW_max double
     * @param P_fl double
     * @param P_max double
     * @param P_mod double
     * @param P_atm double
     * @param CompType double
     * @param LubricantType double
     * @param CntrlType double
     * @param kW_nl double
     *      Units for power kW and Capacity acfm
     *
     */
    Compressors_LoadUnload(const double kW_fl, const double C_fl, const double kW_max, const double P_fl, const double P_max, const double P_mod, const double P_atm = 14.7,
                           const CompressorType CompType = CompressorType::Reciprocating, const Lubricant LubricantType = Lubricant::None, ControlType CntrlType = ControlType::LoadUnload, const double kW_nl = 1) :
                            CompressorsBase(kW_fl, C_fl), kW_max(kW_max), P_atm(P_atm), P_fl(P_fl), P_max(P_max), P_mod(P_mod),
                            CompType(CompType), LubricantType(LubricantType), CntrlType(CntrlType), lf_nl(34.1 / kW_fl), C_storage(C_fl*1/7.481), kW_nl(kW_nl)
    {
        if(CompType == CompressorType::Screw && LubricantType == Lubricant::None)
            throw std::invalid_argument( "Lubricant needs to be Injected or free for Screw Compressor Type" );

        if(CompType == CompressorType::Screw) {
            if(LubricantType == Lubricant::Injected){
                lf_fl = 1.00;
                t_blowdown = 0.001;
                t_sdt = 1.956;

                PerC_ul = 100;
                a_tol = 0.02;
                t_reload = 0.001;
            }
            else if(LubricantType == Lubricant::Free){

            }
        }
        else if(CompType == CompressorType::Reciprocating) {

        }
    }

    /**
     *
     * @param PerkW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerkW(double PerkW) override;

    /**
     *
     * @param C_Per double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromPerC(double C_Per) override;

    /**
     *
     * @param kW double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromkWMeasured(double kW) override;

    /**
     *
     * @param C double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromCMeasured(double C) override;

    /**
     *
     * @param V, Voltage double
     * @param I, Current double
     * @param PF, Power Factor double
     * @param blowPer double
     * @return
     * @param kW_Calc double
     * @param C_Calc double
     * @param PerkW double
     * @param C_Per double
     *      Units for power kW and Capacity acfm
     *
     */
    CompressorsBase::Output calculateFromVIPFMeasured(double V, double I, double PF) override;

    /**
     *
     * @param capacity double
     * @param full_load_bhp double
     * @param poly_exponent double
     * @param P_ratedDischarge double
     * @param P_RatedIn double
     * @param Eff double
     * @param P_fl double
     * @param P_max double
     * @param P_in double
     * @param PresAdj double
     * @param P_atm double
     *      Units for power kW and Capacity acfm
     *
     */
    void Pressure_InletCorrection(const double capacity, const double full_load_bhp, const double poly_exponent, const double P_ratedDischarge, const double P_RatedIn,
                                  const double Eff, const double P_fl, const double P_max, const double P_in, const bool PresAdj, const double P_atm = 14.69) {
        PressureInletCorrection(CompressorType::Screw, capacity, full_load_bhp, poly_exponent, P_ratedDischarge, P_RatedIn, Eff, P_fl, P_max, P_in, PresAdj, P_atm);

        kW_max = kW_max_Adjusted;
    }

private:
    const double kW_nl = 1;
    const double P_fl, P_max, P_mod, P_atm, lf_nl, C_storage;
    const double P_range = 0, x_mod = 1/*Throttle=1, Variable Displacement=2*/;
    CompressorType CompType;
    Lubricant LubricantType;
    ControlType CntrlType;

    double kW_max;
    double P_sump_ul = 15, t_blowdown = 0.003, t_sdt = 0.004, a_tol = 0.02, t_reload = 0.001, PerC_ul = 100, lf_fl = 0.7;

    double CurveFit(double, bool) const;
};

class Compressors_ModulationWithUnload: public Compressors_LoadUnload{
public:
    /**
     *
     * @param kW_fl double
     * @param C_fl double
     * @param kW_max double
     * @param kW_nl double
     * @param P_fl double
     * @param P_max double
     * @param P_mod double
     * @param P_atm double
     * @param CntrlType double
     *      Units for power kW and Capacity acfm
     *
     */
    Compressors_ModulationWithUnload(const double kW_fl, const double C_fl, const double kW_max, const double kW_nl,
                                     const double P_fl, const double P_max, const double P_mod, const double P_atm = 14.7, Compressors::ControlType CntrlType = Compressors::VariableDisplacementUnload) :
            Compressors_LoadUnload(kW_fl, C_fl, kW_max, P_fl, P_max, P_mod, P_atm, Compressors::Screw, Compressors::Injected, CntrlType, kW_nl)
            {

    }
};


class CompressorEEMs {
public:
    struct ReduceAirLeaksOutput
    {
        ReduceAirLeaksOutput(double C_lkred, double C_usage_lkred, double PerC_lkred) : C_lkred(C_lkred), C_usage_lkred(C_usage_lkred), PerC_lkred(PerC_lkred){}

        ReduceAirLeaksOutput() = default;
        double C_lkred = 0, C_usage_lkred = 0, PerC_lkred = 0;
    };

    struct ImproveEndUseEfficiencyOutput
    {
        ImproveEndUseEfficiencyOutput(double C_af_red, double CPer_af_red) : C_af_red(C_af_red), CPer_af_red(CPer_af_red){}

        ImproveEndUseEfficiencyOutput() = default;
        double C_af_red = 0, CPer_af_red = 0;
    };

    struct ReduceSystemAirPressureOutput
    {
        ReduceSystemAirPressureOutput(double P_fl_rpred, double kW_fl_rpadj, double C_usage_rpred, double PerC_rpred) :
        P_fl_rpred(P_fl_rpred), kW_fl_rpadj(kW_fl_rpadj), C_usage_rpred(C_usage_rpred), PerC_rpred(PerC_rpred){}

        ReduceSystemAirPressureOutput() = default;
        double P_fl_rpred = 0, kW_fl_rpadj = 0, C_usage_rpred = 0, PerC_rpred = 0;
    };

    /**
     *
     * @param C_fl double, units acfm
     * @param C_usage double, units acfm
     * @param C_lk double, units acfm
     * @param PerC_lkred double percentage / fraction
     *
     * @return
     * @param C_lkred double, units acfm
     * @param C_usage_lkred double, units acfm
     * @param PerC_lkred double percentage / fraction
     *
     */
    static ReduceAirLeaksOutput ReduceAirLeaks(double C_fl, double C_usage, double C_lk, double PerC_lkred){
        const double C_lkred = PerC_lkred * C_lk;
        const double C_usage_lkred = C_usage - C_lkred;

        return ReduceAirLeaksOutput(C_lkred, C_usage_lkred, C_usage_lkred / C_fl);
    }

    /**
     *
     * @param C_fl double, units acfm
     * @param C_usage double, units acfm
     * @param C_avgaf_red double, units acfm
     *
     * @return
     * @param C_af_red double, units acfm
     * @param CPer_af_red double percentage / fraction
     *
     */
    static ImproveEndUseEfficiencyOutput ImproveEndUseEfficiency(double C_fl, double C_usage, double C_avgaf_red){
        const double C_af_red = C_usage - C_avgaf_red;
        return ImproveEndUseEfficiencyOutput(C_af_red, C_af_red / C_fl);
    }

    /**
     *
     * @param C_fl double, units acfm
     * @param C_usage double, units acfm
     * @param P_fl double, units psig
     * @param kW_fl double, units kW
     * @param P_rpred double, units psig
     * @param P_alt double, units psia
     * @param P_atm double, units psia
     *
     * @return
     * @param P_fl_rpred double, units psig
     * @param kW_fl_rpadj double, units kW
     * @param C_usage_rpred double, units acfm
     * @param PerC_rpred double percentage / fraction
     *
     */
    static ReduceSystemAirPressureOutput ReduceSystemAirPressure(double C_fl, double C_usage, double P_fl, double kW_fl, double P_rpred, double P_alt = 14.69, double P_atm = 14.69){
        const double P_fl_rpred = P_fl - P_rpred;
        const double kW_fl_rpadj = kW_fl * ((pow((P_fl_rpred + P_alt) / P_alt, 0.283) - 1) / (pow((P_fl + P_atm) / P_atm, 0.283) - 1));
        const double C_usage_rpred  = (C_usage - (C_usage - (C_usage * ((P_fl_rpred + P_alt) / (P_fl + P_atm)))) * 0.6);

        return ReduceSystemAirPressureOutput(P_fl_rpred, kW_fl_rpadj, C_usage_rpred,  C_usage_rpred/ C_fl);
    }
};
#endif //AMO_TOOLS_SUITE_COMPRESSORS_H
