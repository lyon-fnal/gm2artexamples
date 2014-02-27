// This is the ReadSimpleTracks Art module.

//  This is an analyzer that will read SimpleTrackData from the event and make some plots

// Art includes
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

// Root + Art includes
#include "TH1F.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

// Hit includes
#include "HitAndTrackObjects/HitDataCollection.hh"
#include "HitAndTrackObjects/Hit.hh"

// Simple track includes
#include "HitAndTrackObjects/SimpleTrackData.hh"

// Namespace
namespace artex {
  class ReadSimpleTracks;
}

// The class
class artex::ReadSimpleTracks : public art::EDAnalyzer {
public:
  explicit ReadSimpleTracks(fhicl::ParameterSet const &p);
  virtual ~ReadSimpleTracks();
  
  virtual void analyze(art::Event const &e) override;
  
  
private:
  
  // Declare member data here
  
  // To find the hit data, we need the name of the module that produced it and an
  // instance name. Note that we don't need to directly access the hit collection, so
  // we don't need those labels. 
  std::string trackModuleLabel_;
  std::string trackInstanceLabel_;
  
  // Name of the sub-directories in the root file
  std::string hist_dir_;
  
  // The histograms
  TH1F *h_nHits_, *h_hit_weight_, *h_track_px_, *h_track_py_, *h_track_pz_;
  
};


artex::ReadSimpleTracks::ReadSimpleTracks(fhicl::ParameterSet const &p) :
  art::EDAnalyzer(p),
trackModuleLabel_   ( p.get<std::string>("trackModuleLabel",  "TrackMaker"   ) ),
trackInstanceLabel_ ( p.get<std::string>("trackInstanceName",  ""     ) ),
hist_dir_           ( p.get<std::string>("hist_dir",           "") )
{
  // You could require that hist_dir has some real strings, but what if the
  // user just leaves them blank. We then want to use the top level directory.
  // Note that the TFileService handle dereferences to an object that inherits from
  // TFileDirectory. This will be a little tricky, so pay close attention
  
  // Get the service handle - dereferencing this will be an object that inherits
  // from TFileDirectory - so it can do the same things as TFileDirectory
  art::ServiceHandle<art::TFileService> tfs;

  // Get the top level directory (has name of the module label of this module)
  art::TFileDirectory histDir = *tfs;
  
  // Did we specify a directory? If so, reassign histDir to the new directory
  if ( ! hist_dir_.empty() ) {
    histDir = tfs->mkdir( hist_dir_ );  // Note how we re-assigned histDir
  }
  
  // Create the histogram objects
  h_nHits_       = histDir.make<TH1F>("nHits",     "Number of htis on track", 50,    0.5,  49.5);
  h_hit_weight_  = histDir.make<TH1F>("hitWeight", "Hit Weight",              50,    0.0,   1.0);
  h_track_px_    = histDir.make<TH1F>("trackPx",   "px of tracks",            50, -100.0, 100.0);
  h_track_py_    = histDir.make<TH1F>("trackPy",   "py of tracks",            50, -100.0, 100.0);
  h_track_pz_    = histDir.make<TH1F>("trackPz",   "pz of tracks",            50, -100.0, 100.0);
}

artex::ReadSimpleTracks::~ReadSimpleTracks() {
}

void artex::ReadSimpleTracks::analyze(art::Event const &e) {
  
  // Extract the hits:
  
  // Make the handle
  art::Handle< SimpleTrackDataCollection > trackCollectionHandle;
  
  // Fill the handle (note the use of the member data)
  e.getByLabel(trackModuleLabel_, trackInstanceLabel_, trackCollectionHandle);
  
  // Resolve the handle
  SimpleTrackDataCollection const & tracks = *trackCollectionHandle;
  
  // Let's use the nice C++11 vector iteration
  for ( auto aTrack : tracks) {
    
    // Fill histograms
    h_track_px_  -> Fill( aTrack.px );
    h_track_py_  -> Fill( aTrack.py );
    h_track_pz_  -> Fill( aTrack.pz );
    
    // Fill the hit information. Simply use the @hits@ member of @SimpleTrack@
    h_nHits_     -> Fill( aTrack.hits.size() );
    
    // Loop over those hits. The @aTrack.hits@ @PtrVector@ acts like a regular vector,
    // so we can use the nice range for feature of C++11
    for ( auto aHit : aTrack.hits ) {
      h_hit_weight_ -> Fill( aHit->weight );
    }
  }
}

DEFINE_ART_MODULE(artex::ReadSimpleTracks)
