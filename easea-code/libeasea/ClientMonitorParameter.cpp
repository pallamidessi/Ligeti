#include "include/ClientMonitorParameter.h"

/*ClientMonitorParameter---------------------------------------------*/
ClientMonitorParameter::ClientMonitorParameter(CEvolutionaryAlgorithm* parent):
                        MonitorParameter(),source(parent){
  strType=SIMPLEDATA;
}


ClientMonitorParameter::~ClientMonitorParameter(){
}


void ClientMonitorParameter::fill(){
  
  dataFlag=true;
  migration=false;
  best=source->population->Best->getFitness();
  worst=source->population->Worst->getFitness();
  stdev=source->cstats->currentStdDev;
  average=source->cstats->currentAverageFitness;
}

void ClientMonitorParameter::sending(){
  dataFlag=false;
  migration=true;
  recv=false;
  send=true;
}

void ClientMonitorParameter::reception(){
  dataFlag=false;
  migration=true;
  recv=true;
  send=false;
}

size_t ClientMonitorParameter::size(){
  return sizeof(this);
}

