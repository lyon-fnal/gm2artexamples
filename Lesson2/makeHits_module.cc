////////////////////////////////////////////////////////////////////////
// Class:       makeHits
// Module Type: producer
// File:        makeHits_module.cc
//
// Generated at Tue Oct 18 16:45:58 2011 by Adam Lyon using artmod
// from art v0_07_13.
//
//  This producer makes hits (see HitAndTrackObjects/Hit.hh). What we'll do 
//  is we'll draw the x,y,z positions from random gaussians, and we'll draw the weight from
//  a flat random number. We'll decide how many hits to make with another flat random number. 
//
//  This module is a little unusual because we're going to have two random number
//  generators (Gaussian and Flat) based off of the same engine. To do this, we need
//  to store the engine as member data. Typically, if you
//  need random numbers you would need only one generator (e.g. Flat) and then you 
//  can store the generator without having to store the engine. See the 
//  "makeTracks" producer for this simpler situation. 
//
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"

// Include the header to our Hit objects
#include "HitAndTrackObjects/HitCollection.hh"

// Random number generator stuff
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/RandGaussQ.h"


namespace artex {
  class makeHits;
}

class artex::makeHits : public art::EDProducer {
public:
  explicit makeHits(fhicl::ParameterSet const &p);
  virtual ~makeHits();

  virtual void produce(art::Event &e);
  virtual void endJob();


private:

    // Declare member data here.
    // We need to hang onto the Random Number Engine since we are going to make two generators from it.
    // If you just had one generator, you would not need to keep the Engine
    CLHEP::HepRandomEngine& engine_;
    
    // The Flat random number generator
    CLHEP::RandFlat* flat_;
    
    // The Gaussian random number generator
    CLHEP::RandGaussQ* gauss_;    
    
    // Just for fun, let's add up how many hits we made
    unsigned int nHits_;
    
    // And count the number of events we saw
    unsigned int nEvents_;
};


artex::makeHits::makeHits(fhicl::ParameterSet const &p)
     : engine_( createEngine(get_seed_value(p)) ), // If there is a "seed" parameter for this module, it will be used
       nHits_(0),
       nEvents_(0)
{
    // Make the random number generators
    // Note that I can't put this in the initialization list (after the : above) because
    // the order of execution of those initializations is not guaranteed. 
    // So put them in the body of the constructor and it'll do what you want. The only sad
    // thing about this is that the member data have to be pointers. 
    flat_ = new CLHEP::RandFlat( engine_ );
    gauss_ = new CLHEP::RandGaussQ( engine_ );
    
    // Call appropriate Produces<>() functions here.
    produces< HitCollection >();
}

artex::makeHits::~makeHits() {
    // Clean up dynamic memory and other resources here.
    delete flat_;
    delete gauss_;
}

void artex::makeHits::produce(art::Event &e) {
    // Make a place to put hits
    std::auto_ptr< HitCollection > hits( new HitCollection );
    
    // Let's decide how many hits we want to make (maximum of 100)
    int nHits = flat_->fireInt(100);
    
    // Debug
    LOG_DEBUG("HitConstruction") << "Making " << nHits << " hits";
    
    // Loop to fill
    for ( unsigned int i=0; i <= nHits; ++i ) {
        
        // We want to fill a hit, make the components!
        double x = gauss_->fire(-5.0,  10.0 );  // Mean = -5, sd=10
        double y = gauss_->fire( 5.0,  10.0 );  // Mean = +5, sd=10
        double z = gauss_->fire( 0.0,  20.0 );  // Mean =  0, sd=20
        double w = flat_->fire();  // (0,1)

        // Some debug output - note that I use a different category here so that
        // these message are suppressed differently
        LOG_DEBUG("HitConstructionSub") << "x=" << x << " y=" << y << " z=" << z << " w=" << w;
        
        // Make the hit and push it into the collection
        hits->push_back( Hit( CLHEP::Hep3Vector( x, y, z ), w ) );  
        
        // Increment our counter (just for diagnostics; note that nHits_ is not the same
        // variables as nHits)
        nHits_++;
    }
    
    // Put the hits into the event (don't forget this!)
    e.put( hits );
    
    // Increment event counter (just for diagnostics)
    nEvents_++;
}

void artex::makeHits::endJob() {
   // Let's print out some summary information
   mf::LogInfo("HitConstructionDone") << "makeHits produced " << nHits_ << " hits in " <<
                                          nEvents_ << " events";

   
}


DEFINE_ART_MODULE(artex::makeHits);
