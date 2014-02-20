/**
 * @file EASEAClientData.c
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
#ifndef _EASEACLIENTDATA_HPP__
#define _EASEACLIENTDATA_HPP__

#include <cstdio>
#include <cstdlib>
#include <vector>

/*For each node of an EASEA Cloud, store the received data*/
class EASEAClientData {
  
  public:
    EASEAClientData ();
    EASEAClientData (int sock);
    virtual ~EASEAClientData ();
    void processBuffer(char* buffer);
    void addData(float best,float worst,float stdev,float average);
    void print();
    /*getter*/
    int getSocket();
    float* getLast();
    bool toIgnore();
    std::vector<float>* getWorstVector();
    std::vector<float>* getBestVector();
    std::vector<float>* getStDevVector();
    std::vector<float>* getAverageVector();
    /*setter*/
    void setIgnoreFlag(bool value);
  private:
  
    /* data */
    int clientSockfd;
    int nbData;
    bool ignoreFlag;
    std::vector<float> best;
    std::vector<float> average;
    std::vector<float> stdev;
    std::vector<float> worst;
};

#endif
