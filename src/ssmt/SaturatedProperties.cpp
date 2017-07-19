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

    double gibbs0 = log(reducedPressure);
    double gibbsPi0 = 1/reducedPressure;
    double gibbsPiPi0 = -1/(pow(reducedPressure,2));
    double gibbsT0 = 0.0;
    double gibbsTT0 = 0.0;
    double gibbsPit0 = 0.0;

    for (int i = 0; i < 9; i++)
    {
        gibbs0 += n0[i] * pow(inverseReducedTemp, J0[i]);
        gibbsT0 += n0[i] * J0[i] * pow(inverseReducedTemp, J0[i] - 1);
        gibbsTT0 += n0[i] * J0[i] * (J0[i] - 1)  * pow(inverseReducedTemp, J0[i] - 2);
    }

    double gibbs1 = 0.0;
    double gibbsPi1 = 0.0;
    double gibbsPiPi01 = 0.0;
    double gibbsT1 = 0.0;
    double gibbsTT1 = 0.0;
    double gibbsPit1 = 0.0;

    for (int i = 0; i < 43; i++)
    {
        gibbs1 += n1[i] * pow(reducedPressure, I1[i]) * pow((inverseReducedTemp - 0.5), J1[i]);
        gibbsPi1 += n1[i] * I1[i] * pow(reducedPressure, I1[i] - 1) * pow((inverseReducedTemp - 0.5), J1[i]);
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

}

double SaturatedProperties::getGasEntropy(){


}

double SaturatedProperties::getEvaporationEntropy(){
    double gasEntropy = getGasEntropy();
    double liquidEnthropy = getLiquidEntropy();
    this->evaporationEntropy_ = gasEntropy - liquidEnthropy;
    return this->evaporationEntropy_;
}

double SaturatedProperties::getLiquidVolume(){


}


double SaturatedProperties::getGasVolume(){


}

double SaturatedProperties::getEvaporationVolume(){
    double gasVolume = getGasVolume();
    double liquidVolume = getLiquidVolume();
    this->evaporationVolume_ = gasVolume - liquidVolume;
    return this->evaporationVolume_;
}