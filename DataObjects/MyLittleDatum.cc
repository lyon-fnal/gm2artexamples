//  MyLittleDatum.cpp
//
//  Created by Adam Lyon on 9/18/11.
//

#include <iostream>

#include "DataObjects/MyLittleDatum.hh"

void artex::MyLittleDatum::print( std::ostream& ost ) const {
    ost << "MyLittleDatum: value = " << datum();
}
