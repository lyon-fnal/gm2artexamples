//
//  HitData.hh
// 
//  A little example Hit object

// The HitData object contains x, y, z and a weight. 

// Following the instructions in &l=DataObjects/readme.doconly&, note that we are *not* going to use 
// an actual @CLHEP::Hep3Vector@. We'll use a _Facade_ class for that. And again, we'll use an easy @struct@. 
//

#ifndef gm2artexamples_HitData_hh
#define gm2artexamples_HitData_hh

// For ostream
#include <iosfwd>

namespace artex {
    
    struct HitData {

        double x, y, z, weight;

        // Default constructor
        HitData() {};

        // Hide the following member functions from Root
        #ifndef __GCCXML__

            // Regular constructor
            HitData(double ix, double iy, double iz, double iweight) :
                x(ix), y(iy), z(iz), weight(iweight)
                {};

            // Pretty printing
            void print( std::ostream& )const;
            
            // Shift operator for printing
            std::ostream& operator<<(std::ostream& ost) {
                print(ost);
                return ost;
            }

        #endif
                
    }; // end class Hit
    
}  // end namespace artex

#endif
