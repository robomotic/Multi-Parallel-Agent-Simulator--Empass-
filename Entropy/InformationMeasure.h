#ifndef INFORMATIONMEASURE_H
#define INFORMATIONMEASURE_H

#include "include/Entropy.h"
#include "include/JointVariable.h"
#include "include/Histogram.h"
#include "MatrixUtil/MatrixOperations.h"
#include <Logger/CSVDatabase.h>
#include <gnuplot-iostream.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <limits>
#include <vector>

using namespace entropy;
using namespace boost::numeric::ublas;


int compute_entropy_retinal_log(string folder,int binstep);
int compute_entropy_retinal_log(string folder,int low,int up,int binstep);
int compute_entropy_reflex_log(string folder,int binstep);
int compute_entropy_reflex_log(string folder,int low,int up,int binstep);
void gnuplot_retinal_field(matrix<float> &retinaltau,string folder,int tau_index);
void gnuplot_avg_retinal(boost::numeric::ublas::vector<float>  &retinaltau,string folder);
void gnuplot_avg_reflex(std::vector<float>  &retinaltau,string folder);

//tau is the temporal delay between the 2 time series
//taumin is the lower bound and taumax is the upper bound
int taumin=10;
int taumax=10;
//ordermin and ordermax is the order of the empowerment
int ordermin=1;
int ordermax=10;
//the number of pixel of the retina
//must be always an even number
const int retinal_W=15;
const int retinal_H=15;
const int retinal_size=retinal_W*retinal_H;
//this is dependend on the instance of the discretized values for
//the motor output resolution and is expressed in degrees
float angle_resolution[]={0.5,1,5,8};
//the robot has a dynamic output range of 360 degrees
int angle_range=360;
//the index of the column in the angle
int offset_angle=3;

#endif // INFORMATIONMEASURE_H
