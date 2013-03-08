// This is the makeSimpleTracksFromNewHits module

// This producer module makes hits and uses them to create simple
// tracks (@HitAndTrackObjects/SimpleTrackData@). The point here is to
// create @Ptr@ for object not already in the event. It is not clear if you
// would ever really want to do this in one module, but let's learn
// how to do it anyway.

// Art includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

// Include the header to our SimpleTrackData objects
#include "HitAndTrackObjects/SimpleTrackData.hh"
#include "HitAndTrackObjects/HitDataCollection.hh"
#include "HitAndTrackObjects/Hit.hh"


// Random number generator stuff
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/RandGaussQ.h"

// Put into the namespace
namespace artex {
  class MakeSimpleTracksFromNewHits;
}

class artex::MakeSimpleTracksFromNewHits : public art::EDProducer {
  
public:
  
  // C'tor and D'tor
  explicit MakeSimpleTracksFromNewHits(fhicl::ParameterSet const &p);
  virtual  ~MakeSimpleTracksFromNewHits() {}
  
  // The Art methods
  virtual void produce(art::Event &e) override;
  virtual void endJob() override;
  
private:
  // Private
  // Declare member data here.
  // We need to hang onto the Random Number Engine since we are going to make two generators from it.
  // If you just had one generator, you could just store the generator itself instead of the engine.
  CLHEP::HepRandomEngine& engine_;
  
  // What cut to place on the hits
  float hitWeightGreaterThanThis_;
  
  unsigned int madeNHits_;
  unsigned int madeNTracks_;
  unsigned int madeNHitsOnTracks_;
  unsigned int nEvents_;

};

// Constructor
artex::MakeSimpleTracksFromNewHits::MakeSimpleTracksFromNewHits(fhicl::ParameterSet const &p) :
engine_( createEngine(get_seed_value(p)) ),  // Use a "seed" parameter if there is one
hitWeightGreaterThanThis_( p.get<float>("hitWeightGreaterThanThis", 0.5 )),
madeNHits_(0), madeNTracks_(0), madeNHitsOnTracks_(0), nEvents_(0)
{
  // We hae to declare what this producer is producing
  produces< artex::HitDataCollection > ();
  produces< artex::SimpleTrackDataCollection > ();
}

// The produce method does all the work
void artex::MakeSimpleTracksFromNewHits::produce(art::Event &e) {
  
  // In reality, tracking finding is a complicated process. Here, were just going to do something stupid
  // and pick hits and values randomally. We really want to show how @Ptr@ works instead of tracking algorithms.
  
  // Make our random number generators
  CLHEP::RandFlat     flat(   engine_ );
  CLHEP::RandGaussQ   gauss(  engine_ );
  
  // Make the empty collections
  std::unique_ptr< HitDataCollection >         hits(   new HitDataCollection );
  std::unique_ptr< SimpleTrackDataCollection > tracks( new SimpleTrackDataCollection );
  
  // Let's decide how many hits we want to make (maximum of 100)
  unsigned int nHits = flat.fireInt(100);
  
  // Debug
  mf::LogDebug("HitConstruction") << "Making " << nHits << " hits";
  
  // Loop to fill
  for (unsigned int i=0; i <= nHits; ++i ) {
    
    // We want to fill a hit, make the components!
    double x = gauss.fire(-5.0,  10.0 );  // Mean = -5, sd=10
    double y = gauss.fire( 5.0,  10.0 );  // Mean = +5, sd=10
    double z = gauss.fire( 0.0,  20.0 );  // Mean =  0, sd=20
    double w = flat.fire();  // (0,1)
    
    // Save our hit
    hits->emplace_back( x, y, z, w );
    
    madeNHits_++;
  }
  
  // We have our hits - note that we cannot put then into the event yet. If we did, we would
  // need to use @std::move@ on the @std::unique_ptr@ which would reset the pointer!
  
  // In order to make @Ptr@ out of the hits, we need the collection product ID (this is what @Ptr@ actually stores).
  // We have an ID reserved for us, so let's get it
  art::ProductID hitCollectionID( getProductID<HitDataCollection>(e) );
  
  // Let's decide how many hit to make
  unsigned int nTracks = flat.fireInt(5);
  
  mf::LogDebug("MakeSimpleTrackFromNewHits") << "Making " << nTracks << " tracks";
  
  // Loop over the tracks we're going to make
  for ( unsigned int iTrack = 0; iTrack < nTracks; iTrack++ ) {
    
    // Let's loop over the hits and randomally assign them to this track.
    // Note that we're going to start out by making the hit a @Ptr@

    // Make an empty @PtrVector@ to hold the hits we're going to want for our track
    art::PtrVector< HitData > desiredHitPtrs;
    
    // We'll loop over our hit collection (remember, here @hits@ is a @std::unique_ptr@)
    for ( unsigned int iHit = 0; iHit < hits->size(); iHit++ ) {
      
      // Hits have a weight between zero and one. Let's pick hit that have weight > 0.5.
      // Again, we have the real hit here.
      if ( ((*hits)[iHit]).weight > hitWeightGreaterThanThis_ ) {
        
        // We want this hit. Now we need to make a Ptr out of it. Since the hit isn't in the event
        // yet, we'll pass to the constructor of Ptr a deferred function that can get the hit information
        // after it goes into the event
        art::Ptr< HitData > aHitPtr( hitCollectionID, iHit, e.productGetter(hitCollectionID) );
        
        // Keep the hit - add the hit @Ptr@ to my vector
        desiredHitPtrs.push_back( aHitPtr );
      }
    }
    
    // We've looped over all the hits. Did we get any?
    if ( desiredHitPtrs.size() > 0 ) {
      
      // Make the track (with random numbers)
      double px = gauss.fire(-5.0, 10.0);
      double py = gauss.fire(-2.0, 2.0);
      double pz = gauss.fire(-8.0, 6.0);
      
      // Remember that @emplace_back@ calls the constructor and makes a @SimpleTrackData@ in the vector
      tracks->emplace_back(px, py, pz, desiredHitPtrs);
      
      // Add to counters
      madeNTracks_++;
      madeNHitsOnTracks_ += desiredHitPtrs.size();
      
    } // if have hits
    
  } // for over tracks

  // Put the data into the event
  e.put( std::move(hits) );
  e.put( std::move(tracks) );
  
  nEvents_++;
}

void artex::MakeSimpleTracksFromNewHits::endJob() {
  // Let's print out some summary information
  mf::LogInfo("Track Construction Done") << "makeSimpleTracksFromNewHits produced " << madeNHits_ << " hits and " <<
             madeNTracks_ << " tracks with a total of " << madeNHitsOnTracks_ << " hits on the tracks in " << nEvents_ << " events";
}

// Better not forget the macro call
DEFINE_ART_MODULE(artex::MakeSimpleTracksFromNewHits)
