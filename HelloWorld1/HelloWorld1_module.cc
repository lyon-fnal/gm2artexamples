//
//  The HelloWorld1 plugin; the first example of an analyzer module.
//
//  $Id: $
//  $Author: $
//  $Date: $
//   

// Includes from art and the packages on which it depends.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"

using namespace std;

namespace artex {

  class HelloWorld1 : public art::EDAnalyzer {

  public:
    explicit HelloWorld1(fhicl::ParameterSet const& pset);
    // Compiler generated d'tor is OK.

    void analyze(const art::Event& event );

  };

  HelloWorld1::HelloWorld1(fhicl::ParameterSet const& pset){
  }

  void HelloWorld1::analyze(const art::Event& event){
    mf::LogVerbatim("test")
      << "Hello, world. From analyze. "
      << event.id();
  }

} // end namespace artex

using artex::HelloWorld1;
DEFINE_ART_MODULE(HelloWorld1);
