////////////////////////////////////////////////////////////////////////
// Class:       HelloWorld2
// Module Type: analyzer
// File:        HelloWorld2_module.cc
//
// Generated at Fri Aug 12 11:40:14 2011 by Adam Lyon using artmod
// from art v0_07_13.
////////////////////////////////////////////////////////////////////////

// Generated by artmod analyzer artex::HelloWorld2

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"

// A different way to handle the namespace
namespace artex {
  class HelloWorld2;
}

class artex::HelloWorld2 : public art::EDAnalyzer {
public:
  // Constructor and destructor
  explicit HelloWorld2(fhicl::ParameterSet const &p);
  virtual ~HelloWorld2();

  // Handle data
  virtual void beginJob(); // Runs on begin job
  virtual void beginRun(art::Run const &run); // Runs on new run
  virtual void analyze(art::Event const &e); // Runs on each event
  virtual void endJob(); // Runs when the job ends

private:

  int m_magicNumber;


};

// Definition of the constructor
artex::HelloWorld2::HelloWorld2(fhicl::ParameterSet const &p)
  :
  m_magicNumber(p.get<int>("magicNumber")) // Get the "magicNumber" parameter - must be int
{
  // Let's print out a little message
  mf::LogVerbatim("test") << "HelloWorld2::constructor - "
                          << "Magic number is " << m_magicNumber
                          << std::endl;
}

artex::HelloWorld2::~HelloWorld2() {
  // Clean up dynamic memory and other resources here.
  // We don't have to do anything here
}

// Definitions of beginJob, beginRun, analyze, endJob
void artex::HelloWorld2::beginJob(){
  mf::LogVerbatim("test") << "HelloWorld2::beginJob - "
                          << "Magic number is " << m_magicNumber
                          << std::endl;
}

void artex::HelloWorld2::beginRun(art::Run const& run){
  mf::LogVerbatim("test") << "HelloWorld2::beginRun -"
                          << " Run info is " << run.id().run()
                          << " Magic number is " << m_magicNumber
                          << std::endl;
}

void artex::HelloWorld2::analyze(art::Event const &e) {
  mf::LogVerbatim("test") << "HelloWorld2::analyze -"
                          << " Event info is " << e.id()
                          << " Magic number is " << m_magicNumber
                          << std::endl;

}

void artex::HelloWorld2::endJob(){
  mf::LogVerbatim("test") << "HelloWorld2::endJob - "
                          << "Magic number is " << m_magicNumber
                          << std::endl;
}

// Some red-tape for the Art system
DEFINE_ART_MODULE(artex::HelloWorld2);