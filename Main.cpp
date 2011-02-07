#include <omp.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <iomanip>
#include <map>
#include <set>
#include <math.h>


#include <World/World2DCartesian.h>

using namespace std;

// global program settings
int     N=0;     // integer parameter
int     M=0;     // double parameter
string  desc="";    // string parameter
int     fparam=0;     // boolean flag
int simtime=0;
int W=100;
int H=100;

int main (int argc, char *argv[]) {

 //arguments decoding
int optind=1;
//build a paremeter object

        // decode arguments
        while ((optind < argc) && (argv[optind][0]=='-')) {
            string sw = argv[optind];
            if (sw=="-N") {
                optind++;
                N = atoi(argv[optind]);
            }
            else if (sw=="-M") {
                optind++;
                M = atoi(argv[optind]);
            }
            else if (sw=="-W") {
                optind++;
                W = atoi(argv[optind]);
            }
            else if (sw=="-H") {
                optind++;
                H = atoi(argv[optind]);
            }
            else if (sw=="-s") {
                optind++;
                desc = argv[optind];
            }
            else if (sw=="-T") {
                optind++;
                simtime = atoi(argv[optind]);
            }
            else if (sw=="-f")
                fparam=1;
            else
                cout << "Unknown switch: "
                     << argv[optind] << endl;
            optind++;
        }

        //take parameters from the console
        if(optind>1)
        {
            World2DCartesian* world=new World2DCartesian(W,H);
            world->filename="/home/epokh/sim1.data";
            world->run(N,M,simtime);

        }
        else
        {
            //a 100x100 unit square world
            World2DCartesian* world=new World2DCartesian(100,100);
            //10 agents and 0 food places for 1000 time steps
            world->filename="/home/epokh/sim1.data";
            world->run(10,0,1000);


        }
 return 0;
}

