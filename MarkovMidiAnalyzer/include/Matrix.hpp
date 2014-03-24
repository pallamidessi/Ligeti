/**
 * @file Matrix.cpp
 * @author Pallamidessi Joseph
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
**/  

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
template<typename T>
  class Matrix {
    public:
      
      Matrix(){
        mSizeGrid=0;
      }

      Matrix (size_t sizeGrid,T defaultValue){
        int i;
        std::vector<T> newLine;
        mSizeGrid=sizeGrid;

        for (i = 0; i < sizeGrid; i++) {
          newLine.push_back(defaultValue);
        }

        for (i = 0; i < sizeGrid; i++) {
          mMat.push_back(newLine);
        }

      }
      
      int size(){
        return mSizeGrid;
      }
      
      int addDimension(T defaultValue){
        int i;
        std::vector<T> newLine;
        
        //for (i = 0; i < mSizeGrid; i++) {
        //  mMat[i].push_back(defaultValue);
        //}

        for (i = 0; i < mSizeGrid+1; i++) {
          newLine.push_back(defaultValue);
        }

        mMat.push_back(newLine);
        mSizeGrid++;
      }

      virtual ~Matrix ();
      
      T operator()(int i,int j){
        /* Raise an exception instead
         if(i>mSizeGrid || i<0 || j>mSizeGrid || j<0)
          return -1;
        */
        return mMat[i][j];
      }
      
      std::vector<T> operator[](int i){
        return mMat[i];
      }
      

    private:
      /* data */
      static int mSizeGrid;
      std::vector< std::vector<T> > mMat;
};
template<typename T>
int Matrix<T>::mSizeGrid=0;

