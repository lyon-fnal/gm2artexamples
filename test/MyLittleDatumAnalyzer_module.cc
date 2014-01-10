// Analyze MyLittleDatum in the event. Make sure it has the right quantitiy.

// Use Boost Unit Test Facility
#include <boost/test/included/unit_test.hpp>

// Include Art stuff
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Handle.h"
#include "cetlib/exception.h"
#include "fhiclcpp/ParameterSet.h"
#include <string>

// Include MyLittleDatm
#include "DataObjects/MyLittleDatum.hh"

// Declare the namespace
namespace artextest {
    class MyLittleDatumAnalyzer;
}

// Define and declare the analyzer class
class artextest::MyLittleDatumAnalyzer: public art::EDAnalyzer
{
public:
    
    // Constructor
    MyLittleDatumAnalyzer( fhicl::ParameterSet const & p )
      : art::EDAnalyzer(p),
	input_label_( p.get<std::string>("input_label") )
        { }
    
    virtual void analyze( art::Event const & e );
    
private:
    
    // For holding the input label
    std::string input_label_;
    
};  // MyLittleDatumAnalyzer

void artextest::MyLittleDatumAnalyzer::analyze( art::Event const & e )
{
    // Check the input label
    mf::LogVerbatim("test") << "input_label is " << input_label_;

    // Make the Handle
    art::Handle<artex::MyLittleDatum> h;
    
    // Load the data
    e.getByLabel(input_label_, h);
    
    // Extract the data
    artex::MyLittleDatum const& mld = *h;
    
    // Check the data
    BOOST_REQUIRE_CLOSE(mld.datum, 25.5, .0001);
    
}  // analyze()


DEFINE_ART_MODULE(artextest::MyLittleDatumAnalyzer)

