CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# project name - use all lowercase)
PROJECT (gm2artexamples)

set( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
if( NOT CETBUILDTOOLS_VERSION )
  message( FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules" )
endif()
set( CMAKE_MODULE_PATH $ENV{CETBUILDTOOLS_DIR}/Modules ${CMAKE_MODULE_PATH} )

# art contains cmake modules that we use
set( ART_VERSION $ENV{ART_VERSION} )
if( NOT ART_VERSION )
  message( FATAL_ERROR "ERROR: setup art to get the cmake modules" )
endif()
set( CMAKE_MODULE_PATH $ENV{ART_DIR}/Modules ${CMAKE_MODULE_PATH} )

# Include the necessary macros
include(CetCMakeEnv)
include(BuildPlugins)
include(ArtMake)

# Configure
cet_cmake_env()

#set_install_root()

# Set compiler flags
cet_set_compiler_flags( DIAGS VIGILANT
   WERROR
   EXTRA_FLAGS -pedantic
   EXTRA_CXX_FLAGS -std=c++11
)

cet_report_compiler_flags()

# Locate some UPS areas (the versions are just minimum required) and set up include paths
find_ups_product(cetbuildtools v3_07_00)

find_ups_product(art v1_08_04)

# Make sure we have gcc
cet_check_gcc()

include(ArtDictionary) # this must come after find_ups_products

# --> Build these directories
add_subdirectory( DataObjects )
add_subdirectory( fcl )
add_subdirectory( HitAndTrackObjects )
add_subdirectory( Lesson1 )
add_subdirectory( Lesson2 )
add_subdirectory( ups )
add_subdirectory( test )

# Packaging facility
include(UseCPack)
