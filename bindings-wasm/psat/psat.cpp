#include <calculator/pump/PumpData.h>
#include "calculator/pump/PumpShaftPower.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/HeadTool.h"
#include "calculator/motor/MotorShaftPower.h"
#include "calculator/pump/PumpEfficiency.h"
#include "results/Results.h"
#include "results/InputData.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(pumpData_class)
{
    class_<PumpData>("PumpData")
        .constructor<std::string, std::string, std::string, std::string, std::string, std::string, std::string,
            std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string,
            int, int, int, int, int, int, double, double, double, double, double, double,
            double, double, double, double, double, double, double, double, double, double,
            double, double, double, double, double, double, double, double, bool>()
            .function("getId", &PumpData::getId)
            .function("getWeight", &PumpData::getWeight)
            .function("getOutOfService", &PumpData::getOutOfService)
            .function("getInletDiameter", &PumpData::getInletDiameter)
            .function("getOutletDiameter", &PumpData::getOutletDiameter)
            .function("getPercentageOfSchedule", &PumpData::getPercentageOfSchedule)
            .function("getDailyPumpCapacity", &PumpData::getDailyPumpCapacity)
            .function("getMeasuredPumpCapacity", &PumpData::getMeasuredPumpCapacity)
            .function("getPumpPerformance", &PumpData::getPumpPerformance)
            .function("getStaticSuctionHead", &PumpData::getStaticSuctionHead)
            .function("getStaticDischargeHead", &PumpData::getStaticDischargeHead)
            .function("getFluidDensity", &PumpData::getFluidDensity)
            .function("getLengthOfDischargePipe", &PumpData::getLengthOfDischargePipe)
            .function("getPipeDesignFrictionLosses", &PumpData::getPipeDesignFrictionLosses)
            .function("getMaxWorkingPressure", &PumpData::getMaxWorkingPressure)
            .function("getMaxAmbientTemperature", &PumpData::getMaxAmbientTemperature)
            .function("getMaxSuctionLift", &PumpData::getMaxSuctionLift)
            .function("getDisplacement", &PumpData::getDisplacement)
            .function("getStartingTorque", &PumpData::getStartingTorque)
            .function("getRatedSpeed", &PumpData::getRatedSpeed)
            .function("getMinFlowSize", &PumpData::getMinFlowSize)
            .function("getPumpSize", &PumpData::getPumpSize)
            .function("getShaftDiameter", &PumpData::getShaftDiameter)
            .function("getImpellerDiameter", &PumpData::getImpellerDiameter)
            .function("getEfficiency", &PumpData::getEfficiency)
            .function("getOutput60Hz", &PumpData::getOutput60Hz)
            .function("getSpeed", &PumpData::getSpeed)
            .function("getNumShafts", &PumpData::getNumShafts)
            .function("getNumStages", &PumpData::getNumStages)
            .function("getYearlyOperatingHours", &PumpData::getYearlyOperatingHours)
            .function("getYearInstalled", &PumpData::getYearInstalled)
            .function("getSerialNumber", &PumpData::getSerialNumber)
            .function("getStatus", &PumpData::getStatus)
            .function("getPumpType", &PumpData::getPumpType)
            .function("getRadialBearingType", &PumpData::getRadialBearingType)
            .function("getThrustBearingType", &PumpData::getThrustBearingType)
            .function("getShaftOrientation", &PumpData::getShaftOrientation)
            .function("getShaftSealType", &PumpData::getShaftSealType)
            .function("getFluidType", &PumpData::getFluidType)
            .function("getDriveType", &PumpData::getDriveType)
            .function("getFlangeConnectionClass", &PumpData::getFlangeConnectionClass)
            .function("getFlangeConnectionSize", &PumpData::getFlangeConnectionSize)
            .function("getType", &PumpData::getType)
            .function("getManufacturer", &PumpData::getManufacturer)
            .function("getModel", &PumpData::getModel)
            .function("getPriority", &PumpData::getPriority)
            .function("getFinalMotorRpm", &PumpData::getFinalMotorRpm)
            .function("setId", &PumpData::setId)
            .function("setWeight", &PumpData::setWeight)
            .function("setOutOfService", &PumpData::setOutOfService)
            .function("setInletDiameter", &PumpData::setInletDiameter)
            .function("setOutletDiameter", &PumpData::setOutletDiameter)
            .function("setPercentageOfSchedule", &PumpData::setPercentageOfSchedule)
            .function("setDailyPumpCapacity", &PumpData::setDailyPumpCapacity)
            .function("setMeasuredPumpCapacity", &PumpData::setMeasuredPumpCapacity)
            .function("setPumpPerformance", &PumpData::setPumpPerformance)
            .function("setStaticSuctionHead", &PumpData::setStaticSuctionHead)
            .function("setStaticDischargeHead", &PumpData::setStaticDischargeHead)
            .function("setFluidDensity", &PumpData::setFluidDensity)
            .function("setLengthOfDischargePipe", &PumpData::setLengthOfDischargePipe)
            .function("setPipeDesignFrictionLosses", &PumpData::setPipeDesignFrictionLosses)
            .function("setMaxWorkingPressure", &PumpData::setMaxWorkingPressure)
            .function("setMaxAmbientTemperature", &PumpData::setMaxAmbientTemperature)
            .function("setMaxSuctionLift", &PumpData::setMaxSuctionLift)
            .function("setDisplacement", &PumpData::setDisplacement)
            .function("setStartingTorque", &PumpData::setStartingTorque)
            .function("setRatedSpeed", &PumpData::setRatedSpeed)
            .function("setMinFlowSize", &PumpData::setMinFlowSize)
            .function("setPumpSize", &PumpData::setPumpSize)
            .function("setShaftDiameter", &PumpData::setShaftDiameter)
            .function("setImpellerDiameter", &PumpData::setImpellerDiameter)
            .function("setEfficiency", &PumpData::setEfficiency)
            .function("setOutput60Hz", &PumpData::setOutput60Hz)
            .function("setSpeed", &PumpData::setSpeed)
            .function("setNumShafts", &PumpData::setNumShafts)
            .function("setNumStages", &PumpData::setNumStages)
            .function("setYearlyOperatingHours", &PumpData::setYearlyOperatingHours)
            .function("setYearInstalled", &PumpData::setYearInstalled)
            .function("setSerialNumber", &PumpData::setSerialNumber)
            .function("setStatus", &PumpData::setStatus)
            .function("setPumpType", &PumpData::setPumpType)
            .function("setRadialBearingType", &PumpData::setRadialBearingType)
            .function("setThrustBearingType", &PumpData::setThrustBearingType)
            .function("setShaftOrientation", &PumpData::setShaftOrientation)
            .function("setShaftSealType", &PumpData::setShaftSealType)
            .function("setFluidType", &PumpData::setFluidType)
            .function("setDriveType", &PumpData::setDriveType)
            .function("setFlangeConnectionClass", &PumpData::setFlangeConnectionClass)
            .function("setFlangeConnectionSize", &PumpData::setFlangeConnectionSize)
            .function("setType", &PumpData::setType)
            .function("setManufacturer", &PumpData::setManufacturer)
            .function("setModel", &PumpData::setModel)
            .function("setPriority", &PumpData::setPriority)
            .function("setFinalMotorRpm", &PumpData::setFinalMotorRpm);

    register_vector<PumpData>("PumpDataV");
}

//pump shaft power (Not Sure Used in Desktop, but good example)
EMSCRIPTEN_BINDINGS(pump_shaft_class)
{
    class_<PumpShaftPower>("PumpShaftPower")
        .constructor<double, Motor::Drive, double>()
        .function("calculate", &PumpShaftPower::calculate);

    class_<PumpShaftPower::Output>("PumpShaftPowerOutput")
        .constructor<double, double>()
        .property("pumpShaftPower", &PumpShaftPower::Output::pumpShaftPower)
        .property("driveEfficiency", &PumpShaftPower::Output::driveEfficiency);
}

//headToolSuctionTank
EMSCRIPTEN_BINDINGS(head_tool_suction_tank_class)
{
    class_<HeadToolSuctionTank>("HeadToolSuctionTank")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &HeadToolSuctionTank::calculate);
}
//headTool
EMSCRIPTEN_BINDINGS(head_tool_class)
{
    class_<HeadTool>("HeadTool")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &HeadTool::calculate);
}
//headToolOutput
EMSCRIPTEN_BINDINGS(head_tool_output)
{
    class_<HeadToolBase::Output>("HeadToolOutput")
        .constructor<double, double, double, double, double, double>()
        .property("differentialElevationHead", &HeadToolBase::Output::elevationHead)
        .property("differentialPressureHead", &HeadToolBase::Output::pressureHead)
        .property("differentialVelocityHead", &HeadToolBase::Output::velocityHeadDifferential)
        .property("estimatedSuctionFrictionHead", &HeadToolBase::Output::suctionHead)
        .property("estimatedDischargeFrictionHead", &HeadToolBase::Output::dischargeHead)
        .property("pumpHead", &HeadToolBase::Output::pumpHead);
}

//resultsExisting & resultsModified
EMSCRIPTEN_BINDINGS(psat_results)
{
    class_<Pump::Input>("PsatInput")
        .constructor<Pump::Style, double, double, Motor::Drive, double, double, int, Pump::SpecificSpeed, double>();

    class_<Pump::FieldData>("PumpFieldData")
        .constructor<double, double, Motor::LoadEstimationMethod, double, double, double>();

    class_<PSATResult>("PSAT")
        .constructor<Pump::Input, Motor, Pump::FieldData, double, double>()
        .function("calculateExisting", &PSATResult::calculateExisting)
        .function("calculateModified", &PSATResult::calculateModified)
        .function("getAnnualSavingsPotential", &PSATResult::getAnnualSavingsPotential)
        .function("getOptimizationRating", &PSATResult::getOptimizationRating);
}

EMSCRIPTEN_BINDINGS(psat_results_output)
{
    class_<PSATResult::Output>("PsatResults")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double>()
        .property("pump_efficiency", &PSATResult::Output::pumpEfficiency)
        .property("motor_rated_power", &PSATResult::Output::motorRatedPower)
        .property("motor_shaft_power", &PSATResult::Output::motorShaftPower)
        .property("pump_shaft_power", &PSATResult::Output::pumpShaftPower)
        .property("motor_efficiency", &PSATResult::Output::motorEfficiency)
        .property("motor_power_factor", &PSATResult::Output::motorPowerFactor)
        .property("motor_current", &PSATResult::Output::motorCurrent)
        .property("motor_power", &PSATResult::Output::motorPower)
        .property("annual_energy", &PSATResult::Output::annualEnergy)
        .property("annual_cost", &PSATResult::Output::annualCost)
        .property("load_factor", &PSATResult::Output::loadFactor)
        .property("drive_efficiency", &PSATResult::Output::driveEfficiency)
        .property("estimatedFLA", &PSATResult::Output::estimatedFLA);
}

//achievableEfficiency
EMSCRIPTEN_BINDINGS(optimal_specified_speed_class)
{
    class_<OptimalSpecificSpeedCorrection>("OptimalSpecificSpeedCorrection")
        .constructor<Pump::Style, double>()
        .function("calculate", &OptimalSpecificSpeedCorrection::calculate);
}
//pumpEfficiency
EMSCRIPTEN_BINDINGS(pump_efficiency)
{
    class_<PumpEfficiency>("PumpEfficiency")
        .constructor<Pump::Style, double>()
        .function("calculate", &PumpEfficiency::calculate);
}

EMSCRIPTEN_BINDINGS(pump_efficiency_output)
{
    class_<PumpEfficiency::Output>("PumpEfficiencyResults")
        .constructor<double, double>()
        .property("average", &PumpEfficiency::Output::average)
        .property("max", &PumpEfficiency::Output::max);
}