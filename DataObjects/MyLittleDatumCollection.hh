// Implementation of the @MyLittleDatumCollection@ _typedef_

// You will typically store more than one instance of an object in the event. For example, you have a @Hit@ object that holds one hit. But in reality, the event will have one or more hits. So what you will store into the event is a @vector@ of @Hit@ objects. This @typedef@ makes it easier to refer to the vector. 

#ifndef GM2ARTEXAMPLES_MYLITTLEDATUMCOLLECTION_HH
#define GM2ARTEXAMPLES_MYLITTLEDATUMCOLLECTION_HH

// Necessary includes

#include <vector>
#include "DataObjects/MyLittleDatum.hh"

// Enclose in a namespace so that the typedef becomes @artex::MyLittleDatumCollection@
namespace artex {

    // Make a _typedef_ for a _vector_ of @MyLittleDatum@ so we don't have to type @std::vector < blah >@ everywhere.
    // Note that we still use the @artex@ namespace for the typedef.
    typedef std::vector< artex::MyLittleDatum > MyLittleDatumCollection;
}

#endif

// If you are following the tutorial, go to the &l=DataObjects/classes.h& file next.
