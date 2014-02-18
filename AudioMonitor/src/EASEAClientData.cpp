#include "EASEAClientData.hpp"


EASEAClientData::EASEAClientData (){
}

EASEAClientData::EASEAClientData (int sock){
  clientSockfd=sock;
}

EASEAClientData::~EASEAClientData (){}

/*The packet received from EASEA nodes have a mask on their first byte, which indicate how
 * many and what data it contained*/
void EASEAClientData::processBuffer(char* buffer){
//regarder comment les truc sont gerer dans EASEA

}
