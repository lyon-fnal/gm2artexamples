//
//  Hit.hh
// 
//  A little example Hit object
//  We'll just store a poistion as a CLHEP::Hep3Vector and a weight as a double.
//

#ifndef gm2artexamples_Hit_hh
#define gm2artexamples_Hit_hh

// For ostream
#include <iosfwd>

#include "CLHEP/Vector/ThreeVector.h"

namespace artex {
    
    class Hit {
    public:
        
        // Default constructor
        Hit() :
            position_(),
            weight_(0.0)
        {}
        
        // The regular constructor
        Hit( CLHEP::Hep3Vector const& position,
             double weight) :
            position_(position),
            weight_(weight)
        {}
        
        // Accessors
        CLHEP::Hep3Vector const& position() const {return position_;}
        double                   weight()   const {return weight_;}
        
        // Pretty printing
        void print( std::ostream& )const;
        
    private:
        
        CLHEP::Hep3Vector    position_;
        double               weight_;
        
        // Shift operator for printing
        inline std::ostream& operator<<(std::ostream& ost) {
            print(ost);
            return ost;
        }
                
    }; // end class Hit
    
}  // end namespace artex

#endif
