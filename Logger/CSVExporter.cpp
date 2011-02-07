#include "CSVExporter.h"

CSVExporter::CSVExporter(string filename)
{
        this->filename=filename;
        file.open(filename.c_str(), ios::out | ios::app);
        if(!file.is_open())
        {
            //should throw an exception
            cout<<"File not opened\n";
        }
        this->separator=",";
}
CSVExporter::~CSVExporter()
{
    file.close();

}

void CSVExporter::exportParameters(SimParameters *params)
{
    string info=params->getParamList(this->separator);
    this->file<<info<<"\n";
}

void CSVExporter::exportPositions()
{
        using boost::lexical_cast;
        using boost::bad_lexical_cast;
        string rowCSV="";
        for (unsigned i = 0; i < vector_agents.size(); ++ i)
        {
            rowCSV+=lexical_cast<std::string>(vector_agents[i]->position->x)+this->separator;
            rowCSV+=lexical_cast<std::string>(vector_agents[i]->position->y)+this->separator;

        }
        //push back the last colon
        rowCSV=rowCSV.substr(0,rowCSV.size()-1);
        this->file<<rowCSV<<"\n";

}


