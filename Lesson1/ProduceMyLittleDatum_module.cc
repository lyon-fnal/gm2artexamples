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
#include "art/Framework/Principal/Event.h"

// Include the header for the data object ( @artex::MyLittleDatumCollection@)
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
    
    // The @produce@ member function is called on every event
    virtual void produce(art::Event &e) override;
    
private:
    
    // End the class declaration
};

// The constructor
artex::ProduceMyLittleDatum::ProduceMyLittleDatum(fhicl::ParameterSet const &)
{
    // Every object we want to put into the event must have a 
    // @produces@ call like the one below
    produces< artex::MyLittleDatumCollection >();
}

// Definition of the @produce@ member function. Runs on each event. Note that we get a 
// _nonconst_ @art::Event@ reference. So we can change it by adding new data
void artex::ProduceMyLittleDatum::produce(art::Event &e) {
    
    // Create an empty data product (in this case a @artex::MyLittleDatumCollection@
    std::unique_ptr< artex::MyLittleDatumCollection > datums(new artex::MyLittleDatumCollection);
    
    // Fill it with some bogus values. We'll put four values in the vector (e.g. like having
    // four hits)
    datums->push_back( MyLittleDatum(3.14) );
    datums->push_back( MyLittleDatum(1.15) );
    datums->push_back( MyLittleDatum(2.93) );
    datums->push_back( MyLittleDatum(19.93) );
    
    // Put it in the event
    e.put( std::move(datums) );    
    
    // Let's write a little log message
    mf::LogVerbatim("test") << "Wrote data for event " << e.id();
    
    // End the @produce@ member function
}

// The regular boilerplate
DEFINE_ART_MODULE(artex::ProduceMyLittleDatum)
