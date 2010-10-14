
#ifndef ICOSISO_H
#define ICOSISO_H

#include "Filters/LowPassFilter.h"
#include <math.h>

namespace Controllers {


/**
  * class IcoSiso
  * The standard ICO controller in SISO mode: single input single output
  */

class IcoSiso
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  IcoSiso ( );

  /**
   * Empty Destructor
   */
  virtual ~IcoSiso ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * Create an Ico learning neuron without filters
   * @param  isLearning
   * @param  initWeight
   */
   IcoSiso (bool isLearning, float initWeight )
  {
       this->isLearning=isLearning;
       this->w1=initWeight;
       this->w0=1.0;
       this->u0_prev=0.0;
       this->u0=0.0;
       this->u1=0.0;
       this->mu=1.0;
  }

   /**
   * Create an Ico learning neuron with 2 filters
   * @param  isLearning
   * @param  initWeight
   */
   IcoSiso (bool isLearning, float initWeight,float damping )
  {
       this->isLearning=isLearning;
       this->w1=initWeight;
       this->w0=1.0;
       this->fir0=new LowPassFilter(damping);
       this->fir1=new LowPassFilter(damping);
       this->u0_prev=0.0;
       this->u0=0.0;
       this->u1=0.0;
       this->mu=1.0;

  }

   /**
   * Create an Ico learning neuron with 2 filters
   * @param  isLearning
   * @param  initWeight
   * @param  damping
   * @param  maxinput
   */
   IcoSiso (bool isLearning, float initWeight,float damping,float maxinput )
  {
       this->isLearning=isLearning;
       this->w1=initWeight;
       this->w0=1.0;
       this->fir0=new LowPassFilter(damping,maxinput);
       this->fir1=new LowPassFilter(damping,maxinput);
       this->u0_prev=0.0;
       this->u0=0.0;
       this->u1=0.0;

  }

  /**
   * @param  isLearning
   */
   IcoSiso (bool isLearning )
  {
       this->isLearning=isLearning;
       this->w1=1.0;
       this->w0=1.0;
  }


  /**
   * Compute the output from the x0 and x1 inputs. Note that they should be filtered
   * first with a LowPassFilter
   * @param  input_reflex
   * @param  input_distal
   */
  void compute (float input_reflex, float input_distal )
  {
      //first of all update the filter if initialized
      if(this->fir0!=NULL && this->fir1!=NULL)
      {
          this->fir0->updateFilter(input_reflex);
          this->fir1->updateFilter(input_distal);
          u0=this->fir0->getOutput();
          u1=this->fir1->getOutput();
      }
      else
      {
          u0=input_reflex;
          u1=input_distal;
      }

      if(!isLearning)
      {
          output=w0*u0;
      }
      else{
          this->derivReflex=u0-u0_prev;
          this->u0_prev=u0;
          this->w1+=derivReflex*u1*mu;

      }
  }


  /**
   * A sigma output function
   * @param  val
   * @param  range
   * @param  saturation
   */
  static float getSigmaValue (float val, float range, float saturation )
  {
      float temp=range/(1+exp(-val/(saturation/2)))-range/2;
      if(abs(temp)>range/2) return 0;
      else return temp;
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

  bool isLearning;
  float output;
  float range;
  float saturation;
  float derivReflex;
  float reflex;
  float w0;
  float w1;
  float mu;
  bool feedback_inhibition;
  bool input_inhibition;
  float gain;
  // A low pass filter for the reflex
  LowPassFilter* fir0;
  // A low pass filter for the distal aka predictor
  LowPassFilter* fir1;
  //filtered values
  float u0;
  float u1;
  float u0_prev;

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of isLearning
   * @param new_var the new value of isLearning
   */
  void setIsLearning ( bool new_var )   {
      isLearning = new_var;
  }

  /**
   * Get the value of isLearning
   * @return the value of isLearning
   */
  bool getIsLearning ( )   {
    return isLearning;
  }

  /**
   * Set the value of output
   * @param new_var the new value of output
   */
  void setOutput ( float new_var )   {
      output = new_var;
  }

  /**
   * Get the value of output
   * @return the value of output
   */
  float getOutput ( )   {
    return output;
  }

  /**
   * Set the value of range
   * @param new_var the new value of range
   */
  void setRange ( float new_var )   {
      range = new_var;
  }

  /**
   * Get the value of range
   * @return the value of range
   */
  float getRange ( )   {
    return range;
  }

  /**
   * Set the value of saturation
   * @param new_var the new value of saturation
   */
  void setSaturation ( float new_var )   {
      saturation = new_var;
  }

  /**
   * Get the value of saturation
   * @return the value of saturation
   */
  float getSaturation ( )   {
    return saturation;
  }

  /**
   * Set the value of derivReflex
   * @param new_var the new value of derivReflex
   */
  void setDerivReflex ( float new_var )   {
      derivReflex = new_var;
  }

  /**
   * Get the value of derivReflex
   * @return the value of derivReflex
   */
  float getDerivReflex ( )   {
    return derivReflex;
  }

  /**
   * Set the value of reflex
   * @param new_var the new value of reflex
   */
  void setReflex ( float new_var )   {
      reflex = new_var;
  }

  /**
   * Get the value of reflex
   * @return the value of reflex
   */
  float getReflex ( )   {
    return reflex;
  }

  /**
   * Set the value of w0
   * @param new_var the new value of w0
   */
  void setW0 ( float new_var )   {
      w0 = new_var;
  }

  /**
   * Get the value of w0
   * @return the value of w0
   */
  float getW0 ( )   {
    return w0;
  }

  /**
   * Set the value of w1
   * @param new_var the new value of w1
   */
  void setW1 ( float new_var )   {
      w1 = new_var;
  }

  /**
   * Get the value of w1
   * @return the value of w1
   */
  float getW1 ( )   {
    return w1;
  }

  /**
   * Set the value of mu
   * @param new_var the new value of mu
   */
  void setMu ( float new_var )   {
      mu = new_var;
  }

  /**
   * Get the value of mu
   * @return the value of mu
   */
  float getMu ( )   {
    return mu;
  }

  /**
   * Set the value of feedback_inhibition
   * @param new_var the new value of feedback_inhibition
   */
  void setFeedback_inhibition ( bool new_var )   {
      feedback_inhibition = new_var;
  }

  /**
   * Get the value of feedback_inhibition
   * @return the value of feedback_inhibition
   */
  bool getFeedback_inhibition ( )   {
    return feedback_inhibition;
  }

  /**
   * Set the value of input_inhibition
   * @param new_var the new value of input_inhibition
   */
  void setInput_inhibition ( bool new_var )   {
      input_inhibition = new_var;
  }

  /**
   * Get the value of input_inhibition
   * @return the value of input_inhibition
   */
  bool getInput_inhibition ( )   {
    return input_inhibition;
  }

  /**
   * Set the value of gain
   * @param new_var the new value of gain
   */
  void setGain ( float new_var )   {
      gain = new_var;
  }

  /**
   * Get the value of gain
   * @return the value of gain
   */
  float getGain ( )   {
    return gain;
  }

  /**
   * Set the value of u0
   * A low pass filter for the reflex
   * @param new_var the new value of u0
   */
  void setU0 ( LowPassFilter* new_var )   {
      fir0 = new_var;
  }

  /**
   * Get the value of u0
   * A low pass filter for the reflex
   * @return the value of u0
   */
  float getU0 ( )   {
    return fir0->getOutput();
  }

  /**
   * Set the value of u1
   * A low pass filter for the distal aka predictor
   * @param new_var the new value of u1
   */
  void setU1 ( LowPassFilter* new_var )   {
      fir1 = new_var;
  }

  /**
   * Get the value of u1
   * A low pass filter for the distal aka predictor
   * @return the value of u1
   */
  float getU1 ( )   {
    return fir1->getOutput();
  }
private:


  void initAttributes ( ) ;

};
}; // end of package namespace

#endif // ICOSISO_H
