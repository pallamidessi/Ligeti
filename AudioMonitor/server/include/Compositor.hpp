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
    virtual ~OSCSender();
    virtual bool send()=0;
    virtual bool send(osc::OutboundPacketStream oscMsg)=0;
    virtual osc::OutboundPacketStream compose(EASEAClientData* cl);
    virtual void notify(EASEAClientData* cl)=0;
    
    static float rescaling(float rangeMin,float rangeMax,float value);

  private:

    /* data */   
    UdpTransmitSocket synthServSocket;
    bool debug;
    unsigned int OUTPUT_BUFFER_SIZE;
    float maxValue; //used for normalizing data 
};

class SimpleCompositor:public Compositor{
    
}
#endif /* end of include guard: COMPOSITOR_H__ */
