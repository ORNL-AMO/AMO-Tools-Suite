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

double SaturatedTemperature::calculate() const {
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


    double SS = std::pow(this->saturatedPressure_, 0.25);

    double E = SS * SS + C3 * SS + C6;
    double F = C1 * SS * SS + C4 * SS + C7;
    double G = C2 * SS * SS + C5 * SS + C8;

    double D = 2 * G / (-F - std::sqrt(pow(F, 2) - 4 * E * G));

    return (C10 + D - std::sqrt(std::pow((C10 + D), 2) - 4 * (C9 + C10 * D))) / 2;
}

double SaturatedPressure::calculate() const {
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

    const double v = saturatedTemperature_ + (C9 / (saturatedTemperature_ - C10));
    const double vSquared = std::pow(v, 2);

    const double A = vSquared + (C1 * v) + C2;
    const double B = (C3 * vSquared) + (C4 * v) + C5;
    const double C = (C6 * vSquared) + (C7 * v) + C8;

    return std::pow((2 * C) / (-B + std::sqrt(std::pow(B, 2) - 4 * A * C)), 4);
}

std::unordered_map<std::string, double> SaturatedProperties::calculate() {
    double liquidEnthalpy = 0;
    double liquidEntropy = 0;
    double liquidVolume = 0;

    std::unordered_map<std::string, double> gasProperties = SteamSystemModelerTool::region2(this->saturatedTemperature_, this->saturatedPressure_);
    double gasEnthalpy = gasProperties["specificEnthalpy"];
    double gasEntropy = gasProperties["specificEntropy"];
    double gasVolume = gasProperties["specificVolume"];

    if ((this->saturatedTemperature_ >= SteamSystemModelerTool::TEMPERATURE_MIN)
        && (this->saturatedTemperature_ <= SteamSystemModelerTool::TEMPERATURE_Tp)) {
        std::unordered_map<std::string, double> liquidProperties = SteamSystemModelerTool::region1(this->saturatedTemperature_, this->saturatedPressure_);
        liquidEnthalpy = liquidProperties["specificEnthalpy"];
        liquidEntropy = liquidProperties["specificEntropy"];
        liquidVolume = liquidProperties["specificVolume"];
    }

    if ((this->saturatedTemperature_ > SteamSystemModelerTool::TEMPERATURE_Tp)
        && (this->saturatedTemperature_ <= SteamSystemModelerTool::TEMPERATURE_CRIT)) {
        std::unordered_map<std::string, double> liquidProperties = SteamSystemModelerTool::region3(this->saturatedTemperature_, this->saturatedPressure_);
        liquidEnthalpy = liquidProperties["specificEnthalpy"];
        liquidEntropy = liquidProperties["specificEntropy"];
        liquidVolume = liquidProperties["specificVolume"];
    }

    const double evaporationEnthalpy = gasEnthalpy - liquidEnthalpy;
    const double evaporationEntropy = gasEntropy - liquidEntropy;
    const double evaporationVolume = gasVolume - liquidVolume;

    return {
            {"pressure", saturatedPressure_}, //pressure in MPa
            {"temperature", saturatedTemperature_}, // temperature in Kelvin
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