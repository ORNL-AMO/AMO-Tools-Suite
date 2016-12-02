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
#    src/FieldData.cpp
#    src/Financial.cpp
    src/Motor.cpp
    src/OptimizationRating.cpp
    src/PSATResult.cpp
    src/Pump.cpp
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
    )

set(INCLUDE_FILES
    include/FieldData.h
    include/Financial.h
    include/Motor.h
    include/OptimizationRating.h
    include/PSATResult.h
    include/Pump.h
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
    )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(third_party)

add_library(amo_suite STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
#add_executable(unit_tests tests/catch.hpp tests/unit_tests.cpp ${SOURCE_FILES} ${INCLUDE_FILES})
add_executable(amo_suite_main main.cpp)

set_target_properties(amo_suite_main PROPERTIES OUTPUT_NAME "amo_suite")
target_link_libraries( amo_suite_main amo_suite )
