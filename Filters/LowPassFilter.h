
#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include <algorithm>
/**
  * class LowPassFilter
  * A 2 pole low pass filter useful for the Ico class.
  */

class LowPassFilter
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  LowPassFilter ( );

  /**
   * Empty Destructor
   */
  virtual ~LowPassFilter ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * Initialization with the filter coefficient and the maximum input predicted for
   * the filter.
   * @param  b
   * @param  max_input
   */
   LowPassFilter (float b, float max_input )
  {
    buffer[0]=0.0;
    buffer[1]=0.0;
    normconst=0.0;
    beta=b;
    normalizeFilter(max_input);
    isNormalized=true;
  }


  /**
   * @param  b
   */
   LowPassFilter (float b )
  {
    buffer[0]=0.0;
    buffer[1]=0.0;
    isNormalized=false;
    beta=b;
  }


  /**
   * @return float
   */
  float getOutput ( )
  {
    return next_output;
  }


  /**
   * @param  max_input
   */
  void normalizeFilter (float max_input )
  {
     resetBuffer();
     for(int k=0;k<10000;k++)
            {
              if(k>=10 && k<=1000) 
                  updateFilter(max_input);
              else
                  updateFilter(0.0);
              normconst=std::max(normconst,next_output);
            }
    resetBuffer();
    if(normconst<=0)
                normconst=1.0;
    
  }


  /**
   */
  void resetBuffer ( )
  {
    buffer[0]=0.0;
    buffer[1]=0.0;
    next_output=0.0;
  }


  /**
   * @param  input
   */
  void updateFilter (float input )
  {
    buffer[1]=beta*(buffer[0])+(1-beta)*input;
    buffer[0]=buffer[1];
    if(isNormalized)
    next_output=buffer[1]/normconst;
    else
    next_output=buffer[1];
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  // beta is the "spring" coefficient
  float beta;
  // This is the buffer of the filter: x(t)=b*x(t-1)+(1-b)*input
  float buffer[2];
  // it is true if the filter is normalized to a unitary output, otherwise is non normalised
  bool isNormalized;
  // the next computed output of the filter
  float next_output;
  // this is the normalised constant to give a unitary output when the input is maximum
  float normconst;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of beta
   * beta is the "spring" coefficient
   * @param new_var the new value of beta
   */
  void setBeta ( float new_var )   {
      beta = new_var;
  }

  /**
   * Get the value of beta
   * beta is the "spring" coefficient
   * @return the value of beta
   */
  float getBeta ( )   {
    return beta;
  }

  /**
   * Get the value of buffer
   * This is the buffer of the filter: x(t)=b*x(t-1)+(1-b)*input
   * @return the value of buffer
   */
  float* getBuffer ( )   {
    return buffer;
  }

  /**
   * Set the value of isNormalized
   * it is true if the filter is normalized to a unitary output, otherwise is non
   * normalised
   * @param new_var the new value of isNormalized
   */
  void setIsNormalized ( bool new_var )   {
      isNormalized = new_var;
  }

  /**
   * Get the value of isNormalized
   * it is true if the filter is normalized to a unitary output, otherwise is non
   * normalised
   * @return the value of isNormalized
   */
  bool getIsNormalized ( )   {
    return isNormalized;
  }

  /**
   * Get the value of next_output
   * the next computed output of the filter
   * @return the value of next_output
   */
  float getNext_output ( )   {
    return next_output;
  }

  /**
   * Set the value of normconst
   * this is the normalised constant to give a unitary output when the input is
   * maximum
   * @param new_var the new value of normconst
   */
  void setNormconst ( float new_var )   {
      normconst = new_var;
  }

  /**
   * Get the value of normconst
   * this is the normalised constant to give a unitary output when the input is
   * maximum
   * @return the value of normconst
   */
  float getNormconst ( )   {
    return normconst;
  }
private:


  void initAttributes ( ) ;

};

#endif // LOWPASSFILTER_H
