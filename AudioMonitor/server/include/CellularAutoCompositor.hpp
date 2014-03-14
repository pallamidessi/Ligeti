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
#ifndef CELLULARAUTOCOMPOSITOR_H__
#define CELLULARAUTOCOMPOSITOR_H__

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <Compositor.hpp>
#include <map>
#include "Point.hpp"

class CellularAutoCompositor:public Compositor,public CellularRules {
  
  public:
    CellularAutoCompositor(size_t gridSize);
    virtual ~CellularAutoCompositor();
    
    void send();
    void send(osc::OutboundPacketStream oscMsg);
    void notify(EASEAClientData* cl);
    void aSending(EASEAClientData* cl);
    void aReception(EASEAClientData* cl);

    void nextStep();
  
  private:
    addClientOnGrid(EASEAClientData* cl);

    std::map<EASEAClientData*,Point<int,int>> mClientOnGrid;
    std::list<Point<int,int>> mPlaceAvailabeOnGrid;
    Matrix<int>* mGrid;
    int mMaxClient;
    size_t mGridSize;
};

#endif /* end of include guard: CELLULARAUTOCOMPOSITOR_H__ */
