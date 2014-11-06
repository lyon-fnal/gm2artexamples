// MyLittleDatumProducer_module.cc

// Create a MyLittleDatum for testing

// Art includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

#include <string>

// Include for MyLittleDatum
#include "DataObjects/MyLittleDatumCollection.hh"

// Declare the namespace
namespace artextest {
    class MyLittleDatumProducer;
}

// The producer class
class artextest::MyLittleDatumProducer : public art::EDProducer {
    
public:
    explicit MyLittleDatumProducer(fhicl::ParameterSet const &p);
    virtual ~MyLittleDatumProducer();
    
    virtual void produce(art::Event &e);
};

// The constructor
artextest::MyLittleDatumProducer::MyLittleDatumProducer(fhicl::ParameterSet const &)
{
    // Tell Art what we are producing
    produces<artex::MyLittleDatumCollection>();
}

// Destructor
artextest::MyLittleDatumProducer::~MyLittleDatumProducer() {
}

// Produce method (put the data into the event)
void artextest::MyLittleDatumProducer::produce(art::Event &e) {
    auto datums = std::make_unique< artex::MyLittleDatumCollection >();
    
    // Fill it with some bogus values. We'll put four values in the vector (e.g. like having
    // four hits)
    datums->emplace_back( 3.14 );
    e.put(std::move(datums));
}

// Standard boiler plate
DEFINE_ART_MODULE(artextest::MyLittleDatumProducer)
