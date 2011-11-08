// Implementation file for the @MyLittleDatum@ class

#include <iostream>

#include "DataObjects/MyLittleDatum.hh"

// Implementation of the @print@ member function. Note the use of the @artex@ 
// namespace
void artex::MyLittleDatum::print( std::ostream& ost ) const {
    ost << "MyLittleDatum: value = " << datum();
}
