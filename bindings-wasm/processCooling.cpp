#include "chillers/ProcessCooling.h"
#include <emscripten/bind.h>

using namespace std;
using namespace emscripten;

EMSCRIPTEN_BINDINGS(processCooling_class)
{
    enum_<ProcessCooling::RefrigerantType>("RefrigerantType")
        .value("R_11", ProcessCooling::RefrigerantType::R_11)
        .value("R_123", ProcessCooling::RefrigerantType::R_123)
        .value("R_12", ProcessCooling::RefrigerantType::R_12)
        .value("R_134a", ProcessCooling::RefrigerantType::R_134a)
        .value("R_22", ProcessCooling::RefrigerantType::R_22)
        .value("R_717", ProcessCooling::RefrigerantType::R_717);

    enum_<ProcessCooling::ACSourceLocation>("ACSourceLocation")
        .value("Inside", ProcessCooling::ACSourceLocation::Inside)
        .value("Outside", ProcessCooling::ACSourceLocation::Outside);

    enum_<ProcessCooling::CoolingSystemType>("CoolingSystemType")
        .value("Water", ProcessCooling::CoolingSystemType::Water)
        .value("Air", ProcessCooling::CoolingSystemType::Air);

    enum_<ProcessCooling::CellFanType>("CellFanType")
        .value("AxialFan", ProcessCooling::CellFanType::AxialFan)
        .value("CentrifugalFan", ProcessCooling::CellFanType::CentrifugalFan);

    enum_<ProcessCooling::TowerSizedBy>("TowerSizedBy")
        .value("Tonnage", ProcessCooling::TowerSizedBy::Tonnage)
        .value("Fan_HP", ProcessCooling::TowerSizedBy::Fan_HP);

    enum_<ProcessCooling::ChillerCompressorType>("ChillerCompressorType")
        .value("Centrifugal", ProcessCooling::ChillerCompressorType::Centrifugal)
        .value("Screw", ProcessCooling::ChillerCompressorType::Screw)
        .value("Reciprocating", ProcessCooling::ChillerCompressorType::Reciprocating);

    enum_<ProcessCooling::FanMotorSpeedType>("FanMotorSpeedType")
        .value("One", ProcessCooling::FanMotorSpeedType::One)
        .value("Two", ProcessCooling::FanMotorSpeedType::Two)
        .value("Variable", ProcessCooling::FanMotorSpeedType::Variable);

    class_<ProcessCooling::WaterCooledSystemInput>("WaterCooledSystemInput")
        .constructor<double, bool, double, bool, double, bool, double, double>();

    class_<ProcessCooling::AirCooledSystemInput>("AirCooledSystemInput")
        .constructor<double, double, ProcessCooling::ACSourceLocation, double, double>();


    class_<ProcessCooling::ChillerOutput>("ChillerOutput")
        .property("efficiency", &ProcessCooling::ChillerOutput::efficiency)
        .property("hours", &ProcessCooling::ChillerOutput::hours)
        .property("power", &ProcessCooling::ChillerOutput::power)
        .property("energy", &ProcessCooling::ChillerOutput::energy);

    class_<ProcessCooling::ChillerPumpingEnergyOutput>("ChillerPumpingEnergyOutput")
        .property("chillerPumpingEnergy", &ProcessCooling::ChillerPumpingEnergyOutput::chillerPumpingEnergy);

    class_<ProcessCooling::TowerOutput>("TowerOutput")
        .property("efficiency", &ProcessCooling::TowerOutput::tempBins)
        .property("hours", &ProcessCooling::TowerOutput::hours)
        .property("energy", &ProcessCooling::TowerOutput::energy);


    class_<ProcessCooling::PumpInput>("PumpInput")
        .constructor<bool, double, double, double, double>();

    class_<ProcessCooling::TowerInput>("TowerInput")
        .constructor<int, int, ProcessCooling::FanMotorSpeedType, ProcessCooling::TowerSizedBy, ProcessCooling::CellFanType, double, double>();

    class_<ProcessCooling::ChillerInput>("ChillerInput")
        .constructor<ProcessCooling::ChillerCompressorType, double, bool, double, double, bool, bool, vector<vector<double>>>()
        .constructor<ProcessCooling::ChillerCompressorType, double, bool, double, double, bool, bool, vector<vector<double>>, bool, ProcessCooling::RefrigerantType, ProcessCooling::RefrigerantType>()
        .constructor<ProcessCooling::ChillerCompressorType, double, bool, double, double, bool, bool, vector<vector<double>>, vector<double>, vector<double>>()
        .constructor<ProcessCooling::ChillerCompressorType, double, bool, double, double, bool, bool, vector<vector<double>>, vector<double>, vector<double>, ProcessCooling::RefrigerantType, ProcessCooling::RefrigerantType>();


    class_<ProcessCooling>("ProcessCooling")
        .constructor<const vector<int>&, const vector<double>&, const vector<double>&, const vector<ProcessCooling::ChillerInput>&, ProcessCooling::TowerInput, ProcessCooling::WaterCooledSystemInput>()
        .constructor<const vector<int>&, const vector<double>&, const vector<double>&, const vector<ProcessCooling::ChillerInput>&, ProcessCooling::AirCooledSystemInput>()
        .function("calculateTowerEnergy", &ProcessCooling::calculateTowerEnergy)
        .function("calculateChillerEnergy", &ProcessCooling::calculateChillerEnergy)
        .function("calculatePumpEnergy", &ProcessCooling::calculatePumpEnergy);

    register_vector<int>("IntVector");
    register_vector<ProcessCooling::ChillerInput>("ChillerInputV");
}