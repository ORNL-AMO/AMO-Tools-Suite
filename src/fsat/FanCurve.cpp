#include <fsat/FanCurve.h>
#include <cmath>

//CurveConditions::CurveConditions(double density, double rpm, double barometricPressure, double isentropicExponent)
//		: density(density), rpm(rpm), barometricPressure(barometricPressure), isentropicExponent(isentropicExponent)
//{
//
//}

void FanCurve::calculate(double q, double p, double h, double density, double n, double densityC, double nC, double pb,
               double pbC, double pt1F, double gamma, double gammaC, double a1, double a2, FanCurveType curveType)
{
	double kp = 1, kpC = 1;
	auto estPt, estPtc;
	for (auto i = 0; i < 7; i++ ) {
		auto saveKpOverKpc = kp / kpC;
		auto const qC = q * (nC / n) * (kp / kpC); // eq 17

		auto const v1 = q / a1; // eq 32, TODO q == Q1? see page 58
		auto const pv1 = density * std::pow(v1 / 1096, 2); // eq 33
		auto const v2 = q / a2;
		auto const pv2 = density * std::pow(v2 / 1096, 2);
		// if a1, a2 blank doesn't apply here, but for now the logic will be if they are negative
		if (a1 < 0 || a2 < 0) {
			estPt = p; // TODO needs further analysis, this is likely wrong.
		} else {
			switch (curveType) {
				case FanCurveType::FanStaticPressure: {
					estPt = p + pv2;
					break;
				}
				case FanCurveType::StaticPressureRise: {
					estPt = p + pv2 - pv1;
					break;
				}
				case FanCurveType::FanTotalPressure: {
					estPt = p;
					break;
				}
			}
		}

		// eq 18, 19 and 20 depend on the type of FanCurve, here pressure (p) represents the pressure type?
		auto const pBoxC = p * std::pow(nC / n, 2) * (densityC / density) * (kp / kpC);
		estPtc = estPt * std::pow(nC / n, 2) * (densityC / density) * (kp / kpC);
		auto const hC = h * std::pow(nC / n, 3) * (densityC / density) * (kp / kpC);
		auto const pt1 = pt1F * estPt; // see page 54 section 4.1.13
		auto const x = estPt / (pt1 + 13.63 * pb); // eq 25 see pg 54
		auto const z = ((gamma - 1) / gamma) * (6362 * h / q) / (pt1 + 13.63 * pb); // TODO might be wrong see page 55
		kp = (std::log(1 + x) / x) * (z / (std::log(1 + z))); // eq 27
		auto const pt1c = pt1F * estPtc; // eq 28
		auto const xc = estPtc / (pt1c + 13.63 * pbC); // eq 29
		auto const zc = ((gammaC - 1) / gammaC) * (6362 * hC / qC) / (pt1c + 13.63 * pbC); // eq 30, TODO number is off significantly, but why?
		kpC = (std::log(1 + xc) / xc) * (zc / (std::log(1 + zc))); // eq 31
		auto const efficiency = (q * p * kp) / (6362 * h);

		// TODO is LHS supposed to be estPtc or ptc? see page 61 eq 38
		if (std::abs(saveKpOverKpc - kp / kpC) < 0.00001) {
			break;
		}
	}
}

