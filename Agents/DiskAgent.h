
#ifndef DISKAGENT_H
#define DISKAGENT_H
#include <World/Steppable.h>
#include <World/Coordinate2D.h>
#include <World/velocityvector2d.h>
#include <Controllers/IcoSiso.h>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace std;
using namespace boost::numeric::ublas;
using namespace Controllers;
/**
  * class DiskAgent
  * An embodied agent with a disk shape, mass and diameter and yes antennas and
  * wheels!
  */

class DiskAgent : public Steppable
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  DiskAgent ( );

    DiskAgent (float x, float y, float speed,float orientation );
    DiskAgent (float x, float y, float speed );

  /**
   * Empty Destructor
   */
  virtual ~DiskAgent ( );

  /**
   * force the agent position, usually when a collision is detected
   */
  void forcePosition (float x,float y)
  {
      position->x=x;
      position->y=y;
  }


  /**
   * Update the agent position no collision
   */
  void updatePosition ();

   /**
   * Update the agent position with a given orientation angle after a collision
   */
  void updatePosition (float newangle);


   /**
   * Compute the velocity vector from the orientation and speed modulus
   */
  void updateVelocityVector();

public:

  float mass;
  float diameter;
  float orientation;
  float speed;
  float energy;
  float reflex_range;
  float distal_range;
  int id;
  int lifetime;

  // The next position
  Coordinate2D* deltaPosition;
  // The current position
  Coordinate2D* position;
  // The last velocity vector computed for the collision algorithm
  VelocityVector2D* velocity;
  //3 ico controller for every behaviour
  IcoSiso *icoFood;
  IcoSiso *icoAgent;
  IcoSiso *icoObstacle;


public:


  // Private attribute accessor methods
  //  
  /**
   * Set the value of mass
   * @param new_var the new value of mass
   */
  void setMass ( float new_var )   {
      mass = new_var;
  }

  void stepBack();

  /**
   * Get the value of mass
   * @return the value of mass
   */
  float getMass ( )   {
    return mass;
  }

  float getVx();
  float getVy();

  /**
   * Get the value of radius
   * @return the value of radius
   */
  float getRadius ( )   {
    return diameter/2;
  }

  /**
   * Set the value of diameter
   * @param new_var the new value of diameter
   */
  void setDiameter ( float new_var )   {
      diameter = new_var;
  }

  /**
   * Get the value of diameter
   * @return the value of diameter
   */
  float getDiameter ( )   {
    return diameter;
  }

  /**
   * Set the value of position
   * @param new_var the new value of position
   */
  void setPosition ( Coordinate2D* new_var )   {
      position = new_var;
  }

  /**
   * Get the value of position
   * @return the value of position
   */
  Coordinate2D* getPosition ( )   {
    return position;
  }

  /**
   * Set the value of orientation
   * @param new_var the new value of orientation
   */
  void setOrientation ( float new_var )   {
      orientation = new_var;
  }

  /**
   * Get the value of orientation
   * @return the value of orientation
   */
  float getOrientation ( )   {
    return orientation;
  }

  /**
   * Set the value of speed
   * @param new_var the new value of speed
   */
  void setSpeed ( float new_var )   {
      speed = new_var;
  }

  /**
   * Get the value of speed
   * @return the value of speed
   */
  float getSpeed ( )   {
    return speed;
  }

  /**
   * Set the value of energy
   * @param new_var the new value of energy
   */
  void setEnergy ( float new_var )   {
      energy = new_var;
  }

  /**
   * Get the value of energy
   * @return the value of energy
   */
  float getEnergy ( )   {
    return energy;
  }

  /**
   * Set the value of reflex_range
   * @param new_var the new value of reflex_range
   */
  void setReflex_range ( float new_var )   {
      reflex_range = new_var;
  }

  /**
   * Get the value of reflex_range
   * @return the value of reflex_range
   */
  float getReflex_range ( )   {
    return reflex_range;
  }

  /**
   * Set the value of distal_range
   * @param new_var the new value of distal_range
   */
  void setDistal_range ( float new_var )   {
      distal_range = new_var;
  }

  /**
   * Get the value of distal_range
   * @return the value of distal_range
   */
  float getDistal_range ( )   {
    return distal_range;
  }

  /**
   * Set the value of id
   * @param new_var the new value of id
   */
  void setId ( int new_var )   {
      id = new_var;
  }

  /**
   * Get the value of id
   * @return the value of id
   */
  int getId ( )   {
    return id;
  }

  /**
   * Set the value of lifetime
   * @param new_var the new value of lifetime
   */
  void setLifetime ( int new_var )   {
      lifetime = new_var;
  }

  /**
   * Get the value of lifetime
   * @return the value of lifetime
   */
  int getLifetime ( )   {
    return lifetime;
  }

  float centerDistance ()
  {
       return (this->position->centerDistance()+this->diameter/2);
  }

  void step();


private:


  void initAttributes ( ) ;

};

#endif // DISKAGENT_H
