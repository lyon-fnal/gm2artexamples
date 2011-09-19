//
//  classes.h
//  gm2artexamples-xcode
//
//  Created by Adam Lyon on 9/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>

#include "art/Persistency/Common/Wrapper.h"

#include "DataObjects/MyLittleDatumCollection.hh"

// template the vector (do not use the typedef)
template class std::vector< MyLittleDatumCollection >;
// template the wrapper for the vector (typedef ok)
template class art::Wrapper< MyLittleDatumCollection >;