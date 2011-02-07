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

bool removeBias=false;

template< class T > float entropy(AleatoryVariable< T > &X);

template< class T > double jointEntropy(AleatoryVariable< T > &X,AleatoryVariable< T > &Y);
template< class T > double conditionalEntropy(AleatoryVariable< T > &X,AleatoryVariable< T > &Y);


//compute the mutual information between the time series X and the time series Y
// MI(X,Y,tau)=MI(X(t),Y(t+tau))
// or
// MI(Y,X,tau)=MI(Y(t),X(t+tau))
template< class T > float mutualInformation(JointVariable< T > &XY,int tau=0);

//compute the mutual information of order K between the time series X and the time series Y
// MI(X,Y,order)=MI(X(t),Y(t+1),...,Y(t+1-K))
// or
// MI(Y,X,order)

template< class T > float mutualInformationN(JointVariable< T > &XY,int order,int tau=1);

template< class T > float entropy(AleatoryVariable< T > &var) {
	T symbol;
        float tempEntropy = 0;

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

        if(tempEntropy<0)//let me know what happened
            var.dumpData();
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
                            //cout<<"P(X) "<<px<<" P(Y) "<<py<<" P(X,Y)"<<pxy<<endl;
                        }
                }
                //var.setNonZeroEvents(nonZeroEvents);
        } catch ( ... ) {
                XY.resetNextSymbol();
        }
        //cout<<"Total pxy "<<totalp<<endl;
        if(removeBias)
        {
            // i need to check the bloody formula!
            unsigned int Px=XY.X->getAlphabetSize();
            unsigned int Py=XY.Y->getAlphabetSize();
            unsigned int N=XY.getSequenceLength();
            float correction=(float)(Px*Py-Px-Py+1)/(float)(2*N);
            tempEntropy=tempEntropy-correction;
            cout<<"Correction ="<<correction<<" Entropy "<<tempEntropy+correction<<endl;
            if(tempEntropy<0) return -1;

        }
        return tempEntropy ;

    }
    else return -1;


}

//compute the mutual information of order K between the time series X and the time series Y
// MI(X,Y,order)=MI(X(t),Y(t+1),...,Y(t+1-K))
// or
// MI(Y,X,order)


template< class T > float mutualInformationN(JointVariable< T > &XY,int order,int tau)
{
    //first of all compute the probability distribution for every variable
    if(XY.X==NULL || XY.Y==NULL)
        return -1;
    //X and Y should contain 2 sequences
    if(XY.isCompatibleSequence(tau))
    {
        unsigned int index=0;
        XY.X->resetFrequencies();
        XY.Y->resetFrequencies();

        while((index+tau+order) < XY.X->getSequenceLength())
        {
        XY.addCouple(XY.X->getSymbolInSeq(index),XY.Y->getSymbolsInSeq(index+tau,index+tau+order));
        //cout<<"Adding X: "<<XY.X->getSymbolInSeq(index)<<" Y "<<XY.Y->getSymbolsInSeq(index+tau,index+tau+order)<<endl;
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
                            //cout<<"P(X) "<<px<<" P(Y) "<<py<<endl;
                        }
                }
                //var.setNonZeroEvents(nonZeroEvents);
        } catch ( ... ) {
                XY.resetNextSymbol();
        }
        //cout<<"Total pxy "<<totalp<<endl;
        if(removeBias)
        {
            // i need to check the bloody formula!
            unsigned int Px=XY.X->getAlphabetSize();
            unsigned int Py=XY.Y->getAlphabetSize();
            unsigned int N=XY.getSequenceLength();
            float correction=(float)(Px*Py-Px-Py+1)/(float)(2*N);
            tempEntropy=tempEntropy-correction;
            cout<<"Correction ="<<correction<<" Entropy "<<tempEntropy+correction<<endl;
            if(tempEntropy<0) return -1;

        }
        return tempEntropy ;

    }
    else return -1;


}

}

#endif /* ENTROPY_H_ */


