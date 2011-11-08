//
//  Hit.cpp
//

#include <iostream>
#include "HitAndTrackObjects/Hit.hh"

void artex::Hit::print( std::ostream& ost ) const {
    ost << "( " 
        << position_ << "; "
        << weight_
        << " )";
}