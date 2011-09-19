//
//  classes.h
//  gm2artexamples-xcode
//
//  Created by Adam Lyon on 9/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>

#include "art/Persistency/Common/Wrapper.h"

#include "DataObjects/MyLittleDatum.hh"

// Vectors go here
template class std::vector< artex::MyLittleDatum >;
template class art::Wrapper< std::vector< artex::MyLittleDatum > >;