/**
 * @file AudioMonitorUtils.hpp
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

#ifndef AUDIOMONITORUTILS_H__
#define AUDIOMONITORUTILS_H__

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

enum{NOTUSE,SIMPLEDATA};

class MonitorParameter {
  public:
    MonitorParameter ();
    virtual ~MonitorParameter();
    virtual void fill();
    virtual void sending();
    virtual void reception();
    virtual size_t size();
    virtual char* serialize()=0;
    virtual void deserialize(char* buf)=0;
    virtual int serialSize()=0;
    virtual void processBuffer(std::string line)=0;
    virtual int getTime();
    
    bool isReception();
    bool isSending();
    bool isData();
    
    unsigned char strType; // The server need to know how to cast this struct
    /*TODO: Better use a mask instead of four boolean ...*/
    bool dataFlag;    
    bool migration;
    bool recv;
    bool send;
    float timeBegin;
    float timeEnd;
    
};

#endif /* end of include guard: AUDIOMONITORUTILS_H__ */
