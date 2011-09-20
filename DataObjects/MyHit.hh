#ifndef DATAOBJECTS_MYHIT_HH
#define DATAOBJECTS_MYHIT_HH

// A very basic hit class

// External includes
#include <iosfwd>  // For std::ostream
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"

// Define our namespace
namespace artex {
    
    class MyHit {
        
    public:
        
        
        // Default C'tor
        MyHit( int detectorNum,
              CLHEP::Hep3Vector const& position,
              CLHEP::HepLorentzVector const& momentum,
              double time ) :
        m_detectorNum( detectorNum ),
        m_position( position ),
        m_momentum( momentum ),
        m_time( time )
        {}
        
        // Accessors            
        int detectorNum() const { return m_detectorNum; }
        
        
        // print method
        void print( std::ostream& ) const;
        
        // Shift left (printing) operator
        inline std::ostream& operator<<(std::ostream& ost) {
            print(ost);
            return ost;
        }
        
    private: 
        // Private data
        int                     m_detectorNum;
        CLHEP::Hep3Vector       m_position;
        CLHEP::HepLorentzVector m_momentum;
        double                  m_time;
        
    }; // end class
    
} // end namespace


#endif
