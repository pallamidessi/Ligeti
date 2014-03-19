/**
 * @file CellularAutoCompositor.cpp
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

#include "CellularAutoCompositor.hpp"
    
CellularAutoCompositor::CellularAutoCompositor(size_t gridSize,int maxClient,std::string synthesisIp,
                                              int portnum,bool dgb):
                        Compositor(synthesisIp,portnum,dbg),conwayRules<int,int,1,0> mGridSize(gridSize){
  
  int nbClientSquared=ceil(sqrt(maxClient));
  int spaceBetweenClient=gridSize/nbClientSquared;
  
  for (i = 0; i < nbClientSquared; i++) {
    for (j = 0; j < nbClientSquared; j++) {
      mPlaceAvailabeOnGrid.push_back(true,new Point<int,int>(i*spaceBetweenClient,j*spaceBetweenClient));
    }
  }

  mGrid=new Matrix<int>(gridSize,0);
}

CellularAutoCompositor::~CellularAutoCompositor(){};

CellularAutoCompositor::addClientOnGrid(EASEAClientData* cl){
  mClientOnGrid.insert(cl,mPlaceAvailabeOnGrid.back());
  mPlaceAvailabeOnGrid.pop_back();
}

//Deferencement multiple beurk ...
void CellularAutoCompositor::nextStep(){
  Matrix<int>* next=new Matrix<int>(mGridSize,0);
  
  for (i = 0; i < mGridSize; i++) {
    for (j = 0; j < mGridSize; j++) {
      if (*mGrid[i][j]) {
        next[i][j]=aliveRules(*mGrid[i][j],mGrid);
      }
      else{
        next[i][j]=deadRules(*mGrid[i][j],mGrid);
      }
    }
  }
  //delete grid
  mGrid=next;
}

void CellularAutoCompositor::startTempoMode(Metronome* tempo){
  std::map<EASEAClientData*,Point<int,int>>::iterator iter;
  std::map<EASEAClientData*,Point<int,int>>::iterator end=mClientOnGrid->end;
  int note;
  //need mutex
  
  while(true){
    tempo->beat();
    
    nextStep();
    for(iter=mClientOnGrid->begin();iter!=end;iter++){
      note=iter->first->computeNote();
      setStruct(iter->second,note);
    }
    
    send(compose(NULL));
  }
}

/*Unused parameter in tempo mode*/
virtual osc::OutboundPacketStream CellularAutoCompositor::compose(EASEAClientData* cl){
  char buffer[10000]; //max 50x50 full grid (conway's game of life tells us that only 54% of the grid can be alve,so we are able to send a 70*70 grid)
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
  
  p << osc::BeginBundleImmediate << osc::BeginMessage( "/CellularGrid" );
  p<<mGridSize<<osc::EndMessag;

  for (i = 0; i < mGridSize; i++) {
    p<<BeginMessage
    for (j = 0; j < mGridSize; j++) {
       if (mGrid[i][j]) {
         p<<mGrid[i][j];
       }
    }
  }
  p<< osc::EndMessag << osc::EndBundle;
}

/*TODO : choose structurs for each case*/
/*use operator (int i,int j) instead */
void CellularAutoCompositor::setStruct(Point<int,int> p,int note){
  int x=p.x();
  int y=p.y();
  
  /*block*/ 
  if(note==NOTE_1){
    mGrid[x][y]=1; 
    mGrid[x+1][y]=1; 
    mGrid[x][y+1]=1; 
    mGrid[x+1][y+1]=1; 
  }
  /*tub*/
  else if (note==NOTE_2) {
    mGrid[x][y]=1; 
    mGrid[x-1][y+1]=1; 
    mGrid[x+1][y+1]=1; 
    mGrid[x][y+2]=1; 
     
  }
  /*boat*/
  else if (note==NOTE_3) {
    mGrid[x][y]=1; 
    mGrid[x+1][y]=1; 
    mGrid[x][y+1]=1; 
    mGrid[x+1][y+2]=1; 
    mGrid[x+2][y+1]=1; 
  
  }
  /*Eater 1*/
  else if (note==NOTE_4) {
    mGrid[x][y]=1; 
    mGrid[x][y-1]=1; 
    mGrid[x+1][y]=1; 
    mGrid[x+2][y-1]=1; 
    mGrid[x+2][y-2]=1; 
    mGrid[x+2][y-3]=1; 
    mGrid[x-3][y-3]=1; 
  }
}
