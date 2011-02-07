#ifndef VELOCITYVECTOR2D_H
#define VELOCITYVECTOR2D_H

class VelocityVector2D
{
private:
    float* v;

public:
    VelocityVector2D();
    float getVx(){return v[0];}
    float getVy(){return v[1];}

    float setVx(float val){return v[0]=val;}
    float setVy(float val){return v[1]=val;}


};

#endif // VELOCITYVECTOR2D_H
