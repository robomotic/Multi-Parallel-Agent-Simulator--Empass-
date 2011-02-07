#include "simparameters.h"


SimParameters::SimParameters()
{
    this->size=list.size();
}

void SimParameters::addParameter(string description,float value)
{
    using boost::lexical_cast;
    this->list[description]=lexical_cast<std::string>(value);
}

void SimParameters::addParameter(string description,int value)
{
    using boost::lexical_cast;
    this->list[description]=lexical_cast<std::string>(value);
}

string SimParameters::getParameter(string description)
{
    return this->list[description];
}

string SimParameters::getParamList(string separator)
{
    string strparam="";
    for(itr = list.begin(); itr != list.end(); ++itr){
    strparam += (*itr).first+ "=" +(*itr).second+separator;
    }
    strparam=strparam.substr(0,strparam.size()-1);
    return strparam;
}


void SimParameters::erase()
{
    this->list.clear();
}
