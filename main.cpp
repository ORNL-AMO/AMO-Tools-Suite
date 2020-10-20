/*#include <iostream>

int main() {
    std::cout << "Run 'doxygen Doxyfile.in' from the root project directory to generate documentation." << std::endl;
	std::cout << "View the documentation by opening docs/html/index.html in a web browser." << std::endl;
	return 0;
}*/

#include <iostream>
#include "calculator/util/CompressedAirCentrifugal.h"

void printout(const CompressedAirCentrifugalBase::Output &out);
void printoutBlowOff(const CompressedAirCentrifugalBase::OutputBlowOff &out);

int main() {
    std::cout << "Start...." << std::endl;

    CompressedAirCentrifugal_BlowOff *bocc = new CompressedAirCentrifugal_BlowOff(452.3, 3138, 370.9, 2510);
    printoutBlowOff(bocc->calculateFromPerkW_BlowOff(0.82, 0.6798));
    printoutBlowOff(bocc->calculateFromPerC_BlowOff(0.01));
    printoutBlowOff(bocc->calculateFromkWMeasured_BlowOff(370.9, 0.6798));
    printoutBlowOff(bocc->calculateFromCMeasured_BlowOff(31.38));
    printoutBlowOff(bocc->calculateFromVIPFMeasured_BlowOff(440,0.02152,50, 0.6798));
    std::cout << std::endl << std::endl;
    bocc->AdjustDischargePressure({3200, 3138, 2885}, {91, 100, 117});
    printoutBlowOff(bocc->calculateFromPerkW_BlowOff(0.82, 0.6798));
    printoutBlowOff(bocc->calculateFromPerC_BlowOff(0.01));
    printoutBlowOff(bocc->calculateFromkWMeasured_BlowOff(370.9, 0.6798));
    printoutBlowOff(bocc->calculateFromCMeasured_BlowOff(31.38));
    printoutBlowOff(bocc->calculateFromVIPFMeasured_BlowOff(440,0.02152,50, 0.6798));
    //printoutBlowOff(bocc->calculateFromPerC_BlowOff(0.94));
    //printoutBlowOff(bocc->calculateFromPerC_BlowOff(0.76));
    //printoutBlowOff(bocc->calculateFromPerC_BlowOff(0));
    std::cout << std::endl << std::endl;

    CompressedAirCentrifugal_LoadUnload *lulcc = new CompressedAirCentrifugal_LoadUnload(452.3, 3138, 71.3);
    printout(lulcc->calculateFromPerkW(0.36));
    printout(lulcc->calculateFromPerC(0.24));
    printout(lulcc->calculateFromkWMeasured(162.828));
    printout(lulcc->calculateFromCMeasured(753.12));
    printout(lulcc->calculateFromVIPFMeasured(440,0.00945,50));
    std::cout << std::endl << std::endl;
    lulcc->AdjustDischargePressure({3200, 3138, 2885}, {91, 100, 117});
    printout(lulcc->calculateFromPerkW(0.36));
    printout(lulcc->calculateFromPerC(0.24));
    printout(lulcc->calculateFromkWMeasured(162.828));
    printout(lulcc->calculateFromCMeasured(753.12));
    printout(lulcc->calculateFromVIPFMeasured(440,0.00945,50));
    std::cout << std::endl << std::endl;

    CompressedAirCentrifugal_ModulationUnload *mulcc = new CompressedAirCentrifugal_ModulationUnload(452.3, 3138, 71.3, 3005, 411.9, 2731);
    printout(mulcc->calculateFromPerkW(0.94));
    printout(mulcc->calculateFromPerC(0.24));
    printout(mulcc->calculateFromkWMeasured(425.162));
    printout(mulcc->calculateFromCMeasured(753.12));
    printout(mulcc->calculateFromVIPFMeasured(440,0.02467,50));
    std::cout << std::endl << std::endl;
    mulcc->AdjustDischargePressure({3200, 3138, 2885}, {91, 100, 117});
    printout(mulcc->calculateFromPerkW(0.94));
    printout(mulcc->calculateFromPerC(0.24));
    printout(mulcc->calculateFromkWMeasured(425.162));
    printout(mulcc->calculateFromCMeasured(753.12));
    printout(mulcc->calculateFromVIPFMeasured(440,0.02467,50));

    std::cout << "Done...." << std::endl;
    return 0;
}

void printout(const CompressedAirCentrifugalBase::Output &out) { std::cout << "kW_Calc: " << out.kW_Calc << "  C_Calc: " << out.C_Calc << "  PerkW: " << out.PerkW << "  C_Per: " << out.C_Per << std::endl; }
void printoutBlowOff(const CompressedAirCentrifugalBase::OutputBlowOff &out) { std::cout << "kW_Calc: " << out.kW_Calc << "  C_Calc: " << out.C_Calc << "  PerkW: " << out.PerkW << "  C_Per: " << out.C_Per << "  C_blow: " << out.C_blow << "  blowPer: " << out.blowPer << std::endl; }
