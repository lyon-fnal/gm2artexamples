//  classes.h

#include <vector>

#include "art/Persistency/Common/Wrapper.h"

// --- For HitDataCollection
#include "HitAndTrackObjects/HitDataCollection.hh"

// template the vector (do not use the typedef)
template class std::vector< artex::HitData >;

// template the wrapper for the vector (typedef ok)
template class art::Wrapper< artex::HitDataCollection >;

// --- For SimpleTrackDataCollection
#include "HitAndTrackObjects/SimpleTrackData.hh"

// template the vector (can't typedef here)
template class std::vector< artex::SimpleTrackData >;

// template the wrapper (typdef ok)
template class art::Wrapper< artex::SimpleTrackDataCollection >;

// template the constituent Ptr to HitData
template class art::Ptr< artex::HitData >;

// template the vector of ptrs (can't typedef)
template class std::vector< art::Ptr< artex::HitData > >;

// template the wrapper of the ptr vector (typedef ok)
template class art::Wrapper< art::PtrVector< artex::HitData > >;

// If you are following the @Ptr@ tutorial, go to &l=HitAndTrackObjects/classes_def.xml& next.
