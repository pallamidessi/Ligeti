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
* \class Compositor 
* \brief    Abstract class, used for polymorphism and to set a standard structure
* and working for all compositor. The compositor also create the connection and
* communicate with the synthesis server/program (SClang).
* \details  Abstract, but all function are implemented and ready to use. 
*
**/
class Compositor {

  public:
    /*Constructor/Destructor------------------------------------------------------*/ 
    /**
    * \brief    Constructor of Compositor
    * \details  Create the udp adress structure. 
    *
    * @param    synthesisIP A string representing the synthesis server IP(v4)
    * @(xxx.xxx.xxx.xxx).
    * @@param    portnum     Port on which the synthsesi server listened.
    * @@param    dbg         Set this to true to display various information during 
    *                       runtime.
    **/
    Compositor(std::string synthesisIP,int portnum,bool dbg=false);
    
    
    /**
    * \brief    Destructor of Compositor
    * \details  Free some networking's structures 
    *
    **/
    virtual ~Compositor();
    
    /*Method----------------------------------------------------------------------*/
    /**
    * \brief    Send the most basic/no argument needed OSC message.
    * \details  Send to the associate server.
    *
    **/
    virtual void send()=0;
    
    
    /**
    * \brief    Send an OSC packet.
    * \details  Send an OSc packet to the associate synthesis server.
    *
    * @param    oscMsg The OSC packet to send.
    **/
    virtual void send(osc::OutboundPacketStream oscMsg)=0;
    
    
    /**
    * \brief    Do something with the specified EASEA node data.
    * \details  The magic happened here !
    *
    *  @param   cl An EASEAClientData which generaly jlust had an update.  
    **/
    virtual osc::OutboundPacketStream compose(EASEAClientData* cl);
    
    
    /**
    * \brief    Main Wrapper to call.
    * \details  it's content depend of the compositor.
    *
    * @param    cl An EASEAClientData which generaly jut had an update.  
    **/
    virtual void notify(EASEAClientData* cl)=0;
   

    /**
    * \brief    Set range and extremes values for normalization operation.
    * \details  the caller MUST or at least estimate the minimun and maximum value
    *           of the run. 
    *
    *  @param   rangeMin   Inferior bound wanted
    *  @param   rangeMax   Superior bound wanted
    *  @param   min        Minimum value of the data set
    *  @param   max        Maximum value of the data set
    **/
    virtual void setNormalization(float rangeMin, float rangeMax,float min,float max);
    
    
    /**
    * \brief    Static method for rescaling data to a range.
    * \details  Equivalent to a call to setNormalization + rescaling(float value). 
    *
    *  @param   rangeMin   Inferior bound wanted
    *  @param   rangeMax   Superior bound wanted
    *  @param   min        Minimum value of the data set
    *  @param   max        Maximum value of the data set
    *  @param   value      Value to rescale
    * @return   resValue   Rescaled value
    **/
    static float rescaling(int rangeMin,int rangeMax,float min,float max,float value);
    
    
    /**
    * /brief    Send an OSC message specific to a sending of individuals.
    * /details 
    *
    *  @param   cl An EASEAClientData which just had an update (sent an individual).  
    **/
    virtual void aSending(EASEAClientData* cl);
    
    
    /**
    * /brief    Send an OSC message specific to a reception of individuals.
    * /details 
    *
    *  @param   cl An EASEAClientData which just received an individual.  
    **/
    virtual void aReception(EASEAClientData* cl);
  
  
  protected:
    

    /**
    * \brief    Rescale giving the class parameter
    * \details The parameters are set by setNormalization 
    *
    * @param  Value The value to rescale 
    * @return  resValue   Rescaled value
    **/
    float rescaling(float value);
    
    /* Data-----------------------------------------------------------------------*/  
    UdpTransmitSocket* synthServSocket;
    bool debug;
    unsigned int OUTPUT_BUFFER_SIZE;
    float projectedMaxValue; //used for normalizing data 
    float projectedMinValue; //used for normalizing data 
    float freqRangeMin;
    float freqRangeMax;
};

/**
*  /struct   SimpleCompositor 
*  /brief    A simple (simplistic ?) implementation of Compositor, mainly used for
*            testing.
*  /details  Use function of base class.
*  
**/
class SimpleCompositor:public Compositor{
  public:
    SimpleCompositor(std::string synthesisIP,int portnum,bool dbg=false);
    void send();
    void send(osc::OutboundPacketStream oscMsg);
    void notify(EASEAClientData* cl);
    void aSending(EASEAClientData* cl);
    void aReception(EASEAClientData* cl);
};
#endif /* end of include guard: COMPOSITOR_H__ */
