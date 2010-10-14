#ifndef JOINTVARIABLE_H
#define JOINTVARIABLE_H

#include <map>
#include <vector>
#include <string>
#include <set>
#include <list>
#include "AleatoryVariable.h"
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::set;
using std::list;


namespace entropy {

template< class T > class JointVariable {
public:
        JointVariable();
        ~JointVariable();
        void setName(string name);
        string getName() const;
        void addCouple(T symbolX,T symbolY);
        float getSymbolProbability(pair<T,T> couple);
        inline unsigned int getSequenceLength() const;
        void estimateProbabilities();
        void setNonZeroEvents(int N);
        void resetNextSymbol() ;
        AleatoryVariable<T> *X;
        AleatoryVariable<T> *Y;
        pair<T,T> getNextSymbol() throw(int);
        bool isCompatibleSequence(int tau);
        void resetFrequencies(){f_map.clear();Nxy=0;}
        //non zero elements
        int Nxy;
private:
        string name;
        //probability map of the joint distribution
        map< pair<T,T>, float > p_map;
        //frequency map of the joint distribution
        map< pair<T,T>, int > f_map;
        set< pair<T,T> > alph;
        //an iterator on the frequency map
        typename map< pair<T,T>, int >::iterator jointIterator;
        //the init iterator
        bool first;




};

template< class T > JointVariable< T >::JointVariable() {
        //this->X=new AleatoryVariable<T>();
        //this->Y=new AleatoryVariable<T>();
        this->first = true;
        this->Nxy=0;
}

template< class T >  JointVariable< T >::~JointVariable() {

}

template< class T >  void JointVariable< T >::resetNextSymbol() {
        this->first = true;
}

template< class T >  void JointVariable< T >::setName(string name) {
        this->name = name;
}

template< class T >  string JointVariable< T >::getName() const {
        return this->name;
}

template< class T >  bool JointVariable< T >::isCompatibleSequence(int tau) {
    if (X->getSequenceLength()-tau<= Y->getSequenceLength())
    {

        return true;
    }
    else return false;

}


//! Append a pair of symbols to the current sequence,
    /*!
      \param T symbolX the first variable
      \param T symbolY the second variable
    */

template< class T >  void JointVariable< T >::addCouple(T symbolX,T symbolY ) {
    //add the symbol to the variables
    X->putSymbol(symbolX);
    Y->putSymbol(symbolY);
    //check if the pair exist
    jointIterator = this->f_map.find(pair<T,T>(symbolX,symbolY));
    //the couple wasn't there so we need to insert
    if ( jointIterator == f_map.end() ) {
        //and the frequency of the symbol is 1 because first time
        pair<T, T> key( symbolX, symbolY );
        this->f_map.insert( pair<pair<T, T>, int> (key, 1));
        this->alph.insert(pair<T,T> (key));
    }
    else {//symbol was there we need to look it up!
        //so we get the previous frequency
        int new_freq=(this->jointIterator)->second+1;
        //delete the old frequency
        this->f_map.erase(jointIterator);
        //then add the new value
        pair<T, T> key( symbolX, symbolY );
        this->f_map.insert(pair<pair<T, T>, int> (key, new_freq));

    }

    Nxy++;
}

template< class T > pair<T,T> JointVariable< T >::getNextSymbol() throw(int) {
        pair<T,T> tempSymbol;

        if ( first ) {
                this->jointIterator = this->f_map.begin();
                first = false;
        }

        if ( this->jointIterator != this->f_map.end() ) {
                tempSymbol = this->jointIterator->first;
                jointIterator++;
                return tempSymbol;
        }
        else {
                throw -1;
        }
}


template< class T >  float JointVariable< T >::getSymbolProbability(pair<T,T> symbol)
{
    typename map< pair<T,T>, float >::const_iterator symbolPosition;

    if ( (symbolPosition = this->p_map.find(symbol)) != this->p_map.end() ) {
            return (*symbolPosition).second;
    }
    return 0;
}

template< class T > void JointVariable< T >::estimateProbabilities() {
    //estimate the individual densities
    X->estimateProbabilities();
    Y->estimateProbabilities();

    //cout << "Variable "<<this->getName()<<endl;
    for ( jointIterator=f_map.begin() ; jointIterator != f_map.end(); jointIterator++ )
    {
        //estimate probabilities with the frequency approach

        int fxy=(jointIterator)->second;
        this->p_map.insert(pair<pair<T, T>, float> ((jointIterator)->first, (float)fxy/Nxy));
        //cout << (jointIterator)->first.first<<" "<<(jointIterator)->first.second<<" f="<<(float)fxy/Nxy<<endl;

    }

}


}

#endif // JOINTVARIABLE_H
