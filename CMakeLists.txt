cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(amo_tools_suite)

set(CMAKE_MACOSX_RPATH 1)

set( CMAKE_VERSION_MAJOR 0 )
set( CMAKE_VERSION_MINOR 1 )
set( CMAKE_VERSION_PATCH 0 )

set(AMO_SUITE_VERSION "${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}.${CMAKE_VERSION_PATCH}")

# Build package
# Requires:
option( BUILD_PACKAGE "Build package" ON )

# Build testing
# Requires:
option( BUILD_TESTING "Build testing targets" ON )

# Build C++ documentation using Doxygen
# Requires: doxygen
#option( BUILD_DOCUMENTATION "Build Documentation" OFF )

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(cmake/ProjectMacros.cmake)
include(cmake/CompilerFlags.cmake)

# On Windows, things end up under Debug/ or Release/.
if (WIN32)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_DATABASE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
else (WIN32)
  # If not on Windows, put them under more standard UNIX-like places.  This is
  # necessary, otherwise they would all end up in
  # ${CMAKE_BINARY_DIR}/src/... or somewhere else random like that.
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_DATABASE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/db)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif (WIN32)

file(MAKE_DIRECTORY ${CMAKE_DATABASE_OUTPUT_DIRECTORY})

set(SOURCE_FILES
#    src/FieldData.cpp
#    src/Financial.cpp
        src/Motor.cpp
    src/OptimizationRating.cpp
        src/psat/PSATResult.cpp
        src/psat/Pump.cpp
    src/calculator/AnnualCost.cpp
    src/calculator/AnnualEnergy.cpp
    src/calculator/CurveFitVal.cpp
    src/calculator/EstimateFLA.cpp
    src/calculator/FluidPower.cpp
    src/calculator/MotorCurrent.cpp
    src/calculator/MotorEfficiency.cpp
    src/calculator/MotorEfficiency25.cpp
    src/calculator/MotorPower.cpp
    src/calculator/MotorPowerFactor.cpp
    src/calculator/MotorShaftPower.cpp
    src/calculator/OptimalDeviationFactor.cpp
    src/calculator/OptimalMotorCurrent.cpp
    src/calculator/OptimalMotorPower.cpp
    src/calculator/OptimalMotorShaftPower.cpp
    src/calculator/OptimalMotorSize.cpp
    src/calculator/OptimalPrePumpEff.cpp
    src/calculator/OptimalPumpEfficiency.cpp
    src/calculator/OptimalPumpShaftPower.cpp
    src/calculator/OptimalSpecificSpeed.cpp
    src/calculator/OptimalSpecificSpeedCorrection.cpp
    src/calculator/Poles.cpp
    src/calculator/PumpEfficiency.cpp
    src/calculator/PumpShaftPower.cpp
    src/calculator/GasLoadChargeMaterial.cpp
    src/calculator/LiquidLoadChargeMaterial.cpp
    src/calculator/SolidLoadChargeMaterial.cpp
    src/calculator/Atmosphere.cpp
    src/calculator/FixtureLosses.cpp
    src/calculator/GasCoolingLosses.cpp
    src/calculator/WaterCoolingLosses.cpp
    src/calculator/LiquidCoolingLosses.cpp
    src/calculator/LeakageLosses.cpp
    src/calculator/WallLosses.cpp
    src/calculator/OpeningLosses.cpp
    src/sqlite/SQLite.cpp
        src/calculator/FlueGas.cpp src/phast/furnace.cpp )

set(INCLUDE_FILES
        include/psat/FieldData.h
    include/Financial.h
        include/Motor.h
    include/OptimizationRating.h
        include/psat/PSATResult.h
        include/psat/Pump.h
    include/calculator/AnnualCost.h
    include/calculator/AnnualEnergy.h
    include/calculator/CurveFitVal.h
    include/calculator/EstimateFLA.h
    include/calculator/FluidPower.h
    include/calculator/MotorCurrent.h
    include/calculator/MotorEfficiency.h
    include/calculator/MotorEfficiency25.h
    include/calculator/MotorPower.h
    include/calculator/MotorPowerFactor.h
    include/calculator/MotorShaftPower.h
    include/calculator/OptimalDeviationFactor.h
    include/calculator/OptimalMotorCurrent.h
    include/calculator/OptimalMotorPower.h
    include/calculator/OptimalMotorShaftPower.h
    include/calculator/OptimalMotorSize.h
    include/calculator/OptimalPrePumpEff.h
    include/calculator/OptimalPumpEfficiency.h
    include/calculator/OptimalPumpShaftPower.h
    include/calculator/OptimalSpecificSpeed.h
    include/calculator/OptimalSpecificSpeedCorrection.h
    include/calculator/Poles.h
    include/calculator/PumpEfficiency.h
    include/calculator/PumpShaftPower.h
    include/calculator/LoadChargeMaterial.h
    include/calculator/SolidLoadChargeMaterial.h
    include/calculator/LiquidLoadChargeMaterial.h
    include/calculator/GasLoadChargeMaterial.h
    include/calculator/Atmosphere.h
    include/calculator/GasCoolingLosses.h
    include/calculator/FixtureLosses.h
    include/calculator/WaterCoolingLosses.h
    include/calculator/LiquidCoolingLosses.h
    include/calculator/LeakageLosses.h
    include/calculator/WallLosses.h
    include/calculator/OpeningLosses.h
    include/sqlite/SQLite.h
    include/calculator/FlueGas.h
        include/phast/Furnace.h include/phast/ChargeMaterial.h)

set(TEST_FILES
    tests/OptimalSpecificSpeedCorrection.unit.cpp
    tests/MotorEfficiency.unit.cpp
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
        tests/FlueGas.unit.cpp)

find_package(PythonInterp 2.7 REQUIRED)
execute_process( COMMAND ${PYTHON_EXECUTABLE} "${PROJECT_SOURCE_DIR}/scripts/seed_database.py" "${CMAKE_DATABASE_OUTPUT_DIRECTORY}/amo_tools_suite.db")

if (MINGW)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif ()

include_directories(${CMAKE_SOURCE_DIR}/include)

# Create amo_tools_suite static library
add_library(amo_tools_suite STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

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
endif()

# if(BUILD_DOCUMENTATION)
#   find_package(Doxygen REQUIRED)
# endif()

if( BUILD_PACKAGE )
  set(CPACK_INSTALL_CMAKE_PROJECTS
    "${CMAKE_BINARY_DIR};amo_tools_suite;ALL;/"
  )

  include(cmake/Install.cmake)
endif()
