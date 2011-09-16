#ifndef DATAOBJECTS_MYHIT_HH
#define DATAOBJECTS_MYHIT_HH

// A very basic hit class

// External includes
#include <iofwd>  // For std::ostream
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"

// Define our namespace
namespace artex {

  class MyHIt {

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

    void print( std::ostream& ) const;

    // Shift left (printing) operator
    inline std::ostream& operator<<(std::ostream& ost,
                                    MyHit const& p ) {
      p.print(ost);
      return ost;
    }

  } // end class

} // end namespaceX


#endif
