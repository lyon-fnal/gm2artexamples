// This is the readHits Art module. 

//  This is an analyzer that will read HitData from the event and make some plots and a root tree

// Art includes
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

// Root + Art includes
#include "TH1F.h"
#include "TTree.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

// Hit includes
#include "HitAndTrackObjects/HitDataCollection.hh"
#include "HitAndTrackObjects/Hit.hh"

// Namespace
namespace artex {
  class readHits;
}

// The class
class artex::readHits : public art::EDAnalyzer {
public:
  explicit readHits(fhicl::ParameterSet const &p);
  virtual ~readHits();

  virtual void analyze(art::Event const &e) override;


private:

    // Declare member data here.

    // To find the hit data, we need the name of the module that produced it and an 
    // instance name. 
    std::string hitModuleLabel_;
    std::string instanceName_;
    
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
    hitModuleLabel_ ( p.get<std::string>("hitModuleLabel",  "HitDataMaker"   ) ),
    instanceName_   ( p.get<std::string>("instanceName",    ""     ) ),
    hist_dir_       ( p.get<std::string>("hist_dir"         ) ),
    tree_dir_       ( p.get<std::string>("tree_dir"         ) )
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
    
    // Did we specify a directory? If so, reassign histDir to the new directory
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
    
    // Create the tree
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

    // Make the handle
    art::Handle< HitDataCollection > hitDataHandle;

    // Fill the handle (note the use of the member data)
    e.getByLabel(hitModuleLabel_, instanceName_, hitDataHandle);

    // Resolve the handle
    HitDataCollection const & hits = *hitDataHandle;

    // Let's use the nice C++11 vector iteration
    for ( auto hdata : hits) {
        
        // h is a hitdata in the collection. Wrap it in our facade
        Hit h(hdata);
        
        // Get the weight. Let's not worry about the type and use @auto@
        auto weight = h.weight();

        // Fill the plots
        h_weights_ -> Fill(weight                );
        h_r_       -> Fill(h.position().r(),   weight);
        h_phi_     -> Fill(h.position().phi(), weight);
        h_z_       -> Fill(h.position().z(),   weight);
        
        // Fill the tree
        tf_event_ = e.id().event();
        tf_r_ = h.position().r();
        tf_phi_ = h.position().phi();
        tf_z_ = h.position().z();
        tf_w_ = h.weight();
        
        t_hitTree_ -> Fill();
    }
    
}

DEFINE_ART_MODULE(artex::readHits)
