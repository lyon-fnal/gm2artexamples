//  classes.h

#include <vector>

#include "art/Persistency/Common/Wrapper.h"

#include "HitAndTrackObjects/HitDataCollection.hh"

// template the vector (do not use the typedef)
template class std::vector< artex::HitData >;

// template the wrapper for the vector (typedef ok)
template class art::Wrapper< artex::HitDataCollection >;