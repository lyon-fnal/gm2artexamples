//  classes.h
//
//  Created by Adam Lyon on 9/19/11.
//

#include <vector>

#include "art/Persistency/Common/Wrapper.h"

#include "HitAndTrackObjects/HitCollection.hh"

// template the vector (do not use the typedef)
template class std::vector< artex::Hit >;

// template the wrapper for the vector (typedef ok)
template class art::Wrapper< HitCollection >;