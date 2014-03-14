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
                        Compositor(synthesisIp,portnum,dbg){
  
  int nbClientSquared=ceil(sqrt(maxClient));
  int spaceBetweenClient=gridSize/nbClientSquared;
  
  for (i = 0; i < nbClientSquared; i++) {
    for (j = 0; j < nbClientSquared; j++) {
      mPlaceAvailabeOnGrid.push_back(true,new Point<int,int>(i*spaceBetweenClient,j*spaceBetweenClient));
    }
  }

  grid=new Matrix<int>(gridSize);

}

CellularAutoCompositor::~CellularAutoCompositor(){};

CellularAutoCompositor::addClientOnGrid(EASEAClientData* cl){
  mClientOnGrid.insert(cl,mPlaceAvailabeOnGrid.back());
  mPlaceAvailabeOnGrid.pop_back();
}


