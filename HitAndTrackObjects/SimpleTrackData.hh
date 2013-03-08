// SimpleTrackData

// SimpleTrackData is an object that forms a track out of a group of hits

// We'll store @Ptr@ objects to the @HitData@. (see below)

#ifndef SIMPLETRACKDATA_HH
#define SIMPLETRACKDATA_HH

#include "art/Persistency/Common/PtrVector.h"

#include "HitAndTrackObjects/HitData.hh"

namespace artex {
  
  struct SimpleTrackData {
    
    // Let's just store a momemtum. Of course a real track will have more parameters
    double px, py, pz;
    
    // Now we want to have pointers to the hits in this track. We can't use actual
    // pointers, because Root can't store them. So we use @art::Ptr<>@ objects. These
    // will act like pointers. Since Tracks are made up of many hits, we really want a
    // @std::vector< art::Ptr< artex::HitData > >@. For convenience, Art provides a
    // shorthand to such a container called @art::PtrVector< artex::HitData >@ .
    art::PtrVector< artex::HitData >  hits;
    
    // Root needs a default constructor
    SimpleTrackData() {};
    
    // Hide the following member functions from Root
    #ifndef __GCCXML__
    
      // Regular constructor (where we pass everything in, including the @PtrVector@)
      SimpleTrackData(double ipx, double ipy, double ipz, const art::PtrVector<artex::HitData>& iHits) :
        px(ipx), py(ipy), pz(ipz),
        hits( iHits )
      {}
    
      // We should have a print method, but we don't have one yet (so we do not need a .cc file)
    
    #endif
  };
  
  // Define the collection of Simple Tracks
  typedef std::vector< artex::SimpleTrackData > SimpleTrackDataCollection;
  
}

// For more information on @art::Ptr@ and @art::PtrVector@ see
// "Mu2e Documetation":http://mu2e.fnal.gov/public/hep/computing/InterProductReferences.shtml#ptr .
// But note that the example code is overly confusing. NOvA's
// "Cluster object":https://cdcvs.fnal.gov/redmine/projects/novaart/repository/entry/trunk/RecoBase/Cluster.h is
// a simpler example.

#endif

// This file starts the @Ptr@ tutorial. If you are following along, go &l=HitAndTrackObjects/HitData.hh& next (where we had to add an @operator<@ method).