#include "World2DCartesian.h"
#include <gnuplot-iostream.h>
#include <ctime>
#include <cerrno>

World2DCartesian::World2DCartesian (float W,float H) {

this->box=new RectangularBox(W,H);
if(W<H)
  this->radius=W/2;
else
  this->radius=H/2;

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

  /**
   * run should take some argument from the main
   */
  void World2DCartesian::run(int n,int m,int steps)
  {
      this->time=0;
      this->N=n;
      this->M=m;

      //init first then go to step or somebody should call the step
      initCircular();
      //set the logger
      if(filename.size()>0)
      {
          enableLogger(filename);

      }
      else
      {

          //Find the current time
          time_t curtime = std::time(0);

           //convert it to tm
           tm now=*localtime(&curtime);

          //BUFSIZ is standard macro that expands to a integer constant expression
          //that is greater then or equal to 256. It is the size of the stream buffer
          //used by setbuf()
          char dest[BUFSIZ]={0};

          //Format string determines the conversion specification's behaviour
          const char format[]="%A, %B %d %Y. Simulation %X.dat";

          //strftime - converts date and time to a string
          if (strftime(dest, sizeof(dest)-1, format, &now)>0)
            std::cout<<dest<<std::endl;
          else
            std::cerr<<"strftime failed. Errno code: "<<errno<<std::endl;

          filename=dest;
          enableLogger(filename);

      }
      //write header
      simParams=new SimParameters();
      simParams->addParameter("Number of agents",N);
      simParams->addParameter("Number of resources",M);
      simParams->addParameter("Time steps",steps);
      //log the agent status
      if(datalogger!=NULL)
      {
      cout<<simParams->getParamList(" ")<<endl;
      this->datalogger->exportParameters(simParams);
      }
      step(steps);

  }

  /**
   * Create a world with n agents and m resources
   * time starts from 0
   * the world is a circle with radius R
   * all the agents are standard
   */
  void World2DCartesian::initCircular()
  {

      //generate the matrix for the agents mutual distances
      agentDistances.resize(N,N);

      //generate the agents on a corona
      float deltaTheta=2*M_PI/N;
      //place the circle in the middle of the square
      float xcenter=box->getW()/2;
      float ycenter=box->getH()/2;
      float rotAngle=0.0;
      float agentDiameter=2.0;
      //the perimeter of the circle where the agents will be positioned
      float perimeter=agentDiameter*2*M_PI*N;
      //the collar is the radius of the corresponding circle
      float collar=perimeter/(2*M_PI);

      if(collar>=radius)
      {
      this->radius=collar+agentDiameter*4;
      this->box->setW(radius);
      this->box->setH(radius);
      std::cout<<"World is too small, enlarged automagically"<<std::endl;
      }

      std::cout<<"N "<<N<<" M "<<M<<" Radius "<<radius<<std::endl;
      vector_agents.reserve(N);
      float xpos,ypos;
      //now create the agents
      for (int i=0; i<N; i++){
         xpos=xcenter+collar*cos(rotAngle);
         ypos=ycenter+collar*sin(rotAngle);
         vector_agents.push_back(new DiskAgent(xpos,ypos,1,rotAngle));
         vector_agents[i]->setDiameter(agentDiameter);
         vector_agents[i]->setId(i);
         vector_agents[i]->setOrientation(rotAngle);
         rotAngle+=deltaTheta;
      }
      std::cout<<"Agents created "<<vector_agents.size()<<std::endl;

      //[TO DO]now create the resources

  }

void World2DCartesian::enableLogger(string filename)
{
   this->datalogger=new CSVExporter(filename);
   this->datalogger->setData(this->vector_agents);

}

void World2DCartesian::step()
{
    //do collision detection for walls
    //when the arena is circular is a simple computation
    for(unsigned int i=0;i<vector_agents.size();i++)
    {
      DiskAgent* current=vector_agents.at(i);
      //query the bounding box if a collision was detected
      //the box object will update the status of the robot automagically
      //this is computed for every single agent
      bool collision=this->box->checkCollision(current);

      //then do collision between agents
      for (unsigned int j = i + 1; j < vector_agents.size(); j++)
      {
          if (this->isColliding(vector_agents[i],vector_agents[j]))
          {

              this->collision2Ds(vector_agents[i],vector_agents[j]);

          }
      }
      //update the status for every agent, here we really change the current position in the box
      current->step();
      //log the agent status
      if(datalogger!=NULL)
      this->datalogger->exportPositions();

    }

    //then increase
    time++;

}
//******************************************************************************
//  Computes the exit velocities supposing that the 2 disks are touching
//  each others
//****************************************************************************


void World2DCartesian::collision2Ds(DiskAgent *agent1,DiskAgent *agent2){

       float  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;
       float vx2,vx1,vy2,vy1;

       m21=(agent2->mass)/(agent1->mass);
       x21=agent2->getPosition()->x-agent1->getPosition()->x;
       y21=agent2->getPosition()->y-agent1->getPosition()->y;
       //update current velocity vector from orientation and speed
       agent1->updateVelocityVector();
       agent2->updateVelocityVector();
       //some useful variables
       vx2=agent2->getVx();
       vy2=agent2->getVy();
       vx1=agent1->getVx();
       vy1=agent1->getVy();

       //velocity difference
       vx21=vx2-vx1;
       vy21=vy2-vy1;
       //common velocity
       vx_cm = (agent1->mass*vx1+agent2->mass*vx2)/(agent1->mass+agent2->mass) ;
       vy_cm = (agent1->mass*vy1+agent2->mass*vy2)/(agent1->mass+agent2->mass) ;


       //*** return old velocities if balls are not approaching ***
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

//     ***  velocity correction for inelastic collisions agents must have the same radius ***
       float R=(agent1->diameter+agent2->diameter)/4;
       vx1=(vx1-vx_cm)*R + vx_cm;
       vy1=(vy1-vy_cm)*R + vy_cm;
       vx2=(vx2-vx_cm)*R + vx_cm;
       vy2=(vy2-vy_cm)*R + vy_cm;

//     now let's go back to the exit angles of the particles
       agent1->orientation=atan2(vy1,vx1);
       agent2->orientation=atan2(vy2,vx2);

       return;
}

void World2DCartesian::initAttributes ( ) {
}

