# cmake driver file for tests

# Define the project
project( gm2artexamples_Tests )

# Include the CET test macro
include(CetTest)

# Link with the data objects library
link_libraries( gm2artexamples_dataobjects )

# Test a little test script
cet_test( toot_a_test.sh PREBUILT )

# Test with a simple C++ program
cet_test( simple_test )

