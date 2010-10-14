#include "Agents/DiskAgent.h"

// Constructors/Destructors
//  

DiskAgent::DiskAgent ( ) {
initAttributes();
}

DiskAgent::~DiskAgent ( ) { }

//  
// Methods
//  

 /**
   * Initialize an agent
   * @param  x x position
   * @param  y y position
   *
   * @param  speed initial speed
   *
   */
  DiskAgent::DiskAgent (float x, float y, float speed )
  {
       initAttributes();
       this->position->x=x;
       this->position->y=y;
       this->speed=speed;
  }


     /**
   * Initialize an agent
   * @param  x x position
   * @param  y y position
   *
   * @param  speed initial speed
   *
   */
  DiskAgent::DiskAgent (float x, float y, float speed,float orientation)
  {
       initAttributes();
       this->position->x=x;
       this->position->y=y;
       this->speed=speed;
       this->orientation=orientation;
       //std::cout<<"Agent  created"<<std::endl;
  }


void DiskAgent::initAttributes ( ) {
    this->mass=1.0;
    this->energy=1.0;
    this->diameter=1.0;
    this->speed=1.0;
    this->distal_range=diameter*4;
    this->reflex_range=diameter*2;
    this->position=new Coordinate2D();
    this->deltaPosition=new Coordinate2D();

}

void DiskAgent::step()
{
    this->position->x+=this->deltaPosition->x;
    this->position->y+=this->deltaPosition->y;

}
