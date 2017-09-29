/**
 * @file
 * @brief Calculator for gas exhaust losses in an Electric Arc Furnace (EAF)
 *
 * This contains the inputs for calculating the exhaust gas losses for an Electric Arc
 * Furnace (EAF)
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
#define AMO_TOOLS_SUITE_EXHAUSTGASEAF_H

class ExhaustGasEAF {
public:

	/**
	 * Constructor for the exhaust gas EAF heat loss with all inputs specified
	 *
	 * @param offGasTemp double, temperature of exhaust gases from EAF before the gases mix with outside air measured in °F
	 * @param CO double, % of CO in exhaust gas
	 * @param H2 double, % of H2 in exhaust gas
	 * @param combustibleGases double, average value of combustible gases % in exhaust gases
	 * @param vfr double, (volume flow rate) total volume of exhaust gases measured in cfm
	 * @param dustLoading double, dust loading for exhaust gases measured in s/scf (number of dust particles per scf)
	 * @return nothing
	 *
	 * */
	ExhaustGasEAF(double offGasTemp, double CO, double H2, double combustibleGases, double vfr, double dustLoading);

//	ExhaustGasEAF(const double offGasTemp, const double CO, const double H2,
//	                             const double combustibleGases, const double vfr, const double dustLoading)
//			: offGasTemp(offGasTemp), CO(CO), H2(H2), combustibleGases(combustibleGases),
//			  vfr(vfr), dustLoading(dustLoading)
//	{
//		calculateTotalHeatExhaust();
//	}

	double getTotalHeatExhaust() const { return totalHeatExhaust; }
	double getOffGasTemp() const { return offGasTemp; }
	double getCO() const { return CO; }
	double getH2() const { return H2; }
	double getCombustibleGases() const { return combustibleGases; }
	double getVfr() const { return vfr; }
	double getDustLoading() const { return dustLoading; }


//	void setOffGasTemp(double offGasTemp) {
//		this->offGasTemp = offGasTemp;
//		calculateTotalHeatExhaust();
//	}
//
//	void setCO(double CO) {
//		this->CO = CO;
//		calculateTotalHeatExhaust();
//	}
//
//	void setH2(double H2) {
//		this->H2 = H2;
//		calculateTotalHeatExhaust();
//	}
//
//	void setCombustibleGases(double combustibleGases) {
//		this->combustibleGases = combustibleGases;
//		calculateTotalHeatExhaust();
//	}
//
//	void setVfr(double vfr) {
//		this->vfr = vfr;
//		calculateTotalHeatExhaust();
//	}
//
//	void setDustLoading(double dustLoading) {
//		this->dustLoading = dustLoading;
//		calculateTotalHeatExhaust();
//	}

	void setOffGasTemp(double offGasTemp);
	void setCO(double CO);
	void setH2(double H2);
	void setCombustibleGases(double combustibleGases);
	void setVfr(double vfr);
	void setDustLoading(double dustLoading);

protected:
	double offGasTemp, CO, H2, combustibleGases, vfr, dustLoading;
	double totalHeatExhaust = 0;

	void calculateTotalHeatExhaust();

//	void calculateTotalHeatExhaust() {
//		const double COheatingValue = CO * 321 / 100;
//		const double H2heatingValue = H2 * 325 / 100;
//		const double combustibles = combustibleGases * 1020 / 100;
//		const double chemicalHeat = COheatingValue + H2heatingValue + combustibles;
//
//		const double sensibleHeat = 0.0225 * (offGasTemp - 60);
//		const double heatInDust = dustLoading * 0.25 * (offGasTemp - 60);
//		const double totalHeatFlue = chemicalHeat + sensibleHeat + heatInDust;
//		const double totalVfr = vfr * 520 / (460 + offGasTemp);
//		totalHeatExhaust = totalVfr * totalHeatFlue * 60;
//	}
};

#endif //AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
