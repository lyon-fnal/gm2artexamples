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
    
    // Do stuff
    void doStuff( artex::MyLittleDatumCollection const& datumVector ) const;
        
private:
    
    // End the class declaration
};

// Definition of the constructor which doesn't do anything
artex::MyDatumReader::MyDatumReader(fhicl::ParameterSet const &p) 
  : art::EDAnalyzer(p)
{}

// Definition of the destructor which doesn't do anything
artex::MyDatumReader::~MyDatumReader() {}

// Definition of the @analyze@ member function
void artex::MyDatumReader::analyze(art::Event const &e) {
    
    // Retreive data from the event. Note that @InputTag@ that tells art what data we want (matching the type specified).
    // The input tag in this case is the _label_ of the producer that created it. You get this from the @makeDatum.fcl@ file. 
    // Normally, we would pass this label in as a parameter. 
    auto datumVectorH = e.getValidHandle<artex::MyLittleDatumCollection>( art::InputTag("makeDatumB") );
   
    doStuff(*datumVectorH);
}

void artex::MyDatumReader::doStuff( artex::MyLittleDatumCollection const& datumVector ) const {
    
    // Let's create a logger
    mf::LogInfo log("test");
    
    // @datumVector@ is the vector of @MyLittleDatum@ objects. Show the size
    log << "Number of datums in list = " << datumVector.size() << "\n";
    
    // Loop over the vector and show the data. Note the use of @size_t@ 

    for (size_t i=0; i<datumVector.size(); ++i) {
        log << "   " << datumVector[i].datum << "\n";
    }

    // A better way is to use the C++11 Range-based for
    for ( auto const& d : datumVector ) {
        log << " " << d.datum << "\n";
    }
}

// Usual boilerplate
DEFINE_ART_MODULE(artex::MyDatumReader)
