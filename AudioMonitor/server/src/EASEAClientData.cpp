#include "EASEAClientData.hpp"


EASEAClientData::EASEAClientData (){
}

EASEAClientData::EASEAClientData (int sock):
                nbData(0),ignoreFlag(true){
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


void EASEAClientData::addData(float best,float worst,float stdev,float average){
  this->best.push_back(best);
  this->best.push_back(worst);
  this->best.push_back(stdev);
  this->best.push_back(average);

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
  lastData[1]=best.back();
  lastData[2]=best.back();
  lastData[3]=best.back();

  return lastData; 
}

bool EASEAClientData::toIgnore(){
  return ignoreFlag;
}
    
void EASEAClientData::setIgnoreFlag(bool value){
  ignoreFlag=value;
}
