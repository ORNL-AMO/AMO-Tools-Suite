#ifndef AMO_TOOLS_SUITE_OPTIMALFANEFFICIENCY_H
#define AMO_TOOLS_SUITE_OPTIMALFANEFFICIENCY_H

#include <functional>
#include <cfloat>
#include <array>

class OptimalFanEfficiency {
public:
	enum class FanType {
		AirfoilSISW,
		BackwardCurvedSISW,
		RadialSISW,
		RadialTipSISW,
		BackwardInclinedSISW,
		AirfoilDIDW,
		BackwardCurvedDIDW,
		BackwardInclinedDIDW,
		VaneAxial,
		AirHandling,
		MaterialHandling,
		LongShavings,
		LongShavingsOpen
	};

	OptimalFanEfficiency(FanType const fanType, const double fanSpeed, const double flowRate, const double inletPressure,
	                     const double outletPressure, const double compressibility)
			: fanType(fanType), fanSpeed(fanSpeed), flowRate(flowRate), outletPressure(outletPressure),
			  inletPressure(inletPressure), compressibility(compressibility)
	{};

	double calculate() {
		FanTypeProperties const & currentFan = fanTypeProperties[static_cast<std::size_t>(fanType)];
		double specificSpeed = (fanSpeed * std::sqrt(flowRate)) / (std::pow(outletPressure - inletPressure, 0.75)
		                                                           * std::pow(compressibility, 0.25));

		if (specificSpeed < currentFan.minSpecificSpeed) {
			specificSpeed = currentFan.minSpecificSpeed;
		} else if (specificSpeed > currentFan.maxSpecificSpeed) {
			specificSpeed = currentFan.maxSpecificSpeed;
		}

		bool isPolynomial = specificSpeed < currentFan.transition;
		if (isPolynomial) {
			return currentFan.polynomialFunction(specificSpeed);
		}
		return currentFan.exponentialFunction(specificSpeed);
	}

private:
	FanType const fanType;
	const double fanSpeed, flowRate, outletPressure, inletPressure, compressibility;


	struct FanTypeProperties {
	private:
		FanTypeProperties(const FanType fanType, const double transition, const double minSpecificSpeed, const double maxSpecificSpeed,
		                  std::function<double (double n)> polynomialFunction,
		                  std::function<double (double n)> exponentialFunction = [](double n) { return 0; })
				: fanType(fanType), transition(transition), minSpecificSpeed(minSpecificSpeed), maxSpecificSpeed(maxSpecificSpeed),
				  polynomialFunction(std::move(polynomialFunction)), exponentialFunction(std::move(exponentialFunction))
		{}

		const FanType fanType; // just for bookkeeping purposes, unused otherwise
		const double transition, minSpecificSpeed, maxSpecificSpeed;
		const std::function<double (double n)> polynomialFunction;
		const std::function<double (double n)> exponentialFunction;
		friend class OptimalFanEfficiency;
	};

	const FanTypeProperties fanTypeProperties[13] = {
			{
					FanType::AirfoilSISW, 40500, 25000, 1200100,
					[](double n) { return -8.0126838E+01 + 1.4126667E-02 * n + -1.0177155E-06 * std::pow(n, 2) + 3.8587782E-11 * std::pow(n, 3) + -8.1056442E-16 * std::pow(n, 4) + 8.9381481E-21 * std::pow(n, 5) + -4.0433292E-26 * std::pow(n, 6); },
					[](double n) { return 0.0028841 + 0.27192 * std::exp(-2.2547E-06 * n) + 0.86849 * std::exp(-0.00001064 * n); }
			},
			{
					FanType::BackwardCurvedSISW, 102000, 27900, 102000,
					[](double n) { return -3.3858306E+00 + 4.1209144E-04 * n + -1.6548201E-08 * std::pow(n, 2) + 3.5761249E-13 * std::pow(n, 3) + -4.5693281E-18 * std::pow(n, 4) + 3.4555013E-23 * std::pow(n, 5) + -1.4316102E-28 * std::pow(n, 6) + 2.5065191E-34 * std::pow(n, 7); },
			},
			{
					FanType::RadialSISW, 37900, 27900, 135800,
					[](double n) { return -1.9069988E+00 + 7.3713948E-04 * n + -1.0257832E-07 * std::pow(n, 2) + 8.3624959E-12 * std::pow(n, 3) + -4.1052861E-16 * std::pow(n, 4) + 1.1767564E-20 * std::pow(n, 5) + -1.8050575E-25 * std::pow(n, 6) + 1.1417504E-30 * std::pow(n, 7); },
					[](double n) { return 0.056999916 + 0.67916774 * std::exp(-2.18789E-05 * n) + 5.1126555 * std::exp(-0.000132336 * n); },
			},
			{
					FanType::RadialTipSISW, 64000, 19400, 213400,
					[](double n) { return 5.2461E-01 + 1.1922E-05 * n + 3.1851E-11 * std::pow(n, 2) + -7.0532E-15 * std::pow(n, 3) + 4.8891E-20 * std::pow(n, 4) + 1.5505E-25 * std::pow(n, 5); },
					[](double n) { return 0.053287 + 0.47705 * std::exp(-7.7713E-06 * n) + 0.93414 * std::exp(-0.000023195 * n); },
			},
			{
					FanType::BackwardInclinedSISW, 150100, 32100, 150100,
					[](double n) { return 0; },
//					Backward Inclined (SISW),-3.8748275E+00,5.7599797E-04,-3.4547599E-08,1.3031136E-12,-3.2700894E-17,5.4984885E-22,-6.1792981E-27,4.5680803E-32,-2.1294090E-37,5.6703436E-43,-6.5731157E-49
			},
			{
					FanType::AirfoilDIDW, 0, 0, 0,
					[](double n) { return 0; },
//					Airfoil (DIDW),-7.7454E+00,5.3186E-04,-1.1335E-08,7.1361E-14,6.9345E-19,-1.1607E-23,4.3954E-29
					[](double n) { return 0; },
//					Airfoil (DIDW),0.019737,0.37398,0.000002682,0.8666,0.000010656
			},
			{
					FanType::BackwardCurvedDIDW, 0, 0, 0,
					[](double n) { return 0; },
//					Backward Curved (DIDW),-8.6410E+00,8.1273E-04,-2.9882E-08,6.1531E-13,-7.7968E-18,6.2161E-23,-3.0415E-28,8.3466E-34,-9.8355E-40
					[](double n) { return 0; },
//					Backward Curved (DIDW),0.11242,1.5789,9.2707E-06,-0.55707,9.9734E-06
			},
			{
					FanType::BackwardInclinedDIDW, 0, 0, 0,
					[](double n) { return 0; },
//					Backward Inclined (DIDW),-2.5449389E+02,2.7852726E-02,-1.3284246E-06,3.6371269E-11,-6.3036202E-16,7.1757531E-21,-5.3686875E-26,2.5473585E-31,-6.9602675E-37,8.3493931E-43
					[](double n) { return 0; },
//					Backward Inclined (DIDW),0.036754527,0.50694842,4.70913E-06,1.0416177,1.79781E-05
			},
			{
					FanType::VaneAxial, 0, 0, 0,
					[](double n) { return 0; },
//					Vane Axial,-5.4813500E+00,5.0387520E-04,-1.8304300E-08,3.7439830E-13,-4.6531220E-18,3.5829160E-23,-1.6699090E-28,4.3158650E-34,-4.7471640E-40
					[](double n) { return 0; },
//					Vane Axial,0.1704079,1.968828,7.24616E-06,-1.782739,1.32444E-05
			},
			{
					FanType::AirHandling, 0, 0, 0,
					[](double n) { return 0; },
//					Air handling,1.9237E-01,8.0744E-05,-4.3274E-09,9.5885E-14,-1.0050E-18,4.0941E-24
			},
			{
					FanType::MaterialHandling, 0, 0, 0,
					[](double n) { return 0; },
//					Material handling,-1.4085021E+02,6.9753242E-02,-1.4963605E-05,1.8305766E-09,-1.4075805E-13,7.0623637E-18,-2.3154680E-22,4.7905555E-27,-5.6833385E-32,2.9495463E-37
					[](double n) { return 0; },
//					Material handling,0.046254578,0.44481692,2.74877E-05,0.61800978,2.56071E-05
			},
			{
					FanType::LongShavings, 0, 0, 0,
					[](double n) { return 0; },
//					Long shavings,-4.9068901E+00,1.1742587E-03,-9.8831999E-08,4.2747034E-12,-1.0139920E-16,1.2507408E-21,-6.2553192E-27
					[](double n) { return 0; },
//					Long shavings,0.026213128,0.31783591,1.22334E-05,0.90262955,4.33422E-05
			},
			{
					FanType::LongShavingsOpen, 0, 0, 0,
					[](double n) { return 0; },
//					Long shavings - open,-4.9068901E+00,1.1742587E-03,-9.8831999E-08,4.2747034E-12,-1.0139920E-16,1.2507408E-21,-6.2553192E-27
					[](double n) { return 0; },
//					Long shavings - open,0.026213128,0.31783591,1.22334E-05,0.90262955,4.33422E-05
			}
	};

	// The numbers at which each fan type transitions to using exponential or polynomial functions
	// The DBL_Max values mean there exists no exponential function for that fan type
//	const double transitionNumbers[13] = {
//			40500, DBL_MAX, 37900, 64000, DBL_MAX, 78000, 148900, 132600, 179670, DBL_MAX, 27000, 38500, 38500
//	};

	// array of the min and max values allowed for specific feed for each fan type
//	const std::pair<unsigned, unsigned> minsAndMaxes[13] = {
//			{25000, 1200100},
//			{102000, 27900},
//			{14000, 135800},
//			{19400, 213400},
//			{32100, 150100},
//			{39000, 1800000},
//			{38000, 270800},
//			{46000, 622500},
//			{60375, 348620},
//			{15100, 67600},
//			{10100, 65600},
//			{12400, 180500},
//			{12400, 180500},
//	};

	// array of polynomial functions
//	const std::function<double (double n)> polynomials[13] = {
//			[](double n) { return -8.01E+01 + 1.41E-02 * n + -1.02E-06 * std::pow(n, 2) + 3.86E-11 * std::pow(n, 3)	+ -8.11E-16 * std::pow(n, 4) + 8.94E-21 * std::pow(n, 5) + -4.04E-26 * std::pow(n, 6); },
//			[](double n) { return -3.3858306E+00 + 4.1209144E-04 * n + -1.6548201E-08 * std::pow(n, 2) + 3.5761249E-13 * std::pow(n, 3) + -4.5693281E-18 * std::pow(n, 4) + 3.4555013E-23 * std::pow(n, 5) + -1.4316102E-28 * std::pow(n, 6) + 2.5065191E-34 * std::pow(n, 7); },
//			[](double n) { return -3.3858306E+00 + 4.1209144E-04 * n + -1.6548201E-08 * std::pow(n, 2) + 3.5761249E-13 * std::pow(n, 3) + -4.5693281E-18 * std::pow(n, 4) + 3.4555013E-23 * std::pow(n, 5) + -1.4316102E-28 * std::pow(n, 6) + 2.5065191E-34 * std::pow(n, 7); },
//			[](double n) { return -1.9069988E+00 + 7.3713948E-04 * n + -1.0257832E-07 * std::pow(n, 2) + 8.3624959E-12 * std::pow(n, 3) + -4.1052861E-16 * std::pow(n, 4) + 1.1767564E-20 * std::pow(n, 5) + -1.8050575E-25 * std::pow(n, 6) + 1.1417504E-30 * std::pow(n, 7); },
//	};

	// array of exponential functions, for each "return 0" definition, there is no existing exponential function, it will always be polynomial
//	const std::function<double (double n)> exponentials[13] = {
//			[](double n) { return 0.0028841 + 0.27192 * std::exp(-2.2547E-06 * n) + 0.86849 * std::exp(-0.00001064 * n); },
//			[](double n) { return 0; },
//			[](double n) { return 0.056999916 + 0.67916774 * std::exp(-2.18789E-05 * n) + 5.1126555 * (-0.000132336 * n); },
//			[](double n) { return 0.053287 + 0.47705 * std::exp(-7.7713E-06 * n) + 0.93414 * std::exp(-0.000023195 * n); },
//	};


};

#endif //AMO_TOOLS_SUITE_OPTIMALFANEFFICIENCY_H
