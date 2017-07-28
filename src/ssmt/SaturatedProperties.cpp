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

double SaturatedProperties::getLiquidEnthalpy(){
    double temp = this->saturatedTemperature_;
    double pressure = this->saturatedPressure_;

    double enthalpy;

    if ((temp >= SteamSystemModelerTool::TEMPERATURE_MIN) && (temp <= SteamSystemModelerTool::TEMPERATURE_Tp))
    {
        std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region1(temp, pressure);
        enthalpy = properties["specificEnthalpy"];
    }

    if ((temp > SteamSystemModelerTool::TEMPERATURE_Tp) && (temp <= SteamSystemModelerTool::TEMPERATURE_CRIT))
    {
        std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region3(temp, pressure);
        enthalpy = properties["specificEnthalpy"];
    }

    return enthalpy;

}

double SaturatedProperties::getGasEnthalpy(){
    double temp = this->saturatedTemperature_;
    double pressure = this->saturatedPressure_;
    std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region2(temp, pressure);
    return properties["specificEnthalpy"];
}



double SaturatedProperties::getEvaporationEnthalpy(){
    double gasEnthalpy = getGasEnthalpy();
    double liquidEnthalpy = getLiquidEnthalpy();
    this->evaporationEnthalpy_ = gasEnthalpy - liquidEnthalpy;
    return this->evaporationEnthalpy_;
}

double SaturatedProperties::getLiquidEntropy(){
    double temp = this->saturatedTemperature_;
    double pressure = this->saturatedPressure_;

    double entropy;

    if ((temp >= SteamSystemModelerTool::TEMPERATURE_MIN) && (temp <= SteamSystemModelerTool::TEMPERATURE_Tp))
    {
        std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region1(temp, pressure);
        entropy = properties["specificEntropy"];
    }
    if ((temp > SteamSystemModelerTool::TEMPERATURE_Tp) && (temp <= SteamSystemModelerTool::TEMPERATURE_CRIT))
    {
        std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region3(temp, pressure);
        //entropy = properties["specificEntropy"];
        entropy = properties["specificEntropy"];
    }

    return entropy;


}

double SaturatedProperties::getGasEntropy(){
    double temp = this->saturatedTemperature_;
    double pressure = this->saturatedPressure_;
    std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region2(temp, pressure);
    return properties["specificEntropy"];

}

double SaturatedProperties::getEvaporationEntropy(){
    double gasEntropy = getGasEntropy();
    double liquidEntropy = getLiquidEntropy();
    this->evaporationEntropy_ = gasEntropy - liquidEntropy;
    return this->evaporationEntropy_;
}

double SaturatedProperties::getLiquidVolume(){
    double temp = this->saturatedTemperature_;
    double pressure = this->saturatedPressure_;

    double volume;

    if ((temp >= SteamSystemModelerTool::TEMPERATURE_MIN) && (temp <= SteamSystemModelerTool::TEMPERATURE_Tp))
    {
        std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region1(temp, pressure);
        volume = properties["specificVolume"];
    }

    if ((temp > SteamSystemModelerTool::TEMPERATURE_Tp) && (temp <= SteamSystemModelerTool::TEMPERATURE_CRIT))
    {
        std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region3(temp, pressure);
        volume = properties["specificVolume"];
    }

    return volume;
}



double SaturatedProperties::getGasVolume(){
    double temp = this->saturatedTemperature_;
    double pressure = this->saturatedPressure_;
    std::unordered_map<std::string, double> properties = SteamSystemModelerTool::region2(temp, pressure);
    return properties["specificVolume"];

}

double SaturatedProperties::getEvaporationVolume(){
    double gasVolume = getGasVolume();
    double liquidVolume = getLiquidVolume();
    this->evaporationVolume_ = gasVolume - liquidVolume;
    return this->evaporationVolume_;
}