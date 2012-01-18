// Do a simple test with boost tools.
// See "here":http://www.boost.org/doc/libs/1_48_0/libs/test/doc/html/utf.html for more information

// Define the test module to Boost and load the utf header
#define BOOST_TEST_MODULE (test_with_boost)
#include "boost/test/auto_unit_test.hpp"

// Include header for MyLittleDatum
#include "DataObjects/MyLittleDatum.hh"

// Define the test suite
BOOST_AUTO_TEST_SUITE ( test_with_boost )

// Test the default constructor
BOOST_AUTO_TEST_CASE ( default_constructor )
{
    artex::MyLittleDatum a;
    BOOST_REQUIRE_EQUAL( a.datum(), 0 );
}

// Test the constructor with an argument
BOOST_AUTO_TEST_CASE ( constructor_with_argument )
{
    artex::MyLittleDatum b(25.2);
    BOOST_REQUIRE_CLOSE( b.datum(), 25.2, 0.0001 );
}

// Declare the end of the test suite (don't forget this line)
BOOST_AUTO_TEST_SUITE_END()