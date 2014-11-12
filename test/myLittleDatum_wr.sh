#!/bin/bash
# A test that creates a datafile with MyLittleDatum and then reads is back in

# Load some helper functions
. cet_test_functions.sh

# FHICL_FILE_PATH just has .
# Need to add minimalMessageService.fcl from the build fcl
# This script typically runs in <build_dir>/gm2artexamples/test/myLittleDatum_wr.sh.d,
#   so the fcl areas should be two levels up
export FHICL_FILE_PATH=$FHICL_FILE_PATH:../../fcl

# Remove old stuff
rm -f data01.root cerr.log warnings.log

# Set the ART command we want to use
export ART_EXEC=gm2

# Run the producer that will make the file
run_art MyLittleDatum_w.fcl --rethrow-all

# Did we make the output file?
check_files "data01.root"

# Run the analyzer -- this has BOOST tests in it, so we need gm2_ut
export ART_EXEC=gm2_ut
run_art MyLittleDatum_r.fcl --rethrow-all