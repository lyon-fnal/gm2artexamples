// The @HelloWorld1@ ART module or plugin

// A very simple ART module example that simply prints a message
// with the event number for each event. 

// Note that ART modules are isolated - nothing else should ever depend
// on code in an ART module. Therefore, ART modules have no header (.hh) files.

// This module will be an *Analyzer*, that is the @analyze@ member function
// runs for each event. @analyze@ gets a @const@ reference to the event, which 
// means that it cannot store anything in the event. 

// The skeleton of this code was generated with 
// <pre>artmod analyzer artex::HelloWorld1</pre>
// (see "here":https://cdcvs.fnal.gov/redmine/projects/g-2/wiki/Artmod for information about @artmod@ )

// h3. Main code

// Include needed ART headers
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"

// Declare everything in a namespace
namespace artex {
    
   // h3. Class declaration

  // Declare the class for our analyzer, @HelloWorld1@. Note that it inherits
  // from @art::EDAnalyzer@, the base class for analyzers. 
  class HelloWorld1 : public art::EDAnalyzer {

  public:

    // The constructor. Note that the configuration parameters for this module
    // are passed in (and not used in this example). There is also a default constructor
    // not written because the compiler generated one is sufficient. <br />
    // <br />
    // See "here":http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml?showone=Explicit_Constructors#Explicit_Constructors for
    // information about the use of @explicit@. All single argument constructors (as is the case here) should be 
    // declared as @explicit@. 
    explicit HelloWorld1(fhicl::ParameterSet const& pset);

    // Declare the @analyze@ member function that runs on each event. Note the use of @override@.
    void analyze(const art::Event& event ) override;
      
    // Declare the destructor (as virtual in case someone inherits from this object)
    virtual ~HelloWorld1();
      
    // End the class declaration
  };
    
  // h3. Class implementation

  // Definition for constructor (it doesn't do anything)
  HelloWorld1::HelloWorld1(fhicl::ParameterSet const& ){
  }
    
  // Definition of the destructor (does nothing)
  HelloWorld1::~HelloWorld1() {}

  // Definition of the @analyze@ member function - run for each event. Note that the event is passed 
  // to the member function as a @const@ reference. That means that the event cannot be changed by the 
  // member function
  void HelloWorld1::analyze(const art::Event& event){
      
    // Write a message to the message facility. @mf::LogVerbatim@ writes the information
    // as it is presented ( @mf::LogInfo@ or similar will also print out information about the 
    // function from where it is called). The @"test"@ argument is the _category_ of the message. 
    // You can set the configuration of @MessageFacility@ to prescale or hide messages of particular
    // categotries. Note that we display the event identifier from the passed in @art::Event@ reference.
    mf::LogVerbatim("test") << "Hello, world. From analyze. " << event.id();
      
    // End the member function  
  }
    
// End of namespace artex
} 

// These are some necessary boilerplate for the ROOT persistency system
using artex::HelloWorld1;
DEFINE_ART_MODULE(HelloWorld1)
