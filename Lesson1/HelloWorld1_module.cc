//  The HelloWorld1 plugin; the first example of an analyzer module.
//   You can generate boilerplate with the "artmod" command
//
// Includes from art and the packages on which it depends.
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"

using namespace std;

// Make a namespace for your stuff (artex = art examples)
namespace artex {

  // Declare the class for our analyzer
  class HelloWorld1 : public art::EDAnalyzer {

  public:
    explicit HelloWorld1(fhicl::ParameterSet const& pset);
    // Compiler generated d'tor is OK.

    // The part that looks at each event
    void analyze(const art::Event& event );

  };

  // Definition for constructor
  HelloWorld1::HelloWorld1(fhicl::ParameterSet const& pset){
    // Don't do anything
  }

  // Definition of analyze
  void HelloWorld1::analyze(const art::Event& event){
    mf::LogVerbatim("test")
      << "Hello, world. From analyze. "
      << event.id();
  }

} // end namespace artex

// Some red-tape for the Art system
using artex::HelloWorld1;
DEFINE_ART_MODULE(HelloWorld1);
