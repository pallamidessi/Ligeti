#include "EASEAClientData.hpp"


EASEAClientData::EASEAClientData (){
}

EASEAClientData::EASEAClientData (int sock):
                nbData(0),ignoreFlag(true),hasSent(false),hasReceived(false){
  clientSockfd=sock;
}

EASEAClientData::EASEAClientData (int sock,std::string ip,int port):
                nbData(0),ignoreFlag(true){
  clientSockfd=sock;
  clPort=port;
  clIP=ip;
}

EASEAClientData::~EASEAClientData (){}

/*The packet received from EASEA nodes have a mask on their first byte, which indicate how
 * many and what data it contained*/
void EASEAClientData::processBuffer(char* buffer){
}

int EASEAClientData::getSocket(){
  return clientSockfd;
}


void EASEAClientData::addData(MonitorParameter* monitor){
  ClientMonitorParameter* tmp=static_cast<ClientMonitorParameter*>(monitor); 
  if(tmp->strType==SIMPLEDATA){
    this->best.push_back(tmp->best);
    this->worst.push_back(tmp->worst);
    this->stdev.push_back(tmp->stdev);
    this->average.push_back(tmp->average);
  }
  nbData++;
}

void EASEAClientData::print(){
  int i;

  printf(" BEST\t\tWORST\t\tSTDEV\t\tAVERAGE\n ");
  for (i = 0; i < nbData; i++) {
    printf(" %e\t\t%e\t\t%e\t\t%e\n ",best[i],worst[i],stdev[i],average[i]); 
  }
}
void EASEAClientData::setIP(std::string ip){
  clIP=ip;
}
void EASEAClientData::setPort(int port){
  clPort=port;
}

int EASEAClientData::getPort(){
  return clPort;
}
std::string EASEAClientData::getIP(){
  return clIP;
}

std::vector<float>* EASEAClientData::getWorstVector(){
  return &worst;
}

std::vector<float>* EASEAClientData::getBestVector(){
  return &best;
}

std::vector<float>* EASEAClientData::getStDevVector(){
  return &stdev;
}

std::vector<float>* EASEAClientData::getAverageVector(){
  return &average;
}

float* EASEAClientData::getLast(){
  float* lastData=new float[5];
  lastData[0]=best.back();
  lastData[1]=worst.back();
  lastData[2]=stdev.back();
  lastData[3]=average.back();

  return lastData; 
}

bool EASEAClientData::toIgnore(){
  return ignoreFlag;
}
    
void EASEAClientData::setIgnoreFlag(bool value){
  ignoreFlag=value;
}

void EASEAClientData::verifyReception(MonitorParameter* params){
  if(params->isReception())
    hasReceived=true;
}

void EASEAClientData::verifySending(MonitorParameter* params){
  if(params->isSending())
    hasSent=true;
}

bool EASEAClientData::isAReception(){
  if(hasReceived){
    hasReceived=false;
    return true;
  }
  else{
    return false;
  }
}

bool EASEAClientData::isASending(){
  if(hasSent){
    hasSent=false;
    return true;
  }
  else{
    return false;
  }
}
