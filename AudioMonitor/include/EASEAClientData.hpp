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

#include <cstdio>
#include <cstdlib>
#include <vector>

/*For each node of an EASEA Cloud, store the received data*/
class EASEAClientData {
  
  public:
    EASEAClientData ();
    EASEAClientData (int sock);
    virtual ~EASEAClientData ();
    void EASEAClientData::processBuffer(char* buffer){
    
    /*getter*/
    int getSocket();
  
  private:
  
    /* data */
    int clientSockfd;
    std::vector<double> best;
    std::vector<double> average;
    std::vector<double> stdev;
    std::vector<double> worst;
};
