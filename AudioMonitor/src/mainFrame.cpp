#include "mainFrame.hpp"

void* launch_monitoring(void* port){
  AudioMonitorServer* serv=new AudioMonitorServer(*((int*)port),0);
  serv->start();
 
  //never return
  return NULL;
}

int main(int argc, char* argv[]){
  int port=27800; //default port
  
  pthread_t TCP_serv,comp;

  if (argc == 2) {
    port=atoi(argv[1]);
  }
  
  pthread_create(&TCP_serv,NULL,&launch_monitoring,(void*)&port);
  //pthread_create(&TCP_serv,NULL,&launch_monitoring,&port);
  return 0;
}
