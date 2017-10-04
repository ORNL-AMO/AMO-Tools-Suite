set( CPACK_PACKAGE_VENDOR "US Department of Energy" )

set(CPACK_PACKAGE_VENDOR "Oak Ridge National Laboratory")
set(CPACK_PACKAGE_CONTACT "Gina Accawi <accawigk@ornl.gov>")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/Modules")

set(CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_VERSION_MAJOR}" )
set(CPACK_PACKAGE_VERSION_MINOR "${CMAKE_VERSION_MINOR}" )
set(CPACK_PACKAGE_VERSION_PATCH "${CMAKE_VERSION_PATCH}" )
set(FULL_VERSION_STRING "${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}.${CMAKE_VERSION_PATCH}")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "AMO Suite is a cross-platform collection of calculations and tools to support industrial equipment modeling.")

# set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/CPack.Description.txt")
# set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/CPack.Description.txt")
# set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/CPack.Welcome.txt")

set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "AMO Suite\n ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://code.ornl.gov/g9a/amo-library")
set(CPACK_DEBIAN_PACKAGE_SECTION "science")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/cmake/debian/postinst")

include(cmake/TargetArch.cmake)
target_architecture(TARGET_ARCH)

if ( "${CMAKE_BUILD_TYPE}" STREQUAL "" OR "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${TARGET_ARCH}")
else()
  set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${TARGET_ARCH}-${CMAKE_BUILD_TYPE}")
endif()

set(CPACK_PACKAGING_INSTALL_PREFIX "/${CMAKE_PROJECT_NAME}")

if( WIN32 AND NOT UNIX )
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
  include(InstallRequiredSystemLibraries)
  if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
    install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION "./")
  endif()
endif()

install(FILES "${CMAKE_SOURCE_DIR}/LICENSE.txt" DESTINATION "./")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")

install(TARGETS amo_tools_suite
        ARCHIVE
        DESTINATION lib
        COMPONENT libraries)

# Install header files
INSTALL(DIRECTORY include/
        DESTINATION include/
        COMPONENT headers
        PATTERN CMakeLists.txt EXCLUDE
)

INSTALL(FILES third_party/sqlite/sqlite3.h
        DESTINATION include/sqlite
        COMPONENT headers
        )

#install(FILES "${CMAKE_DATABASE_OUTPUT_DIRECTORY}/amo_tools_suite.db" DESTINATION "./db/")

set(CPACK_COMPONENTS_ALL libraries headers)
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")

set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
        "Static libraries used to build programs with AMO Suite")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
        "C/C++ header files for use with AMO Suite")

set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)

#if ( BUILD_DOCUMENTATION )
#	install(FILES "${CMAKE_BINARY_DIR}/doc" DESTINATION "./doc")
#endif ()

INCLUDE(CPack)

