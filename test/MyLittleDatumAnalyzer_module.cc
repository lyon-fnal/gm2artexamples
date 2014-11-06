// Analyze MyLittleDatum in the event. Make sure it has the right quantitiy.

// Use Boost Unit Test Facility
#include "art/Utilities/quiet_unit_test.hpp"

// Include Art stuff
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Handle.h"
#include "cetlib/exception.h"
#include "fhiclcpp/ParameterSet.h"
#include <string>

// Include MyLittleDatm
#include "DataObjects/MyLittleDatumCollection.hh"

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
    
    auto mldH = e.getValidHandle<artex::MyLittleDatumCollection>( art::InputTag(input_label_) );
    
    // Check the data
    BOOST_REQUIRE_CLOSE( (*mldH)[0].datum, 3.14, .0001);
    
}  // analyze()


DEFINE_ART_MODULE(artextest::MyLittleDatumAnalyzer)

