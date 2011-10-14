//  classes.h
//
//  Created by Adam Lyon on 9/19/11.
//

#include <vector>

#include "art/Persistency/Common/Wrapper.h"

#include "DataObjects/MyLittleDatumCollection.hh"

// template the vector (do not use the typedef)
template class std::vector< MyLittleDatumCollection >;
// template the wrapper for the vector (typedef ok)
template class art::Wrapper< MyLittleDatumCollection >;