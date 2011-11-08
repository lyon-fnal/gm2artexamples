// Implementation of the @MyLittleDatumCollection@ _typedef_

#ifndef GM2ARTEXAMPLES_MYLITTLEDATUMCOLLECTION_HH
#define GM2ARTEXAMPLES_MYLITTLEDATUMCOLLECTION_HH

#include <vector>
#include "DataObjects/MyLittleDatum.hh"

// Make a _typedef_ for a _vector_ of @MyLittleDatum@ so we don't have to type @std::vector@ everywhere
typedef std::vector< artex::MyLittleDatum > MyLittleDatumCollection;

#endif
