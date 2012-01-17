#!/bin/bash
# A test that creates a datafile with MyLittleDatum and then reads is back in

# Load some helper functions
. cet_test_functions.sh

# Remove old stuff
rm -f data01.root cerr.log warnings.log

# Set the ART command we want to use
export ART_EXEC=gm2_ut

# Run the producer that will make the file
run_art MyLittleDatum_w.fcl --rethrow-all

# Did we make the output file?
check_files "data01.root"

# Run the analyzer -- this has BOOST tests in it, so we need gm2_ut
run_art MyLittleDatum_r.fcl --rethrow-all