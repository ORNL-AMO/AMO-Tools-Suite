#include "calculator/losses/SolidLiquidFlueGasMaterial.h"
#include <cmath>

double SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2(
		const double flueGasO2, const double carbon, const double hydrogen, const double sulphur, const double inertAsh,
		const double o2, const double moisture, const double nitrogen, const double moistureInAirCombustion) {

	// adjust input by weight - step 1
	const double percentTotalFuelComponents = carbon + hydrogen + sulphur + inertAsh + o2 + moisture + nitrogen;
	const double carbonBar = carbon / percentTotalFuelComponents;
	const double hydrogenBar = hydrogen / percentTotalFuelComponents;
	const double sulphurBar = sulphur / percentTotalFuelComponents;
	const double o2Bar = o2 / percentTotalFuelComponents;
	const double moistureBar = moisture / percentTotalFuelComponents;

	double excessAir = (8.52381 * flueGasO2) / (2 - (9.52381 * flueGasO2));
	if (excessAir == 0) return 0;

	// loop a max of 100 times, this loop doesn't take more than roughly 10 iterations right now
	for (auto i = 0; i < 100; i++) {
		// steps 2 and 3
		const double o2sair = carbonBar * (32.0 / 12) + hydrogenBar * 8 + sulphurBar - o2Bar;
		const double n2sair = o2sair * (76.85 / 23.15);
		const double msair = o2sair + n2sair;
		const double mCombustionAir = msair * (1 + excessAir);

		// steps 4 and 5
		const double mCO2 = carbonBar * (44.0 / 12);
		const double mH2O = hydrogenBar * 9 + moistureBar + (moistureInAirCombustion / 100.0) * mCombustionAir;
		const double mSO2 = sulphurBar * 2;
		const double mO2 = o2sair * excessAir;
		const double mN2 = n2sair * (1 + excessAir);

		auto const O2i = mO2 / (mH2O + mCO2 + mN2 + mO2 + mSO2);
		auto const error = fabs((flueGasO2 - O2i) / flueGasO2);
		if (error < 0.02) break;
		if (O2i > flueGasO2) {
			excessAir -= (excessAir * 0.01);
		} else {
			excessAir += (excessAir * 0.01);
		}
	}

	return excessAir;
}

double SolidLiquidFlueGasMaterial::calculateFlueGasO2(const double excessAir, const double carbon,
                                                      const double hydrogen, const double sulphur,
                                                      const double inertAsh, const double o2, const double moisture,
                                                      const double nitrogen, const double moistureInAirCombustion)
{
	const double percentTotalFuelComponents = carbon + hydrogen + sulphur + inertAsh + o2 + moisture + nitrogen;
	const double carbonBar = carbon / percentTotalFuelComponents;
	const double hydrogenBar = hydrogen / percentTotalFuelComponents;
	const double sulphurBar = sulphur / percentTotalFuelComponents;
	const double o2Bar = o2 / percentTotalFuelComponents;
	const double moistureBar = moisture / percentTotalFuelComponents;

	// steps 2 and 3
	const double o2sair = carbonBar * (32.0 / 12) + hydrogenBar * 8 + sulphurBar - o2Bar;
	const double n2sair = o2sair * (76.85 / 23.15);
	const double msair = o2sair + n2sair;
	const double mCombustionAir = msair * (1 + excessAir);

	// steps 4 and 5
	const double mCO2 = carbonBar * (44.0 / 12);
	const double mH2O = hydrogenBar * 9 + moistureBar + (moistureInAirCombustion / 100.0) * mCombustionAir;
	const double mSO2 = sulphurBar * 2;
	const double mO2 = o2sair * excessAir;
	const double mN2 = n2sair * (1 + excessAir);

	return mO2 / (mH2O + mCO2 + mN2 + mO2 + mSO2);
}


double SolidLiquidFlueGasMaterial::calculateHeatingValueFuel(double carbon, double hydrogen, double sulphur,
                                                             double inertAsh, double o2, double moisture,
                                                             double nitrogen)
{
	const double percentTotalFuelComponents = carbon + hydrogen + sulphur + inertAsh + o2 + moisture + nitrogen;
	const double carbonBar = carbon / percentTotalFuelComponents;
	const double hydrogenBar = hydrogen / percentTotalFuelComponents;
	const double sulphurBar = sulphur / percentTotalFuelComponents;
	return carbonBar * 14100 + hydrogenBar * 61100 + sulphurBar * 3980;
}

double SolidLiquidFlueGasMaterial::getHeatLoss() {
	// adjust input by weight - step 1
	const double percentTotalFuelComponents = carbon + hydrogen + sulphur + inertAsh + o2 + moisture + nitrogen;
	const double carbonBar = carbon / percentTotalFuelComponents;
	const double hydrogenBar = hydrogen / percentTotalFuelComponents;
	const double sulphurBar = sulphur / percentTotalFuelComponents;
	const double o2Bar = o2 / percentTotalFuelComponents;
	const double moistureBar = moisture / percentTotalFuelComponents;

	// steps 2 and 3
	const double hFuel = 0.24 * (1 - moistureBar) * (fuelTemperature - 60);
	const double cpCombustionAir = 0.01788166862315 + 0.0000016704748 * combustionAirTemperature;
	const double o2sair = carbonBar * (32.0 / 12) + hydrogenBar * 8 + sulphurBar - o2Bar;
	const double n2sair = o2sair * (76.85 / 23.15);
	const double msair = o2sair + n2sair;
	const double mCombustionAir = msair * (1 + excessAir);
	const double hCombustionAir = mCombustionAir * cpCombustionAir * (combustionAirTemperature - 60) / 0.075;

	// steps 4 and 5
	const double heatingValueFuel = carbonBar * 14100 + hydrogenBar * 61100 + sulphurBar * 3980;
	const double mCO2 = carbonBar * (44.0 / 12);
	const double mH2O = hydrogenBar * 9 + moistureBar + (moistureInAirCombustion / 100.0) * mCombustionAir;
	const double mSO2 = sulphurBar * 2;
	const double mO2 = o2sair * excessAir;
	const double mN2 = n2sair * (1 + excessAir);

	const double pH2O = (mH2O / 0.047636) /
			(mCO2 / 0.116367 + mH2O / 0.047636 + mN2 / 0.074077 + mO2 / 0.084611 + mSO2 / 0.169381);
	const double hSat = 1096.7 * pow(pH2O * 29.926, 0.013);

	// step 6
	auto const cpCO2 = [] (double t) { return 16.2 - 6.53 * 1000 / t + 1.41 * 1000000 / (t * t); };
	auto const cpH2O = [] (double t) { return 19.86 - 597 / pow(t, 0.5) + 7500 / t; };
	auto const cpO2 = [] (double t) { return 11.515 - 172 / pow(t, 0.5) + 1530 / t; };
	auto const cpN2 = [] (double t) { return 9.47 - 3.47 * 1000 / t + 1.07 * 1000000 / (t * t); };

	const double hCO2 = carbonBar * (44.0 / 12) * (cpCO2(flueGasTemperature + 460) / 44.01) * (flueGasTemperature - 60);
	const double hH2O = (hydrogenBar * 9 + moistureBar)
	                    * (hSat + ((cpH2O(flueGasTemperature + 460) / 18.016) * (flueGasTemperature - 60)))
	                    + ((moistureInAirCombustion / 100.0) * mCombustionAir)
	                      * ((cpH2O(flueGasTemperature + 460) / 18.016) * (flueGasTemperature - 60));
	const double hSO2 = (sulphurBar * 2) * (17.472 / 64.06) * (flueGasTemperature - 60);
	const double hO2 = mO2 * (cpO2(flueGasTemperature + 460) / 32) * (flueGasTemperature - 60);
	const double hN2 = mN2 * (cpN2(flueGasTemperature + 460) / 28.016) * (flueGasTemperature - 60);
	const double hFG = hH2O + hCO2 + hN2 + hO2 + hSO2;

	// steps 7, 8 and 9
	const double hMoisture = moisture * (flueGasTemperature - 60);
	const double hCarbon = 14093 * unburnedCarbonInAsh * (inertAsh / percentTotalFuelComponents);
	const double hAsh = (inertAsh / percentTotalFuelComponents) * 0.25 * (1.8 * ashDischargeTemperature + 32 - 60);
	const double hIn = hFuel + hCombustionAir + heatingValueFuel + hMoisture;

	const double availableHeatPercent = (hIn - hFG - hAsh - hCarbon) / heatingValueFuel;
	return availableHeatPercent;
}