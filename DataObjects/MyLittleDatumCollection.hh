// Implementation of the @MyLittleDatumCollection@ _typedef_

#ifndef GM2ARTEXAMPLES_MYLITTLEDATUMCOLLECTION_HH
#define GM2ARTEXAMPLES_MYLITTLEDATUMCOLLECTION_HH

#include <vector>
#include "DataObjects/MyLittleDatum.hh"

// Enclose in a namespace so that the typedef becomes @artex::MyLittleDatumCollection@
namespace artex {

    // Make a _typedef_ for a _vector_ of @MyLittleDatum@ so we don't have to type @std::vector < blah >@ everywhere.
    // Note that we still use the @artex@ namespace for the typedef.
    typedef std::vector< artex::MyLittleDatum > MyLittleDatumCollection;
}

#endif
