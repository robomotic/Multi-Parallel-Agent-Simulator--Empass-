#include <omp.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

#include <map>
#include <math.h>
#include <Controllers/IcoSiso.h>
#include <gnuplot-iostream.h>
#include <World/World2DCartesian.h>
//#include <Test/TestRoutines.h>
#include <Entropy/testEntropy.cpp>



using namespace std;
using namespace entropy;

// global program settings
int     iparam=0;     // integer parameter
double  dparam=0;     // double parameter
string  sparam="";    // string parameter
int     fparam=0;     // boolean flag



void run_simulation()
{

    Gnuplot gp;
    gp << "set terminal png\n";
    World2DCartesian* world=new World2DCartesian();
    world->run(1,0,10);
    gp << "set output 'trajectory.png'\n";
    gp << "p '-' w l t 'coord'\n";
    gp.send(world->xy_pts_agent);
    std::cout<<"Done!"<<std::endl;
}

void compute_entropy()
{
 cout<<"Computing entropy for reflex behaviour\n\n";
 compute_entropy_reflex_log("/home/epokh/Dropbox/PHD/SimpleData/blobshallow/reflex/");
 cout<<"\n\n";
 compute_entropy_retinal_log("/home/epokh/Dropbox/PHD/SimpleData/blobshallow/reflex/");
 cout<<"\n\n";
 cout<<"Computing entropy for learning behaviour \n\n";
 compute_entropy_reflex_log("/home/epokh/Dropbox/PHD/SimpleData/blobshallow/replay/");
 cout<<"\n\n";
 compute_entropy_retinal_log("/home/epokh/Dropbox/PHD/SimpleData/blobshallow/replay/");

}

int main (int argc, char *argv[]) {

 //arguments decoding

    int optind=1;
        // decode arguments
        while ((optind < argc) && (argv[optind][0]=='-')) {
            string sw = argv[optind];
            if (sw=="-i") {
                optind++;
                iparam = atoi(argv[optind]);
            }
            else if (sw=="-d") {
                optind++;
                dparam = atof(argv[optind]);
            }
            else if (sw=="-s") {
                optind++;
                sparam = argv[optind];
            }
            else if (sw=="-f")
                fparam=1;
            else
                cout << "Unknown switch: "
                     << argv[optind] << endl;
            optind++;
        }
 //testsinglefir();
 //testsingleICO();
 //testloop();
 //testmatrix();
 //test_variable();
 //test_histogram();
 //compute_entropy();
 run_simulation();
 return 0;
}

