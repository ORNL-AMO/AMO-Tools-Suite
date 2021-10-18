cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(amo_tools_suite)

set(CMAKE_MACOSX_RPATH 1)

set( CMAKE_VERSION_MAJOR 0 )
set( CMAKE_VERSION_MINOR 3 )
set( CMAKE_VERSION_PATCH 1 )

set(AMO_SUITE_VERSION "${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}.${CMAKE_VERSION_PATCH}")
INCLUDE_DIRECTORIES (node_modules/nan)

# Build package
# Requires:
option( BUILD_PACKAGE "Build package" ON )

# Build testing
# Requires:
option( BUILD_TESTING "Build testing targets" ON )

# Build WASM
# Requires:
option( BUILD_WASM "Build wasm" OFF )

# Build C++ documentation using Doxygen
# Requires: doxygen
# option( BUILD_DOCUMENTATION "Build Documentation" ON )

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(cmake/ProjectMacros.cmake)

if(BUILD_WASM)
  set(BUILD_PACKAGE false)
  set(BUILD_TESTING false)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_FLAGS "-fexceptions --bind -s WASM=1 -O3 -s ASSERTIONS=1 -std=c++11")
else ()
  include(cmake/CompilerFlags.cmake)
endif ()

# On Windows, things end up under Debug/ or Release/.
if (WIN32)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#  set(CMAKE_DATABASE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
else (WIN32)
  # If not on Windows, put them under more standard UNIX-like places.  This is
  # necessary, otherwise they would all end up in
  # ${CMAKE_BINARY_DIR}/src/... or somewhere else random like that.
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#  set(CMAKE_DATABASE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/db)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif (WIN32)

# set (CMAKE_CXX_FLAGS "-Wall")

#file(MAKE_DIRECTORY ${CMAKE_DATABASE_OUTPUT_DIRECTORY})

set(SOURCE_FILES
        src/results/Results.cpp
        src/calculator/util/AnnualCost.cpp
        src/calculator/util/AnnualEnergy.cpp
        src/calculator/util/CurveFitVal.cpp
        src/calculator/motor/EstimateFLA.cpp
        src/calculator/motor/MotorCurrent.cpp
        src/calculator/motor/MotorEfficiency.cpp
        src/calculator/motor/MotorPower.cpp
        src/calculator/motor/MotorPowerFactor.cpp
        src/calculator/motor/MotorShaftPower.cpp
        src/calculator/pump/OptimalDeviationFactor.cpp
        src/calculator/motor/OptimalMotorPower.cpp
        src/calculator/motor/OptimalMotorShaftPower.cpp
        src/calculator/motor/OptimalMotorSize.cpp
        src/calculator/pump/OptimalPrePumpEff.cpp
        src/calculator/pump/OptimalPumpEfficiency.cpp
        src/calculator/pump/OptimalPumpShaftPower.cpp
        src/calculator/pump/OptimalSpecificSpeed.cpp
        src/calculator/pump/OptimalSpecificSpeedCorrection.cpp
        src/calculator/motor/Poles.cpp
        src/calculator/pump/MoverEfficiency.cpp
        src/calculator/pump/PumpShaftPower.cpp
        src/calculator/losses/Atmosphere.cpp
        src/calculator/losses/FixtureLosses.cpp
        src/calculator/losses/GasCoolingLosses.cpp
        src/calculator/losses/WaterCoolingLosses.cpp
        src/calculator/losses/LiquidCoolingLosses.cpp
        src/calculator/losses/LeakageLosses.cpp
        src/calculator/losses/WallLosses.cpp
        src/calculator/losses/OpeningLosses.cpp
        src/sqlite/SQLite.cpp
        src/calculator/losses/GasFlueGasMaterial.cpp
        src/calculator/pump/HeadTool.cpp
        src/calculator/losses/EnergyInputEAF.cpp
        src/calculator/losses/SlagOtherMaterialLosses.cpp
        src/calculator/losses/SolidLiquidFlueGasMaterial.cpp
        src/calculator/losses/AuxiliaryPower.cpp
        src/calculator/losses/ExhaustGasEAF.cpp
        src/calculator/furnace/EnergyEquivalency.cpp
        src/calculator/furnace/EfficiencyImprovement.cpp
        src/calculator/furnace/O2Enrichment.cpp
        src/calculator/furnace/FlowCalculationsEnergyUse.cpp
        src/calculator/furnace/HumidityRatio.cpp
        src/ssmt/SaturatedProperties.cpp
        src/ssmt/SteamProperties.cpp
        src/ssmt/SteamSystemModelerTool.cpp
        src/ssmt/Boiler.cpp
        src/ssmt/HeatLoss.cpp
        src/ssmt/FlashTank.cpp
        src/ssmt/PRV.cpp
        src/ssmt/Deaerator.cpp
        src/ssmt/Header.cpp
        src/ssmt/Turbine.cpp
        src/ssmt/api/BoilerInput.cpp
        src/ssmt/api/HeaderInput.cpp
        src/ssmt/api/OperationsInput.cpp
        src/ssmt/api/SteamModeler.cpp
        src/ssmt/api/SteamModelerInput.cpp
        src/ssmt/api/SteamModelerOutput.cpp
        src/ssmt/api/TurbineInput.cpp
        src/ssmt/domain/BoilerFactory.cpp
        src/ssmt/domain/DeaeratorFactory.cpp
        src/ssmt/domain/FlashTankFactory.cpp
        src/ssmt/domain/FluidPropertiesFactory.cpp
        src/ssmt/domain/HeaderFactory.cpp
        src/ssmt/domain/HeatLossFactory.cpp
        src/ssmt/domain/InletFactory.cpp
        src/ssmt/domain/PrvWithDesuperheatingFactory.cpp
        src/ssmt/domain/PrvWithoutDesuperheatingFactory.cpp
        src/ssmt/domain/SteamModelerOutputFactory.cpp
        src/ssmt/domain/TurbineFactory.cpp
        src/ssmt/service/DeaeratorModeler.cpp
        src/ssmt/service/EnergyFlowCalculator.cpp
        src/ssmt/service/energy_and_cost/EnergyAndCostCalculator.cpp
        src/ssmt/service/high_pressure_header/CondensingTurbineCalculator.cpp
        src/ssmt/service/high_pressure_header/HighPressureCondensateCalculator.cpp
        src/ssmt/service/high_pressure_header/HighPressureFlashTankCalculator.cpp
        src/ssmt/service/high_pressure_header/HighPressureHeaderCalculator.cpp
        src/ssmt/service/high_pressure_header/HighPressureHeaderModeler.cpp
        src/ssmt/service/high_pressure_header/HighToLowSteamTurbineCalculator.cpp
        src/ssmt/service/high_pressure_header/HighToMediumSteamTurbineCalculator.cpp
        src/ssmt/service/low_pressure_header/LowPressureCondensateCalculator.cpp
        src/ssmt/service/low_pressure_header/LowPressureFlashedSteamIntoHeaderCalculator.cpp
        src/ssmt/service/low_pressure_header/LowPressureHeaderCalculator.cpp
        src/ssmt/service/low_pressure_header/LowPressureHeaderModeler.cpp
        src/ssmt/service/low_pressure_header/LowPressurePrvCalculator.cpp
        src/ssmt/service/MassFlowCalculator.cpp
        src/ssmt/service/medium_pressure_header/HighToMediumPrvCalculator.cpp
        src/ssmt/service/medium_pressure_header/MediumPressureCondensateCalculator.cpp
        src/ssmt/service/medium_pressure_header/MediumPressureHeaderCalculator.cpp
        src/ssmt/service/medium_pressure_header/MediumPressureHeaderModeler.cpp
        src/ssmt/service/medium_pressure_header/MediumToLowPressureTurbineCalculator.cpp
        src/ssmt/service/medium_pressure_header/ReducedSteamException.cpp
        src/ssmt/service/medium_pressure_header/SteamBalanceCheckerService.cpp
        src/ssmt/service/medium_pressure_header/UnableToBalanceException.cpp
        src/ssmt/service/power_balance/LowPressureVentedSteamCalculator.cpp
        src/ssmt/service/power_balance/PowerBalanceChecker.cpp
        src/ssmt/service/power_balance/SteamBalanceCalculator.cpp
        src/ssmt/service/power_balance/SteamProductionCalculator.cpp
        src/ssmt/service/power_balance/SteamUseCalculator.cpp
        src/ssmt/service/process_steam_usage/ProcessSteamUsageModeler.cpp
        src/ssmt/service/PrvCalculator.cpp
        src/ssmt/service/RestarterService.cpp
        src/ssmt/service/SteamBalanceException.cpp
        src/ssmt/service/SteamModelCalculator.cpp
        src/ssmt/service/SteamModelRunner.cpp
        src/ssmt/service/SteamReducer.cpp
        src/ssmt/service/TurbineCalculator.cpp
        src/ssmt/service/water_and_condensate/CombinedCondensateCalculator.cpp
        src/ssmt/service/water_and_condensate/HeatExchangerCalculator.cpp
        src/ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.cpp
        src/ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.cpp
        src/ssmt/service/water_and_condensate/MakeupWaterCalculator.cpp
        src/ssmt/service/water_and_condensate/MakeupWaterMassFlowCalculator.cpp
        src/ssmt/service/water_and_condensate/MakeupWaterVolumeFlowCalculator.cpp
        src/ssmt/service/water_and_condensate/ReturnCondensateCalculator.cpp
        src/fans/FanCurve.cpp
        src/calculator/util/CompressedAir.cpp
        src/calculator/util/CHP.cpp
        src/calculator/util/ElectricityReduction.cpp
        src/calculator/util/NaturalGasReduction.cpp
        src/calculator/util/CompressedAirReduction.cpp
        src/calculator/util/CompressedAirPressureReduction.cpp
        src/calculator/util/CompressedAirLeakSurvey.cpp
        src/calculator/util/Compressors.cpp
        src/calculator/processHeat/AirHeatingUsingExhaust.cpp
        src/calculator/processHeat/WaterHeatingUsingExhaust.cpp
        src/calculator/processHeat/WaterHeatingUsingFlue.cpp
        src/calculator/processHeat/WaterHeatingUsingSteam.cpp
        src/calculator/processHeat/CascadeHeatHighToLow.cpp
        src/calculator/util/WaterReduction.cpp
        src/calculator/util/insulation/pipes/InsulatedPipeInput.cpp
        src/calculator/util/insulation/pipes/InsulatedPipeCalculator.cpp
        src/calculator/util/insulation/pipes/InsulatedPipeOutput.cpp
        src/calculator/util/insulation/tanks/InsulatedTankInput.cpp
        src/calculator/util/insulation/tanks/InsulatedTankCalculator.cpp
        src/calculator/util/insulation/tanks/InsulatedTankOutput.cpp
        src/calculator/util/insulation/objects/AirProperties.cpp
        src/calculator/util/insulation/services/ConvectiveHeatTransferCoefficient.cpp
        src/calculator/util/insulation/services/NusseltNumber.cpp
        src/calculator/util/insulation/services/RadiativeHeatTransferCoefficient.cpp
        src/calculator/util/insulation/services/RayleighNumber.cpp
        src/calculator/util/insulation/services/ReynoldsNumber.cpp
        src/calculator/util/insulation/services/ThermalResistance.cpp
        src/calculator/util/SteamReduction.cpp
        src/calculator/util/SludgeVolumeIndex.cpp
        src/calculator/pump/PumpData.cpp
        src/calculator/motor/MotorData.cpp
        src/chillers/CoolingTower.cpp
        src/wasteWater/WasteWater_Treatment.cpp)

if(BUILD_WASM)
  set(SOURCE_FILES_WASM
        src/calculator/motor/MotorPerformance.cpp
        src/calculator/pump/PumpEfficiency.cpp
        ${CMAKE_SOURCE_DIR}/third_party/sqlite/sqlite3.c
        bindings-wasm/psat/psat.cpp
        bindings-wasm/motor/motor.cpp
        bindings-wasm/motor/motorEnum.cpp
        bindings-wasm/psat/psatEnum.cpp
        bindings-wasm/fan/fan.cpp
        bindings-wasm/fan/fanEnum.cpp
        bindings-wasm/phast/phast.cpp
        bindings-wasm/phast/phastEnum.cpp
        bindings-wasm/standalone/standalone.cpp
        bindings-wasm/standalone/standaloneEnum.cpp
        bindings-wasm/ssmt/ssmt.cpp
        bindings-wasm/ssmt/ssmtEnum.cpp
        bindings-wasm/ssmt/ssmtModeler.cpp
        bindings-wasm/processHeat.cpp
        bindings-wasm/chillers.cpp
        bindings-wasm/compressorsCalc.cpp
        bindings-wasm/svi.cpp
        bindings-wasm/wasteWater.cpp
        bindings-wasm/calculator.cpp
        bindings-wasm/db.cpp)
endif ()

set(INCLUDE_FILES
        include/results/Results.h
        include/calculator/util/AnnualCost.h
        include/calculator/util/AnnualEnergy.h
        include/calculator/util/CurveFitVal.h
        include/calculator/motor/EstimateFLA.h
        include/calculator/pump/FluidPower.h
        include/calculator/motor/MotorCurrent.h
        include/calculator/motor/MotorEfficiency.h
        include/calculator/motor/MotorPower.h
        include/calculator/motor/MotorPowerFactor.h
        include/calculator/motor/MotorShaftPower.h
        include/calculator/pump/OptimalDeviationFactor.h
        include/calculator/motor/OptimalMotorPower.h
        include/calculator/motor/OptimalMotorShaftPower.h
        include/calculator/motor/OptimalMotorSize.h
        include/calculator/pump/OptimalPrePumpEff.h
        include/calculator/pump/OptimalPumpEfficiency.h
        include/calculator/pump/OptimalPumpShaftPower.h
        include/calculator/pump/OptimalSpecificSpeed.h
        include/calculator/pump/OptimalSpecificSpeedCorrection.h
        include/calculator/motor/Poles.h
        include/calculator/pump/MoverEfficiency.h
        include/calculator/pump/PumpShaftPower.h
        include/calculator/losses/LoadChargeMaterial.h
        include/calculator/losses/SolidLoadChargeMaterial.h
        include/calculator/losses/LiquidLoadChargeMaterial.h
        include/calculator/losses/GasLoadChargeMaterial.h
        include/calculator/losses/Atmosphere.h
        include/calculator/losses/GasCoolingLosses.h
        include/calculator/losses/FixtureLosses.h
        include/calculator/losses/WaterCoolingLosses.h
        include/calculator/losses/LiquidCoolingLosses.h
        include/calculator/losses/LeakageLosses.h
        include/calculator/losses/WallLosses.h
        include/calculator/losses/OpeningLosses.h
        include/sqlite/SQLite.h
        include/calculator/losses/GasFlueGasMaterial.h
        include/calculator/pump/HeadTool.h
        include/calculator/pump/HeadTool.h
        include/sqlite/SolidLoadChargeMaterialData.h
        include/sqlite/GasLoadChargeMaterialData.h
        include/sqlite/LiquidLoadChargeMaterialData.h
        include/sqlite/SolidLiquidFlueGasMaterialData.h
        include/sqlite/GasFlueGasMaterialData.h
        include/calculator/losses/EnergyInputEAF.h
        include/calculator/losses/SlagOtherMaterialLosses.h
        include/calculator/losses/SolidLiquidFlueGasMaterial.h
        include/calculator/losses/AuxiliaryPower.h
        include/calculator/losses/ExhaustGasEAF.h
        include/calculator/furnace/EnergyEquivalency.h
        include/calculator/furnace/EfficiencyImprovement.h
        include/calculator/furnace/O2Enrichment.h
        include/calculator/furnace/FlowCalculationsEnergyUse.h
        include/calculator/losses/EnergyInputExhaustGasLosses.h
        include/sqlite/AtmosphereSpecificHeatData.h
        include/sqlite/WallLossesSurfaceData.h
        include/calculator/furnace/HumidityRatio.h
        include/ssmt/SaturatedProperties.h
        include/ssmt/SteamProperties.h
        include/ssmt/SteamSystemModelerTool.h
        include/ssmt/Boiler.h
        include/ssmt/HeatLoss.h
        include/ssmt/FlashTank.h
        include/ssmt/PRV.h
        include/ssmt/FlashTank.h
        include/ssmt/Deaerator.h
        include/ssmt/Header.h
        include/ssmt/api/BoilerInput.h
        include/ssmt/api/HeaderInput.h
        include/ssmt/api/OperationsInput.h
        include/ssmt/api/SteamModeler.h
        include/ssmt/api/SteamModelerInput.h
        include/ssmt/api/SteamModelerOutput.h
        include/ssmt/api/TurbineInput.h
        include/ssmt/domain/BoilerFactory.h
        include/ssmt/domain/DeaeratorFactory.h
        include/ssmt/domain/EnergyAndCostCalculationsDomain.h
        include/ssmt/domain/FlashTankFactory.h
        include/ssmt/domain/FluidPropertiesFactory.h
        include/ssmt/domain/HeaderFactory.h
        include/ssmt/domain/HeatLossFactory.h
        include/ssmt/domain/HighPressureHeaderCalculationsDomain.h
        include/ssmt/domain/HighToMediumSteamTurbineCalculationsDomain.h
        include/ssmt/domain/InletFactory.h
        include/ssmt/domain/LowPressureFlashedSteamIntoHeaderCalculatorDomain.h
        include/ssmt/domain/LowPressureHeaderCalculationsDomain.h
        include/ssmt/domain/LowPressureVentedSteamCalculationsDomain.h
        include/ssmt/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h
        include/ssmt/domain/MakeupWaterVolumeFlowCalculationsDomain.h
        include/ssmt/domain/MediumPressureHeaderCalculationsDomain.h
        include/ssmt/domain/PowerBalanceCheckerCalculationsDomain.h
        include/ssmt/domain/ProcessSteamUsageCalculationsDomain.h
        include/ssmt/domain/PrvWithDesuperheatingFactory.h
        include/ssmt/domain/PrvWithoutDesuperheatingFactory.h
        include/ssmt/domain/ReturnCondensateCalculationsDomain.h
        include/ssmt/domain/SteamModelCalculationsDomain.h
        include/ssmt/domain/SteamModelerOutputFactory.h
        include/ssmt/domain/TurbineFactory.h
        include/ssmt/service/DeaeratorModeler.h
        include/ssmt/service/EnergyFlowCalculator.h
        include/ssmt/service/energy_and_cost/EnergyAndCostCalculator.h
        include/ssmt/service/high_pressure_header/CondensingTurbineCalculator.h
        include/ssmt/service/high_pressure_header/HighPressureCondensateCalculator.h
        include/ssmt/service/high_pressure_header/HighPressureFlashTankCalculator.h
        include/ssmt/service/high_pressure_header/HighPressureHeaderCalculator.h
        include/ssmt/service/high_pressure_header/HighPressureHeaderModeler.h
        include/ssmt/service/high_pressure_header/HighToLowSteamTurbineCalculator.h
        include/ssmt/service/high_pressure_header/HighToMediumSteamTurbineCalculator.h
        include/ssmt/service/low_pressure_header/LowPressureCondensateCalculator.h
        include/ssmt/service/low_pressure_header/LowPressureFlashedSteamIntoHeaderCalculator.h
        include/ssmt/service/low_pressure_header/LowPressureHeaderCalculator.h
        include/ssmt/service/low_pressure_header/LowPressureHeaderModeler.h
        include/ssmt/service/low_pressure_header/LowPressurePrvCalculator.h
        include/ssmt/service/MassFlowCalculator.h
        include/ssmt/service/medium_pressure_header/HighToMediumPrvCalculator.h
        include/ssmt/service/medium_pressure_header/MediumPressureCondensateCalculator.h
        include/ssmt/service/medium_pressure_header/MediumPressureHeaderCalculator.h
        include/ssmt/service/medium_pressure_header/MediumPressureHeaderModeler.h
        include/ssmt/service/medium_pressure_header/MediumToLowPressureTurbineCalculator.h
        include/ssmt/service/medium_pressure_header/ReducedSteamException.h
        include/ssmt/service/medium_pressure_header/SteamBalanceCheckerService.h
        include/ssmt/service/medium_pressure_header/UnableToBalanceException.h
        include/ssmt/service/power_balance/LowPressureVentedSteamCalculator.h
        include/ssmt/service/power_balance/PowerBalanceChecker.h
        include/ssmt/service/power_balance/SteamBalanceCalculator.h
        include/ssmt/service/power_balance/SteamProductionCalculator.h
        include/ssmt/service/power_balance/SteamUseCalculator.h
        include/ssmt/service/process_steam_usage/ProcessSteamUsageModeler.h
        include/ssmt/service/PrvCalculator.h
        include/ssmt/service/RestarterService.h
        include/ssmt/service/SteamBalanceException.h
        include/ssmt/service/SteamModelCalculator.h
        include/ssmt/service/SteamModelRunner.h
        include/ssmt/service/SteamReducer.h
        include/ssmt/service/TurbineCalculator.h
        include/ssmt/service/water_and_condensate/CombinedCondensateCalculator.h
        include/ssmt/service/water_and_condensate/HeatExchangerCalculator.h
        include/ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.h
        include/ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.h
        include/ssmt/service/water_and_condensate/MakeupWaterCalculator.h
        include/ssmt/service/water_and_condensate/MakeupWaterMassFlowCalculator.h
        include/ssmt/service/water-and-condensate/MakeupWaterVolumeFlowCalculator.h
        include/ssmt/service/water_and_condensate/ReturnCondensateCalculator.h
        include/fans/Fan203.h
        include/fans/FanShaftPower.h
        include/fans/Planar.h
        include/ssmt/Turbine.h
        include/calculator/util/CHP.h
        include/fans/FanCurve.h
        include/calculator/util/CompressedAir.h
        include/calculator/util/ElectricityReduction.h
        include/calculator/util/NaturalGasReduction.h
        include/calculator/util/CompressedAirReduction.h
        include/calculator/util/CompressedAirLeakSurvey.h
        include/calculator/util/CompressedAirPressureReduction.h
        include/calculator/util/Compressors.h
        include/calculator/processHeat/AirHeatingUsingExhaust.h
        include/calculator/processHeat/AirWaterCoolingUsingFlue.h
        include/calculator/processHeat/WaterHeatingUsingExhaust.h
        include/calculator/processHeat/WaterHeatingUsingFlue.h
        include/calculator/processHeat/WaterHeatingUsingSteam.h
        include/calculator/processHeat/CascadeHeatHighToLow.h
        include/calculator/util/WaterReduction.h
        include/calculator/util/insulation/pipes/InsulatedPipeInput.h
        include/calculator/util/insulation/pipes/InsulatedPipeCalculator.h
        include/calculator/util/insulation/pipes/InsulatedPipeOutput.h
        include/calculator/util/insulation/tanks/InsulatedTankInput.h
        include/calculator/util/insulation/tanks/InsulatedTankCalculator.h
        include/calculator/util/insulation/tanks/InsulatedTankOutput.h
        include/calculator/util/insulation/objects/AirProperties.h
        include/calculator/util/insulation/services/ConvectiveHeatTransferCoefficient.h
        include/calculator/util/insulation/services/NusseltNumber.h
        include/calculator/util/insulation/services/RadiativeHeatTransferCoefficient.h
        include/calculator/util/insulation/services/RayleighNumber.h
        include/calculator/util/insulation/services/ReynoldsNumber.h
        include/calculator/util/insulation/services/ThermalResistance.h
        include/calculator/util/SteamReduction.h
        include/calculator/util/SludgeVolumeIndex.h
        include/calculator/motor/MotorData.h
        include/fans/CompressibilityFactor.h
        include/results/InputData.h
        include/fans/FanEnergyIndex.h
        include/fans/OptimalFanEfficiency.h
        include/ssmt/HeatExchanger.h
        include/calculator/pump/PumpData.h
        include/sqlite/PumpData.h
        include/calculator/motor/MotorData.h
        include/sqlite/MotorData.h
        include/fast-cpp-csv-parser/csv.h
        include/chillers/CoolingTower.h
        include/wasteWater/WasteWater_Treatment.h
        )

# Pending: PumpData calculator unit test

set(TEST_FILES
        tests/OptimalSpecificSpeedCorrection.unit.cpp
        tests/MotorEfficiency.unit.cpp
        tests/Results.unit.cpp
        tests/SolidLoadChargeMaterial.unit.cpp
        tests/LiquidLoadChargeMaterial.unit.cpp
        tests/Atmosphere.unit.cpp
        tests/FixtureLosses.unit.cpp
        tests/GasLoadChargeMaterial.unit.cpp
        tests/GasCoolingLosses.unit.cpp
        tests/LiquidCoolingLosses.unit.cpp
        tests/WaterCoolingLosses.unit.cpp
        tests/LeakageLosses.unit.cpp
        tests/WallLosses.unit.cpp
        tests/OpeningLosses.unit.cpp
        tests/GasFlueGasMaterial.unit.cpp
        tests/HeadTool.unit.cpp
        tests/EnergyInputEAF.unit.cpp
        tests/SQLite.unit.cpp
        tests/SolidLiquidFlueGasMaterial.unit.cpp
        tests/AuxiliaryPower.unit.cpp
        tests/SlagOtherMaterialLosses.unit.cpp
        tests/ExhaustGasEAF.unit.cpp
        tests/EnergyEquivalency.unit.cpp
        tests/EfficiencyImprovement.unit.cpp
        tests/ElectricityReduction.unit.cpp
        tests/NaturalGasReduction.unit.cpp
        tests/CompressedAirReduction.unit.cpp
        tests/CompressedAirLeakSurvey.unit.cpp
        tests/CompressedAirPressureReduction.unit.cpp
        tests/Compressors.unit.cpp
        tests/ProcessHeat.unit.cpp
        tests/WaterReduction.unit.cpp
        tests/InsulatedPipeReduction.unit.cpp
        tests/InsulatedTankReduction.unit.cpp
        tests/InsulationServices.unit.cpp
        tests/SteamReduction.unit.cpp
        tests/SludgeVolumeIndex.unit.cpp
        tests/O2Enrichment.unit.cpp
        tests/FlowCalculationsEnergyUse.unit.cpp
        tests/EnergyInputExhaustGasLosses.unit.cpp
        tests/HumidityRatio.unit.cpp
        tests/SaturatedProperties.unit.cpp
        tests/SteamProperties.unit.cpp
        tests/Boiler.unit.cpp
        tests/HeatLoss.unit.cpp
        tests/FlashTank.unit.cpp
        tests/PRV.unit.cpp
        tests/Deaerator.unit.cpp
        tests/Header.unit.cpp
        tests/Turbine.unit.cpp
        tests/Fan.unit.cpp
        tests/CHP.unit.cpp
        tests/CurveFitVal.unit.cpp
        tests/MotorCurrent.unit.cpp
        tests/CompressedAir.unit.cpp
        tests/FluidPower.unit.cpp
        tests/CompressibilityFactor.unit.cpp
        tests/OptimalFanEfficiency.unit.cpp
        tests/HeatExchanger.unit.cpp
        tests/steamapi/BoilerInput.unit.cpp
        tests/steamapi/HeaderInput.unit.cpp
        tests/steamapi/OperationsInput.unit.cpp
        tests/steamapi/SteamModeler.unit.cpp
        tests/steamapi/TurbineInput.unit.cpp
        tests/CoolingTower.unit.cpp
        tests/WasteWaterTreatment.unit.cpp)

#find_package(PythonInterp 2.7 REQUIRED)
#execute_process( COMMAND ${PYTHON_EXECUTABLE} "${PROJECT_SOURCE_DIR}/scripts/seed_database.py" "${CMAKE_DATABASE_OUTPUT_DIRECTORY}/amo_tools_suite.db")

if (MINGW)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif ()

include_directories(${CMAKE_SOURCE_DIR}/include)

# Create amo_tools_suite static library
add_library(amo_tools_suite STATIC ${SOURCE_FILES} ${SOURCE_FILES_WASM} ${INCLUDE_FILES})

if( UNIX AND NOT APPLE )
  target_link_libraries( amo_tools_suite dl )
endif()

# Add SQLite project
include_directories(${CMAKE_SOURCE_DIR}/third_party/sqlite/ SYSTEM)
add_subdirectory(third_party/sqlite)

# Create command line amo_tools_suite program
add_executable(amo_tools_suite_main main.cpp)
set_target_properties(amo_tools_suite_main PROPERTIES OUTPUT_NAME "amo_tools_suite")
target_link_libraries( amo_tools_suite_main amo_tools_suite )

if( BUILD_TESTING )
    add_library(Catch INTERFACE)
    target_include_directories(Catch INTERFACE third_party/catch/)

    # Create unit testing executable
    add_executable(amo_tools_suite_tests tests/main.unit.cpp ${TEST_FILES})
    target_link_libraries( amo_tools_suite_tests Catch amo_tools_suite )
else (BUILD_WASM)
    add_executable(client ${SOURCE_FILES} ${SOURCE_FILES_WASM})
endif()

#if(BUILD_DOCUMENTATION)
#    find_package(Doxygen REQUIRED)
#set(doxyfile_in ${CMAKE_SOURCE_DIR}/doxyfile.in)
#set(doxyfile ${CMAKE_BINARY_DIR}/doxyfile)
#message("${DOXYGEN_EXECUTABLE} ${doxyfile_in}")
#add_custom_target(
#            doc ALL
#        COMMAND "${DOXYGEN_EXECUTABLE} ${doxyfile_in}"
#            COMMAND
#            $<$<CONFIG:Release>:"${DOXYGEN_EXECUTABLE} ${doxyfile_in}">
#            $<$<NOT:$<CONFIG:Release>>:${CMAKE_COMMAND} -E echo "Only done in Release builds" >
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc
#            COMMENT "Generating API documentation with Doxygen"
#            VERBATIM
#    )
#endif()

if( BUILD_PACKAGE )
  set(CPACK_INSTALL_CMAKE_PROJECTS
    "${CMAKE_BINARY_DIR};amo_tools_suite;ALL;/"
  )

  include(cmake/Install.cmake)
endif()