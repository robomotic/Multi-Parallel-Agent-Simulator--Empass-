#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/lexical_cast.hpp>
using namespace boost::numeric::ublas;


//! A function to sum the elements underlying a column
/*!
      \param data a boost matrix
      \param intex the index of the column that we want to sum
      \return either the average or just the sum of the elements in the column
      \sa sum_row()
*/

template <class T>T sum_column(const matrix<T> &data,int index,bool doAverage=false)
{
        T result=0;
        for (unsigned i = 0; i < data.size1 (); ++ i)
        {
                result+=data(i, index);
        }

        if(doAverage)result=result/data.size1();

        return result;

}

//! A function to sum the elements underlying a row
/*!
      \param data a boost matrix
      \param intex the index of the row that we want to sum
      \return either the average or just the sum of the elements in the row
      \sa sum_column()
*/

template <class T>T sum_row(const matrix<T> &data,int index,bool doAverage)
{
        T result=0;
        for (unsigned j = 0; j < data.size2 (); ++ j)
        {
                result+=data(index, j);
        }
        if(doAverage)result=result/data.size2();
        return result/data.size1();
}


//! A function that serializes the element in a row
/*!
      \param data a boost matrix
      \param inted the index of the row that we want to serialize to a string
      \return a string containing a serialized version of the row
      \sa sum_column()
*/

template <class T>string serialize_row(const matrix<T> &data,int index,unsigned int dimension)
{
    //[TO FIX]
        using boost::lexical_cast;
        using boost::bad_lexical_cast;
        string ser="";
        for (unsigned j = 0; j < data.size2 (); ++ j)
        {
            ser=ser+boost::lexical_cast<std::string>(data(index, j))+" ";
            if((j>dimension) && j%dimension==0)
                ser+=" \n ";
        }
        return ser;
}

//! A function to build a vector containing the sum of each row
/*!
      \param data a boost matrix
      \return a column vector containing the average of every row
      \sa sum_column()
*/

template <class T> boost::numeric::ublas::vector<T> sum_row(const matrix<T> &data)
{
        boost::numeric::ublas::vector<T> rvect(data.size1());

        T result=0;
        for (unsigned i = 0; i < data.size1 (); ++ i)
        {
            for (unsigned j = 0; j < data.size2 (); ++ j)
            {
                result+=data(i, j);
            }
            rvect(i)=result/data.size2();
            result=0;
         }

        return rvect;

}

//! A function to build a vector containing the sum of each row
/*!
      \param data a boost matrix
      \return the index of the maximum element for the average of the row
      \sa sum_row()
*/

template <class T> unsigned int find_max_vector(const matrix<T> &data)
{

        if(data.size1()==0)
            return 0;

        std::vector<T> tempvec(data.size1());


        T result=0;
        for (unsigned i = 0; i < data.size1 (); ++ i)
        {
            for (unsigned j = 0; j < data.size2 (); ++ j)
            {
                result+=data(i, j);
            }
            tempvec[i]=result/data.size2();
            result=0;
         }

        return distance(tempvec.begin(), max_element (tempvec.begin(),tempvec.end()));

}

//! A function to sum all the elements of the matrix and do the average
/*!
      \param data a boost matrix
      \param doAverage a flag to use the average or not after the sum
      \return either the average or just the sum of the elements in the column
      \sa sum_row(),sum_column()
*/
template <class T>T sum_all(const matrix<T> &data,bool doAverage)
{
        T result=0;
        for (unsigned i = 0; i < data.size1 (); ++ i)
        for (unsigned j = 0; j < data.size2 (); ++ j)
                result+=data(i, j);

        if(doAverage)result=result/(data.size1()*data.size2());
        return result;
}


#endif // MATRIXOPERATIONS_H
