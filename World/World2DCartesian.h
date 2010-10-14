
#ifndef WORLD2DCARTESIAN_H
#define WORLD2DCARTESIAN_H


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <Agents/DiskAgent.h>
#include <vector>
#include <map>

using namespace boost::numeric::ublas;
using namespace std;

/**
  * class World2DCartesian
  * 
  */

class World2DCartesian: public Steppable
{

public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  World2DCartesian ( );

  /**
   * Empty Destructor
   */
  virtual ~World2DCartesian ( );

  bool isColliding(DiskAgent *agent1,DiskAgent *agent2);
  void collision2Ds(DiskAgent *agent1,DiskAgent *agent2);

  /**
   * run should take some argument from the main
   */
  void run (int n,int m,float radius )
  {
      this->time=0;
      this->N=n;
      this->M=m;
      this->radius=radius;
      //init first then go to step or somebody should call the step
      init();
      step(20);

  }


  /**
   * Create a world with n agents and m resources
   * time starts from 0
   * the world is a circle with radius R
   * all the agents are standard
   */
  void init ()
  {

      //
      agentDistances.resize(N,N);

      //generate the agents on a corona
      float deltaTheta=2*M_PI/N;
      float xpos=0.0;
      float ypos=0.0;
      float rotAngle=0.0;
      float agentDiameter=2.0;
      float perimeter=agentDiameter*2*M_PI*N;
      float collar=perimeter/(2*M_PI);

      if(collar>=radius)
      {
      this->radius=collar+agentDiameter*4;
      std::cout<<"World is too small, enlarged automagically"<<std::endl;
      }

      std::cout<<"N "<<N<<" M "<<M<<" Radius "<<radius<<std::endl;
      vector_agents.reserve(N);
      //now create the agents
      for (int i=0; i<N; i++){

         xpos=collar*cos(rotAngle);
         ypos=collar*sin(rotAngle);
         vector_agents.push_back(new DiskAgent(xpos,ypos,1,rotAngle));
         vector_agents[i]->setDiameter(agentDiameter);
         vector_agents[i]->setId(i);
         vector_agents[i]->setOrientation(rotAngle);
         rotAngle+=deltaTheta;

         }
      std::cout<<"Agents created "<<vector_agents.size()<<std::endl;

      //now create the resources

  }


  void step ()
  {
      //do collision detection for walls
      //when the arena is circular is a simple computation
      for(unsigned int i=0;i<vector_agents.size();i++)
      {
        DiskAgent* current=vector_agents.at(i);
        std::cout<<"Time "<<time<<std::endl;
        //the robot touches the arean walls
        if((current->getPosition()->centerDistance()) >= this->radius)
        {
            //go back in time 1 step to the previous position
            current->updatePosition(true);//collision detected
            std::cout<<"Hit ("<<current->getPosition()->x<< ","<<current->getPosition()->y<<")"<<std::endl;
            std::cout<<"Tetha "<<current->getOrientation()<<std::endl;

        }
        else
        {
            std::cout<<"Step ("<<current->getPosition()->x<< ","<<current->getPosition()->y<<")"<<std::endl;
            std::cout<<"Omega "<<current->getOrientation()<<std::endl;
            current->updatePosition(false);//no collision detected
        }
        current->step();
        //then do collision between agents
        for (unsigned int j = i + 1; j < vector_agents.size(); j++)
        {
            if (this->isColliding(vector_agents[i],vector_agents[j]))
            {
                //a collision was found
                std::cout<<"Collision ("<<i<<","<<j<<")="<<std::endl;
                this->collision2Ds(vector_agents[i],vector_agents[j]);

            }
        }

        //single logging of coordinates should be improved, so silly!
        if(i==0)
        {
            xy_pts_agent[current->getPosition()->x]=current->getPosition()->y;
        }

      }


      //then increase
      time++;

  }

  /**
   * @param  times number of steps
   */
  void step (int times )
  {
      for(int i=0;i<times;i++) step();


  }

private:

  //The group of agents are contained in a vector at the moment

  std::vector<DiskAgent*> vector_agents;

  // A symmetric matrix containing the mutual distances between agents
  matrix<double> agentDistances;
  // A symmetric matrix containing the mutual angles between agents
  matrix<double> agentAngles;
  // A matrix containing the distances between angents and food places
  matrix<double> foodDistances;
  // A matrix containing the angles between agents and food places
  matrix<double> foodAngles;
  // the time track
  long int time;
  //the number of agents
  int N;
  //the number of food resources
  int M;
  //the world is circular with ratius
  float radius;

 public:
  //some stuff for logging
  std::map<float, float> xy_pts_agent;


private:


  void initAttributes ( ) ;

};

#endif // WORLD2DCARTESIAN_H
