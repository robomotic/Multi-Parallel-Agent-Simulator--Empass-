
#ifndef COORDINATE2D_H
#define COORDINATE2D_H
#include <math.h>

using namespace std;
/**
  * class Coordinate2D
  * 
  */

class Coordinate2D
{
public:

  /**
   * Empty Constructor
   */
  Coordinate2D ( );

  /**
   * Empty Destructor
   */
  virtual ~Coordinate2D ( );

  float x,y;

public:

  /**
   * The euclidean distance between 2 points in cartesian space
   */
  static float euclideanDistance (Coordinate2D *a,Coordinate2D *b)
  {
       return sqrt(pow(a->x-b->x,2)+pow(a->y-b->y,2));
  }

   /**
   * The manhattan distance between 2 points in cartesian space
   */

  static float manhattanDistance (Coordinate2D *a,Coordinate2D *b)
  {
       return fabs(a->x-b->x)+fabs(a->y-b->y);
  }

   /**
   * The manhattan distance between 2 points in cartesian space
   */

  static float centerDistance (Coordinate2D *point)
  {
       return sqrt(pow(point->x,2)+pow(point->y,2));
  }

  float centerDistance ()
  {
       return sqrt(pow(this->x,2)+pow(this->y,2));
  }

};

#endif // COORDINATE2D_H
