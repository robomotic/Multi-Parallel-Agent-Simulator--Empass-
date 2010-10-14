#include "IcoSiso.h"

// Constructors/Destructors
//  
namespace Controllers {
IcoSiso::IcoSiso ( ) {
initAttributes ( );
}

IcoSiso::~IcoSiso ( ) {
    //check if some objects were still allocated
    if(this->fir0!=NULL)
    delete(this->fir0);
    if(this->fir1!=NULL)
    delete(this->fir0);
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void IcoSiso::initAttributes ( ) {
}
}
