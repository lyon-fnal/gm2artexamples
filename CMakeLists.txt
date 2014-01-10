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
# Add g-2 modules
#set(CMAKE_MODULE_PATH $ENV{GM2SOFTWARETOOLS_DIR}/Modules ${CMAKE_MODULE_PATH} )


# Include the necessary macros
include(CetCMakeEnv)
include(BuildPlugins)
include(ArtDictionary)

# Configure
cet_cmake_env()

# Set compiler flags
cet_set_compiler_flags( DIAGS VIGILANT WERROR
   EXTRA_FLAGS -pedantic
   EXTRA_CXX_FLAGS -std=c++11
)
cet_have_qual( sse2 SSE2 )
if ( SSE2 )
  cet_add_compiler_flags(CXX -msse2 -ftree-vectorizer-verbose=2)
endif()

cet_report_compiler_flags()

# Locate some UPS areas (the versions are just minimum required) and set up include paths
find_ups_product(cetbuildtools v3_06_02)

find_ups_product(cpp0x v1_03_23)
find_ups_product(cppunit v1_12_1)
find_ups_product(clhep v2_1_3_1)
find_ups_product(cetlib v1_03_23)
find_ups_product(gccxml v0_9_20130621)
find_ups_product(art v1_08_04)
find_ups_product(fhiclcpp v2_17_10)
find_ups_product(messagefacility v1_10_24)
find_ups_root( v5_34_09 )
find_ups_boost( v1_53_0 )

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
