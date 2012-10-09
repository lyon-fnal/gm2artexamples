//
//  Hit.cpp
//

#include <iostream>
#include "HitAndTrackObjects/Hit.hh"

void artex::Hit::print( std::ostream& ost ) const {
    ost << "( " 
        << vec_ << "; "
        << weight_
        << " )";
}