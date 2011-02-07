
#ifndef WORLD2DCARTESIAN_H
#define WORLD2DCARTESIAN_H


#include <vector>
#include <map>

#include <Logger/CSVExporter.h>
#include <Agents/DiskAgent.h>
#include <World/geometry/RectangularBox.h>
#include <World/simparameters.h>

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
  World2DCartesian (float W,float H);

  /**
   * Empty Destructor
   */
  virtual ~World2DCartesian ( );

  bool isColliding(DiskAgent *agent1,DiskAgent *agent2);
  void collision2Ds(DiskAgent *agent1,DiskAgent *agent2);
  void step();

  /**
   * run should take some argument from the main
   */
  void run (int n,int m,int steps);

  /**
   * Create a world with n agents and m resources
   * time starts from 0
   * the world is a circle with radius R
   * all the agents are standard
   */
  void initCircular();


  /**
   * @param  times number of steps
   */
  void step (int times )
  {
      for(int i=0;i<times;i++) {
          step();
      }
  }

  void enableLogger(string filename);

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
  //the bounding box here is a square
  RectangularBox *box;
  //the parameter list
  SimParameters *simParams;

 public:
  //data point structure for logging with gnuplot
  std::map<float, float> xy_pts_agent;
  //a text file logger
  CSVExporter* datalogger;
  //the filename for the data log
  string filename;

private:

  void initAttributes ( ) ;

};

#endif // WORLD2DCARTESIAN_H
