// This is a very simple test showing how you can use a simple test function that 
// sets the exit code

// Let's test @MyLittleDatum@

// Include cstdlib to get std::exit
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

// Include header for MyLittleDatum
#include "DataObjects/MyLittleDatum.hh"

// Here's the function that does the work! Test the claim and exit if fails
void ensure( int which, const std::string message, bool claim ) {
    // If test fails, show message and exit
    if ( not claim ) {
        std::cerr << "TEST FAILED: " << message << std::endl;
        std::exit(which);
    }
}

// The main function
int main () {
    
    // Test the default constructor
    artex::MyLittleDatum a;
    ensure(1, "Default constructor", a.datum == 0 );
    
    // Test the constructor with an argument
    artex::MyLittleDatum b(25.2);
    ensure(2, "Constructor with argument", fabs(b.datum - 25.2) < 0.00001 );
}