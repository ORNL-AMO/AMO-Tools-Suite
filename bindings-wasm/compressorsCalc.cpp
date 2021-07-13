#include "calculator/util/Compressors.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(compressors_class)
{
    enum_<Compressors::CompressorType>("CompressorType")
        .value("Centrifugal", Compressors::CompressorType::Centrifugal)
        .value("Screw", Compressors::CompressorType::Screw)
        .value("Reciprocating", Compressors::CompressorType::Reciprocating);

    enum_<Compressors::ControlType>("ControlType")
        .value("LoadUnload", Compressors::ControlType::LoadUnload)
        .value("ModulationUnload", Compressors::ControlType::ModulationUnload)
        .value("BlowOff", Compressors::ControlType::BlowOff)
        .value("ModulationWOUnload", Compressors::ControlType::ModulationWOUnload)
        .value("StartStop", Compressors::ControlType::StartStop)
        .value("VariableDisplacementUnload", Compressors::ControlType::VariableDisplacementUnload)
        .value("MultiStepUnloading", Compressors::ControlType::MultiStepUnloading)
        .value("VFD", Compressors::ControlType::VFD);

    enum_<Compressors::Stage>("Stage")
        .value("Single", Compressors::Stage::Single)
        .value("Two", Compressors::Stage::Two)
        .value("Multiple", Compressors::Stage::Multiple);

    enum_<Compressors::Lubricant>("Lubricant")
        .value("Injected", Compressors::Lubricant::Injected)
        .value("Free", Compressors::Lubricant::Free)
        .value("None", Compressors::Lubricant::None);

    enum_<Compressors::Modulation>("Modulation")
        .value("Throttle", Compressors::Modulation::Throttle)
        .value("VariableDisplacement", Compressors::Modulation::VariableDisplacement);

    enum_<Compressors::ComputeFrom>("ComputeFrom")
        .value("PercentagePower", Compressors::ComputeFrom::PercentagePower)
        .value("PercentageCapacity", Compressors::ComputeFrom::PercentageCapacity)
        .value("PowerMeasured", Compressors::ComputeFrom::PowerMeasured)
        .value("CapacityMeasured", Compressors::ComputeFrom::CapacityMeasured)
        .value("PowerFactor", Compressors::ComputeFrom::PowerFactor);

    class_<Compressors::Output>("CompressorsOutput")
        .property("kW_Calc", &Compressors::Output::kW_Calc)
        .property("C_Calc", &Compressors::Output::C_Calc)
        .property("PerkW", &Compressors::Output::PerkW)
        .property("C_Per", &Compressors::Output::C_Per);

    class_<Compressors::OutputBlowOff>("CompressorsOutputBlowOff")
        .property("kW_Calc", &Compressors::OutputBlowOff::kW_Calc)
        .property("C_Calc", &Compressors::OutputBlowOff::C_Calc)
        .property("PerkW", &Compressors::OutputBlowOff::PerkW)
        .property("C_Per", &Compressors::OutputBlowOff::C_Per)
        .property("C_blow", &Compressors::OutputBlowOff::C_blow)
        .property("blowPer", &Compressors::OutputBlowOff::blowPer);

    class_<CompressorEEMs::ReduceAirLeaksOutput>("ReduceAirLeaksOutput")
        .property("C_lkred", &CompressorEEMs::ReduceAirLeaksOutput::C_lkred)
        .property("C_usage_lkred", &CompressorEEMs::ReduceAirLeaksOutput::C_usage_lkred)
        .property("PerC_lkred", &CompressorEEMs::ReduceAirLeaksOutput::PerC_lkred);

    class_<CompressorEEMs::ImproveEndUseEfficiencyOutput>("ImproveEndUseEfficiencyOutput")
        .property("C_af_red", &CompressorEEMs::ImproveEndUseEfficiencyOutput::C_af_red)
        .property("CPer_af_red", &CompressorEEMs::ImproveEndUseEfficiencyOutput::CPer_af_red);

    class_<CompressorEEMs::ReduceSystemAirPressureOutput>("ReduceSystemAirPressureOutput")
        .property("P_fl_rpred", &CompressorEEMs::ReduceSystemAirPressureOutput::P_fl_rpred)
        .property("kW_fl_rpadj", &CompressorEEMs::ReduceSystemAirPressureOutput::kW_fl_rpadj)
        .property("C_usage_rpred", &CompressorEEMs::ReduceSystemAirPressureOutput::C_usage_rpred)
        .property("PerC_rpred", &CompressorEEMs::ReduceSystemAirPressureOutput::PerC_rpred);

    class_<CompressorEEMs::AdjustCascadingSetPointOutput>("AdjustCascadingSetPointOutput")
        .property("kW_fl_adj", &CompressorEEMs::AdjustCascadingSetPointOutput::kW_fl_adj)
        .property("C_usage_adj", &CompressorEEMs::AdjustCascadingSetPointOutput::C_usage_adj)
        .property("PerC_adj", &CompressorEEMs::AdjustCascadingSetPointOutput::PerC_adj);

    class_<CompressorEEMs::PressureReductionSavingOutput>("PressureReductionSavingOutput")
        .property("kW_savings", &CompressorEEMs::PressureReductionSavingOutput::kW_savings)
        .property("kWh_savings", &CompressorEEMs::PressureReductionSavingOutput::kWh_savings)
        .property("cost_savings", &CompressorEEMs::PressureReductionSavingOutput::cost_savings);

    class_<Compressors_Centrifugal_LoadUnload>("Compressors_Centrifugal_LoadUnload")
        .constructor<double, double, double>()
        .function("calculateFromPerkW", &Compressors_Centrifugal_LoadUnload::calculateFromPerkW)
        .function("calculateFromPerC", &Compressors_Centrifugal_LoadUnload::calculateFromPerC)
        .function("calculateFromkWMeasured", &Compressors_Centrifugal_LoadUnload::calculateFromkWMeasured)
        .function("calculateFromCMeasured", &Compressors_Centrifugal_LoadUnload::calculateFromCMeasured)
        .function("calculateFromVIPFMeasured", &Compressors_Centrifugal_LoadUnload::calculateFromVIPFMeasured)
        .function("AdjustDischargePressure", &Compressors_Centrifugal_LoadUnload::AdjustDischargePressure)
        .property("C_fl_Adjusted", &Compressors_Centrifugal_LoadUnload::getC_fl_Adjusted);

    class_<Compressors_Centrifugal_ModulationUnload>("Compressors_Centrifugal_ModulationUnload")
        .constructor<double, double, double, double, double, double>()
        .function("calculateFromPerkW", &Compressors_Centrifugal_ModulationUnload::calculateFromPerkW)
        .function("calculateFromPerC", &Compressors_Centrifugal_ModulationUnload::calculateFromPerC)
        .function("calculateFromkWMeasured", &Compressors_Centrifugal_ModulationUnload::calculateFromkWMeasured)
        .function("calculateFromCMeasured", &Compressors_Centrifugal_ModulationUnload::calculateFromCMeasured)
        .function("calculateFromVIPFMeasured", &Compressors_Centrifugal_ModulationUnload::calculateFromVIPFMeasured)
        .function("AdjustDischargePressure", &Compressors_Centrifugal_ModulationUnload::AdjustDischargePressure)
        .property("C_fl_Adjusted", &Compressors_Centrifugal_ModulationUnload::getC_fl_Adjusted)
        .property("C_max_Adjusted", &Compressors_Centrifugal_ModulationUnload::getC_max_Adjusted);

    class_<Compressors_Centrifugal_BlowOff>("Compressors_Centrifugal_BlowOff")
        .constructor<double, double, double, double>()
        .function("calculateFromPerkW_BlowOff", &Compressors_Centrifugal_BlowOff::calculateFromPerkW_BlowOff)
        .function("calculateFromPerC_BlowOff", &Compressors_Centrifugal_BlowOff::calculateFromPerC_BlowOff)
        .function("calculateFromkWMeasured_BlowOff", &Compressors_Centrifugal_BlowOff::calculateFromkWMeasured_BlowOff)
        .function("calculateFromCMeasured_BlowOff", &Compressors_Centrifugal_BlowOff::calculateFromCMeasured_BlowOff)
        .function("calculateFromVIPFMeasured_BlowOff", &Compressors_Centrifugal_BlowOff::calculateFromVIPFMeasured_BlowOff)
        .function("AdjustDischargePressure", &Compressors_Centrifugal_BlowOff::AdjustDischargePressure)
        .property("C_fl_Adjusted", &Compressors_Centrifugal_BlowOff::getC_fl_Adjusted);

    class_<Compressors_ModulationWOUnload>("Compressors_ModulationWOUnload")
        .constructor<double, double, double, double, bool, Compressors::CompressorType>()
        .function("calculateFromPerkW", &Compressors_ModulationWOUnload::calculateFromPerkW)
        .function("calculateFromPerC", &Compressors_ModulationWOUnload::calculateFromPerC)
        .function("calculateFromkWMeasured", &Compressors_ModulationWOUnload::calculateFromkWMeasured)
        .function("calculateFromCMeasured", &Compressors_ModulationWOUnload::calculateFromCMeasured)
        .function("calculateFromVIPFMeasured", &Compressors_ModulationWOUnload::calculateFromVIPFMeasured)
        .function("Pressure_InletCorrection", &Compressors_ModulationWOUnload::Pressure_InletCorrection)
        .property("C_fl_Adjusted", &Compressors_ModulationWOUnload::getC_fl_Adjusted)
        .property("C_max_Adjusted", &Compressors_ModulationWOUnload::getC_max_Adjusted)
        .property("kW_fl_Adjusted", &Compressors_ModulationWOUnload::getkW_fl_Adjusted)
        .property("kW_max_Adjusted", &Compressors_ModulationWOUnload::getkW_max_Adjusted);

    class_<Compressors_StartStop>("Compressors_StartStop")
        .constructor<double, double, double, double>()
        .function("calculateFromPerkW", &Compressors_StartStop::calculateFromPerkW)
        .function("calculateFromPerC", &Compressors_StartStop::calculateFromPerC)
        .function("calculateFromkWMeasured", &Compressors_StartStop::calculateFromkWMeasured)
        .function("calculateFromCMeasured", &Compressors_StartStop::calculateFromCMeasured)
        .function("calculateFromVIPFMeasured", &Compressors_StartStop::calculateFromVIPFMeasured)
        .function("Pressure_InletCorrection", &Compressors_StartStop::Pressure_InletCorrection)
        .property("C_fl_Adjusted", &Compressors_StartStop::getC_fl_Adjusted)
        .property("C_max_Adjusted", &Compressors_StartStop::getC_max_Adjusted)
        .property("kW_fl_Adjusted", &Compressors_StartStop::getkW_fl_Adjusted)
        .property("kW_max_Adjusted", &Compressors_StartStop::getkW_max_Adjusted);

    class_<Compressors_LoadUnload>("Compressors_LoadUnload")
        .constructor<double, double, double, double, double, double, double, double,
                Compressors::CompressorType, Compressors::Lubricant, Compressors::ControlType, double, double>()
        .function("calculateFromPerkW", &Compressors_LoadUnload::calculateFromPerkW)
        .function("calculateFromPerC", &Compressors_LoadUnload::calculateFromPerC)
        .function("calculateFromkWMeasured", &Compressors_LoadUnload::calculateFromkWMeasured)
        .function("calculateFromCMeasured", &Compressors_LoadUnload::calculateFromCMeasured)
        .function("calculateFromVIPFMeasured", &Compressors_LoadUnload::calculateFromVIPFMeasured)
        .function("Pressure_InletCorrection", &Compressors_LoadUnload::Pressure_InletCorrection)
        .property("C_fl_Adjusted", &Compressors_LoadUnload::getC_fl_Adjusted)
        .property("C_max_Adjusted", &Compressors_LoadUnload::getC_max_Adjusted)
        .property("kW_fl_Adjusted", &Compressors_LoadUnload::getkW_fl_Adjusted)
        .property("kW_max_Adjusted", &Compressors_LoadUnload::getkW_max_Adjusted);

    class_<Compressors_ModulationWithUnload, base<Compressors_LoadUnload>>("Compressors_ModulationWithUnload")
        .constructor<double, double, double, double, double, double, double, double, double, Compressors::ControlType>()
        .function("calculateFromPerkW", &Compressors_ModulationWithUnload::calculateFromPerkW)
        .function("calculateFromPerC", &Compressors_ModulationWithUnload::calculateFromPerC)
        .function("calculateFromkWMeasured", &Compressors_ModulationWithUnload::calculateFromkWMeasured)
        .function("calculateFromCMeasured", &Compressors_ModulationWithUnload::calculateFromCMeasured)
        .function("calculateFromVIPFMeasured", &Compressors_ModulationWithUnload::calculateFromVIPFMeasured)
        .function("Pressure_InletCorrection", &Compressors_ModulationWithUnload::Pressure_InletCorrection)
        .property("C_fl_Adjusted", &Compressors_ModulationWithUnload::getC_fl_Adjusted)
        .property("C_max_Adjusted", &Compressors_ModulationWithUnload::getC_max_Adjusted)
        .property("kW_fl_Adjusted", &Compressors_ModulationWithUnload::getkW_fl_Adjusted)
        .property("kW_max_Adjusted", &Compressors_ModulationWithUnload::getkW_max_Adjusted);

    function("ReduceAirLeaks", &CompressorEEMs::ReduceAirLeaks);
    function("ImproveEndUseEfficiency", &CompressorEEMs::ImproveEndUseEfficiency);
    function("ReduceSystemAirPressure", &CompressorEEMs::ReduceSystemAirPressure);
    function("AdjustCascadingSetPoint", &CompressorEEMs::AdjustCascadingSetPoint);

    function("PressureReductionSaving", &CompressorEEMs::PressureReductionSaving);
    function("kWAdjusted", &CompressorEEMs::kWAdjusted);
}
