cmake_minimum_required(VERSION 2.8.11.2)
project(amo_library)

set(CMAKE_MACOSX_RPATH 1)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(cmake/ProjectMacros.cmake)
include(cmake/CompilerFlags.cmake)

# On Windows, things end up under Debug/ or Release/.
if (WIN32)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
else (WIN32)
  # If not on Windows, put them under more standard UNIX-like places.  This is
  # necessary, otherwise they would all end up in
  # ${CMAKE_BINARY_DIR}/src/... or somewhere else random like that.
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)
endif (WIN32)

set(SOURCE_FILES
#    FieldData.cpp
#    Financial.cpp
    Motor.cpp
    OptimizationRating.cpp
    PSATResult.cpp
    Pump.cpp
    calculator/AnnualCost.cpp
    calculator/AnnualEnergy.cpp
    calculator/CurveFitVal.cpp
    calculator/EstimateFLA.cpp
    calculator/FluidPower.cpp
    calculator/MotorCurrent.cpp
    calculator/MotorEfficiency.cpp
    calculator/MotorEfficiency25.cpp
    calculator/MotorPower.cpp
    calculator/MotorPowerFactor.cpp
    calculator/MotorShaftPower.cpp
    calculator/OptimalDeviationFactor.cpp
    calculator/OptimalMotorCurrent.cpp
    calculator/OptimalMotorPower.cpp
    calculator/OptimalMotorShaftPower.cpp
    calculator/OptimalMotorSize.cpp
    calculator/OptimalPrePumpEff.cpp
    calculator/OptimalPumpEfficiency.cpp
    calculator/OptimalPumpShaftPower.cpp
    calculator/OptimalSpecificSpeed.cpp
    calculator/OptimalSpecificSpeedCorrection.cpp
    calculator/Poles.cpp
    calculator/PumpEfficiency.cpp
    calculator/PumpShaftPower.cpp
    )

set(INCLUDE_FILES
    FieldData.h
    Financial.h
    Motor.h
    OptimizationRating.h
    PSATResult.h
    Pump.h
    calculator/AnnualCost.h
    calculator/AnnualEnergy.h
    calculator/CurveFitVal.h
    calculator/EstimateFLA.h
    calculator/FluidPower.h
    calculator/MotorCurrent.h
    calculator/MotorEfficiency.h
    calculator/MotorEfficiency25.h
    calculator/MotorPower.h
    calculator/MotorPowerFactor.h
    calculator/MotorShaftPower.h
    calculator/OptimalDeviationFactor.h
    calculator/OptimalMotorCurrent.h
    calculator/OptimalMotorPower.h
    calculator/OptimalMotorShaftPower.h
    calculator/OptimalMotorSize.h
    calculator/OptimalPrePumpEff.h
    calculator/OptimalPumpEfficiency.h
    calculator/OptimalPumpShaftPower.h
    calculator/OptimalSpecificSpeed.h
    calculator/OptimalSpecificSpeedCorrection.h
    calculator/Poles.h
    calculator/PumpEfficiency.h
    calculator/PumpShaftPower.h
    )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(third_party)

add_library(amo_suite STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
#add_executable(unit_tests tests/catch.hpp tests/unit_tests.cpp ${SOURCE_FILES} ${INCLUDE_FILES})
add_executable(amo_suite_main main.cpp)

set_target_properties(amo_suite_main PROPERTIES OUTPUT_NAME "amo_suite")

target_link_libraries( amo_suite_main amo_suite )

if (WIN32)
  target_link_libraries( amo_suite Shlwapi )
  target_link_libraries( amo_suite Shlwapi )
endif()
