#include "mainFrame.hpp"
AudioMonitorServer* serv;

void* launch_monitoring(void* arg){
  serv=new AudioMonitorServer(((int*)arg)[0],0);
  serv->setCompositor((SimpleCompositor*)(((int*)arg)[1]));
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
  
  MIDICompositor* test=new MIDICompositor("127.0.0.1",57120,true);
  //test->setNormalization(300,2000,0,130);
  int arg[2];
  arg[0]=port;
  arg[1]=test;
  pthread_create(&TCP_serv,NULL,&launch_monitoring,(void*)&arg);
  
  pthread_join(TCP_serv,NULL);
  return 0;
}
