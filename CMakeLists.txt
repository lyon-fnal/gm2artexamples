# ======================================================================
#  gm2artexamples main build file
#
#  . mrb slp   # Run if you have local products to set up
#  . mrb s     # Needed to set up local development products
#  mrb b       # Build
#  mrb t       # Test (if applicable)
#  mrb i       # Install to local products
#  gm2 -c <fhicl_file>  # Run!
#
# ======================================================================

# use cmake 2.8 or later
cmake_minimum_required (VERSION 2.8)
project(gm2artexamples)

# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()

set(CMAKE_MODULE_PATH $ENV{ART_DIR}/Modules
		      $ENV{CETBUILDTOOLS_DIR}/Modules
		      ${CMAKE_MODULE_PATH})

include(CetCMakeEnv)
cet_cmake_env()

set_install_root()

# Add ART_MAKE_PREPEND_PRODUCT_NAME
set (ART_MAKE_PREPEND_PRODUCT_NAME TRUE)

cet_set_compiler_flags(DIAGS CAUTIOUS
     WERROR
     EXTRA_FLAGS -pedantic )

cet_report_compiler_flags()

# these are minimum required versions, not the actual product versions
find_ups_product( art v1_12_02 )
find_ups_product( clhep v2_2_0_3 )

find_ups_product( cetbuildtools v4_03_02 )

# macros for dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

# ADD SOURCE CODE SUBDIRECTORIES HERE
add_subdirectory( DataObjects )
add_subdirectory( fcl )
add_subdirectory( HitAndTrackObjects )
add_subdirectory( Lesson1 )
add_subdirectory( Lesson2 )
add_subdirectory( ups )
add_subdirectory( test )

# packaging utility
include(UseCPack)
