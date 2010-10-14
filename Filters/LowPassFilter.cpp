#include "Filters/LowPassFilter.h"

// Constructors/Destructors
//  

LowPassFilter::LowPassFilter ( ) {
initAttributes();
}

LowPassFilter::~LowPassFilter ( ) { }

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void LowPassFilter::initAttributes ( ) {
    buffer[0]=0.0;
    buffer[1]=0.0;
    isNormalized=false;
    normconst=1.0;
    beta=1.0;
}

