/**
 * @file
 * @brief Contains the implementation of the flue gas loss calculations.
 *
 * @author Gina Accawi (accawigk) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include <array>
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

double gasCompositions::calculateSensibleHeat(const double combustionAirTemp) {
    double specificHeatFuel = 0;
    for ( auto const & comp : gasses ) {
        specificHeatFuel += comp.second->compByWeight * (comp.second->specificHeat(520) / comp.second->molecularWeight);
    }

    return 1 * specificHeatFuel * (combustionAirTemp - 32);
}

double gasCompositions::calculateHeatCombustionAir(const double combustionAirTemp, const double excessAir) {
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
                             + 0.769 * (N2->specificHeat(rAir) / N2->molecularWeight);

    return mCombustionAir * cpCombustionAir * (combustionAirTemp - 32);
}

double gasCompositions::calculateHeatingValueFuel(){
    double heatValueFuel = 0;
	for ( auto const & comp : gasses ) {
        heatValueFuel += comp.second->compByWeight * comp.second->heatingValue;
    }
    return heatValueFuel;
}

void gasCompositions::calculateMassFlueGasComponents(const double excessAir) {
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

    // TODO this formula was taken from page 7 of the doc, which is NOT included in example 3
    for ( auto const & comp : gasses ) {
        mSO2 += comp.second->so2Generated * comp.second->compByWeight / comp.second->molecularWeight;
    }
}

void gasCompositions::calculateEnthalpy() {
    auto const & H2O = gasses["H2O"];
    auto const & CO2 = gasses["CO2"];
    auto const & N2 = gasses["N2"];
    auto const & O2 = gasses["O2"];
    auto const & SO2 = gasses["SO2"];

    const double ppH2O = (mH2O / H2O->specificWeight) /
            (mCO2 / CO2->specificWeight + mH2O / H2O->specificWeight + mN2 / N2->specificWeight
             + mO2 / O2->specificWeight + mSO2 / SO2->specificWeight);

    hH2Osat = 1096.7 * pow(ppH2O * 29.926, 0.013);
    tH2Osat = 36.009 * log(ppH2O * 29.926) + 81.054;
}

double gasCompositions::calculateTotalHeatContentFlueGas(const double flueGasTemp) {
    auto const & H2O = gasses["H2O"];

    const double hH2O = mH2O
                        * (hH2Osat
                           + 0.5 * ((H2O->specificHeat(flueGasTemp + 460) / H2O->molecularWeight)
                                    + (H2O->specificHeat(520) / H2O->molecularWeight)) * (flueGasTemp - tH2Osat));


    std::array<std::tuple<gasProperties *, const double>, 4> gasArray = {
            std::make_tuple(gasses["CO2"], mCO2), std::make_tuple(gasses["N2"], mN2),
            std::make_tuple(gasses["O2"], mO2), std::make_tuple(gasses["SO2"], mSO2)
    };

	double result = 0.0;
    for ( int i = 0; i < gasArray.size(); i++ ) {
	    auto const & tup = gasArray[i];
	    auto const & c = std::get<0>(tup);
        const double mass = std::get<1>(tup);
        result += mass * (0.5 * ((c->specificHeat(flueGasTemp + 460) / c->molecularWeight) + (c->specificHeat(520) / c->molecularWeight)) * (flueGasTemp - 32));
    }

    return hH2O + result;
}

double FlueGas::getHeatLoss() {
	compositions_.calculateCompByWeight();
    double heatInFlueGasses = compositions_.calculateSensibleHeat(combustionAirTemperature_);
    double hCombustionAir = compositions_.calculateHeatCombustionAir(combustionAirTemperature_, excessAirPercentage_);
    double hValueFuel = compositions_.calculateHeatingValueFuel();
    compositions_.calculateMassFlueGasComponents(excessAirPercentage_);
    compositions_.calculateEnthalpy();
    double totalHeatContentFlueGas = compositions_.calculateTotalHeatContentFlueGas(flueGasTemperature_);

    double heatInput = heatInFlueGasses + hCombustionAir + hValueFuel;

    return (heatInput - totalHeatContentFlueGas) / hValueFuel;
}