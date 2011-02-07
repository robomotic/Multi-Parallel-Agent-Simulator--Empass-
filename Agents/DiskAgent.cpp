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
   * @param  x x0 position of the agent
   * @param  y y0 position of the agent
   * @param  orientation intial orientation of the agent
   * @param  speed initial speed in modulus
   *
   */
  DiskAgent::DiskAgent (float x, float y, float speed,float orientation)
  {
       initAttributes();
       this->position->x=x;
       this->position->y=y;
       this->speed=speed;
       this->orientation=orientation;

  }

  void DiskAgent::updatePosition ()
  {

      deltaPosition->x=cos(orientation)*speed;
      deltaPosition->y=sin(orientation)*speed;

  }

  void DiskAgent::updatePosition (float newangle)
  {
      //update the angle
      this->orientation= newangle;
      //compute the orientation
      deltaPosition->x=cos(orientation)*speed;
      deltaPosition->y=sin(orientation)*speed;

  }

  //do a step back in case of collision
  void DiskAgent::stepBack()
  {
      position->y-=deltaPosition->y;
      position->x-=deltaPosition->x;

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
        this->velocity=new VelocityVector2D();

  }

  void DiskAgent::step()
  {
        this->position->x+=this->deltaPosition->x;
        this->position->y+=this->deltaPosition->y;

  }

    /**
    * Compute the velocity vector from the orientation and speed modulus
    */
  void DiskAgent::updateVelocityVector()
  {
      velocity->setVx(this->speed*cos(this->orientation));
      velocity->setVy(this->speed*sin(this->orientation));

  }

  float DiskAgent::getVx()
  {
      return velocity->getVx();

  }

  float DiskAgent::getVy()
  {
      return velocity->getVy();

  }


