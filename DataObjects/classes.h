// Root dictionary file for @MyLittleDatum@ and @MyLittleDatumCollection@

// We will store @MyLittleDatumCollection@ into the event. To do that, we need
// to tell _ROOT_ (the persistency mechanism) details about our class. We
// do this by implementing special templates.

// We need to implement two templates:
// # The vector we want to store itself (we cannot use a _typedef_ here)
// # A @wrapper@ of the vector (we can use the _typedef_ for this case). The @wrapper@ template will bring in code that will allow @ROOT@ to store instances of the object

// Note we use the @wrapper@ for the thing we *want to store*. So we need to do a wrapper for the vector of @MyLittleDatum@ (we can use our @MyLittleDatumCollection@ typedef). Since we never store an individual instance of @MyLittleDatum@ (it's always in a vector), we do not need to wrap @MyLittleDatum@ itself. 

// h3. Main code

// We need to include @vector@ because we will use it below
#include <vector>

// Include definitions of the special templates
#include "art/Persistency/Common/Wrapper.h"

// Include our @MyLittleDatumCollection@ header
#include "DataObjects/MyLittleDatumCollection.hh"

// Template the vector (do not use the _typedef_) here)
template class std::vector< artex::MyLittleDatum >;

// Template the wrapper for the vector ( _typedef_ ok here)
template class art::Wrapper< artex::MyLittleDatumCollection >;

// If you are following the tutorial, go on to &l=DataObjects/classes_def.xml&.