/*
 * AleatoryVariable.h
 *
 *  Created on: October,2010
 *      Author: Paolo Di Prodi <epokh@elec.gla.ac.uk>
 *
 *     License: GPL
 */

#ifndef ENTROPY_H_
#define ENTROPY_H_

#include "AleatoryVariable.h"
#include "JointVariable.h"

#include <cmath>
#include <set>
#include <map>
#include <list>

using std::set;
using std::map;
using std::pair;
using std::list;

namespace entropy{

template< class T > double entropy(AleatoryVariable< T > &X);

template< class T > double jointEntropy(AleatoryVariable< T > &X,AleatoryVariable< T > &Y);
template< class T > double conditionalEntropy(AleatoryVariable< T > &X,AleatoryVariable< T > &Y);

//compute the mutual information between the time series X and the time series Y
// MI(tau)=MI(X(t),Y(t+tau))
template< class T > float mutualInformation(JointVariable< T > &XY,int tau=0);


template< class T > double entropy(AleatoryVariable< T > &var) {
	T symbol;
	double tempEntropy = 0;

	var.resetNextSymbol();
	try {
		while ( true ) {
                        //this is very imporant we scan every symbol
			symbol = var.getNextSymbol();
                        //there could be symbols with 0 probability (never occurred)
                        if(var.getSymbolProbability(symbol)>0)
                        {
                            tempEntropy -= var.getSymbolProbability(symbol) * log2(var.getSymbolProbability(symbol));

                        }
		}
	} catch ( ... ) {
		var.resetNextSymbol();
	}

        return tempEntropy;
}

template< class T > float mutualInformation(JointVariable< T > &XY,int tau)
{
    //first of all compute the probability distribution for every variable

    //X and Y should contain 2 sequences
    if(XY.isCompatibleSequence(tau))
    {
        unsigned int index=0;
        unsigned int end_sample=XY.X->getSequenceLength()-tau;
        XY.X->resetFrequencies();
        XY.Y->resetFrequencies();

        while(index<end_sample)
        {
        XY.addCouple(XY.X->getSymbolInSeq(index),XY.Y->getSymbolInSeq(index+tau));
        //cout<<"Adding X: "<<XY.X->getSymbolInSeq(index)<<" Y "<<XY.Y->getSymbolInSeq(index+tau)<<endl;
        index++;
        }

        pair<T,T> symbolXY;
        float tempEntropy = 0;
        int nonZeroEvents=0;
        float totalp=0;
        XY.resetNextSymbol();
        //now need to estimate the probabilities
        XY.estimateProbabilities();
        try {
                while ( true ) {
                        //this is very imporant we scan every symbol
                        symbolXY = XY.getNextSymbol();
                        //cout<<"X "<<symbolXY.first<<" Y "<<symbolXY.second<<endl;
                        float px=XY.X->getSymbolProbability(symbolXY.first);
                        float py=XY.Y->getSymbolProbability(symbolXY.second);
                        float pxy=XY.getSymbolProbability(symbolXY);
                        //there could be symbols with 0 probability (never occurred)
                        if(px>0 && py>0)
                        {
                            tempEntropy += pxy * log2(pxy/(px*py));
                            totalp+=pxy;
                            nonZeroEvents++;
                        }
                }
                //var.setNonZeroEvents(nonZeroEvents);
        } catch ( ... ) {
                XY.resetNextSymbol();
        }
        cout<<"Total pxy "<<totalp<<endl;
        return tempEntropy ;

    }
    else return -1;


}

}

#endif /* ENTROPY_H_ */


