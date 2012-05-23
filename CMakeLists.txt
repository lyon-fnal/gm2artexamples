#  This file is the main CMakeLists.txt file for the @gm2artexamples@ package. 

# h2. Introduction 

#  Before running cmake, you must ensure that all external
#  packages are set up already (e.g. source all necessary setup
#  files, including the appropriate @setup_for_development@ script).

#  When you run cmake, you must run it from the build directory.
#  e.g. @cmake ../src@

#  If you are copying this project to use as a template for a new project, you will need to make some minor changes. The 
#  areas where you would have to do so are marked with -->

#  This most important place where you would have to add to this file
#  is at the bottom.

# h2. Main code


# Ensure we are using a moden version of CMake
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# h3. Project definition

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
                
# h3. Load build system modules

# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules 
                      $ENV{GM2SOFTWARETOOLS_DIR}/Modules
                      $ENV{ART_DIR}/
                      $ENV{CETBUILDTOOLS_DIR}/Modules 
                      ${CMAKE_MODULE_PATH})

include(CetCMakeEnv)

include(Gm2CMakeEnv)

include(CetMake)
include(CetTest)

# h3. Configure version

if ( NOT qualifier )
    message (FATAL_ERROR "ERROR: please call cmake with -Dqualifier:STRING=qualifier")
endif ( NOT qualifier )
cet_cmake_env( gm2artexamples v0_00_01 ${qualifier} )

cet_report_compiler_flags()

## Set the ups version
message(STATUS ${version})
set_version_from_ups( ${version} )

## Define the flavor (e.g. Linux x86_64)
set_flavor_qual()

message(STATUS "version will be ${version}")
message(STATUS "qualifier will be ${qualifier}")
message(STATUS "flavor will be ${UPSFLAVOR}")

# h3. Declare dependencies 

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
find_art_products ( )
find_my_products ( ) 
## --> You may have to add additional dependency checks here 
## like @find_ups_geant4( $ENV{GEANT4_VERSION} )@

# Let cmake define variables for external libraries and executables
#define FHICLCPP
find_library( FHICLCPP NAMES fhiclcpp PATHS $ENV{FHICLCPP_LIB} )

# Define CLHEP
find_library( CLHEP  NAMES CLHEP   PATHS $ENV{CLHEP_BASE}/lib )

# Define CETLIB
find_library( CETLIB NAMES cetlib PATHS $ENV{CETLIB_LIB} )

# Add some more includes
include_directories ( $ENV{LIBSIGCPP_INC}/sigc++-2.0 )
include_directories ( $ENV{LIBSIGCPP_LIB}/sigc++-2.0/include )

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

# h3. Specify subdirectories to build

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


