/**
 * @file TransitionMatrix.cpp
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
#include "MarkovAnalyzer.hpp"


int TransitionMatrix::addNewIndexKey(std::list<int>* list){
  mTransition.addDimension(0);
  mIndex.push_back(*list);
  return mIndex.size()-1;
}

void TransitionMatrix::addTransition(int from,int to){
  //TODO tester les bornes
  mTotal+=1;
  mTransition[from][to]=mTransition[from][to]+1;
}

void TransitionMatrix::computeProbabilities(){
  int i;
  int j;
  int size=mTransition.size();

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      mTransition[i][j]=mTransition[i][j]/mTotal;
    }
  }
}

int TransitionMatrix::find(std::list<int>* someChord){
  int size=mIndex.size();
  int i;

  for (i = 0; i < size; i++) {
    if(*someChord == mIndex[i])
      return i;
  }
  return -1;
}

void TransitionMatrix::print(){
  int i,j;
  int sizeIndex=mIndex.size();
  int sizeElem;
  std::list<int>::iterator iter;
  std::list<int>::iterator end;

  for (i = 0; i < sizeIndex; i++) {
    sizeElem=mIndex[i].size();
    
    end=mIndex[i].end();
    for (iter = mIndex[i].begin(); iter!=end ; iter++) {
      printf("%f-",*iter);
    }
    printf("   ");
  }

  printf("\n");
  
  for (i = 0; i < sizeIndex; i++) {
    sizeElem=mIndex[i].size();
    
    end=mIndex[i].end();
    for (iter = mIndex[i].begin(); iter!=end ; iter++) {
      printf("%f-",*iter);
    }
    
    printf("   ");
    
    for (j = 0; j < sizeIndex; j++) {
      float test=mTransition[i][j];
      printf("%f   ",test);
    }

    printf("\n");
  }

}

