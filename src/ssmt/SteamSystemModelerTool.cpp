#include <ssmt/SteamSystemModelerTool.h>
#include <array>
#include <cmath>

// where t is temperature and p is pressure
std::unordered_map<std::string, double> SteamSystemModelerTool::region1(const double t, const double p) {

	const std::array<double, 34> n = {
			0.14632971213167, -0.84548187169114, -0.37563603672040e1, 0.33855169168385e1, -0.95791963387872,
			0.15772038513228, -0.16616417199501e-1, 0.81214629983568e-3, 0.28319080123804e-3, -0.60706301565874e-3,
			-0.18990068218419e-1, -0.32529748770505e-1, -0.21841717175414e-1, -0.52838357969930e-4,
			-0.47184321073267e-3, -0.30001780793026e-3, 0.47661393906987e-4, -0.44141845330846e-5,
			-0.72694996297594e-15, -0.31679644845054e-4, -0.28270797985312e-5, -0.85205128120103e-9,
			-0.22425281908000e-5, -0.65171222895601e-6, -0.14341729937924e-12, -0.40516996860117e-6,
			-0.12734301741641e-8, -0.17424871230634e-9, -0.68762131295531e-18, 0.14478307828521e-19,
			0.26335781662795e-22, -0.11947622640071e-22, 0.18228094581404e-23, -0.93537087292458e-25
	};

	const std::array<int, 34> j = {
			-2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -1, 0, 1, 3, -3, 0, 1, 3, 17, -4, 0, 6, -5, -2, 10, -8, -11, -6, -29,
			-31, -38, -39, -40, -41
	};

	const std::array<int, 34> i = {
			0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 8, 8, 21, 23, 29, 30, 31, 32
	};

	auto const reducedPressure = p / 16.53;
	auto const inversedReducedTemp = 1386.0 / t;

	double gibbs = 0, gibbsPi = 0, gibbsPiPi = 0, gibbsT = 0, gibbsTT = 0, gibbsPit = 0;

	for ( auto k = 0; k < n.size(); k++ ) {
		gibbs += n[k] * pow((7.1 - reducedPressure), i[k]) * pow((inversedReducedTemp - 1.222), j[k]);
		gibbsPi += (-1 * n[k]) * i[k] * pow((7.1 - reducedPressure), i[k] - 1) * pow((inversedReducedTemp - 1.222), j[k]);
		gibbsT += n[k] * pow((7.1 - reducedPressure), i[k]) * j[k] * pow((inversedReducedTemp - 1.222), j[k] - 1);
	}

	auto const r = 0.461526;
	return {
			{"temperature", t}, //temperature in Kelvin
			{"pressure", p}, //pressure in MPa
//			{"phase", "Liquid"},
//			{"quality", t},
			{"specificVolume", reducedPressure * gibbsPi * t * r / p / 1000.0}, //volume in m³/kg
			{"density", 1 / (reducedPressure * gibbsPi * t * r / p / 1000.0)}, //density in kg/m³
			{"specificEnthalpy", inversedReducedTemp * gibbsT * t * r}, // enthalpy in kJ/kg
			{"specificEntropy", (inversedReducedTemp * gibbsT - gibbs) * r} // entropy in kJ/kg/K
	};
}

// where t is temperature and p is pressure
std::unordered_map<std::string, double> SteamSystemModelerTool::region2(const double t, const double p) {

	const std::array<double, 9> n0 = {
			-0.96927686500217E+01, 0.10086655968018E+02, -0.56087911283020E-02,
			0.71452738081455E-01, -0.40710498223928E+00,  0.14240819171444E+01,
			-0.43839511319450E+01, -0.28408632460772E+00, 0.21268463753307E-01
	};
	const std::array<double, 9> j0 = {
			0, 1, -5, -4, -3, -2, -1, 2, 3
	};
	const std::array<double, 43> n1 = {
			-0.17731742473213E-02, -0.17834862292358E-01, -0.45996013696365E-01, -0.57581259083432E-01,
			-0.50325278727930E-01, -0.33032641670203E-04, -0.18948987516315E-03, -0.39392777243355E-02,
			-0.43797295650573E-01, -0.26674547914087E-04, 0.20481737692309E-07,  0.43870667284435E-06,
			-0.32277677238570E-04, -0.15033924542148E-02, -0.40668253562649E-01, -0.78847309559367E-09,
			0.12790717852285E-07,  0.48225372718507E-06, 0.22922076337661E-05, -0.16714766451061E-10,
			-0.21171472321355E-02, -0.23895741934104E+02, -0.59059564324270E-17, -0.12621808899101E-05,
			-0.38946842435739E-01, 0.11256211360459E-10, -0.82311340897998E+01, 0.19809712802088E-07,
			0.10406965210174E-18, -0.10234747095929E-12, -0.10018179379511E-08, -0.80882908646985E-10,
			0.10693031879409E+00, -0.33662250574171E+00, 0.89185845355421E-24, 0.30629316876232E-12,
			-0.42002467698208E-05, -0.59056029685639E-25, 0.37826947613457E-05, -0.12768608934681E-14,
			0.73087610595061E-28, 0.55414715350778E-16, -0.94369707241210E-06
	};
	const std::array<double, 43> j1 = {
			0, 1, 2, 3, 6, 1, 2, 4, 7, 36, 0, 1, 3, 6, 35, 1, 2, 3, 7, 3, 16, 35, 0, 11,
			25, 8, 36, 13, 4, 10, 14, 29, 50, 57, 20, 35, 48, 21, 53, 39, 26, 40, 58
	};
	const std::array<double, 43> i1 = {
			1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6, 7, 7, 7,
			8, 8, 9, 10, 10, 10, 16, 16, 18, 20, 20, 20, 21, 22, 23, 24, 24, 24
	};

	auto const reducedPressure = p;
	auto const inverseReducedTemp = 540 / t;

	double gibbs0 = log(reducedPressure);
	double gibbsPi0 = 1 / reducedPressure;
	double gibbsPiPi0 = -1 / std::pow(reducedPressure, 2.0);
	double gibbsT0 = 0, gibbsTT0 = 0, gibbsPit0 = 0;

	for (int k = 0; k < 9; k++) {
		gibbs0 += n0[k] * std::pow(inverseReducedTemp, j0[k]);
		gibbsT0 += n0[k] * j0[k] * std::pow(inverseReducedTemp, j0[k] - 1);
		gibbsTT0 += n0[k] * j0[k] * (j0[k] - 1) * std::pow(inverseReducedTemp, j0[k] - 2);
	}

	double gibbs1 = 0, gibbsPi1 = 0, gibbsPiPi1 = 0, gibbsT1 = 0, gibbsTT1 = 0, gibbsPit1 = 0;

	for (int k = 0; k < 43; k++) {
		gibbs1 += n1[k] * std::pow(reducedPressure, i1[k]) * std::pow((inverseReducedTemp - 0.5), j1[k]);
		gibbsPi1 += n1[k] * i1[k] * std::pow(reducedPressure, i1[k] - 1) * std::pow((inverseReducedTemp - 0.5), j1[k]);
		gibbsT1 += n1[k] * std::pow(reducedPressure, i1[k]) * j1[k] * std::pow((inverseReducedTemp - 0.5), j1[k] - 1);
	}
	auto const r = 0.461526;
	return {
			{"temperature", t}, // temperature in Kelvin
			{"pressure", p}, //pressure in MPa
//			{"phase", "Gas"},
//			{"quality", NULL},
			{"specificVolume", reducedPressure * (gibbsPi0 + gibbsPi1) * t * r / p / 1000.0}, // volume in m³/kg
			{"density", 1 / (reducedPressure * (gibbsPi0 + gibbsPi1) * t * r / p / 1000.0)}, // density in kg/m³
			{"internalEnergy", (inverseReducedTemp * (gibbsT0 + gibbsT1) - reducedPressure
			                                                               * (gibbsPi0 + gibbsPi1) * t * r)}, // energy in MJ

			{"specificEnthalpy", inverseReducedTemp * (gibbsT0 + gibbsT1) * t * r}, // enthalpy in kJ/kg
			{"specificEntropy", ((inverseReducedTemp * (gibbsT0 + gibbsT1)) - (gibbs0 + gibbs1)) * r} // entropy in kJ/kg/K
	};
}

std::unordered_map<std::string, double> SteamSystemModelerTool::region3(const double t, const double p) {
	auto boundary13Properties = region1(t, p);
	auto densityA = boundary13Properties["density"];
	auto region3propNew = region3Density( densityA, t);
	auto testPressureA = region3propNew["pressure"];

    double temperature = 0.57254459862746E+03 + pow((p - 13.918839778870) / 0.0010192970039326, 0.5);

	auto boundary23Properties = region2(p, temperature);//boundaryByTemperatureRegion3to2Pressure(p));
	auto densityB = boundary23Properties["density"];
	region3propNew = region3Density(densityB, t);
	auto testPressureB = region3propNew["pressure"];

	double pressureNew;
	for ( size_t i = 0; i < 4; i++ ) {
		auto const densityNew = (densityA + densityB) / 2.0;
		auto region3propNew = region3Density(densityNew, t);
		pressureNew = region3propNew["pressure"];
//		if ( p > pressureNew ) {
//			densityB = densityNew;
//			testPressureB = pressureNew;
//		} else {
//			densityA = densityNew;
//			testPressureA = pressureNew;
//		}
	}

//	// Uses Linear Interpolation
//	size_t counter = 0;
//	while (std::abs(pressureNew - p) > 1e-10 and counter++ < 50 and testPressureA != testPressureB) {
//		auto densityNew = p * (densityA - densityB) / (testPressureA - testPressureB) + densityA - testPressureA * (densityA - densityB) / (testPressureA - testPressureB);
//		region3propNew = region3Density(densityNew, t);
//		pressureNew = region3propNew["pressure"];
//		densityB = densityA;
//		densityA = densityNew;
//		testPressureB = testPressureA;
//		testPressureA = pressureNew;
//	}
	//return region3propNew;
    region3propNew["specificEntropy"] = temperature;
    return region3propNew;



//    auto boundary13Properties = region1(t, p);
//    auto densityA = boundary13Properties["density"];
//    auto region3propNew = region3Density( densityA, t);
//
//    return boundary13Properties;


//    double boundary3to2 = (0.34805185628969E+03 - 0.11671859879975E+01 * 0.10192970039326E-02 * std::pow(t, 2));
//    //auto boundary23Properties = region2(p, boundaryByTemperatureRegion3to2Pressure(p));
//    auto boundary23Properties = region2(p, boundary3to2);
//	auto densityB = boundary23Properties["density"];
//   // boundary23Properties["specificVolume"] = 0.34805185628969E+03 - 0.11671859879975E+01 * 0.10192970039326E-02 * std::pow(t, 2);
//    auto region3propNew = region3Density(densityB, t);
//
//    return boundary23Properties;
}

std::unordered_map<std::string, double> SteamSystemModelerTool::region3Density(const double d, const double t) {

    const std::array<double, 40> n = {
			0.10658070028513E+01, -0.15732845290239E+02, 0.20944396974307E+02, -0.76867707878716E+01,
			0.26185947787954E+01, -0.28080781148620E+01, 0.12053369696517E+01, -0.84566812812502E-02,
			-0.12654315477714E+01, -0.11524407806681E+01, 0.88521043984318E+00, -0.64207765181607E+00,
			0.38493460186671E+00, -0.85214708824206E+00, 0.48972281541877E+01, -0.30502617256965E+01,
			0.39420536879154E-01, 0.12558408424308E+00, -0.27999329698710E+00, 0.13899799569460E+01,
			-0.20189915023570E+01, -0.82147637173963E-02, -0.47596035734923E+00, 0.43984074473500E-01,
			-0.44476435428739E+00, 0.90572070719733E+00, 0.70522450087967E+00, 0.10770512626332E+00,
			-0.32913623258954E+00, -0.50871062041158E+00, -0.22175400873096E-01, 0.94260751665092E-01,
			0.16436278447961E+00, -0.13503372241348E-01, -0.14834345352472E-01, 0.57922953628084E-03,
			0.32308904703711E-02, 0.80964802996215E-04, -0.16557679795037E-03, -0.44923899061815E-04
	};
	const std::array<int, 40> j = {
			0, 0, 1, 2, 7, 10, 12, 23, 2, 6, 15, 17, 0, 2, 6, 7, 22, 26, 0, 2,
			4, 16, 26, 0, 2, 4, 26, 1, 3, 26, 0, 2, 26, 2, 26, 2, 26, 0, 1, 2
	};
	const std::array<int, 40> i = {
			0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3,
			3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 8, 9, 9, 10, 10, 1
	};

	auto const reducedDensity = d / 322.0;
	auto const inverseReducedTemp = 647.096 / t;
	auto helmholtz = n[0] * std::log(reducedDensity);
	auto helmholtzS = n[0] / reducedDensity;
	auto helmholtzSS = n[0] / std::pow(reducedDensity, 2);
	double helmholtzT = 0, helmholtzTT = 0, helmholtzST = 0;

	for (size_t k = 1; k < 40; k++) {
		helmholtz += n[k] * std::pow(reducedDensity, i[k]) * std::pow(inverseReducedTemp, j[k]);
		helmholtzS += n[k] * i[k] * std::pow(reducedDensity, i[k] - 1.0) * std::pow(inverseReducedTemp, j[k]);
		helmholtzT += n[k] * std::pow(reducedDensity, i[k]) * j[k] * std::pow(inverseReducedTemp, j[k] - 1);
	}

	auto const r = 0.461526;
	return {
			{"temperature", t}, // temperature in Kelvin
			{"pressure", reducedDensity * helmholtzS * d * t * r / 1000.0},
			{"density", d },
			{"specificVolume", 1 / d},
			{"internalEnergy", (inverseReducedTemp * helmholtzT * t * r) / 1055.056},
			{"specificEnthalpy", (inverseReducedTemp * helmholtzT + reducedDensity * helmholtzS) * t * r},
			{"specificEntropy", (inverseReducedTemp * helmholtzT - helmholtz) * r}
	};
}


double SteamSystemModelerTool::region4(const double t) {
	auto const v = t + -0.23855557567849E+00 / (t - 0.65017534844798E+03);
	auto const a = v * v + 0.11670521452767E+04 * v + -0.72421316703206E+06;
	auto const b = -0.17073846940092E+02 * v * v + 0.12020824702470E+05 * v + -0.32325550322333E+07;
	auto const c = 0.14915108613530E+02 * v * v + -0.48232657361591E+04 * v + 0.40511340542057E+06;

	return pow(2 * c / (-b + sqrt(pow(b, 2) - 4 * a * c)), 4);
}

// where t is temperature and p is pressure
int SteamSystemModelerTool::regionSelect(const double p, const double t) {
	const double boundaryPressure = (t >= TEMPERATURE_Tp) ? boundaryByTemperatureRegion3to2Temperature(t) : region4(t);

	if (t >= TEMPERATURE_MIN and t <= TEMPERATURE_Tp) {
		if (p <= PRESSURE_MAX and p >= boundaryPressure) return 1;
		if (p > 0 and p <= boundaryPressure) return 2;
	}

	if (t >= TEMPERATURE_Tp and t <= TEMPERATURE_REGION3_MAX) {
		if (p > 0 and p <= boundaryPressure) return 2;
		if (p <= PRESSURE_MAX and p > boundaryPressure) return 3;
	}

//	if (t > TEMPERATURE_REGION3_MAX and t <= TEMPERATURE_MAX) // last if statement in the php code
	return 2;
}
