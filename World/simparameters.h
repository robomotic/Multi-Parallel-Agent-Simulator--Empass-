#ifndef SIMPARAMETERS_H
#define SIMPARAMETERS_H
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
using namespace std;


class SimParameters
{
private:
    //alla parameters will be converted to string values with their description
    map<string,string> list;
    int size;
    map<string,string>::const_iterator itr;
public:
    SimParameters();
    void addParameter(string description,float value);
    void addParameter(string description,int value);
    string addParameter(string description);
    string getParamList(string separator);
    string getParameter(string description);
    void erase();

};

#endif // SIMPARAMETERS_H
