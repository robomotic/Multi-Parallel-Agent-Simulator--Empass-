
#include "include/Entropy.h"
#include "include/JointVariable.h"
#include "include/Histogram.h"
#include <Logger/CSVDatabase.h>
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <limits>


using namespace entropy;

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::set;
using std::numeric_limits;
using std::string;

void test_variable()
{
AleatoryVariable< char > *varX = new AleatoryVariable< char>();
AleatoryVariable< char > *varY = new AleatoryVariable< char>();
varX->setName("X");
varY->setName("Y");

varX->enqueueInSequence('a');
varY->enqueueInSequence('1');
varX->enqueueInSequence('b');
varY->enqueueInSequence('1');
varX->enqueueInSequence('c');
varY->enqueueInSequence('1');

JointVariable<char> *varXY=new JointVariable<char>();
varXY->X=varX;
varXY->Y=varY;
float mi=entropy::mutualInformation(*varXY);
std::cout<<"MI :"<<mi<<std::endl;

return;
}

void test_histogram()
{
        Histogram hist(0,360,1);
        hist.Add(10);
        hist.Add(409);

}

void compute_entropy_retinal_log(string folder,int low,int up)
{

AleatoryVariable<string> *motor=new AleatoryVariable<string>();
motor->setName("Motor Angle(Deg) Z");
CSVDatabase<string> data_motor(motor,folder+"angle.dat");
//read the second colum and put it in the random variable
//data_motor.mustDiscretize=true;
//data_motor.setDiscretization(0,360,360*2);
if(low==up)
{
data_motor.subset=true;
data_motor.lowersample=low;
data_motor.uppersample=up;
}

data_motor.readCSV(4);
motor->estimateProbabilities();
cout<<"H(Z)="<<entropy::entropy(*motor)<<endl;

float sum_retinal=0;
for(int i=0;i<16;i++)
{
RandomVarString *reflex=new RandomVarString();
cout<<"Retinal X1("<<i<<")\n";
reflex->setName("X1");
CSVDatabase<string> data_reflex(reflex,folder+"predictor.dat");
if(low==up)
{
data_reflex.subset=true;
data_reflex.lowersample=low;
data_reflex.uppersample=up;
}
data_reflex.countSamples();
cout<<"#samples "<<data_reflex.getTotalSamples()<<endl;
data_reflex.readCSV(i);
reflex->estimateProbabilities();
//cout<<"Entropy reflex "<<entropy::entropy(*reflex)<<endl;

JointVariable<string> *jvar;
for(int tau=10;tau<=10;tau++)
{
jvar=new JointVariable<string>();
jvar->X=motor;
jvar->Y=reflex;
jvar->setName("MI(Z,X1)");
float currentMI=entropy::mutualInformation(*jvar,tau);
cout<<"MI(Z,X1("<<i<<"),tau="<<tau<<")=" <<currentMI<<endl;
//cout<<"Samples taken: "<<jvar->Nxy<<endl;
sum_retinal+=currentMI;
}
}
cout<<"Mean(MI(Z,X1))="<<sum_retinal/16.0<<endl;
}

void compute_entropy_retinal_log(string folder)
{
    compute_entropy_retinal_log(folder,0,0);
}
void compute_entropy_reflex_log(string folder,int low,int up)
{
    Gnuplot gp;
    gp << "set terminal png\n";
    gp<<"set title 'Reflex probability'\n";
    gp<<"set auto x\n";
    gp<<"set style data histogram\n";
    gp<<"set style histogram cluster gap 1\n";
    //gp<<"set style fill solid border -1\n";
    gp<<"set boxwidth 0.9\n";
    gp<<"set xtic rotate by -45 scale 0\n";

RandomVarString *reflex=new RandomVarString();
reflex->setName("Reflex X0");
CSVDatabase<string> data_reflex(reflex,folder+"reflex.dat");

if(low==up)
{
data_reflex.subset=true;
data_reflex.lowersample=low;
data_reflex.uppersample=up;
}
data_reflex.readCSV();
reflex->estimateProbabilities();
cout<<"H(X0)="<<entropy::entropy(*reflex)<<endl;
reflex->dumpGnuplotData();

    gp << "set output '"<<folder<<"densityReflex.png'\n";
    gp << "p '-' with boxes lw 1 \n";
    gp.send(reflex->bin_data);

AleatoryVariable<string> *motor=new AleatoryVariable<string>();
motor->setName("MotorAngle Z");
CSVDatabase<string> data_motor(motor,folder+"angle.dat");
//read the second colum and put it in the random variable
//data_motor.mustDiscretize=true;
//data_motor.setDiscretization(0,360,360*2);
if(low==up)
{
data_motor.subset=true;
data_motor.lowersample=low;
data_motor.uppersample=up;
}
data_motor.countSamples();
cout<<"#samples "<<data_motor.getTotalSamples()<<endl;
data_motor.readCSV(4);

motor->estimateProbabilities();
motor->dumpGnuplotData();
//cout<<"Entropy motor "<<entropy::entropy(*motor)<<endl;

    gp<<"set title 'Predictor probability'\n";
    gp<<"set auto x\n";
    gp <<"set output '"<<folder<<"densityPredictor.png'\n";
    gp <<"p '-' with boxes lw 1 \n";
    gp.send(motor->bin_data);

JointVariable<string> *jvar;
for(int tau=10;tau<=10;tau++)
{
jvar=new JointVariable<string>();
jvar->X=motor;
jvar->Y=reflex;
jvar->setName("MI(Z,X0)");
float currentMI=entropy::mutualInformation(*jvar,tau);
cout<<"MI(Z,X0,tau="<<tau<<")=" <<currentMI<<endl;
//cout<<"Samples taken: "<<jvar->Nxy<<endl;
}
}

void compute_entropy_reflex_log(string folder)
{
    compute_entropy_reflex_log(folder,0,0);

}
