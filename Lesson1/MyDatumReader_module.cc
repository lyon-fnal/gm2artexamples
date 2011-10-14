////////////////////////////////////////////////////////////////////////
// Class:       MyDatumReader
// Module Type: analyzer
// File:        MyDatumReader_module.cc
//
// Generated at Mon Sep 19 12:50:17 2011 by Adam Lyon using artmod
// from art v0_07_13.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"

#include "DataObjects/MyLittleDatumCollection.hh"

namespace artex {
    class MyDatumReader;
}

class artex::MyDatumReader : public art::EDAnalyzer {
public:
    explicit MyDatumReader(fhicl::ParameterSet const &p);
    virtual ~MyDatumReader();
    
    virtual void analyze(art::Event const &e);
        
private:
};

artex::MyDatumReader::MyDatumReader(fhicl::ParameterSet const &p)
// :
// Initialize member data here.
{}

artex::MyDatumReader::~MyDatumReader() {
    // Clean up dynamic memory and other resources here.
}

void artex::MyDatumReader::analyze(art::Event const &e) {
    // Implementation of required member function here.
    
    // Extract a reference to the data
    art::Handle< MyLittleDatumCollection > datumHandle;
    e.getByLabel("makeDatumB", datumHandle); // The name here is the "producer label"
    MyLittleDatumCollection const& datumVector = *datumHandle;
    
    mf::LogInfo log("test");
    log << "Number of datums in list = " << datumVector.size() << "\n";
    
    for (size_t i=0; i<datumVector.size(); ++i) {
        log << "   " << datumVector[i].datum() << "\n";
    }
}

DEFINE_ART_MODULE(artex::MyDatumReader);
