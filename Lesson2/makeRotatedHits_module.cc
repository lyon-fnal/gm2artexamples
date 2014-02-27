// This is the makeHits Art module. 

//  This producer makes hits (see HitAndTrackObjects/HitData.hh). What we'll do 
//  is we'll draw the x,y,z positions from random gaussians, and we'll draw the weight from
//  a flat random number. To make things even more complicated, we'll rotate the 3 vector.
//  We'll decide how many hits to make with another flat random number. 

// Art includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

// Include the header to our Hit objects
#include "HitAndTrackObjects/HitDataCollection.hh"
#include "HitAndTrackObjects/Hit.hh"

// Random number generator stuff
#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/RandGaussQ.h"

// Put into the namespace
namespace artex {
  class makeRotatedHits;
}

// The class
class artex::makeRotatedHits : public art::EDProducer {
public:

  // C'tor and D'tor
  explicit makeRotatedHits(fhicl::ParameterSet const &p);
  virtual ~makeRotatedHits() {};

  // Art methods
  virtual void produce(art::Event &e) override;
  virtual void endJob() override;


private:

    // Declare member data here.
    // We need to hang onto the Random Number Engine since we are going to make two generators from it.
    // If you just had one generator, you could just store the generator itself instead of the engine. 
    CLHEP::HepRandomEngine& engine_;
    
    // Just for fun, let's add up how many hits we made
    unsigned int nHits_;
    
    // And count the number of events we saw
    unsigned int nEvents_;
};


// The constructor
artex::makeRotatedHits::makeRotatedHits(fhicl::ParameterSet const &p)
     : engine_( createEngine(get_seed_value(p)) ), // If there is a "seed" parameter for this module, it will be used
       nHits_(0),
       nEvents_(0)
{
    // Every object we want to put into the event must have a 
    // @produces@ call like the one below
    produces< artex::HitDataCollection >() ;
}


// The Art produce method
void artex::makeRotatedHits::produce(art::Event &e) {

    // Let's make flat and gaussian random number generators
    CLHEP::RandFlat     flat(   engine_ );
    CLHEP::RandGaussQ   gauss(  engine_ );

    // Make a place to put hits
    std::unique_ptr< artex::HitDataCollection > hits( new artex::HitDataCollection );
    
    // Let's decide how many hits we want to make (maximum of 100)
    unsigned int nHits = flat.fireInt(100);
    
    // Debug
    LOG_DEBUG("HitConstruction") << "Making " << nHits << " hits";
    
    // Loop to fill
    for ( unsigned int i=0; i <= nHits; ++i ) {
        
        // We want to fill a hit, make the components!
        double x = gauss.fire(-5.0,  10.0 );  // Mean = -5, sd=10
        double y = gauss.fire( 5.0,  10.0 );  // Mean = +5, sd=10
        double z = gauss.fire( 0.0,  20.0 );  // Mean =  0, sd=20
        double w = flat.fire();  // (0,1)

        // Some debug output - note that I use a different category here so that
        // these message are suppressed differently
        LOG_DEBUG("HitConstructionSub") << "x=" << x << " y=" << y << " z=" << z << " w=" << w;

        // Make a @CLHEP::Hep3Vector@
        CLHEP::Hep3Vector v( x, y, z);

        // Roate it
        const CLHEP::Hep3Vector & rotated = v.rotateZ( flat.fire(6.0) );

        // Use this to create a hit
        Hit aHit( rotated, w);

        // Add it to the vector
        hits->emplace_back( aHit.data() );
 
        // Increment our counter (just for diagnostics; note that nHits_ is not the same
        // variables as nHits)
        nHits_++;
    }
    
    // Put the hits into the event (don't forget this!). Note that hits is a @unique_ptr@. These smart 
    // pointers cannot be assigned. You must use @std::move@. Note that @unique_ptr@ replaces @auto_ptr@ in
    // C++2011
    e.put( std::move(hits) );
    
    // Increment event counter (just for diagnostics)
    nEvents_++;
}

// endJob method
void artex::makeRotatedHits::endJob() {
   // Let's print out some summary information
   mf::LogInfo("HitConstructionDone") << "makeRotatedHits produced " << nHits_ << " hits in " <<
                                          nEvents_ << " events";

   
}

// The important macro call
DEFINE_ART_MODULE(artex::makeRotatedHits)
