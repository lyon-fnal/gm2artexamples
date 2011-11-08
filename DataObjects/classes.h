// Root dictionary file for @MyLittleDatum@ and @MyLittleDatumCollection@

// We will store @MyLittleDatumCollection@ into the event. To do that, we need
// to tell _ROOT_ (the persistency mechanism) details about our class. We
// do this by implementing special templates.

// We need to implement two templates:
// # The vector we want to store itself (we cannot use a _typedef_ here)
// # A @wrapper@ of the vector (we can use the _typedef_ for this case). The @wrapper@ template will bring in code that will allow @ROOT@ to store instances of the object

// Note we use the @wrapper@ for the thing we *want to store*. Had we been storing one individual @MyLittleDatum@, we
// would need a @wrapper@ for it as well

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
template class art::Wrapper< MyLittleDatumCollection >;