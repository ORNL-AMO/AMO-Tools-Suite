cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(amo_tools_suite)

set(CMAKE_MACOSX_RPATH 1)

set(CMAKE_VERSION_MAJOR 0)
set(CMAKE_VERSION_MINOR 3)
set(CMAKE_VERSION_PATCH 1)

set(AMO_SUITE_VERSION "${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}.${CMAKE_VERSION_PATCH}")

option(BUILD_PACKAGE "Build package" OFF)
option(BUILD_TESTING "Build testing targets" ON)
option(BUILD_WASM "Build wasm" OFF)

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
  set(CMAKE_CXX_FLAGS "-fexceptions -O3 -std=c++11")
  set(CMAKE_EXE_LINKER_FLAGS "--no-entry --bind -s WASM=1 -s ASSERTIONS=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0")
else()
  include(cmake/CompilerFlags.cmake)
endif()

# On Windows, things end up under Debug/ or Release/.
if(WIN32)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
else(WIN32)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif (WIN32)

file(GLOB_RECURSE SOURCE_FILES "src/**.cpp")
file(GLOB_RECURSE INCLUDE_FILES "include/**.h")
if(BUILD_TESTING)
    file(GLOB_RECURSE TEST_FILES "tests/cpp/**.cpp")
elseif(BUILD_WASM)
	file(GLOB_RECURSE WASM_FILES_SOURCE "bindings-wasm/**.cpp")
    set(SOURCE_FILES_WASM ${CMAKE_SOURCE_DIR}/third_party/sqlite/sqlite3.c ${WASM_FILES_SOURCE})
endif ()

if(MINGW)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

# Create amo_tools_suite static library
add_library(amo_tools_suite STATIC ${SOURCE_FILES} ${SOURCE_FILES_WASM} ${INCLUDE_FILES})

if(UNIX AND NOT APPLE)
  target_link_libraries(amo_tools_suite dl)
endif()

# Add SQLite project
include_directories(${CMAKE_SOURCE_DIR}/third_party/sqlite/ SYSTEM)
add_subdirectory(third_party/sqlite)

# Create command line amo_tools_suite program
add_executable(amo_tools_suite_main main.cpp)
set_target_properties(amo_tools_suite_main PROPERTIES OUTPUT_NAME "amo_tools_suite")
target_link_libraries(amo_tools_suite_main amo_tools_suite)

if(BUILD_TESTING)
    add_library(Catch INTERFACE)
    target_include_directories(Catch INTERFACE third_party/catch/)
    add_executable(cpp_tests tests/cpp/main.unit.cpp ${TEST_FILES})
    target_link_libraries(cpp_tests Catch amo_tools_suite)
elseif(BUILD_WASM)
    add_executable(client ${SOURCE_FILES} ${SOURCE_FILES_WASM})
endif()

if(BUILD_PACKAGE)
  set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};amo_tools_suite;ALL;/")
  include(cmake/Install.cmake)
endif()
