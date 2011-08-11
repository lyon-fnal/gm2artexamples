#
#  gm2softwaretools/CMakeLists.txt
#
#  CMake build file for gm2artexamples
#
#  install steps:
#  cd /path/to/build/directory
#  source /path/to/gm2artexamples/ups/setup_for_development
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path] $GM2SOFTWARETOOLS_SOURCE
#  make install
#  make package (tar file for ups)

## Here we assume that art and its dependents are already setup

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (gm2artexamples)
set (product gm2artexamples)

message(STATUS "--- BUILDING ${product} FROM ${PROJECT_SOURCE_DIR} --- ")

## Set the version from git
## Set the version from git
execute_process(COMMAND git-version-gen.sh
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                OUTPUT_VARIABLE version
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# We don't want a qualifier
SET (qualifier "")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Modules)

# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()
set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules")
set(CMAKE_MODULE_PATH $ENV{CETBUILDTOOLS_DIR}/Modules $ENV{ART_FQ_DIR}/Modules ${CMAKE_MODULE_PATH})
message(STATUS "module path is ${CMAKE_MODULE_PATH}" )

#IF ($ENV{CMAKE_INSTALL_PREFIX} )
  SET ( CMAKE_INSTALL_PREFIX $ENV{CMAKE_INSTALL_PREFIX} )
#ENDIF($ENV{CMAKE_INSTALL_PREFIX} )

message(STATUS "Install prefix is ${CMAKE_INSTALL_PREFIX}")

# because we want to move these libraries about,
# do not embed full path in shared libraries or executables
set (CMAKE_SKIP_RPATH)

# require GCC
set( GCC_VERSION $ENV{GCC_VERSION} )
if ( NOT GCC_VERSION )
  message(FATAL_ERROR "Can't locate GCC_VERSION, required for building ToyCmake")
endif ()

# define some necessary modules
include (FindUpsPackage)
include(FindUpsBoost)
include(FindUpsRoot)
include( SetFlavorQual )
include(ParseUpsVersion)
include(EnsureOutOfSourceBuild)
include(CetMake)

# make sure someone isn't typing cmake in the source code tree
cet_ensure_out_of_source_build()

# Set the ups version
message(STATUS ${version})
set_version_from_ups( ${version} )

# Define the flavor
set_flavor_qual()

message(STATUS "gm2 version will be ${version}")
message(STATUS "gm2 qualifier will be ${qualifier}")
message(STATUS "gm2 flavor will be ${UPSFLAVOR}")

# Use cmake directive include_directories to define include search path

# We want to be able to #include "MyProduct/MyHeader.h" in source code,
# generated code, and user code.
# We achieve this by putting all headers into a MyProduct subdirectory
# instead of an include subdirectory.
# PROJECT_SOURCE_DIR is a cmake variable which points to the top of the
# source code tree.
include_directories ("${PROJECT_SOURCE_DIR}")

# Generated code will be created in the build directory,
# so we also add PROJECT_BINARY_DIR to the include search path.
# This step may be omitted if there are no generated headers.
include_directories ("${PROJECT_BINARY_DIR}")

# Check for dependencies
find_ups_product( gccxml $ENV{GCCXML_VERSION} )
# find_ups_boost takes a minimum required version and an optional list of boost libraries
# this will also define the ROOT library variables
find_ups_product( art $ENV{ART_VERSION} )
find_ups_product (messagefacility $ENV{MESSAGEFACILITY_VERSION} )
find_ups_product( fhiclcpp $ENV{FHICLCPP_VERSION}  )
find_ups_product( cetlib $ENV{CETLIB_VERSION} )
find_ups_product( libsigcpp $ENV{LIBSIGCPP_VERSION} )
include_directories( $ENV{LIBSIGCPP_INC}/sigc++-2.0 )
include_directories( $ENV{LIBSIGCPP_LIB}/sigc++-2.0/include )
include_directories( $ENV{CLHEP_INC} )
find_ups_product( cpp0x $ENV{CPP0X_VERSION} )
find_ups_root( $ENV{ROOT_VERSION} )
find_ups_boost( $ENV{BOOST_VERSION} )

# let cmake define variables for external libraries and executables

# define FHICLCPP
find_library( FHICLCPP NAMES fhiclcpp PATHS $ENV{FHICLCPP_LIB} )

# define CLHEP
find_library( CLHEP  NAMES CLHEP   PATHS $ENV{CLHEP_BASE}/lib )

# define CETLIB
find_library( CETLIB NAMES cetlib PATHS $ENV{CETLIB_LIB} )

# Building  all libraries and binaries in a single lib and bin directory
# is useful for a complex product like art.
# You may not want to do this for smaller products.

#build all libraries in a single directory
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

#build all executables in a single directory
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# The environment has been established, now generate the Makefiles.

include(BuildPlugins)
include(ArtDictionary)


# Pickup  the ups directory
subdirs(ups)

subdirs(HelloWorld1)
subdirs(fcl)

# packaging utility
include(UseCPack)
