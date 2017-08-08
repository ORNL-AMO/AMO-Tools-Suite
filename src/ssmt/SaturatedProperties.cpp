/**
 * @file
 * @brief Contains the implementation of the saturated properties calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/SaturatedProperties.h"
#include "ssmt/SteamSystemModelerTool.h"
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


    double SS = pow(this->saturatedPressure_, 0.25);

    double E = SS * SS + C3 * SS + C6;
    double F = C1 * SS * SS + C4 * SS + C7;
    double G = C2 * SS * SS + C5 * SS + C8;

    double D = 2 * G/(-F - pow((pow(F, 2) - 4 * E * G), 0.5));

    this->saturatedTemperature_ = (C10 + D - pow((pow((C10 + D), 2) - 4 *(C9 + C10 * D)), 0.5))/2;

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


    double V = this->saturatedTemperature_ + (C9/(this->saturatedTemperature_ - C10));

    double A = (V * V )+ (C1 * V) + C2;
    double B = (C3 * V * V) + (C4 * V) + C5;
    double C = (C6 * V * V) + (C7 * V) + C8;

    this->saturatedPressure_ = pow(((2 * C)/(-B + sqrt( pow(B, 2) - 4 * A * C))), 4);

    return this->saturatedPressure_;
}

std::unordered_map<std::string, double> SaturatedProperties::calculate() {
   // std::unordered_map<std::string, double> satProps;
    double p = this->saturatedPressure_;
    double t = this->saturatedTemperature_;

    double liquidEnthalpy = 0;
    double liquidEntropy = 0;
    double liquidVolume = 0;

    std::unordered_map<std::string, double> gasProperties = SteamSystemModelerTool::region2(this->saturatedTemperature_, this->saturatedPressure_);
    double gasEnthalpy = gasProperties["specificEnthalpy"];
    double gasEntropy = gasProperties["specificEntropy"];
    double gasVolume = gasProperties["specificVolume"];

    if ((this->saturatedTemperature_ >= SteamSystemModelerTool::TEMPERATURE_MIN) && (this->saturatedTemperature_ <= SteamSystemModelerTool::TEMPERATURE_Tp))
    {
        std::unordered_map<std::string, double> liquidProperties = SteamSystemModelerTool::region1(this->saturatedTemperature_, this->saturatedPressure_);
        liquidEnthalpy = liquidProperties["specificEnthalpy"];
        liquidEntropy = liquidProperties["specificEntropy"];
        liquidVolume = liquidProperties["specificVolume"];
    }

    if ((this->saturatedTemperature_ > SteamSystemModelerTool::TEMPERATURE_Tp) && (this->saturatedTemperature_ <= SteamSystemModelerTool::TEMPERATURE_CRIT))
    {
        std::unordered_map<std::string, double> liquidProperties = SteamSystemModelerTool::region3(this->saturatedTemperature_, this->saturatedPressure_);
        liquidEnthalpy = liquidProperties["specificEnthalpy"];
        liquidEntropy = liquidProperties["specificEntropy"];
        liquidVolume = liquidProperties["specificVolume"];
    }

    double evaporationEnthalpy = gasEnthalpy - liquidEnthalpy;
    double evaporationEntropy = gasEntropy - liquidEntropy;
    double evaporationVolume = gasVolume - liquidVolume;

    return {
            {"pressure", p}, //pressure in MPa
            {"temperature", t}, // temperature in Kelvin
            {"gasSpecificEnthalpy", gasEnthalpy}, //enthalpy in kJ/kg
            {"gasSpecificEntropy", gasEntropy}, // entropy in kJ/kg/K
            {"gasSpecificVolume", gasVolume}, // volume in m³/kg
            {"liquidSpecificEnthalpy", liquidEnthalpy}, // enthalpy in kJ/kg
            {"liquidSpecificEntropy", liquidEntropy}, // entropy in kJ/kg/K
            {"liquidSpecificVolume", liquidVolume}, // volume in m³/kg
            {"evaporationSpecificEnthalpy", evaporationEnthalpy}, // enthalpy in kJ/kg
            {"evaporationSpecificEntropy", evaporationEntropy}, // entropy in kJ/kg/K
            {"evaporationSpecificVolume", evaporationVolume}, // volume in m³/kg
    };

}