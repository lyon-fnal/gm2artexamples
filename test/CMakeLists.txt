# The cmake driver file for tests

# h3. Setup CMake

# Define the project
project( gm2artexamples_Tests )

# Include the CET test macro (mandatory)
include(CetTest)

# Link with the data objects library - we are going to test the objects in here
link_libraries( gm2artexamples_dataobjects )

# h3. Unit tests

# Test a little &l=test/very_simple_test.sh|test script&. The test script just needs to do something and return an exit code. If the exit code is zero, the test passes. Note that we use the @PREBUILT@ flag because we want to copy the script out of the soucrce tree and into the build area. 
cet_test( very_simple_test.sh PREBUILT )

# Test with a simple &l=test/simple_test.cc|C++ program&. It creates a @MyLittleDatum@ object from the @gm2artexamples_dataobjects@ library. The testing function sets the exit code non-zero if it fails. 
cet_test( simple_test )

# Test with BOOST UTF (unit test facility) and a &l=test/test_with_boost.cc|simple program&
cet_test( test_with_boost USE_BOOST_UNIT )

# h3. Integration tests

# Let's make a very simple integration test for the MyLittleDatum object by running ART with real 
# modules

# Define producer and analyzer modules (for code, see &l=test/MyLittleDatumProducer_module.cc& and &l=test/MyLittleDatumAnalyzer_module.cc& . Note that we use the @NOINSTALL@ flag since these files don't go into the release sysetm
simple_plugin( MyLittleDatumProducer "module" NOINSTALL )
simple_plugin( MyLittleDatumAnalyzer "module" NOINSTALL USE_BOOST_UNIT )

# Test writing data to the event and reading it back out again
# Here, HANDBUILT means that the modules and executables will already exist 
# and in the right places in the build directory or PATH. 
# Note that since we use MyLittleDatumAnalyzer, and that uses BOOST unit tests, we have to use
# @gm2_ut@ to get the testing library linked in. If you don't use @gm2_ut@, you'll get error
# messages like "can't use testing tools before framework is initialized". The fcl file we
# call is &l=test/fcl/MyLittleDatum_test.fcl&
cet_test(MyLittleDatum_test HANDBUILT
    TEST_EXEC gm2_ut
    TEST_ARGS --rethrow-all -c MyLittleDatum_test.fcl
    DATAFILES
        fcl/MyLittleDatum_test.fcl
        fcl/messageDefaults.fcl
)

# Another test where we write data to a file, and then read it back in again
# Here, PREBUILT means to copy an item out of the source tree (the script in this case) and run it. The fcl files we'll call are
# &l=test/fcl/MyLittleDatum_w.fcl& and &l=test/fcl/MyLittleDatum_r.fcl&
cet_test(myLittleDatum_wr.sh PREBUILT
    DATAFILES
        fcl/messageDefaults.fcl
        fcl/MyLittleDatum_r.fcl
        fcl/MyLittleDatum_w.fcl
)
