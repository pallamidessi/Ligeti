#include "EASEAClientData.hpp"

int EASEAClientData::mGlobalID=0;

EASEAClientData::EASEAClientData ():Note(){
  mID=mGlobalID;
  mGlobalID++;
}


EASEAClientData::EASEAClientData (int sock):
                Note(),nbData(0),ignoreFlag(true),hasSent(false),hasReceived(false),mLastEvalued(){
  clientSockfd=sock;
  mID=mGlobalID;
  mGlobalID++;
}


EASEAClientData::EASEAClientData (int sock,std::string ip,int port):
                Note(),nbData(0),ignoreFlag(true),mLastEvalued(){
  clientSockfd=sock;
  clPort=port;
  clIP=ip;
  mID=mGlobalID;
  mGlobalID++;
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


int EASEAClientData::getID(){      
  return mID;
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


EASEAClientRow EASEAClientData::getLast(){
  return EASEAClientRow(best.back(),average.back(),
                        stdev.back(),worst.back()); 
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


int EASEAClientData::computeNote(){
  int variaBest=0;
  int variaWorst=0;
  int variaStdev=0;
  int variaAverage=0;
  
  EASEAClientRow last=getLast();
  
  /*Best variation*/
  if (mLastEvalued.best()>last.best()) {
    variaBest=1;
  }

  /*Worst variation*/
  if (mLastEvalued.worst()>last.worst()) {
    variaWorst=1;
  }

  /*Average variation*/
  if(mLastEvalued.average()>last.average()){
    variaAverage=1;
  }
   
  /*Stdev variation*/
  if (mLastEvalued.stdev()<last.stdev()) {
    variaStdev=2;
  }
  else if(mLastEvalued.stdev()>last.stdev()){
    variaStdev=1;
  }
  
  //TODO: copy operator EASEAClientRow
  mLastEvalued=last;

  if(variaBest && variaWorst && variaAverage && variaStdev==2){
    return NOTE_1;
  }
  else if (!variaStdev && variaAverage && variaBest && !variaWorst) {
    return NOTE_2;
  }
  else if (variaStdev==1 && variaAverage && !variaBest && !variaWorst) {
    return NOTE_3;
  }
  else{
    return NOTE_4;
  }  
}

