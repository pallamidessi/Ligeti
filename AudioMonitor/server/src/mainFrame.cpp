#include "mainFrame.hpp"
AudioMonitorServer* serv;

struct parameters{
  Compositor* maestro;
  int port;
};

void* launch_monitoring(void* arg){
  parameters* param=(parameters*)arg;
  serv=new AudioMonitorServer(param->port,0);
  serv->setCompositor(param->maestro);
  serv->start();
 
  //never return
  return NULL;
}

int main(int argc, char* argv[]){
  int port=27800; //default port
  
  pthread_t TCP_serv; 

  if (argc == 2) {
    port=atoi(argv[1]);
  }
  
  FluidCompositor* test=new FluidCompositor("127.0.0.1",57120,true);
  //test->setNormalization(300,2000,0,130);
  parameters arg;
  arg.port=port;
  arg.maestro=test;
  serv=new AudioMonitorServer(arg.port,0);
  serv->setCompositor(arg.maestro);
  serv->start();
  //pthread_create(&TCP_serv,NULL,&launch_monitoring,(void*)&arg);
  
 // pthread_join(TCP_serv,NULL);
  return 0;
}
