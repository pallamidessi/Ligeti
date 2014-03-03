/**
 * @file AudioMonitorUtils.cpp
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

#include "include/AudioMonitorUtils.h"

/*MonitorParameter---------------------------------------------*/
MonitorParameter::MonitorParameter(CEvolutionaryAlgorithm* parent):
                  source(parent),strType(NOTUSE){
}


MonitorParameter::~MonitorParameter(){
}

void MonitorParameter::sending(){
}

void MonitorParameter::reception(){
}

void MonitorParameter::fill(){
}


size_t MonitorParameter::size(){
  return sizeof(this);
}

bool MonitorParameter::isData(){
  return dataFlag;
}

/*SimpleMonitorParameter---------------------------------------------*/
SimpleMonitorParameter::SimpleMonitorParameter(CEvolutionaryAlgorithm* parent):
                        MonitorParameter(parent){
}


SimpleMonitorParameter::~SimpleMonitorParameter(){
}


void SimpleMonitorParameter::fill(){
  
  dataFlag=true;
  migration=false;
  best=source->population->Best->getFitness();
  worst=source->population->Worst->getFitness();
  stdev=source->cstats->currentStdDev;
  average=source->cstats->currentAverageFitness;
}

void SimpleMonitorParameter::sending(){
  dataFlag=false;
  migration=true;
  recv=false;
  send=true;
}

void SimpleMonitorParameter::reception(){
  dataFlag=false;
  migration=true;
  recv=true;
  send=false;
}

size_t SimpleMonitorParameter::size(){
  return sizeof(this);
}

