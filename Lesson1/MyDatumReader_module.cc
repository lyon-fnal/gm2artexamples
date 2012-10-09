// The @MyDatumReader@ ART module

// An example ART module that reads in data produced by 
// the @ProduceMyLittleDatum@ module. It gets the @artex::MyLittleDatumCollection@ from the 
// event and displays it.


// The skeleton of this code was generated with 
// <pre>artmod analyzer artex::MyDatumReader</pre>
// (see "here":https://cdcvs.fnal.gov/redmine/projects/g-2/wiki/Artmod for information about @artmod@ )

// h3. Main code

// Include needed ART headers
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

// Include the header for the data object (@artex::MyLittleDatumCollection@)
#include "DataObjects/MyLittleDatumCollection.hh"

// Set up the namespace
namespace artex {
    class MyDatumReader;
}

// h3. Class declaration
// Since we are reading the data, we use an _analyzer_
class artex::MyDatumReader : public art::EDAnalyzer {
    
public:
    
    // Constructor and destructor
    explicit MyDatumReader(fhicl::ParameterSet const &p);
    virtual ~MyDatumReader();
    
    // The usual @analyze@ member function
    virtual void analyze(art::Event const &e) override;
        
private:
    
    // End the class declaration
};

// Definition of the constructor which doesn't do anything
artex::MyDatumReader::MyDatumReader(fhicl::ParameterSet const &) {}

// Definition of the destructor which doesn't do anything
artex::MyDatumReader::~MyDatumReader() {}

// Definition of the @analyze@ member function
void artex::MyDatumReader::analyze(art::Event const &e) {
    

    // Retrieving data from the event requires (at least) three steps. Here they are...
    
    // 1. Create a templated @art::Handle@ that will hold a "pointer" to the data in the event ( _pointer_ is 
    // in quotes because the Handle is more complicated, but we will use it like a pointer)
    art::Handle< artex::MyLittleDatumCollection > datumHandle;
    
    // 2. Load the handle with the data in the event. We use the Event's @getByLabel@ member function. 
    // You supply the _label_ and the handle of the data you want to load. The _label_ is the label of the 
    // producer that created the data in the producer @.fcl@ file. In this case, it is @makeDatumB@ -- see the @makeDatum.fcl@
    // file. Calling @getByLabel@ will fill the @datumHandle@
    e.getByLabel("makeDatumB", datumHandle);
    
    // 3. With @datumHandle@ filled by the above step, we can now extract the the data itself by dereferencing the handle 
    // (like a pointer). Note that we have to use a *const* reference. 
    artex::MyLittleDatumCollection const& datumVector = *datumHandle;
    
    // Let's create a logger
    mf::LogInfo log("test");
    
    // @datumVector@ is the vector of @MyLittleDatum@ objects. Show the size
    log << "Number of datums in list = " << datumVector.size() << "\n";
    
    // Loop over the vector and show the data. Note the use of @size_t@ 
    for (size_t i=0; i<datumVector.size(); ++i) {
        log << "   " << datumVector[i].datum << "\n";
    }
    
    // End the @analyze@ member function
}

// Usual boilerplate
DEFINE_ART_MODULE(artex::MyDatumReader)
