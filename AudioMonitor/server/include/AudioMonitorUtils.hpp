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
#include "CEvolutionaryAlgorithm.h"
enum{NOTUSE,SIMPLEDATA};

class MonitorParameter {
  public:
    MonitorParameter (CEvolutionaryAlgorithm* parent);
    virtual ~MonitorParameter();
    virtual void fill();
    virtual void sending();
    virtual void reception();
    virtual size_t size();
    bool isData();

    /*TODO: Better use a mask instead of four boolean ...*/
    bool dataFlag;    
    bool migration;
    bool recv;
    bool send;
    CEvolutionaryAlgorithm* source;
    unsigned char strType; // The server need to know how to cast this struct
  
};

class SimpleMonitorParameter:public MonitorParameter {
  public:
    SimpleMonitorParameter (CEvolutionaryAlgorithm* parent);
    virtual ~SimpleMonitorParameter();
    virtual void fill();
    virtual void sending();
    virtual void reception();
    virtual size_t size();
    
    float best;
    float worst;
    float stdev;
    float average;
};

#endif /* end of include guard: AUDIOMONITORUTILS_H__ */
