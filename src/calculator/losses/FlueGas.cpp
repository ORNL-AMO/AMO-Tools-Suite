/**
 * @file
 * @brief Contains the implementation of the flue gas loss calculations.
 *
 * @author Gina Accawi (accawigk) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "calculator/losses/FlueGas.h"

void gasCompositions::calculateCompByWeight() {
    double summationDenom = 0;
    for ( auto const & compound : gasses ) {
        summationDenom += compound.second->compAdjByVol * compound.second->specificWeight;
    }

    for ( auto & comp : gasses ) {
        comp.second->compByWeight = (comp.second->compAdjByVol * comp.second->specificWeight) / summationDenom;
    }
}

void gasCompositions::calculateSensibleHeat() {
    // calc specific heat
    double specificHeatFuel = 0;
    for ( auto const & comp : gasses ) {
        specificHeatFuel += comp.second->compByWeight * (comp.second->specificHeat(520) / comp.second->molecularWeight);
    }

    sensibleHeatFuel = 1 * specificHeatFuel * (combustionAirTemp - 32);
}

void gasCompositions::calculateHeatCombustionAir() {
    double o2Air = 0;
    for ( auto const & comp : gasses ) {
        o2Air += comp.second->compByWeight * (comp.second->o2Generated / comp.second->molecularWeight);
    }

    double mAir = o2Air / 0.231;
    double mCombustionAir = mAir * (1 + excessAir);
    double rAir = combustionAirTemp + 460;
    auto const & O2 = gasses["O2"];
    auto const & N2 = gasses["N2"];

    double cpCombustionAir = 0.231 * (O2->specificHeat(rAir) / O2->molecularWeight)
                             + 0.769 * (N2->specificHeat(rAir) / O2->molecularWeight);

    heatCombustionAir = mCombustionAir * cpCombustionAir * (combustionAirTemp - 32);
}

void gasCompositions::calculateHeatingValueFuel(){
    heatValueFuel = 0;
	for ( auto const & comp : gasses ) {
        heatValueFuel += comp.second->compByWeight * comp.second->heatingValue;
    }
}

void gasCompositions::calculateMassFlueGasComponents() {
    for ( auto const & comp : gasses ) {
        mH2O += (comp.second->h2oGenerated * comp.second->compByWeight) / comp.second->molecularWeight;
        mCO2 += (comp.second->co2Generated * comp.second->compByWeight) / comp.second->molecularWeight;
        mO2 += (comp.second->o2Generated * comp.second->compByWeight) / comp.second->molecularWeight;
    }
    mO2 *= excessAir;

	auto const & N2 = gasses["N2"];
    for ( auto const & comp : gasses ) {
        auto const & c = comp.second;
        mN2 += ((c->o2Generated * c->compByWeight) / c->molecularWeight);

    }
    mN2 = ((1 - 0.231) / 0.231) * mN2 + mO2 * (1 - 0.231) / 0.231 + N2->compByWeight;
}

double FlueGas::getHeatLoss() {
	// fuel analysis by volume percentage




    return 2850767;
}