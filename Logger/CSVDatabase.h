#ifndef CSVDATABASE_H
#define CSVDATABASE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Entropy/include/JointVariable.h"
#include "Entropy/include/Histogram.h"

using namespace entropy;
using namespace std;

typedef AleatoryVariable<string> RandomVarString;
typedef JointVariable<string> RandomJointString;

typedef std::string String;
typedef std::vector<String> CSVRow;
typedef CSVRow::const_iterator CSVRowCI;

template <class T>
bool from_string(T& t,const std::string& s,std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}


template <class T> class CSVDatabase{

    private:
        std::vector<CSVRow> db;
        std::vector<CSVRow>::const_iterator i;
        string filename;
        std::fstream file;
        AleatoryVariable<T> *var;
        Histogram *bin;
        int nsamples;
        float minval;
        float maxval;
    public:
        bool mustDiscretize;
        bool wrapValues;
        int lowersample;
        int uppersample;
        bool subset;

        CSVDatabase(AleatoryVariable<T> *var,string filename);
        ~CSVDatabase();
        void countSamples();
        void setDiscretization(float min,float max,int N=0);
        void readCSVhist(int col_index=0);
        void readCSV(int col_index=0);
        void display(const CSVRow& row);
        void display();
        int getTotalSamples(){return nsamples;}

};
    template< class T > CSVDatabase< T >::CSVDatabase(AleatoryVariable<T> *var,string filename)
    {
        this->filename=filename;
        this->var=var;
        file.open(filename.c_str(), std::ios::in);
        if(!file.is_open())
        {
            //should throw an exception
            std::cout<<"File not opened\n";
        }
        nsamples=0;
        mustDiscretize=false;
        wrapValues=true;
        lowersample=0;
        uppersample=0;
        subset=false;
    }

   template< class T > CSVDatabase< T >:: ~CSVDatabase(){file.close();}

   template< class T > void CSVDatabase< T >::countSamples()
    {
       if(!file.is_open())
       file.open(filename.c_str(), std::ios::in);
       string line ;
       std::vector<string> lines ;
       while( getline( file, line ) ) lines.push_back( line ) ;
       nsamples=lines.size();
       file.close();
    }

    template< class T > void CSVDatabase< T >::setDiscretization(float min,float max,int N)
    {
        if(N>0)
        {
            bin=new Histogram(min,max,N);
            bin->setBins(N);
        }
        else
        {
            countSamples();
            bin=new Histogram(min,max,nsamples);

        }
        this->minval=min;
        this->maxval=max;
    }

    template< class T > void CSVDatabase< T >::readCSV(int col_index)
    {
      if(!file.is_open())
      file.open(filename.c_str(), std::ios::in);
      //this string contains a line of the file
      String csvLine;
      // read EVERY line from the stream not very efficient but useful for small files
      int sampleindex=0;
          while( std::getline(file, csvLine) ){
            std::istringstream csvStream(csvLine);
            CSVRow csvRow;
            String csvCol;
            // read every element from the line that is seperated by commas
            // and put it into the vector or strings
            int index=0;
            while( std::getline(csvStream, csvCol, ',') )
            {
                if(subset==false || (subset==true && sampleindex>=lowersample && sampleindex<=uppersample))
                {
                //trim spaces
                remove(csvCol.begin(), csvCol.end(), ' ');
                //then if the string contains something put it
                if(csvCol.size()>0)
                    csvRow.push_back(csvCol);
                if(index==col_index)
                    var->enqueueInSequence(csvCol);
                index++;
                }
            }
            db.push_back(csvRow);
            sampleindex++;
         }
      nsamples=var->getSequenceLength();
      file.close();
    }

template< class T > void CSVDatabase< T >::display(const CSVRow& row){
  if(!row.size())
    return;
  CSVRowCI i=row.begin();
  std::cout<<*(i++);
  for(;i != row.end();++i)
    std::cout<<','<<*i;
}
template< class T > void CSVDatabase< T >::display(){
  if(!db.size())
    return;
  i=db.begin();
  for(; i != db.end(); ++i){
    display(*i);
    std::cout<<std::endl;
  }
}

#endif // CSVDATABASE_H
