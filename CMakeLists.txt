#  This file is the main CMakeLists.txt file for the @gm2artexamples@ package. 

#  Before running cmake, you must ensure that all external
#  packages are set up already (e.g. source all necessary setup
#  files, including the appropriate @setup_for_development@ script).

#  When you run cmake, you must run it from the build directory.
#  e.g. @cmake ../src@

#  You typically only have to make minor changes to this file. The 
#  areas where you would have to do so are marked with -->

#  This most important place where you would have to add to this file
#  is at the bottom.

# h3. Main code


# Ensure we are using a moden version of CMake
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# --> Define the name of this project (replace @gm2artexamples@ with your 
# project name - use all lowercase)
PROJECT (gm2artexamples)
set (product gm2artexamples)

message(STATUS "--- BUILDING ${product} FROM ${PROJECT_SOURCE_DIR} --- ")

# Determine the version hash or tag from git. This calls
# a script @git-version-gen.sh@ in @$GM2SOFTWARETOOLS_DIR/bin/@ ( @setup gm2@ puts it in your path)
execute_process(COMMAND git-version-gen.sh
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                OUTPUT_VARIABLE version
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# --> If you want a qualifier (typically not) then add it here
SET (qualifier "")

# Load in some Cmake helper modules - some gymnastics follow
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Modules)

# We use CMake modules from the @CETBUILDTOOLS@ area
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()
set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules")
set(CMAKE_MODULE_PATH $ENV{CETBUILDTOOLS_DIR}/Modules $ENV{ART_FQ_DIR}/Modules ${CMAKE_MODULE_PATH})
message(STATUS "module path is ${CMAKE_MODULE_PATH}" )


# Set the install prefix from the environment variable (typically set in the local setup script)
#IF ($ENV{CMAKE_INSTALL_PREFIX} )
  SET ( CMAKE_INSTALL_PREFIX $ENV{CMAKE_INSTALL_PREFIX} )
#ENDIF($ENV{CMAKE_INSTALL_PREFIX} )

message(STATUS "Install prefix is ${CMAKE_INSTALL_PREFIX}")

# Because we want to move these libraries about,
# do not embed full path in shared libraries or executables
set (CMAKE_SKIP_RPATH)

# Make sure we know where gcc is and require it
set( GCC_VERSION $ENV{GCC_VERSION} )
if ( NOT GCC_VERSION )
  message(FATAL_ERROR "Can't locate GCC_VERSION, required for building ToyCmake")
endif ()

## Load some external cmake modules that we'll use later
include (FindUpsPackage)
include(FindUpsBoost)
include(FindUpsRoot)
include( SetFlavorQual )
include(ParseUpsVersion)
include(EnsureOutOfSourceBuild)
include(CetMake)

## Make sure someone isn't typing cmake in the source code tree
cet_ensure_out_of_source_build()

## Set the ups version
message(STATUS ${version})
set_version_from_ups( ${version} )

## Define the flavor (e.g. Linux x86_64)
set_flavor_qual()

message(STATUS "version will be ${version}")
message(STATUS "qualifier will be ${qualifier}")
message(STATUS "flavor will be ${UPSFLAVOR}")

# Use cmake directive include_directories to define include search path

# We want to be able to #include "MyProduct/MyHeader.h" in source code,
# generated code, and user code.
# We achieve this by putting all headers into a MyProduct subdirectory
# instead of an include subdirectory.
# @PROJECT_SOURCE_DIR@ is a cmake variable which points to the top of the
# source code tree.
include_directories ("${PROJECT_SOURCE_DIR}")

# Generated code will be created in the build directory,
# so we also add PROJECT_BINARY_DIR to the include search path.
# This step may be omitted if there are no generated headers.
include_directories ("${PROJECT_BINARY_DIR}")

# Check for dependencies
find_ups_product( gccxml $ENV{GCCXML_VERSION} )
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
find_ups_boost( v1_47_0 filesystem
                        program_options
                        regex
                        thread
                        unit_test_framework
)

## --> You may have to add additional dependency checks here 
## like @find_ups_geant4( $ENV{GEANT4_VERSION} )@

# Let cmake define variables for external libraries and executables
#define FHICLCPP
find_library( FHICLCPP NAMES fhiclcpp PATHS $ENV{FHICLCPP_LIB} )

# Define CLHEP
find_library( CLHEP  NAMES CLHEP   PATHS $ENV{CLHEP_BASE}/lib )

# Define CETLIB
find_library( CETLIB NAMES cetlib PATHS $ENV{CETLIB_LIB} )

# Building all libraries and binaries in a single lib and bin directory
# is useful for a complex product like art.
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Build all executables in a single directory
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

## Include cmake modules that define "simple_plugin" and other tools
include(BuildPlugins)
include(ArtDictionary)

# Include the packaging utility
include(UseCPack)

# Test scripts and stuff will be placed in the build/bin area. Since this product doesn't
# normally have a bin area (it makes a library), we need to create one here
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# --> You have to tell Cmake about *EVERY* subdirectory that contains 
# directories or files to build. If you don't, cmake will ignore those subdirectories
# and you will be sad. The order does not really matter (but it is the order of building, which
# should not really matter because CMake will figure out the dependencies)
add_subdirectory(ups)
add_subdirectory(fcl)
add_subdirectory(Lesson1)
add_subdirectory(DataObjects)
add_subdirectory(HitAndTrackObjects)
add_subdirectory(Lesson2)
add_subdirectory(test)


