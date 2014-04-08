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


TransitionMatrix::TransitionMatrix ():mTotal(0){};
TransitionMatrix::~TransitionMatrix (){};

int TransitionMatrix::addNewIndexKey(std::list<int>* list){
  mTransition.addDimension(0);
  mIndex.push_back(*list);
  mFreq.push_back(0);
  return mIndex.size()-1;
}

void TransitionMatrix::addTransition(int from,int to){
  //TODO tester les bornes
  mFreq[to]+=1;
  //mTransition[from][to]=mTransition[from][to]+1;
  mTransition.incr(from,to);
}

void TransitionMatrix::computeProbabilities(){
  int i,j;
  int freq;
  int size=mTransition.size();

  for (i = 0; i < size; i++) {
    freq=mFreq[i];
    for (j = 0; j < size; j++) {
      mTransition[i][j]=mTransition[i][j]/freq;
    }
  }
}

void TransitionMatrix::sumProbabilities(){
  int i,j;
  float sum;
  int size=mTransition.size();

  for (i = 0; i < size; i++) {
    sum=0;
    for (j = 0; j < size; j++) {
      sum+=mTransition[i][j];
    }
    printf("%f ",sum);
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
  printf("Size matrix %d \n",sizeIndex);
  printf("Number element %d \n",mTotal);
  for (i = 0; i < sizeIndex; i++) {
    sizeElem=mIndex[i].size();

    end=mIndex[i].end();
    for (iter = mIndex[i].begin(); iter!=end ; iter++) {
      printf("%d-",*iter);
    }
    printf(" ");
  }

  printf("\n");

  for (i = 0; i < sizeIndex; i++) {
    sizeElem=mIndex[i].size();

    end=mIndex[i].end();
    for (iter = mIndex[i].begin(); iter!=end ; iter++) {
      printf("%d-",*iter);
    }

    printf("   ");

    for (j = 0; j < sizeIndex; j++) {
      float test=mTransition[i][j];
      if(test!=0)
        printf("%2.2e ",test);
    }

    printf("\n");
  }
}

int TransitionMatrix::createFirstChord(juce::MidiMessageSequence* track){
  
  int range=mIndex.size();
  int indexChord;
  int stdDuration=100;
  uint8 stdVelocity=65;

  std::list<int> chord;
  std::list<int>::iterator iter;
  std::list<int>::iterator end;
  juce::MidiMessage curOn;
  juce::MidiMessage curOff;

  indexChord=rand()%range;
  chord=mIndex[indexChord];
  end=chord.end();

  for (iter = chord.begin(); iter!=end; iter++) {
    curOn=juce::MidiMessage::noteOn(2,*iter,stdVelocity);
    curOn.setTimeStamp(0);
    
    curOff=juce::MidiMessage::noteOff(2,*iter,stdVelocity);
    curOff.setTimeStamp(stdDuration);

    track->addEvent(curOn);
    track->addEvent(curOff);
  }
  
  track->updateMatchedPairs();
  
  return indexChord;
}

int TransitionMatrix::createNewChord(juce::MidiMessageSequence* track,int prevChordIndex){
  static int mainTimestamp=0;
  int range=mIndex.size();
  int indexChord;
  float nextChord;
  int stdDuration=50;
  uint8 stdVelocity=65;
  float inf=0;
  float sup=0;
  float tmp=0;
  bool cont=true;
  std::list<int> chord;
  std::list<int>::iterator iter;
  std::list<int>::iterator end;
  juce::MidiMessage curOn;
  juce::MidiMessage curOff;
  

  nextChord=((float)(rand()%10000))/((float)(10000));
  
  printf("%f\n",nextChord);
  for (indexChord = 0; indexChord < mTransition.size()-1 && cont; indexChord++) {
    tmp=sup;
    sup+=mTransition[prevChordIndex][indexChord];
    if (nextChord<=sup && nextChord>=inf ) {
      cont=false;
    }
    inf=tmp;
  }
  

  chord=mIndex[indexChord];
  end=chord.end();

  for (iter = chord.begin(); iter!=end; iter++) {
    curOn=juce::MidiMessage::noteOn(2,*iter,stdVelocity);
    curOn.setTimeStamp(mainTimestamp);
    
    curOff=juce::MidiMessage::noteOff(2,*iter,stdVelocity);
    curOff.setTimeStamp(mainTimestamp+stdDuration);

    track->addEvent(curOn);
    track->addEvent(curOff);
  }
  mainTimestamp+=stdDuration;
  track->updateMatchedPairs();
  
  return indexChord;
}
