#include <ssmt/SteamSystemModelerTool.h>

double SteamSystemModelerTool::region4(const double t) {
	auto const v = t + -0.23855557567849E+00 / (t - 0.65017534844798E+03);
	auto const a = v * v + 0.11670521452767E+04 * v + -0.72421316703206E+06;
	auto const b = -0.17073846940092E+02 * v * v + 0.12020824702470E+05 * v + -0.32325550322333E+07;
	auto const c = 0.14915108613530E+02 * v * v + -0.48232657361591E+04 * v + 0.40511340542057E+06;

	return pow(2 * c / (-b + sqrt(pow(b, 2) - 4 * a * c)), 4);
//	function region4($temperature){
//		$constant_n[1]=0.11670521452767E+04
//		$constant_n[2]=-0.72421316703206E+06
//		$constant_n[3]=-0.17073846940092E+02
//		$constant_n[4]=0.12020824702470E+05
//		$constant_n[5]=-0.32325550322333E+07
//		$constant_n[6]=0.14915108613530E+02
//		$constant_n[7]=-0.48232657361591E+04
//		$constant_n[8]=0.40511340542057E+06
//		$constant_n[9]=-0.23855557567849E+00
//		$constant_n[10]=0.65017534844798E+03
//
//		$equ_v=$temperature+$constant_n[9]/($temperature-$constant_n[10]);
//
//		$equ_A=$equ_v*$equ_v+$constant_n[1]*$equ_v+$constant_n[2];
//		$equ_B=$constant_n[3]*$equ_v*$equ_v+$constant_n[4]*$equ_v+$constant_n[5];
//		$equ_C=$constant_n[6]*$equ_v*$equ_v+$constant_n[7]*$equ_v+$constant_n[8];
//
//		$pressure=pow(2*$equ_C/(-$equ_B+sqrt(pow($equ_B,2)-4*$equ_A*$equ_C)),4);
//
//		return $pressure;
//	}
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


//	function regionSelect($pressure, $temperature){
//		$region=0;
//		//Determine Boundary
//		if ($temperature>=self::TEMPERATURE_Tp){
//			$boundaryPressure = $this->boundaryByTemperatureRegion3to2($temperature);
//		}else{
//			$boundaryPressure = $this->saturatedPressure($temperature);
//		}
//
//		if ($temperature>=self::TEMPERATURE_MIN and $temperature<=self::TEMPERATURE_Tp){
//			if ($pressure<=self::PRESSURE_MAX and $pressure>=$boundaryPressure){
//				$region=1; //Liquid
//			}
//			if ($pressure>0 and $pressure<=$boundaryPressure){
//				$region=2; //Gas
//			}
//		}
//		if ($temperature>=self::TEMPERATURE_Tp and $temperature<=self::TEMPERATURE_REGION3_MAX){
//			if ($pressure>0 and $pressure<=$boundaryPressure){
//				$region=2; //Gas
//			}
//			if ($pressure<=self::PRESSURE_MAX and $pressure>$boundaryPressure){
//				$region=3; //Liquid
//			}
//		}
//		if ($temperature>self::TEMPERATURE_REGION3_MAX and $temperature<=self::TEMPERATURE_MAX) $region=2; //Gas
//		return $region;
//	}
