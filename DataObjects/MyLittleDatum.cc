//
//  MyLittleDatum.cpp
//  gm2artexamples-xcode
//
//  Created by Adam Lyon on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "DataObjects/MyLittleDatum.hh"

void artex::MyLittleDatum::print( std::ostream& ost ) const {
    ost << "MyLittleDatum: value = " << datum();
}
