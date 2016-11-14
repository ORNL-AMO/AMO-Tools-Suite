cmake_minimum_required(VERSION 3.5)
project(amo_library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES "*.h" "calculator*.h" "*.cpp" "calculator/*.cpp" )
set(LIB_FILES ${SOURCE_FILES} calculator/CurveFitVal.cpp calculator/CurveFitVal.h)
list(REMOVE_ITEM LIB_FILES "main.cpp")

add_executable(amo_library_cmd_line ${SOURCE_FILES})
add_library(amo_library SHARED ${LIB_FILES})