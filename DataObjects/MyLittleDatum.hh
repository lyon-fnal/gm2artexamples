// Header file for the @MyLittleDatum@ class. 

// MyLittleDatum is a small example of creating, storing, and retrieving
// a simple data object in ART. Note that there are no references to anything in ART itself
// in this file.

// Header guards
#ifndef GM2ARTEXAMPLES_MYLITTLEDATUM_H
#define GM2ARTEXAMPLES_MYLITTLEDATUM_H

// We need to include @iosfwd@ for @std::ostream@
#include <iosfwd> 

// We put everything in the @artex@ namespace. Get used to using namespaces, as 
// they are important for avoiding name clashes that can cause hard to find bugs
namespace artex {
    
    // Now we define the class    
    class MyLittleDatum {
        
    private:
        
        // We'll just have one data member, a simple float
        float m_datum;
        
    public:
        
        // The constructor
        MyLittleDatum(float datum) :
            m_datum(datum)
        {}
        
        // Every class needs a default constructor for the persistency mechanism
        MyLittleDatum() :
            m_datum(0)
        {}
        
        // An accessor for the data member
        float datum() const { return m_datum; }
        
        // Print method for nicely displaying the object. Used by the @&lt;&lt;@ operator below
        void print( std::ostream& ) const;
        
        // Printing operator (shift left). For example, 
        // <pre>mf::LogVerbatim("test") << m;</pre>
        inline std::ostream& operator<<(std::ostream& ost) {
            print(ost);
            return ost;
        }            
    
    // End of class    
    };    
   
// End of namespace    
}

// End of the header guard
#endif

// If you are following the tutorial, you should go to the &l=DataObjects/MyLittleDatum.cc& file next (the implementation file of this class). 
