/**
 * @file
 * @brief Calculate estimated power(kW) consumption and air flow(acfm) for a compressor based on control type.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#include <algorithm>
#include "calculator/util/Compressors.h"

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromPerkW_BlowOff(double PerkW, double blowPer)
{
    double CPer = 0;

    if (PerkW <= kWPer_blow)
        CPer = CPer_blow - blowPer;
    else
        CPer = ((1 - CPer_blow) / (1 - kWPer_blow)) * (PerkW - 1 + ((1 - kWPer_blow) / (1 - CPer_blow)));

    const double C_blowPer = CPer_blow - CPer;

    return OutputBlowOff(PerkW * kW_fl, C_fl * CPer, PerkW, CPer, C_blowPer * C_fl, C_blowPer);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromPerC_BlowOff(double CPer)
{
    double PerkW = 0;
    double C_blowPer = 0;

    if (CPer < CPer_blow)
    {
        PerkW = kWPer_blow;
        C_blowPer = CPer_blow - CPer;
    }
    else
        PerkW = ((1 - kWPer_blow) / (1 - CPer_blow)) * (CPer) + 1 - ((1 - kWPer_blow) / (1 - CPer_blow)) * 1;

    return OutputBlowOff(PerkW * kW_fl, C_fl * CPer, PerkW, CPer, C_blowPer * C_fl, C_blowPer);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromkWMeasured_BlowOff(double kW, double blowPer)
{
    return Compressors_Centrifugal_BlowOff::calculateFromPerkW_BlowOff(kW / kW_fl, blowPer);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromCMeasured_BlowOff(double C)
{
    return Compressors_Centrifugal_BlowOff::calculateFromPerC_BlowOff(C / C_fl);
}

CompressorsBase::OutputBlowOff Compressors_Centrifugal_BlowOff::calculateFromVIPFMeasured_BlowOff(double V, double I, double PF, double blowPer)
{
    return Compressors_Centrifugal_BlowOff::calculateFromkWMeasured_BlowOff(V * I * PF * 1.732 / 1000, blowPer);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromPerkW(double PerkW)
{
    const double CPer = ((PerkW - kWPer_nl) * ((CPer_fl - CPer_nl) / (1 - kWPer_nl)));

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromPerC(double CPer)
{
    const double PerkW = (((1 - kWPer_nl) / (CPer_fl - CPer_nl)) * (CPer) + kWPer_nl);

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_Centrifugal_LoadUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromCMeasured(double C)
{
    return Compressors_Centrifugal_LoadUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_Centrifugal_LoadUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_Centrifugal_LoadUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromPerkW(double PerkW)
{
    double CPer = 1;
    if (PerkW <= kWPer_nl)
        CPer = CPer_nl;
    else if (PerkW < kWPer_ul)
        CPer = (PerkW - kWPer_nl) * ((CPer_ul - CPer_nl) / (kWPer_ul - kWPer_nl));
    else if (PerkW >= kWPer_ul)
        CPer = ((1 - CPer_ulB) / (kWPer_max - kWPer_ul)) * PerkW + (1 - (1 - CPer_ulB) / (kWPer_max - kWPer_ul));

    return Output(PerkW * kW_fl, (CPer < CPer_ulB ? C_fl : C_max) * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromPerC(double CPer)
{
    double PerkW = 1;
    if (CPer < kWPer_ul)
        PerkW = ((kWPer_ul - kWPer_nl) / (CPer_ul - CPer_nl)) * (CPer) + kWPer_nl;
    else if (CPer < CPer_max)
        PerkW = ((kWPer_max - kWPer_ul) / (CPer_max - CPer_ul)) * (CPer) + kWPer_max - ((kWPer_max - kWPer_ul) / (CPer_max - CPer_ul)) * CPer_max;

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_Centrifugal_ModulationUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromCMeasured(double C)
{
    return Compressors_Centrifugal_ModulationUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_Centrifugal_ModulationUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_Centrifugal_ModulationUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromPerkW(double PerkW)
{
    double C_Calc = 1;
    if (PerkW < lf_nl)
        C_Calc = 0;
    else if (PerkW == 1)
        C_Calc = C_fl;
    else
        C_Calc = pow(((PerkW * kW_fl - kW_nl) / ((woUnload ? kW_fl : kW_nl / 0.7) - kW_nl)), 1 / mod_exp) * C_fl;

    return Output(PerkW * kW_fl, C_Calc, (PerkW), (C_Calc / C_fl));
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromPerC(double CPer)
{

    const double kW_Calc = ((woUnload ? kW_fl : kW_nl / 0.7) - kW_nl) * pow(CPer, mod_exp) + kW_nl;

    return Output(kW_Calc, C_fl * CPer, kW_Calc / kW_fl, CPer);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_ModulationWOUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromCMeasured(double C)
{
    return Compressors_ModulationWOUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_ModulationWOUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_ModulationWOUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

CompressorsBase::Output Compressors_StartStop::calculateFromPerkW(double PerkW)
{
    double C_Calc = C_fl * PerkW / ((kWPer_fl + kW_max / kW_fl) / 2);

    return Output(PerkW * kW_fl, C_Calc, (PerkW), (C_Calc / C_fl));
}

CompressorsBase::Output Compressors_StartStop::calculateFromPerC(double CPer)
{
    const double kW_Calc = (((kWPer_fl + kW_max / kW_fl) / 2) * CPer * kW_fl);
    return Output(kW_Calc, C_fl * CPer, kW_Calc / kW_fl, CPer);
}

CompressorsBase::Output Compressors_StartStop::calculateFromkWMeasured(double kW)
{
    return Compressors_StartStop::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_StartStop::calculateFromCMeasured(double C)
{
    return Compressors_StartStop::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_StartStop::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_StartStop::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}

double Compressors_LoadUnload::CurveFit(double value, bool capacityVPower) const
{
    const double kW_maxmod = lf_fl * kW_max;
    const double kW_nl = lf_nl * kW_fl;
    const double C_ul = C_fl * PerC_ul / 100;
    const double kW_ul = (kW_max - kW_maxmod) * pow(C_ul / C_fl, mod_exp) + kW_maxmod;
    const double P_ul = P_max + (1 - C_ul / C_fl) * P_mod;
    const double t_bdc = t_blowdown / log(1 / a_tol);

    const double t_spc = t_sdt / log(1 / a_tol);

    std::vector<double> PerCapacity;
    std::vector<double> PerPower;
    const double decrementC = C_fl / 75;
    double C_curve = C_fl;

    do
    {
        double t_rmod = 1;
        double kW_avg_mod = 0;
        if (C_ul != C_fl)
        {
            if (C_curve < C_ul)
            {
                t_rmod = P_mod * C_storage / P_atm / C_fl * log((C_fl - C_curve) / (C_ul - C_curve)) * 60;
                if (t_rmod == 0)
                    t_rmod = 1;

                const double P_avg_mod = (P_max + P_mod - C_curve * P_mod / C_fl) +
                                         (C_curve * P_mod / C_fl - P_mod) * (P_mod * C_storage / P_atm * C_fl) *
                                             (1 - exp(-P_atm * C_fl / P_mod / C_storage * t_rmod / 60)) / t_rmod * 60;
                kW_avg_mod = (kW_max - kW_maxmod) * pow((P_max + P_mod - P_avg_mod) / P_avg_mod, mod_exp) + kW_maxmod;
            }
            else
            {
                kW_avg_mod = (kW_max - kW_maxmod) * pow(C_curve / C_fl, mod_exp) + kW_maxmod;
            }
        }

        double kW_curve = C_curve == C_ul ? kW_fl : kW_avg_mod;
        if (C_curve < C_ul)
        {
            const double t_dd = C_storage * 60 * ((P_ul - P_fl) / (C_curve * P_atm));
            const double t_bd = std::min(t_blowdown, t_dd);
            const double P_sump_bla = P_sump_ul + (P_ul - P_sump_ul) * exp(-t_bd / t_bdc);

            double kW_min_bd = 0;
            if (t_bd == t_blowdown)
            {
                kW_min_bd = kW_nl;
            }
            else
            {
                kW_min_bd = kW_nl + ((((kW_ul - kW_maxmod) * exp(-t_bd / t_spc) + kW_maxmod) - kW_nl) * exp(-t_bd / t_bdc));
            }
            const double kW_avg_bd = (kW_nl + ((kW_ul - kW_maxmod) * exp(-t_bd / t_spc) + kW_maxmod - kW_nl) * (1 - exp(-t_bd / t_bdc)) * t_bdc / t_bd);

            const double t_ol = t_dd - t_bd;
            const double kW_avg_ol = kW_fl * lf_nl;
            const double t_rl = t_reload * (P_ul - P_sump_bla) / (P_ul - (P_ul - P_sump_ul) * a_tol);
            const double kW_avg_rl = (kW_min_bd + kW_fl) / 2;
            const double t_rpu = 60 * C_storage * (P_max - P_fl + t_rl / 60 * P_atm * C_curve / C_storage) / (P_atm * (C_storage - C_curve));
            const double kW_avg_rpu = ((1 - P_atm * C_curve * t_rl / (C_storage * 60 * 200)) * kW_fl + kW_max) / 2;

            kW_curve = (t_bd * kW_avg_bd + t_ol * kW_avg_ol + t_rl * kW_avg_rl + t_rpu * kW_avg_rpu + ((C_ul != C_fl) ? t_rmod * kW_avg_mod : 0)) /
                       (t_bd + t_ol + t_rl + t_rpu + (C_ul != C_fl ? (t_rmod == 0 ? 1 : t_rmod) : 1));
        }

        PerCapacity.push_back(C_curve / C_fl);
        PerPower.push_back(kW_curve / kW_fl);

        if (C_curve == 0.0001)
            break;
        C_curve -= decrementC;
        if (C_curve <= 0)
            C_curve = 0.0001;
    } while (C_curve >= 0);

    if (capacityVPower)
    {
        CurveFitVal curveFitValCap(PerCapacity, PerPower, 4);
        return curveFitValCap.calculate(value);
    }

    CurveFitVal curveFitValCap(PerPower, PerCapacity, 6);
    return curveFitValCap.calculate(value);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromPerkW(double PerkW)
{
    if (PerkW == 1)
        return Output(PerkW * kW_fl, C_fl, PerkW, 1);

    const double CPer = CurveFit(PerkW, false);
    if (CntrlType == ControlType::ModulationUnload || CntrlType == ControlType::VariableDisplacementUnload)
    {
        const double mffp = kW_max * lf_fl;
        const double kW_ul = ((kW_max - mffp) * pow((PerC_ul / 100), mod_exp) + mffp);
        if (PerkW * kW_fl >= kW_ul)
            return Compressors_ModulationWOUnload(kW_fl, C_fl, mffp, CntrlType == ControlType::VariableDisplacementUnload ? 2 : 1, false).calculateFromPerkW(PerkW);
    }

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromPerC(double CPer)
{
    std::cout << "CPer: " << CPer << std::endl;
    if (CPer == 1)
        return Output(kW_fl, C_fl * CPer, 1, CPer);

    double PerkW = CurveFit(CPer, true);
    if (CntrlType == ControlType::ModulationUnload || CntrlType == ControlType::VariableDisplacementUnload)
    {
        double C_ul = C_fl * PerC_ul / 100;
        if (C_fl * CPer >= C_ul)
        {
            std::cout << "Calc modulation with unload" << std::endl;
            return Compressors_ModulationWOUnload(kW_fl, C_fl, kW_max * lf_fl, CntrlType == ControlType::VariableDisplacementUnload ? 2 : 1, false).calculateFromPerC(CPer);
        }
    }

    std::cout << "PerkW: " << PerkW << std::endl;
    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromkWMeasured(double kW)
{
    return Compressors_LoadUnload::calculateFromPerkW(kW / kW_fl);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromCMeasured(double C)
{
    return Compressors_LoadUnload::calculateFromPerC(C / C_fl);
}

CompressorsBase::Output Compressors_LoadUnload::calculateFromVIPFMeasured(double V, double I, double PF)
{
    return Compressors_LoadUnload::calculateFromkWMeasured(V * I * PF * 1.732 / 1000);
}
