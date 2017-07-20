/**
 * @file
 * @brief Contains the implementation of the saturated properties calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/SaturatedProperties.h"
#include <cmath>

double SaturatedTemperature::calculate() {
    const double C1 = 0.11670521452767E+04;
    const double C2 = -0.72421316703206E+06;
    const double C3 = -0.17073846940092E+02;
    const double C4 = 0.12020824702470E+05;
    const double C5 = -0.32325550322333E+07;
    const double C6 = 0.14915108613530E+02;
    const double C7 = -0.48232657361591E+04;
    const double C8 = 0.40511340542057E+06;
    const double C9 = -0.23855557567849E+00;
    const double C10 = 0.65017534844798E+03;

    double pressureInMpa = ((this->saturatedPressure_) +  + 14.696) * 0.00689475728;

    double SS = pow(pressureInMpa, 0.25);

    double E = SS * SS + C3 * SS + C6;
    double F = C1 * SS * SS + C4 * SS + C7;
    double G = C2 * SS * SS + C5 * SS + C8;

    double D = 2 * G/(-F - pow((pow(F, 2) - 4 * E * G), 0.5));

    double tempInK = (C10 + D - pow((pow((C10 + D), 2) - 4 *(C9 + C10 * D)), 0.5))/2;

    this->saturatedTemperature_ = (tempInK * 9 / 5) - 459.67;

    return this->saturatedTemperature_;

}

double SaturatedPressure::calculate() {
    const double C1 = 0.11670521452767E+04;
    const double C2 = -0.72421316703206E+06;
    const double C3 = -0.17073846940092E+02;
    const double C4 = 0.12020824702470E+05;
    const double C5 = -0.32325550322333E+07;
    const double C6 = 0.14915108613530E+02;
    const double C7 = -0.48232657361591E+04;
    const double C8 = 0.40511340542057E+06;
    const double C9 = -0.23855557567849E+00;
    const double C10 = 0.65017534844798E+03;

    double tempInK = ((this->saturatedTemperature_) + 459.67) * 5/9;

    double V = tempInK + (C9/(tempInK - C10));

    double A = (V * V )+ (C1 * V) + C2;
    double B = (C3 * V * V) + (C4 * V) + C5;
    double C = (C6 * V * V) + (C7 * V) + C8;

    double pressureInMpa = pow(((2 * C)/(-B + sqrt( pow(B, 2) - 4 * A * C))), 4);

    this->saturatedPressure_ = (pressureInMpa / .006894757293) - 14.696;

    return this->saturatedPressure_;
}

double SaturatedProperties::getLiquidEnthalpy(){
    double tempInK = ((this->saturatedTemperature_) + 459.67) * 5/9;
    double pressureInMpa = ((this->saturatedPressure_) +  + 14.696) * 0.00689475728;

    if ((tempInK >= 273.15) && (tempInK <= 623.15)){
        double n[] ={0.14632971213167,     -0.84548187169114,    -0.37563603672040e1,
                     0.33855169168385e1,   -0.95791963387872,     0.15772038513228,
                     -0.16616417199501e-1,   0.81214629983568e-3,  0.28319080123804e-3,
                     -0.60706301565874e-3,  -0.18990068218419e-1, -0.32529748770505e-1,
                     -0.21841717175414e-1,  -0.52838357969930e-4, -0.47184321073267e-3,
                     -0.30001780793026e-3,   0.47661393906987e-4, -0.44141845330846e-5,
                     -0.72694996297594e-15, -0.31679644845054e-4, -0.28270797985312e-5,
                     -0.85205128120103e-9,  -0.22425281908000e-5, -0.65171222895601e-6,
                     -0.14341729937924e-12, -0.40516996860117e-6, -0.12734301741641e-8,
                     -0.17424871230634e-9,  -0.68762131295531e-18, 0.14478307828521e-19,
                     0.26335781662795e-22, -0.11947622640071e-22, 0.18228094581404e-23,
                     -0.93537087292458e-25};

        double J[] = { -2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -1, 0, 1, 3, -3, 0, 1, 3, 17,
                       -4, 0, 6, -5, -2, 10, -8, -11, -6, -29, -31, -38, -39, -40, -41};

        double I[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3,
                      4, 4, 4, 5, 8, 8, 21, 23, 29, 30, 31, 32};

        double reducedPressure = pressureInMpa/16.53;
        double inverseReducedTemp = 1386/tempInK;

        double gibbs = 0.0;
        double gibbsPi = 0.0;
        double gibbsPipi = 0.0;
        double gibbsT = 0.0;
        double gibbsTT = 0.0;
        double gibbsPit = 0.0;

        for (int i = 0; i < 34; i++)
        {
            gibbs += n[i] * pow((7.1 - reducedPressure), I[i]) * pow((inverseReducedTemp - 1.222), J[i]);
            gibbsPi += -n[i] * I[i] * pow((7.1 - reducedPressure), I[i] - 1) * pow((inverseReducedTemp - 1.222), J[i]);
            gibbsT += n[i] * pow((7.1 - reducedPressure), I[i]) * J[i] * pow((inverseReducedTemp - 1.222), J[i] - 1);
        }

        double R = 0.461526;
        this->liquidEnthalpy_ = inverseReducedTemp * gibbsT * tempInK * R;
        return this->liquidEnthalpy_ / 2.325997;
    }

    if ((tempInK > 623.15) && (tempInK <= 647.096))
    {
        return 1;
    }


}

double SaturatedProperties::getGasEnthalpy(){
    double n0[] = {-0.96927686500217E+01,  0.10086655968018E+02, -0.56087911283020E-02,
                   0.71452738081455E-01, -0.40710498223928E+00,  0.14240819171444E+01,
                   -0.43839511319450E+01, -0.28408632460772E+00,  0.21268463753307E-01};

    double J0[] = {0, 1, -5, -4, -3, -2, -1, 2,  3};

    double n1[] = {-0.17731742473213E-02,  -0.17834862292358E-01,  -0.45996013696365E-01,
                   -0.57581259083432E-01,  -0.50325278727930E-01,  -0.33032641670203E-04,
                   -0.18948987516315E-03,  -0.39392777243355E-02,  -0.43797295650573E-01,
                   -0.26674547914087E-04,   0.20481737692309E-07,   0.43870667284435E-06,
                   -0.32277677238570E-04,  -0.15033924542148E-02,  -0.40668253562649E-01,
                   -0.78847309559367E-09,   0.12790717852285E-07,   0.48225372718507E-06,
                   0.22922076337661E-05,  -0.16714766451061E-10,  -0.21171472321355E-02,
                   -0.23895741934104E+02,  -0.59059564324270E-17,  -0.12621808899101E-05,
                   -0.38946842435739E-01,   0.11256211360459E-10,  -0.82311340897998E+01,
                   0.19809712802088E-07,   0.10406965210174E-18,  -0.10234747095929E-12,
                   -0.10018179379511E-08,  -0.80882908646985E-10,   0.10693031879409E+00,
                   -0.33662250574171E+00,   0.89185845355421E-24,   0.30629316876232E-12,
                   -0.42002467698208E-05,  -0.59056029685639E-25,   0.37826947613457E-05,
                   -0.12768608934681E-14,   0.73087610595061E-28,   0.55414715350778E-16,
                   -0.94369707241210E-06};

    double J1[] = {0, 1, 2, 3, 6, 1, 2, 4, 7, 36, 0, 1, 3, 6, 35, 1, 2, 3, 7, 3, 16, 35, 0, 11,
                   25, 8, 36, 13, 4, 10, 14, 29, 50, 57, 20, 35, 48, 21, 53, 39, 26, 40, 58};

    double I1[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6, 7, 7, 7,
                   8, 8, 9, 10, 10, 10, 16, 16, 18, 20, 20, 20, 21, 22, 23, 24, 24, 24};

    double pressureInMpa = ((this->saturatedPressure_) +  + 14.696) * 0.00689475728;
    double tempInK = ((this->saturatedTemperature_) + 459.67) * 5/9;

    double reducedPressure = pressureInMpa;
    double inverseReducedTemp = 540/tempInK;

    double gibbsT0 = 0.0;

    for (int i = 0; i < 9; i++)
    {
        gibbsT0 += n0[i] * J0[i] * pow(inverseReducedTemp, J0[i] - 1);
    }

    double gibbsT1 = 0.0;

    for (int i = 0; i < 43; i++)
    {
        gibbsT1 += n1[i] * pow(reducedPressure, I1[i]) * J1[i] * pow((inverseReducedTemp - 0.5), J1[i] - 1);
    }

    const double R = 0.461526;
    this->gasEnthalpy_ = inverseReducedTemp * (gibbsT0 + gibbsT1) * tempInK * R;
    return this->gasEnthalpy_ / 2.325997;
}



double SaturatedProperties::getEvaporationEnthalpy(){
    double gasEnthalpy = getGasEnthalpy();
    double liquidEnthalpy = getLiquidEnthalpy();
    this->evaporationEnthalpy_ = gasEnthalpy - liquidEnthalpy;
    return this->evaporationEnthalpy_;
}

double SaturatedProperties::getLiquidEntropy(){
    double tempInK = ((this->saturatedTemperature_) + 459.67) * 5/9;
    double pressureInMpa = ((this->saturatedPressure_) +  + 14.696) * 0.00689475728;

    if ((tempInK >= 273.15) && (tempInK <= 623.15)){
    double n[] ={0.14632971213167,     -0.84548187169114,    -0.37563603672040e1,
                 0.33855169168385e1,   -0.95791963387872,     0.15772038513228,
                 -0.16616417199501e-1,   0.81214629983568e-3,  0.28319080123804e-3,
                 -0.60706301565874e-3,  -0.18990068218419e-1, -0.32529748770505e-1,
                 -0.21841717175414e-1,  -0.52838357969930e-4, -0.47184321073267e-3,
                 -0.30001780793026e-3,   0.47661393906987e-4, -0.44141845330846e-5,
                 -0.72694996297594e-15, -0.31679644845054e-4, -0.28270797985312e-5,
                 -0.85205128120103e-9,  -0.22425281908000e-5, -0.65171222895601e-6,
                 -0.14341729937924e-12, -0.40516996860117e-6, -0.12734301741641e-8,
                 -0.17424871230634e-9,  -0.68762131295531e-18, 0.14478307828521e-19,
                 0.26335781662795e-22, -0.11947622640071e-22, 0.18228094581404e-23,
                 -0.93537087292458e-25};

    double J[] = { -2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -1, 0, 1, 3, -3, 0, 1, 3, 17,
                   -4, 0, 6, -5, -2, 10, -8, -11, -6, -29, -31, -38, -39, -40, -41};

    double I[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3,
                  4, 4, 4, 5, 8, 8, 21, 23, 29, 30, 31, 32};

    double reducedPressure = pressureInMpa/16.53;
    double inverseReducedTemp = 1386/tempInK;

    double gibbs = 0.0;
    double gibbsPi = 0.0;
    double gibbsPipi = 0.0;
    double gibbsT = 0.0;
    double gibbsTT = 0.0;
    double gibbsPit = 0.0;

    for (int i = 0; i < 34; i++)
    {
        gibbs += n[i] * pow((7.1 - reducedPressure), I[i]) * pow((inverseReducedTemp - 1.222), J[i]);
        gibbsPi += -n[i] * I[i] * pow((7.1 - reducedPressure), I[i] - 1) * pow((inverseReducedTemp - 1.222), J[i]);
        gibbsT += n[i] * pow((7.1 - reducedPressure), I[i]) * J[i] * pow((inverseReducedTemp - 1.222), J[i] - 1);
    }

    double R = 0.461526;
    this->liquidEntropy_ = (inverseReducedTemp * gibbsT - gibbs) * R;
    return this->liquidEntropy_ / 4.1868;
}
    if ((tempInK > 623.15) && (tempInK <= 647.096))
    {
        return 1;
    }

}

double SaturatedProperties::getGasEntropy(){
    double n0[] = {-0.96927686500217E+01,  0.10086655968018E+02, -0.56087911283020E-02,
                   0.71452738081455E-01, -0.40710498223928E+00,  0.14240819171444E+01,
                   -0.43839511319450E+01, -0.28408632460772E+00,  0.21268463753307E-01};

    double J0[] = {0, 1, -5, -4, -3, -2, -1, 2,  3};

    double n1[] = {-0.17731742473213E-02,  -0.17834862292358E-01,  -0.45996013696365E-01,
                   -0.57581259083432E-01,  -0.50325278727930E-01,  -0.33032641670203E-04,
                   -0.18948987516315E-03,  -0.39392777243355E-02,  -0.43797295650573E-01,
                   -0.26674547914087E-04,   0.20481737692309E-07,   0.43870667284435E-06,
                   -0.32277677238570E-04,  -0.15033924542148E-02,  -0.40668253562649E-01,
                   -0.78847309559367E-09,   0.12790717852285E-07,   0.48225372718507E-06,
                   0.22922076337661E-05,  -0.16714766451061E-10,  -0.21171472321355E-02,
                   -0.23895741934104E+02,  -0.59059564324270E-17,  -0.12621808899101E-05,
                   -0.38946842435739E-01,   0.11256211360459E-10,  -0.82311340897998E+01,
                   0.19809712802088E-07,   0.10406965210174E-18,  -0.10234747095929E-12,
                   -0.10018179379511E-08,  -0.80882908646985E-10,   0.10693031879409E+00,
                   -0.33662250574171E+00,   0.89185845355421E-24,   0.30629316876232E-12,
                   -0.42002467698208E-05,  -0.59056029685639E-25,   0.37826947613457E-05,
                   -0.12768608934681E-14,   0.73087610595061E-28,   0.55414715350778E-16,
                   -0.94369707241210E-06};

    double J1[] = {0, 1, 2, 3, 6, 1, 2, 4, 7, 36, 0, 1, 3, 6, 35, 1, 2, 3, 7, 3, 16, 35, 0, 11,
                   25, 8, 36, 13, 4, 10, 14, 29, 50, 57, 20, 35, 48, 21, 53, 39, 26, 40, 58};

    double I1[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6, 7, 7, 7,
                   8, 8, 9, 10, 10, 10, 16, 16, 18, 20, 20, 20, 21, 22, 23, 24, 24, 24};

    double pressureInMpa = ((this->saturatedPressure_) +  + 14.696) * 0.00689475728;
    double tempInK = ((this->saturatedTemperature_) + 459.67) * 5/9;

    double reducedPressure = pressureInMpa;
    double inverseReducedTemp = 540/tempInK;

    double gibbs0 = log(reducedPressure);
    double gibbsT0 = 0.0;

    for (int i = 0; i < 9; i++)
    {
        gibbs0 += n0[i] * pow(inverseReducedTemp, J0[i]);
        gibbsT0 += n0[i] * J0[i] * pow(inverseReducedTemp, J0[i] - 1);
    }

    double gibbs1 = 0.0;
    double gibbsT1 = 0.0;

    for (int i = 0; i < 43; i++)
    {
        gibbs1 += n1[i] * pow(reducedPressure, I1[i]) * pow((inverseReducedTemp - 0.5), J1[i]);
        gibbsT1 += n1[i] * pow(reducedPressure, I1[i]) * J1[i] * pow((inverseReducedTemp - 0.5), J1[i] - 1);
    }

    const double R = 0.461526;
    this->gasEntropy_ = (inverseReducedTemp * (gibbsT0 + gibbsT1) - (gibbs0 + gibbs1)) * R;
    return this->gasEntropy_ / 4.1868;

}

double SaturatedProperties::getEvaporationEntropy(){
    double gasEntropy = getGasEntropy();
    double liquidEntropy = getLiquidEntropy();
    this->evaporationEntropy_ = gasEntropy - liquidEntropy;
    return this->evaporationEntropy_;
}

double SaturatedProperties::getLiquidVolume(){
    double tempInK = ((this->saturatedTemperature_) + 459.67) * 5/9;
    double pressureInMpa = ((this->saturatedPressure_) +  + 14.696) * 0.00689475728;

    double n[] ={0.14632971213167,     -0.84548187169114,    -0.37563603672040e1,
                 0.33855169168385e1,   -0.95791963387872,     0.15772038513228,
                 -0.16616417199501e-1,   0.81214629983568e-3,  0.28319080123804e-3,
                 -0.60706301565874e-3,  -0.18990068218419e-1, -0.32529748770505e-1,
                 -0.21841717175414e-1,  -0.52838357969930e-4, -0.47184321073267e-3,
                 -0.30001780793026e-3,   0.47661393906987e-4, -0.44141845330846e-5,
                 -0.72694996297594e-15, -0.31679644845054e-4, -0.28270797985312e-5,
                 -0.85205128120103e-9,  -0.22425281908000e-5, -0.65171222895601e-6,
                 -0.14341729937924e-12, -0.40516996860117e-6, -0.12734301741641e-8,
                 -0.17424871230634e-9,  -0.68762131295531e-18, 0.14478307828521e-19,
                 0.26335781662795e-22, -0.11947622640071e-22, 0.18228094581404e-23,
                 -0.93537087292458e-25};

    double J[] = { -2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -1, 0, 1, 3, -3, 0, 1, 3, 17,
                   -4, 0, 6, -5, -2, 10, -8, -11, -6, -29, -31, -38, -39, -40, -41};

    double I[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3,
                  4, 4, 4, 5, 8, 8, 21, 23, 29, 30, 31, 32};

    double reducedPressure = pressureInMpa/16.53;
    double R = 0.461526;

    if ((tempInK >= 273.15) && (tempInK <= 623.15))
    {
        double inverseReducedTemp = 1386/tempInK;

        double gibbs = 0.0;
        double gibbsPi = 0.0;
        double gibbsPipi = 0.0;
        double gibbsT = 0.0;
        double gibbsTT = 0.0;
        double gibbsPit = 0.0;

        for (int i = 0; i < 34; i++)
        {
            gibbs += n[i] * pow((7.1 - reducedPressure), I[i]) * pow((inverseReducedTemp - 1.222), J[i]);
            gibbsPi += -n[i] * I[i] * pow((7.1 - reducedPressure), I[i] - 1) * pow((inverseReducedTemp - 1.222), J[i]);
            gibbsT += n[i] * pow((7.1 - reducedPressure), I[i]) * J[i] * pow((inverseReducedTemp - 1.222), J[i] - 1);
        }

        this->liquidVolume_ = reducedPressure * gibbsPi * tempInK * R / pressureInMpa/1000;
        return this->liquidVolume_ * 16.01846353;
    }

    if ((tempInK > 623.15) && (tempInK <= 647.096))
    {

        double gibbsPi1 = 0.0;

        for (int i = 0; i < 34; i++)
        {
            gibbsPi1 += -n[i] * I[i] * pow((7.1 - reducedPressure), I[i] - 1) * pow((623.15 - 1.222), J[i]);
        }

        double volume = reducedPressure * gibbsPi1 * 623.15 * R;
        double density = 1/volume;

        double n1[] = {
                0.10658070028513E+01, -0.15732845290239E+02, 0.20944396974307E+02,
                -0.76867707878716E+01, 0.26185947787954E+01, -0.28080781148620E+01,
                0.12053369696517E+01, -0.84566812812502E-02, -0.12654315477714E+01,
                -0.11524407806681E+01, 0.88521043984318E+00, -0.64207765181607E+00,
                0.38493460186671E+00, -0.85214708824206E+00, 0.48972281541877E+01,
                -0.30502617256965E+01, 0.39420536879154E-01, 0.12558408424308E+00,
                -0.27999329698710E+00, 0.13899799569460E+01, -0.20189915023570E+01,
                -0.82147637173963E-02, -0.47596035734923E+00, 0.43984074473500E-01,
                -0.44476435428739E+00, 0.90572070719733E+00, 0.70522450087967E+00,
                0.10770512626332E+00, -0.32913623258954E+00, -0.50871062041158E+00,
                -0.22175400873096E-01, 0.94260751665092E-01, 0.16436278447961E+00,
                -0.13503372241348E-01, -0.14834345352472E-01, 0.57922953628084E-03,
                0.32308904703711E-02, 0.80964802996215E-04, -0.16557679795037E-03,
                -0.44923899061815E-04};

        double J1[] = {0,  0,  1, 2, 7, 10, 12, 23, 2, 6, 15, 17, 0, 2, 6, 7, 22, 26, 0,  2,
                       4, 16, 26, 0, 2, 4, 26,  1, 3, 26, 0, 2, 26, 2, 26, 2, 26, 0, 1, 26};

        double I1[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4,
                       4, 4, 5, 5, 5, 6, 6, 6, 7, 8, 9, 9, 10, 10, 11};

        double reducedDensity = density/322.0;
        double inverseReducedTemp1 = 647.096/tempInK;

        double helmholtz = n1[0] * log(reducedDensity);
        double helmholtzS = n1[0]/reducedDensity;
        double helmholtzSS = -n1[0] / pow(reducedDensity,2);
        double helmholtzT = 0.0;
        double helmholtzTT = 0.0;
        double helmholtzSt = 0.0;

        for (int i = 1; i < 40; i++)
        {
            helmholtz += n1[i] * pow(reducedDensity , I1[i]) * pow(inverseReducedTemp1, J1[i]);
            helmholtzS += n1[i] * I1[i] * pow(reducedDensity, I1[i] - 1) * pow(inverseReducedTemp1, J1[i]);
            helmholtzT +=n1[i] * pow(reducedDensity, I1[i]) * J1[i] * pow(inverseReducedTemp1, J1[i] - 1);
        }

        double pressureA = reducedDensity * helmholtzS * density * tempInK * R/1000;
    }
}



double SaturatedProperties::getGasVolume(){
    double n1[] = {-0.17731742473213E-02,  -0.17834862292358E-01,  -0.45996013696365E-01,
                   -0.57581259083432E-01,  -0.50325278727930E-01,  -0.33032641670203E-04,
                   -0.18948987516315E-03,  -0.39392777243355E-02,  -0.43797295650573E-01,
                   -0.26674547914087E-04,   0.20481737692309E-07,   0.43870667284435E-06,
                   -0.32277677238570E-04,  -0.15033924542148E-02,  -0.40668253562649E-01,
                   -0.78847309559367E-09,   0.12790717852285E-07,   0.48225372718507E-06,
                   0.22922076337661E-05,  -0.16714766451061E-10,  -0.21171472321355E-02,
                   -0.23895741934104E+02,  -0.59059564324270E-17,  -0.12621808899101E-05,
                   -0.38946842435739E-01,   0.11256211360459E-10,  -0.82311340897998E+01,
                   0.19809712802088E-07,   0.10406965210174E-18,  -0.10234747095929E-12,
                   -0.10018179379511E-08,  -0.80882908646985E-10,   0.10693031879409E+00,
                   -0.33662250574171E+00,   0.89185845355421E-24,   0.30629316876232E-12,
                   -0.42002467698208E-05,  -0.59056029685639E-25,   0.37826947613457E-05,
                   -0.12768608934681E-14,   0.73087610595061E-28,   0.55414715350778E-16,
                   -0.94369707241210E-06};

    double J1[] = {0, 1, 2, 3, 6, 1, 2, 4, 7, 36, 0, 1, 3, 6, 35, 1, 2, 3, 7, 3, 16, 35, 0, 11,
                   25, 8, 36, 13, 4, 10, 14, 29, 50, 57, 20, 35, 48, 21, 53, 39, 26, 40, 58};

    double I1[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6, 7, 7, 7,
                   8, 8, 9, 10, 10, 10, 16, 16, 18, 20, 20, 20, 21, 22, 23, 24, 24, 24};

    double pressureInMpa = ((this->saturatedPressure_) +  + 14.696) * 0.00689475728;
    double tempInK = ((this->saturatedTemperature_) + 459.67) * 5/9;

    double reducedPressure = pressureInMpa;
    double inverseReducedTemp = 540/tempInK;

    double gibbsPi0 = 1/reducedPressure;


    double gibbsPi1 = 0.0;

    for (int i = 0; i < 43; i++)
    {
        gibbsPi1 += n1[i] * I1[i] * pow(reducedPressure, I1[i] - 1) * pow((inverseReducedTemp - 0.5), J1[i]);
    }

    const double R = 0.461526;
    this->gasVolume_ = reducedPressure * (gibbsPi0 + gibbsPi1) * tempInK * R / pressureInMpa/1000;
    return this->gasVolume_ * 16.01846353;

}

double SaturatedProperties::getEvaporationVolume(){
    double gasVolume = getGasVolume();
    double liquidVolume = getLiquidVolume();
    this->evaporationVolume_ = gasVolume - liquidVolume;
    return this->evaporationVolume_;
}