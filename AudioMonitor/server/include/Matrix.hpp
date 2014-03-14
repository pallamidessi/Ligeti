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

template<typename T>
  class Matrix {
    public:
      
      Matrix (size_t sizeGrid,T defaultValue):mSizeGrid(sizeGrid){
        mMat=new *T[sizeGrid];

        for (i = 0; i < sizeGrid; i++) {
          T[i]=new T[sizeGrid];
        }
        for (i = 0; i < sizeGrid; i++) {
          for (j = 0; j < sizeGrid; j++) {
            T[i][j]=defaultValue;
          }
        }
      }
      
      int size(){
        return mSizeGrid;
      }
      
      virtual ~Matrix ();
      T operator()(int i,int j){
        /* Raise an exception instead
         if(i>mSizeGrid || i<0 || j>mSizeGrid || j<0)
          return -1;
        */
        return mMat[i][j];
      }
      
      T* operator[](int i){
        return mMat[i];
      }

    private:
      /* data */
      int mSizeGrid;
      T** mMat;
};

