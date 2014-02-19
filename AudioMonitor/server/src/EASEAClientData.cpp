#include "EASEAClientData.hpp"


EASEAClientData::EASEAClientData (){
}

EASEAClientData::EASEAClientData (int sock):
                nbData(0){
  clientSockfd=sock;
}

EASEAClientData::~EASEAClientData (){}

/*The packet received from EASEA nodes have a mask on their first byte, which indicate how
 * many and what data it contained*/
void EASEAClientData::processBuffer(char* buffer){
  //regarder comment les truc sont gerer dans EASEA
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

  printf("%s\n");
  for (i = 0; i < nbData; i++) {
    printf("%e %e %e %e\n"); 
  }
}
vector<float>* EASEAClientData::getWorstVector{}
vector<float>* EASEAClientData::getBestVector{}
vector<float>* EASEAClientData::getStDevVector{}
vector<float>* EASEAClientData::getAverageVector{}
float* EASEAClientData::getLast(){}
