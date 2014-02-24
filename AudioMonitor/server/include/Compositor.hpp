/**
 * @file OSCSender.cpp
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

#ifndef COMPOSITOR_H__
#define COMPOSITOR_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "EASEAClientData.hpp"

class Compositor {

  public:
    Compositor(std::string synthesisIP,int portnum,bool dbg=false);
    virtual ~Compositor();
    virtual void send()=0;
    virtual void send(osc::OutboundPacketStream oscMsg)=0;
    virtual osc::OutboundPacketStream compose(EASEAClientData* cl);
    virtual void notify(EASEAClientData* cl)=0;
    virtual void setNormalization(float rangeMin, float rangeMax,float min,float max);
    static float rescaling(int rangeMin,int rangeMax,float min,float max,float value);
  
  protected:
    
    float rescaling(float value);
    
    /* data */   
    UdpTransmitSocket* synthServSocket;
    bool debug;
    unsigned int OUTPUT_BUFFER_SIZE;
    float projectedMaxValue; //used for normalizing data 
    float projectedMinValue; //used for normalizing data 
    float freqRangeMin;
    float freqRangeMax;
};

class SimpleCompositor:public Compositor{
  public:
    SimpleCompositor(std::string synthesisIP,int portnum,bool dbg=false);
    void send();
    void send(osc::OutboundPacketStream oscMsg);
    void notify(EASEAClientData* cl);
};
#endif /* end of include guard: COMPOSITOR_H__ */
