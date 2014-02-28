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

#include "AudioMonitorUtils.hpp"

/*MonitorParameter---------------------------------------------*/
MonitorParameter::MonitorParameter(CEvolutionaryAlgorithm* parent):
                  strType(NOTUSE){
  source=parent;
}


MonitorParameter::~MonitorParameter(){
}


void MonitorParameter::fill(){
}


size_t MonitorParameter::size(){
  return sizeof(this);
}

bool MonitorParameter::isData(){
  return isData;
}

/*SimpleMonitorParameter---------------------------------------------*/
SimpleMonitorParameter::SimpleMonitorParameter(CEvolutionaryAlgorithm* parent):
                        strType(SIMPLEDATA){
  source=parent;
}


SimpleMonitorParameter::~SimpleMonitorParameter(){
}


void SimpleMonitorParameter::fill(){
  
  isData=true;
  migration=false;
  best=parent->population->Best->getFitness();
  worst=parent->population->Worst->getFitness();
  stdev=parent->cstats->currentStdDev;
  average=parent->cstats->currentAverageFitness;
}

void SimpleMonitorParameter::sending(){
  isData=false;
  migration=true;
  recv=false;
  send=true;
}

void SimpleMonitorParameter::reception(){
  isData=false;
  migration=true;
  recv=true;
  send=false;
}

size_t SimpleMonitorParameter::size(){
  return sizeof(this);
}

