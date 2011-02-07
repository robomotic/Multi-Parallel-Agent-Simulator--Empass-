#ifndef CIRCULARBOX_H
#define CIRCULARBOX_H
#include <World/Coordinate2D.h>
#include <Agents/DiskAgent.h>
#include <vector>

class CircularBox
{
public:
    CircularBox(float radius);
    //compute the new angle if a collision was detected
    void checkCollision(DiskAgent *agent);

private:
    //the width of the bounding box
    float radius;
    //the points of the polygon, can be used to draw
    std::vector<Coordinate2D> points;

};

#endif // CIRCULARBOX_H
