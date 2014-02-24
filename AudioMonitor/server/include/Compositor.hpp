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

/**
* /brief    Abstract class, used for polymorphism and to set a standard structure
* and working for all compositor. The compositor also create the connection and
* communicate with the synthesis server/program (SClang).
* /details  Abstract, but all function are implemented and ready to use. 
*
**/
class Compositor {

  public:
    /**
    * /brief    Constructor of Compositor
    * /details  Create the udp adress structure. 
    *
    *  @param  synthesisIP A string representing the synthesis server IP(v4)
    *  (xxx.xxx.xxx.xxx).
    *  @param  portnum port on which the synthsesi server listened.
    *  @param  dbg Set this to true to display various information during runtime
    **/
    Compositor(std::string synthesisIP,int portnum,bool dbg=false);
    
    
    /**
    * /brief    Destructor of Compositor
    * /details Free some networking's structures 
    *
    **/
    virtual ~Compositor();
    
    
    /**
    * /brief    Send the most basic/no argument needed OSC message.
    * /details  Send to the associate server.
    *
    **/
    virtual void send()=0;
    
    
    /**
    * /brief    Send an OSC packet.
    * /details Send an OSc packet to the associate synthesis server.
    *
    * @param  oscMsg The OSC packet to send.
    **/
    virtual void send(osc::OutboundPacketStream oscMsg)=0;
    
    
    /**
    * /brief    Do something with the specified EASEA node data.
    * /details  The magic happened here !
    *
    *  @param  cl An EASEAClientData which generaly jut had an update.  
    **/
    virtual osc::OutboundPacketStream compose(EASEAClientData* cl);
    
    
    /**
    * /brief    Main Wrapper to call.
    * /details  it's content depend of the compositor.
    *
    * @param  cl An EASEAClientData which generaly jut had an update.  
    **/
    virtual void notify(EASEAClientData* cl)=0;
   

    /**
    * /brief    Set range and extremes values for normalization operation.
    * /details  the caller MUST or at least estimate the minimun and maximum value
    * of the run. 
    *
    *  @param  rangeMin   Inferior bound wanted
    *  @param  rangeMax   Superior bound wanted
    *  @param  min        Minimum value of the data set
    *  @param  max        maximum value of the data set
    **/
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
