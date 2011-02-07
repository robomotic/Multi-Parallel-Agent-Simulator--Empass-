#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <sstream>
using namespace std;

using std::string;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::streamsize;


// A histogram class.
// The Histogram object can keep a tally of values
// within a range, the range is arranged into some
// number of bins specified during construction.
// Any allocation of a Histogram object may throw
// a bad_alloc exception.
class Histogram
{

   private:
      float Start,End,nBins_by_interval;
      unsigned int nBins;
      unsigned int* freq;
      unsigned int lastbin;

   public:
      // Construct a histogram that can count
      // within a range of values.
      // All bins of the histogram are set to zero.
      Histogram(const float& Start,const float& End,const unsigned int& nSamples)
      {
         this->Start=Start;
         this->End=End;
         nBins=sqrt(nSamples);
         nBins_by_interval=nBins/(End-Start);
         freq=new unsigned int[nBins];
         for(unsigned int i(0); i < nBins; ++i)
            freq[i] = 0U;
      }

      // Construct a histogram by copying another one.
      Histogram(const Histogram& other):
         Start(other.Start),
         nBins_by_interval(other.nBins_by_interval),
         nBins(other.nBins),
         freq( new unsigned int[nBins] )
      {
         for(unsigned int i(0); i < nBins; ++i)
            freq[i] = other.freq[i];
      }
      // Deallocate the memory that was allocated for
      // the tallied counts.
      ~Histogram() {delete[] freq;}

      //
      void setBins(unsigned int nBins)
      {
          this->nBins=nBins;
         nBins_by_interval=nBins/(End-Start);
         freq=new unsigned int[nBins];
         for(unsigned int i(0); i < nBins; ++i)
            freq[i] = 0U;
      }
      // Set this histogram equal to another.
      Histogram& operator=(const Histogram& other)
      {
         if( this != &other )
         {
            Start = other.Start;
            nBins_by_interval = other.nBins_by_interval;
            if( nBins != other.nBins )
            {
               nBins = other.nBins;
               delete[] freq;
               freq = new unsigned int[nBins];
            }
            for(unsigned int i(0); i < nBins; ++i)
               freq[i] = other.freq[i];
         }
         return *this;
      }
      // Increase the count for the bin that holds a
      // value that is in range for this histogram.
      void Add(const float& x)
      {
         const unsigned int i(
               static_cast<unsigned int>(
                  (x-Start)*nBins_by_interval) );
         if( i < nBins ) freq[i]++;
         lastbin=i;
      }

      string getLastBin()
      {
        std::string s;
        std::stringstream out;
        out << lastbin;
        s = out.str();
        return s;
      }
      // Get the sum of all counts in the histogram.
      unsigned int GetTotalCount() const
      {
         unsigned int c(0U);
         for( unsigned int i(0); i < nBins; ++i )
            c += freq[i];
         return c;
      }

};

#endif // HISTOGRAM_H
