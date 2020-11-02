//
// Created by 7bo on 10/12/2020.
//

#include "calculator/util/CompressedAirCentrifugal.h"

CompressedAirCentrifugal_BlowOff::OutputBlowOff CompressedAirCentrifugal_BlowOff::calculateFromPerkW_BlowOff(double PerkW, double blowPer) {
    double CPer = 0;

    if(PerkW <= kWPer_blow)
        CPer = CPer_blow- blowPer;
    else
        CPer = ((1-CPer_blow)/(1-kWPer_blow))*( PerkW -1+((1-kWPer_blow)/(1-CPer_blow)));

    const double C_blowPer = CPer_blow - CPer;

    return OutputBlowOff(PerkW * kW_fl, C_fl * CPer, PerkW, CPer, C_blowPer * C_fl, C_blowPer);
}

CompressedAirCentrifugal_BlowOff::OutputBlowOff CompressedAirCentrifugal_BlowOff::calculateFromPerC_BlowOff(double CPer) {
    double PerkW = 0;
    double C_blowPer = 0;

    if(CPer < CPer_blow) {
        PerkW = kWPer_blow;
        C_blowPer = CPer_blow - CPer;
    }
    else
        PerkW = ((1- kWPer_blow)/(1- CPer_blow))*( CPer)+1 -((1 - kWPer_blow)/( 1 - CPer_blow))*1;

    return OutputBlowOff(PerkW * kW_fl, C_fl * CPer, PerkW, CPer, C_blowPer * C_fl, C_blowPer);
}

CompressedAirCentrifugal_BlowOff::OutputBlowOff CompressedAirCentrifugal_BlowOff::calculateFromkWMeasured_BlowOff(double kW, double blowPer) {
    return CompressedAirCentrifugal_BlowOff::calculateFromPerkW_BlowOff(kW/kW_fl, blowPer);
}

CompressedAirCentrifugal_BlowOff::OutputBlowOff CompressedAirCentrifugal_BlowOff::calculateFromCMeasured_BlowOff(double C) {
    return CompressedAirCentrifugal_BlowOff::calculateFromPerC_BlowOff(C/C_fl);
}

CompressedAirCentrifugal_BlowOff::OutputBlowOff CompressedAirCentrifugal_BlowOff::calculateFromVIPFMeasured_BlowOff(double V, double I, double PF, double blowPer) {
    return CompressedAirCentrifugal_BlowOff::calculateFromPerkW_BlowOff(V*I*PF*1.732/1000, blowPer);
}


CompressedAirCentrifugal_LoadUnload::Output CompressedAirCentrifugal_LoadUnload::calculateFromPerkW(double PerkW) {
    const double CPer = Round((PerkW - kWPer_nl) * ((CPer_fl-CPer_nl) / (1 - kWPer_nl)));

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressedAirCentrifugal_LoadUnload::Output CompressedAirCentrifugal_LoadUnload::calculateFromPerC(double CPer) {
    const double PerkW = Round(((1 - kWPer_nl) / (CPer_fl-CPer_nl))*(CPer) + kWPer_nl);

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressedAirCentrifugal_LoadUnload::Output CompressedAirCentrifugal_LoadUnload::calculateFromkWMeasured(double kW) {
    return CompressedAirCentrifugal_LoadUnload::calculateFromPerkW(kW/kW_fl);
}

CompressedAirCentrifugal_LoadUnload::Output CompressedAirCentrifugal_LoadUnload::calculateFromCMeasured(double C) {
    return CompressedAirCentrifugal_LoadUnload::calculateFromPerC(C/C_fl);
}

CompressedAirCentrifugal_LoadUnload::Output CompressedAirCentrifugal_LoadUnload::calculateFromVIPFMeasured(double V, double I, double PF) {
    return CompressedAirCentrifugal_LoadUnload::calculateFromPerkW(V*I*PF*1.732/1000);
}


CompressedAirCentrifugal_ModulationUnload::Output CompressedAirCentrifugal_ModulationUnload::calculateFromPerkW(double PerkW) {
    double CPer = 1;
    if(PerkW <=kWPer_nl)
        CPer = CPer_nl;
    else if(PerkW < kWPer_ul)
        CPer  = (PerkW -kWPer_nl)*(( CPer_ul - CPer_nl)/( kWPer_ul -kWPer_nl));
    else if(PerkW >= kWPer_ul)
        CPer  = ((1- CPer_ulB)/( kWPer_max - kWPer_ul))* PerkW +(1-(1 - CPer_ulB)/( kWPer_max - kWPer_ul));

    return Output(PerkW * kW_fl, (CPer < CPer_ulB ? C_fl : C_max) * CPer, PerkW, CPer);
}

CompressedAirCentrifugal_ModulationUnload::Output CompressedAirCentrifugal_ModulationUnload::calculateFromPerC(double CPer) {
    double PerkW = 1;
    if(CPer <kWPer_ul)
            PerkW = ((kWPer_ul - kWPer_nl)/( CPer_ul - CPer_nl))*( CPer)+ kWPer_nl;
    else if(CPer < CPer_max)
            PerkW = ((kWPer_max - kWPer_ul)/( CPer_max - CPer_ul))*( CPer)+ kWPer_max -(( kWPer_max - kWPer_ul)/( CPer_max - CPer_ul))* CPer_max;

    return Output(PerkW * kW_fl, C_fl * CPer, PerkW, CPer);
}

CompressedAirCentrifugal_ModulationUnload::Output CompressedAirCentrifugal_ModulationUnload::calculateFromkWMeasured(double kW) {
    return CompressedAirCentrifugal_ModulationUnload::calculateFromPerkW(kW/kW_fl);
}

CompressedAirCentrifugal_ModulationUnload::Output CompressedAirCentrifugal_ModulationUnload::calculateFromCMeasured(double C) {
    return CompressedAirCentrifugal_ModulationUnload::calculateFromPerC(C/C_fl);
}

CompressedAirCentrifugal_ModulationUnload::Output CompressedAirCentrifugal_ModulationUnload::calculateFromVIPFMeasured(double V, double I, double PF) {
    return CompressedAirCentrifugal_ModulationUnload::calculateFromPerkW(V*I*PF*1.732/1000);
}
