////////////////////////////////////////////////////////////////////////
// Class:       ProduceMyLittleDatum
// Module Type: producer
// File:        ProduceMyLittleDatum_module.cc
//
// Generated at Mon Sep 19 00:56:40 2011 by Adam Lyon using artmod
// from art v0_07_13.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"

#include "DataObjects/MyLittleDatum.hh"
#include <vector>

using namespace std;

namespace artex {
    class ProduceMyLittleDatum;
}

class artex::ProduceMyLittleDatum : public art::EDProducer {
public:
    explicit ProduceMyLittleDatum(fhicl::ParameterSet const &p);
    virtual ~ProduceMyLittleDatum();
    
    virtual void produce(art::Event &e);
    
    
private:
    
    // Declare member data here.
    
};


artex::ProduceMyLittleDatum::ProduceMyLittleDatum(fhicl::ParameterSet const &p)
// :
// Initialize member data here.
{
    // Call appropriate Produces<>() functions here.
    // Note that if you wanted to produce more than one of these in the same
    // event, give an 'instance name' in the arguments. 
    produces< vector< artex::MyLittleDatum > >();
}

artex::ProduceMyLittleDatum::~ProduceMyLittleDatum() {
    // Clean up dynamic memory and other resources here.
}

void artex::ProduceMyLittleDatum::produce(art::Event &e) {
    //Create an empty data product (note, the space between the > > is important!)
    auto_ptr< vector< artex::MyLittleDatum> > datums(new vector<artex::MyLittleDatum>);
    
    // Fill it
    datums->push_back( MyLittleDatum(3.14) );
    datums->push_back( MyLittleDatum(1.15) );
    datums->push_back( MyLittleDatum(2.93) );
    datums->push_back( MyLittleDatum(19.93) );
    
    // Put it in the event
    e.put( datums );    
    
    // Let's write a little log message
    mf::LogVerbatim("test") << "Wrote datum for event " << e.id();
}

DEFINE_ART_MODULE(artex::ProduceMyLittleDatum);
