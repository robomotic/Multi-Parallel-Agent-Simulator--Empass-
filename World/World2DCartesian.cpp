#include "World2DCartesian.h"

// Constructors/Destructors
//  

World2DCartesian::World2DCartesian ( ) {
initAttributes();
}

World2DCartesian::~World2DCartesian ( ) { }


bool World2DCartesian::isColliding(DiskAgent *agent1,DiskAgent *agent2){
    //first compute the mutual distance
    float mutual_dist=Coordinate2D::euclideanDistance(agent1->getPosition(),agent2->getPosition());
    //save the distance in the proper matrix
    agentDistances(agent1->getId(),agent2->getId())=mutual_dist;
    //and in the simmetric position
   agentDistances(agent2->getId(),agent1->getId())=mutual_dist;
    if(mutual_dist<=(agent1->diameter+agent2->diameter))
         return true;
    else return false;

}
//******************************************************************************
//  Simplified Version
//  The advantage of the 'remote' collision detection in the program above is
//  that one does not have to continuously track the balls to detect a collision.
//  The program needs only to be called once for any two balls unless their
//  velocity changes. However, if somebody wants to use a separate collision
//  detection routine for whatever reason, below is a simplified version of the
//  code which just calculates the new velocities, assuming the balls are already
//  touching (this condition is important as otherwise the results will be incorrect)
//****************************************************************************


void World2DCartesian::collision2Ds(DiskAgent *agent1,DiskAgent *agent2){

       double  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;

       //double m1, m2, R,x1,y1,x2,y2,& vx1,& vy1,& vx2,& vy2;


       m21=agent2->mass/agent1->mass;
       x21=agent2->getPosition()->x-agent1->getPosition()->x;
       y21=agent2->getPosition()->y-agent1->getPosition()->y;
       /*
       vx21=vx2-vx1;
       vy21=vy2-vy1;

       vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
       vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;


//     *** return old velocities if balls are not approaching ***
       if ( (vx21*x21 + vy21*y21) >= 0) return;


//     *** I have inserted the following statements to avoid a zero divide;
//         (for single precision calculations,
//          1.0E-12 should be replaced by a larger value). **************

       fy21=1.0E-12*fabs(y21);
       if ( fabs(x21)<fy21 ) {
                   if (x21<0) { sign=-1; } else { sign=1;}
                   x21=fy21*sign;
        }

//     ***  update velocities ***
       a=y21/x21;
       dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
       vx2=vx2+dvx2;
       vy2=vy2+a*dvx2;
       vx1=vx1-m21*dvx2;
       vy1=vy1-a*m21*dvx2;

//     ***  velocity correction for inelastic collisions ***
       vx1=(vx1-vx_cm)*R + vx_cm;
       vy1=(vy1-vy_cm)*R + vy_cm;
       vx2=(vx2-vx_cm)*R + vx_cm;
       vy2=(vy2-vy_cm)*R + vy_cm;
*/
       return;
}


//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void World2DCartesian::initAttributes ( ) {
}

