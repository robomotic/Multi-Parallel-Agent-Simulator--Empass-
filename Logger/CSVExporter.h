#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <Agents/DiskAgent.h>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <World/simparameters.h>

using namespace boost::numeric::ublas;
using namespace std;


class CSVExporter{

    private:

        string filename;
        string separator;
        fstream file;
        //The group of agents are contained in a vector at the moment
        std::vector<DiskAgent*> vector_agents;


    public:

        CSVExporter(string filename);
        ~CSVExporter();
        void exportPositions();
        void exportVelocities();
        void exportParameters(SimParameters *params);
        void exportDistances();
        void setData( std::vector<DiskAgent*> vector_agents){this->vector_agents=vector_agents;}


 };

#endif // CSVEXPORTER_H
