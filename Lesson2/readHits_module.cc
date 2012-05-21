////////////////////////////////////////////////////////////////////////
// Class:       readHits
// Module Type: analyzer
// File:        readHits_module.cc
//
// Generated at Tue Oct 18 16:46:20 2011 by Adam Lyon using artmod
// from art v0_07_13.
//
//  We'll read in the hit information and make some histograms and 
//  a simple root-tuple. This module will make use of the "TFileService" to 
//  show how to manipulate and create things in a Root file. We'll
//  put the histograms and ntuple in different directories of the root file.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include "TH1F.h"
#include "TTree.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

#include "HitAndTrackObjects/HitCollection.hh"


namespace artex {
  class readHits;
}

class artex::readHits : public art::EDAnalyzer {
public:
  explicit readHits(fhicl::ParameterSet const &p);
  virtual ~readHits();

  virtual void analyze(art::Event const &e);


private:

    // Declare member data here.
    
    // Names of the sub-directories in the root file
    std::string hist_dir_, tree_dir_;
    
    // The histograms
    TH1F * h_weights_, * h_z_, * h_r_, * h_phi_; 
    
    // The root-tuple
    TTree * t_hitTree_;
    
    // Variables for the tree
    int tf_event_;
    float tf_r_, tf_phi_, tf_z_, tf_w_;
};


artex::readHits::readHits(fhicl::ParameterSet const &p) :
    hist_dir_( p.get<std::string>("hist_dir") ),
    tree_dir_( p.get<std::string>("tree_dir") )
{
    // You could require that hist_dir and tree_dir have some real strings, but what if the
    // user just leaves them blank. We then want to use the top level directory.
    // Note that the TFileService handle dereferences to an object that inherits from 
    // TFileDirectory. This will be a little tricky, so pay close attention
    
    // Get the service handle - dereferencing this will be an object that inherits
    // from TFileDirectory - so it can do the same things as TFileDirectory
    art::ServiceHandle<art::TFileService> tfs;
    
    // Do the histograms first. 
    // Let's assume the top directory. This is *tfs itself
    art::TFileDirectory histDir = *tfs;
    
    // Did we specify a directory, if so, reassign histDir to the new directory
    if ( ! hist_dir_.empty() ) {
        histDir = tfs->mkdir( hist_dir_ );  // Note how we re-assigned histDir
    }
    
    // Create the histogram objects
    h_weights_ = histDir.make<TH1F>("hitWeights", "Hit Weights", 25,    0.0,   1.0);
    h_z_       = histDir.make<TH1F>("hitZ",       "z of hits",   50, -100.0, 100.0);
    h_r_       = histDir.make<TH1F>("hitR",       "r of hits",   50,    0.0, 100.0);
    h_phi_     = histDir.make<TH1F>("hitPhi",     "phi of hits", 50,    0.0,   6.3);
    
    // Do the tree next
    art::TFileDirectory treeDir = *tfs;
    if ( ! tree_dir_.empty() ) {
        treeDir = tfs->mkdir( tree_dir_ );
    }
    
    t_hitTree_ = treeDir.make<TTree>("hitTree", "Tree of hits");
    t_hitTree_->Branch("event", &tf_event_, "event/I");
    t_hitTree_->Branch("r", &tf_r_, "r/F");
    t_hitTree_->Branch("phi", &tf_phi_, "phi/F");
    t_hitTree_->Branch("z", &tf_z_, "z/F");
    t_hitTree_->Branch("weights", &tf_w_, "weights/F");
}
    
artex::readHits::~readHits() {
  // Clean up dynamic memory and other resources here.
}

void artex::readHits::analyze(art::Event const &e) {
  
    // Extract the hits
    art::Handle< HitCollection > hitHandle;
    e.getByLabel("makeHits", hitHandle); // The name here is the producer label
    HitCollection const& hits = *hitHandle;
    
    // Loop over the hits
    for ( size_t i=0; i < hits.size(); ++i ) {
        
        // Get the hit
        Hit const& hit = hits[i];
        CLHEP::Hep3Vector const& position = hit.position();
        double weight = hit.weight();
        
        // Fill the plots
        h_weights_ -> Fill(weight                );
        h_r_       -> Fill(position.r(),   weight);
        h_phi_     -> Fill(position.phi(), weight);
        h_z_       -> Fill(position.z(),   weight);
        
        // Fill the tree
        tf_event_ = e.id().event();
        tf_r_ = position.r();
        tf_phi_ = position.phi();
        tf_z_ = position.z();
        tf_w_ = weight;
        
        t_hitTree_ -> Fill();
    }
    
}

DEFINE_ART_MODULE(artex::readHits);
