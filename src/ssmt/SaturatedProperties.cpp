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

double SaturatedTemperature::calculate() const {
    const double C1 = 0.11670521452767E+04, C2 = -0.72421316703206E+06, C3 = -0.17073846940092E+02;
    const double C4 = 0.12020824702470E+05, C5 = -0.32325550322333E+07, C6 = 0.14915108613530E+02;
    const double C7 = -0.48232657361591E+04, C8 = 0.40511340542057E+06, C9 = -0.23855557567849E+00;
    const double C10 = 0.65017534844798E+03;

    const double SS = std::pow(saturatedPressure, 0.25);
    const double E = SS * SS + C3 * SS + C6;
    const double F = C1 * SS * SS + C4 * SS + C7;
    const double G = C2 * SS * SS + C5 * SS + C8;
    const double D = 2 * G / (-F - std::sqrt(pow(F, 2) - 4 * E * G));

    return (C10 + D - std::sqrt(std::pow((C10 + D), 2) - 4 * (C9 + C10 * D))) / 2;
}

double SaturatedPressure::calculate() const {
    const double C1 = 0.11670521452767E+04, C2 = -0.72421316703206E+06, C3 = -0.17073846940092E+02;
    const double C4 = 0.12020824702470E+05, C5 = -0.32325550322333E+07, C6 = 0.14915108613530E+02;
    const double C7 = -0.48232657361591E+04, C8 = 0.40511340542057E+06, C9 = -0.23855557567849E+00;
    const double C10 = 0.65017534844798E+03;

    const double v = saturatedTemperature + (C9 / (saturatedTemperature - C10));
    const double vSquared = std::pow(v, 2);

    const double A = vSquared + (C1 * v) + C2;
    const double B = (C3 * vSquared) + (C4 * v) + C5;
    const double C = (C6 * vSquared) + (C7 * v) + C8;

    return std::pow((2 * C) / (-B + std::sqrt(std::pow(B, 2) - 4 * A * C)), 4);
}

SteamSystemModelerTool::SaturatedPropertiesOutput SaturatedProperties::calculate() {
    auto const gasProperties = SteamSystemModelerTool::region2(saturatedTemperature, saturatedPressure);
    SteamSystemModelerTool::SteamPropertiesOutput liquidProperties;

    if ((saturatedTemperature >= SteamSystemModelerTool::TEMPERATURE_MIN)
        && (saturatedTemperature <= SteamSystemModelerTool::TEMPERATURE_Tp)) {
        liquidProperties = SteamSystemModelerTool::region1(saturatedTemperature, saturatedPressure);
    }

    if ((saturatedTemperature > SteamSystemModelerTool::TEMPERATURE_Tp)
        && (saturatedTemperature <= SteamSystemModelerTool::TEMPERATURE_CRIT)) {
        liquidProperties = SteamSystemModelerTool::region3(saturatedTemperature, saturatedPressure);
    }

    const double evaporationEnthalpy = gasProperties.specificEnthalpy - liquidProperties.specificEnthalpy;
    const double evaporationEntropy = gasProperties.specificEntropy - liquidProperties.specificEntropy;
    const double evaporationVolume = gasProperties.specificVolume - liquidProperties.specificVolume;

	return {saturatedTemperature, saturatedPressure, gasProperties.specificVolume, gasProperties.specificEnthalpy,
            gasProperties.specificEntropy, liquidProperties.specificVolume, liquidProperties.specificEnthalpy,
            liquidProperties.specificEntropy, evaporationVolume, evaporationEnthalpy, evaporationEntropy};
}