// This is the makeSimpleTracksFromOldHits module

// This producer module takes hits *already* in the event and uses them to create simple
// tracks (@HitAndTrackObjects/SimpleTrackData@).

// Our goal is to learn about Ptr's. NOvA also has a nice example module
// "here":https://cdcvs.fnal.gov/redmine/projects/novaart/repository/entry/trunk/ClusterMakerSS/MakePlaneClusters.cxx

// Note that this is a very stupid nonsensical way to make tracks. The goal here is to explain
// the @Ptr@ concepts with an easy example. Certainly don't use this example to learn track finding!

// Art includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

// Include the header to our SimpleTrackData objects
#include "HitAndTrackObjects/SimpleTrackData.hh"
#include "HitAndTrackObjects/HitDataCollection.hh"

// Random number generator stuff
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/RandGaussQ.h"

// Put into the namespace
namespace artex {
  class MakeSimpleTracksFromOldHits;
}

class artex::MakeSimpleTracksFromOldHits : public art::EDProducer {
  
  public:
  
    // C'tor and D'tor
    explicit MakeSimpleTracksFromOldHits(fhicl::ParameterSet const &p);
    virtual  ~MakeSimpleTracksFromOldHits() {}
  
    // The Art methods
    virtual void produce(art::Event &e) override;
    virtual void endJob() override;
  
  private:
    // Declare member data here.
    // We need to hang onto the Random Number Engine since we are going to make two generators from it.
    // If you just had one generator, you could just store the generator itself instead of the engine.
    CLHEP::HepRandomEngine& engine_;
  
    // What cut to place on the hits for inclusion into the tracks
    float hitWeightGreaterThanThis_;

  // Parameters for finding the hits
    std::string hitsModuleLabel_;
    std::string hitsInstanceLabel_;
  
    unsigned int madeNTracks_;
    unsigned int madeNHitsOnTracks_;
    unsigned int nEvents_;
};

// Constructor
artex::MakeSimpleTracksFromOldHits::MakeSimpleTracksFromOldHits(fhicl::ParameterSet const &p) :
  engine_( createEngine(get_seed_value(p)) ),  // Use a "seed" parameter if there is one
  hitWeightGreaterThanThis_( p.get<float>("hitWeightGreaterThanThis", 0.5 )),
  hitsModuleLabel_( p.get<std::string>("hitsModuleLabel")),
  hitsInstanceLabel_( p.get<std::string>("hitsInstanceLabel")),
  madeNTracks_(0), madeNHitsOnTracks_(0), nEvents_(0)
{
  // We have to declare what this producer is producing
  produces< artex::SimpleTrackDataCollection > ();
}

// The produce method does all the work
void artex::MakeSimpleTracksFromOldHits::produce(art::Event &e) {
  
  // In reality, tracking finding is a complicated process. Here, we're just going to do something stupid
  // and pick hits and values semi-randomally. We really want to show how @Ptr@ works instead of tracking algorithms.
  
  // Make our random number generators
  CLHEP::RandFlat     flat(   engine_ );
  CLHEP::RandGaussQ   gauss(  engine_ );
  
  // Make the empty collection we're going to fill with our created tracks
  std::unique_ptr< SimpleTrackDataCollection > tracks( new SimpleTrackDataCollection );
  
  // Let's decide how many tracks to make
  unsigned int nTracks = flat.fireInt(5);
  
  mf::LogDebug("MakeSimpleTrackFromOldHits") << "Making " << nTracks << " tracks";
  
  // Let's pull the hits out of the event.
  art::Handle< HitDataCollection > hitsHandle;
  e.getByLabel( hitsModuleLabel_, hitsInstanceLabel_, hitsHandle );
  
  // Lopp to create the tracks
  for ( unsigned int iTrack = 0; iTrack < nTracks; iTrack++ ) {
    
    // Let's loop over the hits and randomally assign them to this track. We'll also
    // apply a cut on the weight of the hit.
    // Note that we're going to start out by making the hit a @Ptr@
    
    // Make an empty @PtrVector@ to hold the hits that will make up our track
    art::PtrVector< HitData > desiredHitPtrs;
    
    // Remember that @->@ on a handle pretends that it is a pointer to the object
    for ( unsigned int iHit = 0; iHit < hitsHandle->size(); iHit++ ) {
      
      // Pay close attention to how we're going to get the hit. We could simply
      // dereference the handle to get at the real hit collection vector and
      // loop over that. BUT, since we eventually want the Ptr to the hit to put
      // in the track, instead we'll make a @Ptr@ right off the bat. Since
      // @Ptr@ needs to know how to store data, it really wants to know about the
      // handle and where in the collection you are associating. Hence,
      art::Ptr< HitData > aHitPtr( hitsHandle, iHit );
      
      // Throw a random number to decide if we want this hit on the track, and also
      // cut on the hit weight (a value between zero and one).
      // Note how we use the @Ptr@ like a pointer. You can dereference it to get the real
      // @HitData@ object too (e.g. @HitData const & h = *aHitPtr;@ ), but we don't need to do that here.
      if ( flat.fire() > 0.5 && aHitPtr->weight > hitWeightGreaterThanThis_ ) {
        
        // Keep the hit - add the hit @Ptr@ to the PtrVector
        desiredHitPtrs.push_back( aHitPtr );
      }
    }
    
    // We've looped over all the hits. Did we get any (if not, then there's no track to make)?
    if ( ! desiredHitPtrs.empty() ) {
      
      // Make the track (with random numbers)
      double px = gauss.fire(-5.0, 10.0);
      double py = gauss.fire(-2.0, 2.0);
      double pz = gauss.fire(-8.0, 6.0);
      
      // Add this track to the @SimpleTrackCollection@. Remember that the constructor for
      // @SimpleTrack@ takes a @PtrVector@ of the hits that make it up.
      // Remember that @emplace_back@ calls the constructor and makes a @SimpleTrackData@ in the vector
      tracks->emplace_back(px, py, pz, desiredHitPtrs);
      
      // Add to counters
      madeNTracks_++;
      madeNHitsOnTracks_ += desiredHitPtrs.size();
      
    }
  }
  
  // Put the data into the event
  e.put( std::move(tracks) );
  
  nEvents_++;
}

// Art endJob method
void artex::MakeSimpleTracksFromOldHits::endJob() {
  
  // Let's print out some summary information
  mf::LogInfo("Track Construction Done") << "makeSimpleTracksFromOldHits produced " << madeNTracks_
                  << " tracks with a total of " << madeNHitsOnTracks_ << " hits on the tracks in "
                  << nEvents_ << " events";
  
}


// Better not forget the macro call
DEFINE_ART_MODULE(artex::MakeSimpleTracksFromOldHits)
