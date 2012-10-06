//
//  HitData.cpp
//

#include <iostream>
#include "HitAndTrackObjects/HitData.hh"

void artex::HitData::print( std::ostream& ost ) const {
    ost << "( " 
        << "x=" << x << " "
        << "y=" << y << " "
        << "z=" << z << " "
        << "weight=" << weight << " )";
}