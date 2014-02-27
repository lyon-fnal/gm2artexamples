// The @HelloWorld2@ ART module

// Another simple ART module that handles a configuration parameter and
// prints a message for each event

// See @HelloWorld1@ for more basic information.

// The skeleton of this code was generated with 
// <pre>artmod analyzer artex::HelloWorld2</pre>
// (see "here":https://cdcvs.fnal.gov/redmine/projects/g-2/wiki/Artmod for information about @artmod@ )

// h3. Main code

// Include needed ART headers
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Run.h"

// Here is a differnet way to handle the namespace (compare to @HelloWorld1_module.cc@)
namespace artex {
  class HelloWorld2;
}

// h3. Class declaration
class artex::HelloWorld2 : public art::EDAnalyzer {

public:

  // Constructor and destructor
  explicit HelloWorld2(fhicl::ParameterSet const &p);
  virtual ~HelloWorld2();

  // h4. Member function declaration
    
  // @beginJob@ runs when the ART job starts  
  virtual void beginJob() override;
    
  // @beginRun@ runs when ART advances into a new run  
  virtual void beginRun(art::Run const &run) override;
    
  // @analyze@ runs for every event  
  virtual void analyze(art::Event const &e) override;
    
  // @endJob@ runs at the end of the ART job
  virtual void endJob() override;
    
// h4. Member data
private:

  // This ART module will hold a configuration parameter, @magicNumber@. In real life, 
  // one would use such a value as input to some algorithm or something like that
  int m_magicNumber;


  // End the class declaration
};

// Definition of the constructor. Note the contructor is passed in the configuration parameter
// set for this module (parameters are set in the @.fcl@ file. Note the use of the colon to 
// initialize the one member datum of the class ( @m_magicNumber@ ). The configuration parameter set,
// @fhicl::ParameterSet@, is passed in as a @const@ reference as the @p@ argument. @fhicl::ParameterSet@ has 
// a templated member function, @get&lt;&gt;@, that is used to retrieve parameter values. The template argument
// is the type of the value, @int@ in this case. The function argument is the name of the parameter in the
// @.fcl@ file. 
artex::HelloWorld2::HelloWorld2(fhicl::ParameterSet const &p) :
  art::EDAnalyzer(p),
  m_magicNumber(p.get<int>("magicNumber")) 
{
  // Let's print out a little message on construction
  mf::LogVerbatim("test") << "HelloWorld2::constructor - "
                          << "Magic number is " << m_magicNumber
                          << std::endl;
}

// Definition of the destructor. We don't do anything here, but you would use this to clean up
// dynamically allocated memory and other resources.
artex::HelloWorld2::~HelloWorld2() {}

// Definition of @beginJob@. Note that we print the module parameter that we stored
void artex::HelloWorld2::beginJob(){
  mf::LogVerbatim("test") << "HelloWorld2::beginJob - "
                          << "Magic number is " << m_magicNumber
                          << std::endl;
}

// Definition of @beginRun@
void artex::HelloWorld2::beginRun(art::Run const& run){
  mf::LogVerbatim("test") << "HelloWorld2::beginRun -"
                          << " Run info is " << run.id().run()
                          << " Magic number is " << m_magicNumber
                          << std::endl;
}

// Definition of @analyze@
void artex::HelloWorld2::analyze(art::Event const &e) {
  mf::LogVerbatim("test") << "HelloWorld2::analyze -"
                          << " Event info is " << e.id()
                          << " Magic number is " << m_magicNumber
                          << std::endl;

}

// Definition of @endJob@
void artex::HelloWorld2::endJob(){
  mf::LogVerbatim("test") << "HelloWorld2::endJob - "
                          << "Magic number is " << m_magicNumber
                          << std::endl;
}

// Some boiler plate for the Art system. Note that the namespace is handled
// differently here than in @HelloWorld1@
DEFINE_ART_MODULE(artex::HelloWorld2)
