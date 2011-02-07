/*
 * AleatoryVariable.h
 *
 *  Created on: October,2010
 *      Author: Paolo Di Prodi <epokh@elec.gla.ac.uk>
 *
 *     License: GPL
 */

#ifndef ALEATORYVARIABLE_H_
#define ALEATORYVARIABLE_H_

#include <map>
#include <vector>
#include <string>
#include <set>
#include <list>
#include <iostream>

using namespace std;

using std::map;
using std::pair;
using std::vector;
using std::string;
using std::set;
using std::list;
using std::cout;
using std::ofstream;

namespace entropy {

template< class T > class AleatoryVariable {
public:
	AleatoryVariable();
	~AleatoryVariable();
	void setName(string name);
	string getName() const;
	inline unsigned int getSymbolsNumber() const;
	T getNextSymbol() throw(int);
	void resetNextSymbol();
	double getSymbolProbability(T symbol) const;
        T getSymbolInSeq(unsigned int index) throw(int);
        void addSymbol(T symbol, double probability) throw(int);
        void enqueueInSequence(T symbol);
        void putSymbol(T symbol);
        inline unsigned int getSequenceLength() const;
        void estimateProbabilities();
        void setNonZeroEvents(int N);
        void dumpGnuplotData();
        void dumpData();
        void resetFrequencies(){f_map.clear();NZ=0;}
        int getNonZeroEvents(){return NZ;}
        //gnuplot data structure for generating graph
        std::map<T, float> bin_data;
        void setAlphabetSize(unsigned int size){alphabet_dim=size;}
        unsigned int getAlphabetSize(){return alphabet_dim;}
        T getSymbolsInSeq(unsigned int low,unsigned int up) throw(int);
private:
	string name;
	bool first;
        //probability map: is the probability estimation
        map< T, float > p_map;
        //frequency map: count how many occurencies
        map< T, int > f_map;
	set< T > alph;
	typename set< T >::const_iterator alphIterator;
        typename map<T,int>::iterator fIterator;
        typename map<T,float>::iterator pIterator;
        std::vector< T > sequence;
        int NZ;//non zero events
        unsigned int alphabet_dim;
};

template< class T > AleatoryVariable< T >::AleatoryVariable() {
	this->first = true;
        this->NZ=0;
        this->name="X";
        this->alphabet_dim=0;
        this->p_map.clear();
        this->f_map.clear();
}

template< class T >  AleatoryVariable< T >::~AleatoryVariable() {

}

template< class T >  void AleatoryVariable< T >::setName(string name) {
	this->name = name;
}

template< class T >  string AleatoryVariable< T >::getName() const {
	return this->name;
}

template< class T >  inline unsigned int AleatoryVariable< T >::getSymbolsNumber() const {
	return static_cast< unsigned int >((this->alph).size());
}

template< class T > T AleatoryVariable< T >::getNextSymbol() throw(int) {
	T tempSymbol;

	if ( first ) {
		this->alphIterator = this->alph.begin();
		first = false;
	}

	if ( this->alphIterator != this->alph.end() ) {
		tempSymbol = *(this->alphIterator);
                alphIterator++;
		return tempSymbol;
	}
	else {
		throw -1;
	}
}

template< class T > T AleatoryVariable< T >::getSymbolInSeq(unsigned int index) throw(int) {

        if (index>sequence.size() ) {
                 throw -1;
        }
        else {
                return sequence[index];
        }
}

template< class T > T AleatoryVariable< T >::getSymbolsInSeq(unsigned int low,unsigned int up) throw(int) {

        //now we need to compose the sequence: it must work only for strings we should check the type
        // but I'm lazy
        T concat;
        if (low<sequence.size() && low<up && up<sequence.size()) {
                for(unsigned int k=low;k<=up;++k)
                {
                    concat=concat+sequence[k];
                }
                return concat;
        }
        else {
                throw -1;
        }
}


template< class T >  void AleatoryVariable< T >::resetNextSymbol() {
	this->first = true;
}

template< class T > double AleatoryVariable< T >::getSymbolProbability(T symbol) const {
        typename map< T, float >::const_iterator symbolPosition;

        if ( (symbolPosition = this->p_map.find(symbol)) != this->p_map.end() ) {
		return (*symbolPosition).second;
	}
	return 0;
}

//be careful this operation overwrites the previous operation
template< class T > void AleatoryVariable< T >::addSymbol(T symbol, double probability) throw(int) {
        if(probability>=0 && probability<=1.0)
        {   this->alph.insert(symbol);
            //this->p_map.insert(pair< T, double >(symbol, probability));
        }
        else throw -1;
}

template< class T > void AleatoryVariable< T >::estimateProbabilities() {
    //first of all delete the previously estimated probabilities
    this->p_map.clear();
    // show content:
    //cout << "Variable "<<this->getName()<<endl;
    for ( fIterator=f_map.begin() ; fIterator != f_map.end(); fIterator++ )
    {
        //estimate probabilities with the frequency approach
        this->p_map.insert(pair< T, float >((*fIterator).first, (float)(*fIterator).second/ (float)NZ));
        //cout << (*fIterator).first << " => " <<(float)(*fIterator).second/ (float)NZ<< endl;

    }
    //cout<<"NZ="<<NZ<<endl;
}

template< class T > void AleatoryVariable< T >::dumpGnuplotData() {

    // show content:
    //cout << "Variable "<<this->getName()<<endl;
    for ( pIterator=p_map.begin() ; pIterator != p_map.end(); pIterator++ )
    {

        //cout << (*pIterator).first << " => " << (*pIterator).second << endl;
        this->bin_data[(*pIterator).first]=(*pIterator).second;

    }
}

template< class T > void AleatoryVariable< T >::dumpData() {

    // show content:
    cout << "P("<<this->getName()<<")"<<endl;
    for ( pIterator=p_map.begin() ; pIterator != p_map.end(); pIterator++ )
    {

       // cout << (*pIterator).first << " => " << (*pIterator).second << endl;

    }
    cout << "F("<<this->getName()<<")"<<endl;
    for ( fIterator=f_map.begin() ; fIterator != f_map.end(); fIterator++ )
    {

        cout << (*fIterator).first << " => " <<(*fIterator).second<< endl;

    }
    cout <<" N="<<NZ<<endl;

}

//! Set the number of non zero symbols that were found in the sequence
    /*!
      \param T symbol the symbol to be enqueued
    */

template< class T > void AleatoryVariable< T >::setNonZeroEvents(int N){
    this->NZ=N;
}

//! Append the symbol to the current sequence, the list can be reset on request
    /*!
      \param T symbol the symbol to be enqueued
    */

template< class T > void AleatoryVariable< T >::enqueueInSequence(T symbol) {
        //push the symbol in the sequence always
        this->sequence.push_back(symbol);
        fIterator = f_map.find(symbol);
        //symbol wasn't there so we need to insert
        if ( fIterator == f_map.end() ) {
            //and the frequency of the symbol is 1 because first time
            this->f_map.insert(pair< T, int >(symbol, 1));
            this->alph.insert(symbol);

        }
        else {//symbol was there we need to look it up!
            //so we get the previous frequency
            int new_freq=(this->fIterator)->second+1;
            this->f_map.erase(fIterator);
            this->f_map.insert(pair< T, int >(symbol, new_freq));

        }
        NZ++;
}

template< class T > void AleatoryVariable< T >::putSymbol(T symbol) {

        fIterator = f_map.find(symbol);
        //symbol wasn't there so we need to insert
        if ( fIterator == f_map.end() ) {
            //and the frequency of the symbol is 1 because first time
            this->f_map.insert(pair< T, int >(symbol, 1));

        }
        else {//symbol was there we need to look it up!
            //so we get the previous frequency
            int new_freq=(this->fIterator)->second+1;
            this->f_map.erase(fIterator);
            this->f_map.insert(pair< T, int >(symbol, new_freq));

        }
        this->NZ++;
}

template< class T > inline unsigned int AleatoryVariable< T >::getSequenceLength() const {
        return static_cast< unsigned int >((this->sequence).size());
}

}

#endif /* ALEATORYVARIABLE_H_ */

