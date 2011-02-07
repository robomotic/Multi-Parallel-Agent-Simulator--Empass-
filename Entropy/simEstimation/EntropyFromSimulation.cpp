//#include "EntropyFromSimulation.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <iomanip>
#include <map>
#include <math.h>
#include <gnuplot-iostream.h>
#include <Entropy/testEntropy.cpp>
#include <Entropy/computeEntropySingle.cpp>

using namespace std;
using namespace entropy;

void compute_entropy_single()
{
  string homefolder="/home/epokh/Documents/SimpleData/rallysimple2/";

 int nsamp;
 int angle_res=4;

 cout<<"Computing entropy for close antenna \n\n";
  nsamp=compute_entropy_reflex_log(homefolder+"close/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";
 nsamp=compute_entropy_retinal_log(homefolder+"close/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";
 homefolder="/home/epokh/Dropbox/PHD/SimpleData/rallysimple2/far1neuron6/";

 cout<<"Computing entropy for a single neuron predictor \n\n";
 nsamp=compute_entropy_reflex_log(homefolder,1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";
 nsamp=compute_entropy_predictor_log(homefolder,1,2048,1,4);
 //cout<<"\n # samples "<<nsamp<<"\n";



}

void compute_entropy_differential(string distance)
{
    string homefolder="/home/epokh/Documents/SimpleData/rallysimple2/";
    cout<<"Sensors distance= "<<distance<<" \n\n";
    cout<<"Computing entropy for close reflex\n\n";
    int nsamp;
    int angle_res=4;
    nsamp=compute_entropy_reflex_log(homefolder+"close"+distance+"/",1,2048,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder+"close"+distance+"/",1,2048,angle_res);

    cout<<"Computing entropy for retinal field \n\n";
    nsamp=compute_entropy_reflex_log(homefolder+"fardist"+distance+"/",1,2048,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder+"fardist"+distance+"/",1,2048,angle_res);


}


void compute_entropy_maze(int order)
{
    string homefolder="/home/epokh/Documents/RetinalData2/maze/predictive/";

    int nsamp;
    int angle_res=3;

    cout<<"Information flow after step \n\n";

    nsamp=compute_entropy_reflex_log(homefolder,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,angle_res);


    homefolder="/home/epokh/Documents/RetinalData2/maze/reflex/";

    cout<<"Information flow before step\n\n";
    nsamp=compute_entropy_reflex_log(homefolder,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,angle_res);

}

void compute_entropy_icolearner(int order)
{
    string homefolder="/home/epokh/Documents/RetinalData2/shallow/predictive/";

    int nsamp;
    int angle_res=3;
    /*
    cout<<"Information flow after shallow \n\n";

    nsamp=compute_entropy_reflex_log(homefolder,0,1400-1,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,0,1400-1,angle_res);


    homefolder="/home/epokh/Documents/RetinalData2/shallow/reflex/";

    cout<<"Information flow before shallow \n\n";
    nsamp=compute_entropy_reflex_log(homefolder,0,1400-1,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,0,1400-1,angle_res);

    homefolder="/home/epokh/Documents/RetinalData2/middle/predictive/";
    cout<<"Information flow after middle \n\n";

    nsamp=compute_entropy_reflex_log(homefolder,0,1582-1,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,0,1582-1,angle_res);


    homefolder="/home/epokh/Documents/RetinalData2/middle/reflex/";

    cout<<"Information flow before middle \n\n";
    nsamp=compute_entropy_reflex_log(homefolder,0,1582-1,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,0,1582-1,angle_res);
*/

    homefolder="/home/epokh/Documents/RetinalData2/step/predictive/";
    cout<<"Information flow after step \n\n";

    nsamp=compute_entropy_reflex_log(homefolder,0,2080-1,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,0,2080-1,angle_res);


    homefolder="/home/epokh/Documents/RetinalData2/step/reflex/";

    cout<<"Information flow before step\n\n";
    nsamp=compute_entropy_reflex_log(homefolder,0,2080-1,angle_res);
    nsamp=compute_entropy_retinal_log(homefolder,0,2080-1,angle_res);

}

void compute_entropy_retinal()
{

 string homefolder="/home/epokh/Documents/SimpleData/rallysimple2/";
 cout<<"Computing entropy for close antenna \n\n";
 int nsamp;
 int angle_res=4;
 nsamp=compute_entropy_reflex_log(homefolder+"close/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";
 nsamp=compute_entropy_retinal_log(homefolder+"close/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";


 cout<<"Computing entropy for far antenna 6 \n\n";
 nsamp=compute_entropy_reflex_log(homefolder+"fardist6/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";
 nsamp=compute_entropy_retinal_log(homefolder+"fardist6/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";


 cout<<"Computing entropy for far antenna 12 \n\n";
 nsamp=compute_entropy_reflex_log(homefolder+"fardist12/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";
 nsamp=compute_entropy_retinal_log(homefolder+"fardist12/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";

 cout<<"Computing entropy for far antenna 24 \n\n";
 nsamp=compute_entropy_reflex_log(homefolder+"fardist24/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";
 nsamp=compute_entropy_retinal_log(homefolder+"fardist24/",1,2048,angle_res);
 //cout<<"\n # samples "<<nsamp<<"\n";


}

