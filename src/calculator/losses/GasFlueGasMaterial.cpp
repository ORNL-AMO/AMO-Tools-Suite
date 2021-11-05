/**
 * @file
 * @brief Contains the implementation of the flue gas loss calculations.
 *
 * @author Gina Accawi (accawigk) & Preston Shires (pshires) & Omer Aziz (omerb)
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
    double excessAir = getExcessAir(flueGasO2);
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

double GasCompositions::getExcessAir(const double flueGasO2) const { return ((stoichometricAir / 32 - 1) * flueGasO2) / (2 - (stoichometricAir / 32 * flueGasO2)); }

double GasCompositions::getEnthalpyAtSaturation(const double ppH2O) const { return 1096.7 * pow(ppH2O * 29.926, 0.013); }

double GasCompositions::getSaturationTemperature(const double ppH2O) const { return 36.009 * log(ppH2O * 29.926) + 81.054; }

GasCompositions::ProcessHeatPropertiesResults GasCompositions::getProcessHeatProperties(const double flueGasTempF, const double flueGasO2, const double combAirTemperatureF,
                                                                                        const double fuelTempF, const double ambientAirTempF, const double combAirMoisturePerc,
                                                                                        const double excessAir)
{
    double exsAir = 0;
    double flueO2 = 0;
    if(excessAir != 0){
        exsAir = excessAir;
        flueO2 = calculateO2(exsAir);
        flueGasO2AdjustForCalcError(excessAir, flueO2);
    }else {
        exsAir = calculateExcessAir(flueGasO2);
        flueO2 = flueGasO2;
    }

    const double initialTemp = (460 + combAirTemperatureF);
    const double finalTemp = (460 + flueGasTempF);

    //Begin - calculate average Cp across temperature range of combustion air to flue gas
    const double initialTempCpO2 = (11.515 - 172 / pow(initialTemp, 0.5) + 1530 / initialTemp);
    const double finalTempCpO2 = (11.515 - 172 / pow(finalTemp, 0.5) + 1530 / finalTemp);
    const double initialTempCpSCFO2 = initialTempCpO2 / 378.2;
    const double finalTempCpSCFO2 = finalTempCpO2 / 378.2;
    const double avgCpO2 = (initialTempCpO2 + finalTempCpO2) / 2 / 32;

    const double initialTempCpN2 = (9.47 - 3.47 * 1000 / initialTemp + 1.07 * 1000000 / pow(initialTemp, 2));
    const double finalTempCpN2 = (9.47 - 3.47 * 1000 / finalTemp + 1.07 * 1000000 / pow(finalTemp, 2));
    const double initialTempCpSCFN2 = initialTempCpN2 / 378.2;
    const double finalTempCpSCFN2 = finalTempCpN2 / 378.2;
    const double avgCpN2 = (initialTempCpN2 + finalTempCpN2) / 2 / 28;

    const double initialTempCpH2O = (19.86 - 597 / pow(initialTemp, 0.5) + 7500 / initialTemp);
    const double finalTempCpH2O = (19.86 - 597 / pow(finalTemp, 0.5) + 7500 / finalTemp);
    const double initialTempCpSCFH2O = initialTempCpH2O / 378.2;
    const double finalTempCpSCFH2O = finalTempCpH2O / 378.2;
    const double avgCpH2O = (initialTempCpH2O + finalTempCpH2O) / 2 / 18;

    const double initialTempCpCO2 = (16.2 - 6.53 * 1000 / initialTemp + 1.41 * 1000000 / pow(initialTemp,2)) / 44;
    const double finalTempCpCO2 = (16.2 - 6.53 * 1000 / finalTemp + 1.41 * 1000000 / pow(finalTemp,2)) / 44;
    const double avgCpCO2 = (initialTempCpCO2 + finalTempCpCO2) / 2;

    const double stdO2PercVol = 20.7;
    const double stdN2PercVol = 78.3;
    const double stdH2OPercVol = 1;
    const double initialTempMeanCP = (stdO2PercVol * initialTempCpSCFO2 + stdN2PercVol * initialTempCpSCFN2 + stdH2OPercVol * initialTempCpSCFH2O) / 100;
    const double finalTempMeanCP = (stdO2PercVol * finalTempCpSCFO2 + stdN2PercVol * finalTempCpSCFN2 + stdH2OPercVol * finalTempCpSCFH2O) / 100;
    const double cpB = (finalTempMeanCP - initialTempMeanCP) / (flueGasTempF - ambientAirTempF);
    const double cpA = finalTempMeanCP - cpB / flueGasTempF;
    //End - calculate average Cp across temperature range of combustion air to flue gas

    double heatValueFuel = 0;
    double CO2GeneratedWt = 0;
    double H20GeneratedWt = 0;
    double O2GeneratedWt = 0;
    for ( auto const & compound : gasses ) {
        heatValueFuel += compound.second->compAdjByVol * compound.second->heatingValueVolume;
        CO2GeneratedWt += compound.second->compAdjByVol * compound.second->co2Generated;
        H20GeneratedWt += compound.second->compAdjByVol * compound.second->h2oGenerated;
        O2GeneratedWt += compound.second->compAdjByVol * compound.second->o2Generated;
    }

    const double CO2GeneratedVol = CO2GeneratedWt * 0.022722;
    const double H20GeneratedVol = H20GeneratedWt * 0.055506;

    CO2GeneratedWt *= 0.0026365;
    O2GeneratedWt /= 32;
    const double stoichAir = O2GeneratedWt * (1 + (1 - 0.209) / 0.209);
    const double combAirMoisture = combAirMoisturePerc == 0 ? 0 : ((combAirMoisturePerc - 0.009) * (stoichAir * (1 + exsAir)) * 0.0763);
    H20GeneratedWt *= 0.0026365;
    H20GeneratedWt += combAirMoisture;

    const double O2GeneratedVol = exsAir * O2GeneratedWt;
    const double N2GeneratedVol = (1 + exsAir) * O2GeneratedWt * (1 - 0.209) / 0.209;

    const double N2GeneratedWt = N2GeneratedVol * 0.0744;
    O2GeneratedWt = O2GeneratedVol * 0.0846;

    const double partialPressureH2O = H20GeneratedVol / (CO2GeneratedVol + H20GeneratedVol + O2GeneratedVol + N2GeneratedVol);

    const double H2OHeatContent = (getEnthalpyAtSaturation(partialPressureH2O) + avgCpH2O * (flueGasTempF - getSaturationTemperature(partialPressureH2O))) * 100 * H20GeneratedWt;
    const double CO2HeatContent = avgCpCO2 * (flueGasTempF - ambientAirTempF) * 100 * CO2GeneratedWt;
    const double N2HeatContent = avgCpN2 * (flueGasTempF - ambientAirTempF) * 100 * N2GeneratedWt;
    const double O2HeatContent = avgCpO2 * (flueGasTempF - ambientAirTempF) * 100 * O2GeneratedWt;

    //heat in preheated combustion air
    const double preHeatedAirEff = stoichAir * (1 + exsAir) * (((combAirTemperatureF + ambientAirTempF) / 2) * cpB + cpA) * (combAirTemperatureF - ambientAirTempF);
    //heat content of air moisture
    const double preHeatedAirMoistureEff = combAirMoisture * avgCpH2O * (flueGasTempF - combAirTemperatureF);

    const double totalGenerated = CO2GeneratedWt + H20GeneratedWt + O2GeneratedWt + N2GeneratedWt;

    const double specificHeat = (CO2GeneratedWt * avgCpCO2 + H20GeneratedWt * avgCpH2O + O2GeneratedWt * avgCpO2 + N2GeneratedWt * avgCpN2) / totalGenerated;
    const double sensibleHeat = 1 * specificHeat * (fuelTempF - ambientAirTempF);
    const double availableHeat = (100 * (sensibleHeat + heatValueFuel + preHeatedAirEff + preHeatedAirMoistureEff) - (H2OHeatContent + CO2HeatContent + N2HeatContent + O2HeatContent)) / (100 * heatValueFuel);

    return ProcessHeatPropertiesResults(stoichAir, exsAir, availableHeat, specificHeat, totalGenerated, heatValueFuel, flueO2);
}

void GasCompositions::flueGasO2AdjustForCalcError(const double excessAir, double &flueO2) const {
    if (flueO2 > 0){
        for (auto i = 0; i < 100; i++) {
            flueO2 = (double)((int)(flueO2 * 1000 + .5)) / 1000;
            double excessAirNew = getExcessAir(flueO2);
            if (fabs(1 - excessAirNew/excessAir) < 0.02) break;
            flueO2 *= excessAirNew > excessAir ? 0.99 : 1.01;
        }
    }
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

double GasCompositions::calculateStoichometricAir() {
    double o2Required = 0;
    for ( auto const & compound : gasses ) {
        o2Required  += compound.second->compAdjByVol * compound.second->o2Generated;
    }
    return o2Required * (1+ (1-0.209)/0.209);
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

    hH2Osat = getEnthalpyAtSaturation(ppH2O);
    tH2Osat = getSaturationTemperature(ppH2O);
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
    return compositions.getProcessHeatProperties(flueGasTemperature, excessAirPercentage/100, combustionAirTemperature, fuelTemperature, 60, 0).availableHeat;

    //This is old method use the improved method, called above
	/*compositions.calculateCompByWeight();
    const double heatInFlueGasses = compositions.calculateSensibleHeat(fuelTemperature);
    const double hCombustionAir = compositions.calculateHeatCombustionAir(combustionAirTemperature, excessAirPercentage);
    const double hValueFuel = compositions.calculateHeatingValueFuel();
    compositions.calculateMassFlueGasComponents(excessAirPercentage);
    compositions.calculateEnthalpy();
    const double totalHeatContentFlueGas = compositions.calculateTotalHeatContentFlueGas(flueGasTemperature);

    const double heatInput = heatInFlueGasses + hCombustionAir + hValueFuel;

    return (heatInput - totalHeatContentFlueGas) / hValueFuel;*/
}