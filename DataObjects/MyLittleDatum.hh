//
//  MyLittleDatum.h
//  gm2artexamples-xcode
//
//  Created by Adam Lyon on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GM2ARTEXAMPLES_MYLITTLEDATUM_H
#define GM2ARTEXAMPLES_MYLITTLEDATUM_H

#include <iosfwd>  // For std::ostream

// Here's a little example of a datum in Art
namespace artex {
    
    class MyLittleDatum {
    private:
        float m_datum;  
        
    public:
        // C'tor
        MyLittleDatum(float datum) :
            m_datum(datum)
        {}
        
        // A default constructor
        MyLittleDatum() :
            m_datum(0)
        {}
        
        // Accessors
        float datum() const { return m_datum; }
        
        // print method
        void print( std::ostream& ) const;
        
        // Shift left (printing) operator
        inline std::ostream& operator<<(std::ostream& ost) {
            print(ost);
            return ost;
        }
            
    };
    
}

#endif
