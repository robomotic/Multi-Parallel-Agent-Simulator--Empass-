#ifndef RECTANGULARBOX_H
#define RECTANGULARBOX_H
#include <World/Coordinate2D.h>
#include <Agents/DiskAgent.h>
#include <vector>
class RectangularBox
{

private:
    //the width of the bounding box
    float width;
    //the height of the bounding box
    float height;
    //the points of the polygon
    std::vector<Coordinate2D> points;

public:
    RectangularBox(float w,float h);
    //compute the new angle if a collision was detected
    bool checkCollision(DiskAgent *agent);
    float getW(){return width;}
    float getH(){return height;}
    void setW(float W){this->width=W;}
    void setH(float H){this->height=H;}



};

#endif // RECTANGULARBOX_H
