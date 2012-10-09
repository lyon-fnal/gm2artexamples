//
//  Hit.hh
// 
// A facade class for a HitData object. Add the power of @CLHEP::Hep3Vector@ to HitData.

// You can also construct a HitData object from a @CLHEP::Hep3Vector@

// Since it is easy to create a HitData, we'll keep everything in terms of the @CLHEP::Hep3Vector@.

#ifndef gm2artexamples_Hit_hh
#define gm2artexamples_Hit_hh

// For ostream
#include <iosfwd>

#include "CLHEP/Vector/ThreeVector.h"
#include "HitAndTrackObjects/HitData.hh"

namespace artex {
    
    class Hit {

    public:

        // Construct a Hit given a HitData
        Hit(const HitData& hitData) :
            vec_(hitData.x, hitData.y, hitData.z),
            weight_(hitData.weight)
            {}

        // Construct a hit given a Hep3Vector and a weight
        Hit(const CLHEP::Hep3Vector& v, double weight) :
            vec_(v), 
            weight_(weight)
            {}

        // Construct a hit with x, y, z, and w
        Hit(double x, double y, double z, double w) :
            vec_(x, y, z),
            weight_(w)
            {}

        // Accessors
        CLHEP::Hep3Vector const & position() const { return vec_; }
        double                    weight()   const { return weight_;}

        // Return a unique pointer to the data. This function is useful if we create a Hit and then
        // want to store the HitData in an event
        HitData data() const { return HitData(vec_.x(), vec_.y(), vec_.z(), weight_); }

        // Pretty printing
        void print( std::ostream & ) const;

    private:

        CLHEP::Hep3Vector   vec_;
        double              weight_;
        
        // Shift operator for printing
        std::ostream& operator<<(std::ostream& ost) {
            print(ost);
            return ost;
        }
                
    }; // end class Hit
    
}  // end namespace artex

#endif
