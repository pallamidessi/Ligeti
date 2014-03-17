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

  grid=new Matrix<int>(gridSize,0);
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
      if (*grid[i][j]) {
        next[i][j]=aliveRules(*grid[i][j],grid);
      }
      else{
        next[i][j]=deadRules(*grid[i][j],grid);
      }
    }
  }
  //delete grid
  grid=next;
}

void CellularAutoCompositor::startTempoMode(Metronome* tempo,std::list<EASEAClientData*>* cl){
  std::list<EASEAClientData*>::iterator iter;
  std::list<EASEAClientData*>::iterator iter;
  std::list<EASEAClientData*>::iterator end=list->end();
  std::map<EASEAClientData*,Point<int,int>>::iterator cur;
  int note;
  //need mutex
  
  while(true){
    tempo->beat();

    for(iter=list->begin();iter!=end;iter++){
      note=iter->computeNote();
      cur=mClientOnGrid.find(*iter);
      setStruct(cur->second,note);
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
       if (grid[i][j]) {
         p<<grid[i][j];
       }
    }
  }
  p<< osc::EndMessag << osc::EndBundle;
}

/*TODO : choose structur for each case*/
void CellularAutoCompositor::setStruct(Point<int,int>,int note){
  
  if(note==NOTE_1){
     
  }
  else if (note==NOTE_2) {
  
  }
  else if (note==NOTE_3) {
  
  }
  else if (note==NOTE_4) {
  
  }


}
