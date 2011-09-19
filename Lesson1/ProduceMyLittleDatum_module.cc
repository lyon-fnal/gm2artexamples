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

#include "DataObjects/MyLittleDatumCollection.hh"

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
    produces<MyLittleDatumCollection>();
}

artex::ProduceMyLittleDatum::~ProduceMyLittleDatum() {
  // Clean up dynamic memory and other resources here.
}

void artex::ProduceMyLittleDatum::produce(art::Event &e) {
    //Create an empty data product
    auto_ptr<MyLittleDatumCollection> datums(new MyLittleDatumCollection);
    datums->push_back( MyLittleDatum(3.14) );
    
    e.put( datums );    
}

DEFINE_ART_MODULE(artex::ProduceMyLittleDatum);
