#include "CircularBox.h"

CircularBox::CircularBox(float radius)
{
    this->radius=radius;
}


 void CircularBox::checkCollision(DiskAgent *agent)
 {

      float new_angle=0;

      //check if the particle is bounching horizzontal boundaries
      if((agent->getPosition()->centerDistance()) >= this->radius)
      {
          // it needs to compute a perfect reflection
          //this->orientation= this->orientation-2*atan2(position->y,position->x)-M_PI/2;
          new_angle= agent->getOrientation()-2*atan2(agent->position->y,agent->position->x)-M_PI;
          //this->orientation= 2*atan2(position->y,position->x)-this->orientation;
          //do a step back, to avoid standing on the boundary wall
          agent->updatePosition(new_angle);

      }
      else
      {//set the particle to the position before the collision
          agent->updatePosition();
      }

 }

