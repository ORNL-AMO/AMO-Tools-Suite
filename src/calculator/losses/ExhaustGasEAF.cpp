#include <calculator/losses/ExhaustGasEAF.h>

ExhaustGasEAF::ExhaustGasEAF(const double offGasTemp, const double CO, const double H2,
                             const double combustibleGases, const double vfr, const double dustLoading)
		: offGasTemp(offGasTemp), CO(CO), H2(H2), combustibleGases(combustibleGases),
		  vfr(vfr), dustLoading(dustLoading)
{
	calculateTotalHeatExhaust();
}

void ExhaustGasEAF::calculateTotalHeatExhaust() {
	const double COheatingValue = CO * 321 / 100;
	const double H2heatingValue = H2 * 325 / 100;
	const double combustibles = combustibleGases * 1020 / 100;
	const double chemicalHeat = COheatingValue + H2heatingValue + combustibles;

	const double sensibleHeat = 0.0225 * (offGasTemp - 60);
	const double heatInDust = dustLoading * 0.25 * (offGasTemp - 60);
	const double totalHeatFlue = chemicalHeat + sensibleHeat + heatInDust;
	const double totalVfr = vfr * 520 / (460 + offGasTemp);
	totalHeatExhaust = totalVfr * totalHeatFlue * 60;
}

void ExhaustGasEAF::setOffGasTemp(double offGasTemp) {
	this->offGasTemp = offGasTemp;
	calculateTotalHeatExhaust();
}

void ExhaustGasEAF::setCO(double CO) {
	this->CO = CO;
	calculateTotalHeatExhaust();
}

void ExhaustGasEAF::setH2(double H2) {
	this->H2 = H2;
	calculateTotalHeatExhaust();
}

void ExhaustGasEAF::setCombustibleGases(double combustibleGases) {
	this->combustibleGases = combustibleGases;
	calculateTotalHeatExhaust();
}

void ExhaustGasEAF::setVfr(double vfr) {
	this->vfr = vfr;
	calculateTotalHeatExhaust();
}

void ExhaustGasEAF::setDustLoading(double dustLoading) {
	this->dustLoading = dustLoading;
	calculateTotalHeatExhaust();
}
