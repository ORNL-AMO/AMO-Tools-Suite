/**
 * @file
 * @brief Contains the implementation of the flue gas loss calculations.
 *
 * @author Gina Accawi (accawigk) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include <array>
#include "calculator/losses/GasFlueGasMaterial.h"

std::string GasCompositions::getSubstance() const {
    return substance;
}

// used for calculating excess air in flue gas given O2 levels
double GasCompositions::calculateExcessAir(const double flueGasO2) {
    calculateCompByWeight();
    double excessAir = (8.52381 * flueGasO2) / (2 - (9.52381 * flueGasO2));
	if (excessAir == 0) return 0;

    for (auto i = 0; i < 100; i++) {
        calculateMassFlueGasComponents(excessAir);
        auto const O2i = mO2 / (mH2O + mCO2 + mN2 + mO2 + mSO2);
        auto const error = std::fabs((flueGasO2 - O2i) / flueGasO2);
        if (error < 0.02) break;
        if (O2i > flueGasO2) {
            excessAir -= (excessAir * 0.01);
        } else {
            excessAir += (excessAir * 0.01);
        }
    }
	return excessAir;
}

// used for calculating O2 in flue gas given excess air as a decimal
double GasCompositions::calculateO2(const double excessAir) {
    calculateCompByWeight();
    calculateMassFlueGasComponents(excessAir);
    return mO2 / (mH2O + mCO2 + mN2 + mO2 + mSO2);
}

void GasCompositions::calculateCompByWeight() {
    double summationDenom = 0;
    for ( auto const & compound : gasses ) {
        summationDenom += compound.second->compAdjByVol * compound.second->specificWeight;
    }

    for ( auto & comp : gasses ) {
        comp.second->compByWeight = (comp.second->compAdjByVol * comp.second->specificWeight) / summationDenom;
    }
}

double GasCompositions::calculateSensibleHeat(const double fuelTemp) {
    double specificHeatFuel = 0;
    for ( auto const & comp : gasses ) {
        specificHeatFuel += comp.second->compByWeight * (comp.second->specificHeat(520) / comp.second->molecularWeight);
    }

    return 1 * specificHeatFuel * (fuelTemp - 32);
}

double GasCompositions::calculateHeatCombustionAir(const double combustionAirTemp, const double excessAir) {
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

double GasCompositions::calculateSpecificGravity() {
    double summationNumerator = 0;
    for ( auto const & compound : gasses ) {
        summationNumerator += compound.second->compAdjByVol * compound.second->molecularWeight;
    }
    return summationNumerator / (22.4 * 1.205);
}

double GasCompositions::calculateHeatingValueFuel() {
    double heatValueFuel = 0;
	for ( auto const & comp : gasses ) {
        heatValueFuel += comp.second->compByWeight * comp.second->heatingValue;
    }
    return heatValueFuel;
}

double GasCompositions::calculateHeatingValueFuelVolume() {
    double heatValueFuel = 0;
    for ( auto const & comp : gasses ) {
        heatValueFuel += comp.second->compAdjByVol * comp.second->heatingValueVolume;
    }
    return heatValueFuel;
}

void GasCompositions::calculateMassFlueGasComponents(const double excessAir) {
	mH2O = 0, mCO2 = 0, mO2 = 0, mN2 = 0, mSO2 = 0;
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

    for ( auto const & comp : gasses ) {
        mSO2 += comp.second->so2Generated * comp.second->compByWeight / comp.second->molecularWeight;
    }
}

void GasCompositions::calculateEnthalpy() {
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

double GasCompositions::calculateTotalHeatContentFlueGas(const double flueGasTemp) {
    auto const & H2O = gasses["H2O"];

    const double hH2O = mH2O
                        * (hH2Osat
                           + 0.5 * ((H2O->specificHeat(flueGasTemp + 460) / H2O->molecularWeight)
                                    + (H2O->specificHeat(520) / H2O->molecularWeight)) * (flueGasTemp - tH2Osat));

    std::array<std::tuple<std::shared_ptr<GasProperties>, const double>, 4> gasArray = {
            {
                    std::make_tuple(gasses["CO2"], mCO2),
                    std::make_tuple(gasses["N2"], mN2),
                    std::make_tuple(gasses["O2"], mO2),
                    std::make_tuple(gasses["SO2"], mSO2)
            }
    };

	double result = 0.0;
    for ( auto const & gas : gasArray ) {
//	    auto const & tup = gas;
	    auto const & c = std::get<0>(gas);
        const double mass = std::get<1>(gas);
        result += mass * (0.5 * ((c->specificHeat(flueGasTemp + 460) / c->molecularWeight) + (c->specificHeat(520) / c->molecularWeight)) * (flueGasTemp - 32));
    }

    return hH2O + result;
}

double GasFlueGasMaterial::getHeatLoss() {
	compositions.calculateCompByWeight();
    const double heatInFlueGasses = compositions.calculateSensibleHeat(fuelTemperature);
    const double hCombustionAir = compositions.calculateHeatCombustionAir(combustionAirTemperature, excessAirPercentage);
    const double hValueFuel = compositions.calculateHeatingValueFuel();
    compositions.calculateMassFlueGasComponents(excessAirPercentage);
    compositions.calculateEnthalpy();
    const double totalHeatContentFlueGas = compositions.calculateTotalHeatContentFlueGas(flueGasTemperature);

    const double heatInput = heatInFlueGasses + hCombustionAir + hValueFuel;

    return (heatInput - totalHeatContentFlueGas) / hValueFuel;
}