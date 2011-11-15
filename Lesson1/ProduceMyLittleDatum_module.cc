// The @ProduceMyLittleDatum@ ART module

// This ART module creates data (@MyLittleDatum@ objects) and puts them into the event.
// This ART module is a *producer*

// The skeleton of this code was generated with 
// <pre>artmod producer artex::ProduceMyLittleDatum</pre>
// (see "here":https://cdcvs.fnal.gov/redmine/projects/g-2/wiki/Artmod for information about @artmod@ )

// h3. Main code

// Include the needed ART headers
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"

// Include the header for the data object (@artex::MyLittleDatumCollection@)
#include "DataObjects/MyLittleDatumCollection.hh"

// Set up the namespace
namespace artex {
    class ProduceMyLittleDatum;
}

// h3. Class declaration
// Since we are putting data into the event, we use a _producer_
class artex::ProduceMyLittleDatum : public art::EDProducer {
    
public:
    
    // Constructor and destructor
    explicit ProduceMyLittleDatum(fhicl::ParameterSet const &p);
    virtual ~ProduceMyLittleDatum();
    
    // The @produce@ member function is called on every event
    virtual void produce(art::Event &e);
    
private:
    
    // End the class declaration
};

artex::ProduceMyLittleDatum::ProduceMyLittleDatum(fhicl::ParameterSet const &p)
// :
// Initialize member data here.
{
    // Call appropriate Produces<>() functions here.
    // Note that if you wanted to produce more than one of these in the same
    // event, give an 'instance name' in the arguments. 
    produces< artex::MyLittleDatumCollection >();
}

artex::ProduceMyLittleDatum::~ProduceMyLittleDatum() {
    // Clean up dynamic memory and other resources here.
}

void artex::ProduceMyLittleDatum::produce(art::Event &e) {
    //Create an empty data product
    auto_ptr< artex::MyLittleDatumCollection > datums(new artex::MyLittleDatumCollection);
    
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
