//  HitDataCollection.hh

//  typedef the vector of hit data to make things easier

#ifndef gm2artexamples_HitDataCollection_hh
#define gm2artexamples_HitDataCollection_hh

#include <vector>
#include "HitAndTrackObjects/HitData.hh"

// Make a typedef for the vector
namespace artex {
    typedef std::vector< artex::HitData > HitDataCollection;
}

#endif
