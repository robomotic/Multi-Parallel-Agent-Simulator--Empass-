#include "RectangularBox.h"

RectangularBox::RectangularBox(float W,float H)
{
    this->width=W;
    this->height=H;

}


 bool RectangularBox::checkCollision(DiskAgent *agent)
 {

      float new_angle=0;
      //check if the particle is bounching horizzontal boundaries
      if((agent->position->y)<=agent->getRadius() || (agent->position->y+agent->getRadius())>=height)
      {
          new_angle=2*M_PI-agent->getOrientation();
          agent->stepBack();
          //then update position
          agent->updatePosition(new_angle);
          return true;

      }//check if the particle is bouncing vertical boundaries
      else if((agent->position->x)<=agent->getRadius() || (agent->position->x+agent->getRadius())>=width)
      {
          new_angle=M_PI-agent->getOrientation();
          //first do a step back
          agent->stepBack();
          //then update the position
          agent->updatePosition(new_angle);
          return true;
      }
      else
      {//set the particle to the position before the collision
          agent->updatePosition();
          return false;

      }

 }
