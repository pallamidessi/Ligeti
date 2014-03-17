/**
 * @file CellularRules.cpp
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
#include <stdio>
#include <stdlib>
#include "Matrix.cpp"
#include "Point.cpp"

template<typename T,typename TT,>
  class CellularRules {
    public:
    CellularRules(TT defaultAlive,TT defaultDead) :mDefaultAlive(defaultAlive),mDefaultDead(defaultDead){};
      virtual ~CellularRules (){};
  
      virtual TT aliveRules(Point<T,T>,Matrix<TT>*)=0;
      virtual TT deadRules(Point<T,T>,Matrix<TT>*)=0;
    protected:
     
      bool isAlive(Point<T,T> p,int offsetX,int offsetY,Matrix<TT> m){
        int gridSize
        
        if(p.x()+offsetX>gridSize || p.x()+offsetX<0)
          return false;
        else if(p.y()+offsetY>gridSize || p.y()+offsetY<0)
          return false;
        else if(m[p.x()+offsetX][p.y()+offsetY])
          return true;
        else
          return false;
      }

      int countMooreNeighbours(point<T,T> p,Matrix<TT> m){
        int sum=0;
        
        if(isAlive(p,0,1,m))
          sum++;
        if(isAlive(p,1,0,m))
          sum++;
        if(isAlive(p,1,1,m))
          sum++;
        if(isAlive(p,0,-1,m))
          sum++;
        if(isAlive(p,-1,0,m))
          sum++;
        if(isAlive(p,-1,-1,m))
          sum++;
        if(isAlive(p,1,-1,m))
          sum++;
        if(isAlive(p,-1,1,m))
          sum++;
      
        return sum;
      }

      int countNeumannNeighbours(Point<T,T> p,Matrix<TT> m){
        int sum=0;

        if(isAlive(p,-1,0,m))
          sum++;
        if(isAlive(p,1,0,m))
          sum++;
        if(isAlive(p,0,1,m))
          sum++;
        if(isAlive(p,0,-1,m))
          sum++;
      
        return sum;
      }
      
    protected:
      TT mDefaultAlive;
      TT mDefaultDead;
};

template<typename T,typename TT,TT defaultAlive,TT defaultDead>
  class ConwayRules:CellularRules {
    public:
      ConwayRules(TT defaultAlive,TT defaultDead):CellularRules<T,TT>(defaultAlive,defaultDead){};
      virtual ~ConwayRules (){};
  
      virtual TT aliveRules(point<T,T> p,Matrix<TT>* m){
        int nbNeighbours=countMooreNeighbours(p,m);

        if (nbNeighbours<2) {
          return mDefaultDead;
        }
        else if (nbNeighbours>3) {
          return mDefaultDead;
        }
      }

      virtual TT deadRules(point<T,T>,Matrix<TT>*){
        int nbNeighbours=countMooreNeighbours(p,m);

        if (nbNeighbours==3) {
          return mDefaultAlive;
        }
        else {
          return mDefaultDead;
        }
      }

    private:
}
