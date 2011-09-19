//
//  File.cpp
//  gm2artexamples-xcode
//
//  Created by Adam Lyon on 9/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "DataObjects/MyHit.hh"

void artex::MyHit::print( std::ostream& ost ) const {
    ost << "( " 
        << m_detectorNum << "; "
        << m_position << "; "
        << m_momentum << "; "  
        << m_time
        << " )";
}


