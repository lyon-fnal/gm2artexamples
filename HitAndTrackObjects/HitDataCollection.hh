//
//  HitDataCollection.hh
//
//  Created by Adam Lyon on 10/19/11.
//
//  typedef the vector of hit data to make things easier
//

#ifndef gm2artexamples_HitDataCollection_hh
#define gm2artexamples_HitDataCollection_hh

#include <vector>
#include "HitAndTrackObjects/HitData.hh"

// Make a typedef for the vector
namespace artex {
    typedef std::vector< artex::HitData > HitDataCollection;
}

#endif
