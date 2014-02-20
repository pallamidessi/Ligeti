#include "AudioMonitorServer.hpp"

/*Constructor of AudioMonitorServer, create the server socket and initialize the data
 * structure*/

/**
 * /brief    Constructor of AudioMonitorServer
 * /details  Create the server socket and initialize the data structure
 *
 * @param  prt Port num of this server
 * @param  dbg Debug flag, print numerous information
 **/
AudioMonitorServer::AudioMonitorServer(int prt=27800,int dbg=1):
  debug(1),port(prt){

    /* socket factory*/
    if((servSockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == -1)
    {
      perror("socket");
      exit(EXIT_FAILURE);
    }


    /* init local addr structure and other params */
    my_addr.sin_family      = AF_INET;
    my_addr.sin_port        = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addrlen                 = sizeof(struct sockaddr_in);

    /* bind addr structure with socket */
    if(bind(servSockfd,(struct sockaddr*)&my_addr,addrlen) == -1)
    {
      perror("bind");
      close(servSockfd);
      exit(EXIT_FAILURE);
    }

    /*Set servSockfd to be non-blocking*/
    fcntl(servSockfd,F_SETFL,O_NONBLOCK);

    /* set the socket in passive mode (only used for accept())
     * and set the list size for pending connection*/
    listen(servSockfd,SOMAXCONN);

    max_select=servSockfd;

    list_client=new std::vector<EASEAClientData>;
  }

/**
 * /brief    Destructor of AudioMonitorServer
 * /details  Free alloc'd structure and release opened socket
 *
 **/
AudioMonitorServer::~AudioMonitorServer(){
  /*close every opened socket*/
  unsigned int i;

  for(i=0;i<list_client->size();i++){
    close(list_client->at(i).getSocket());
  }

}


void AudioMonitorServer::signalHandler(){
  /*Signal handler in case of ^C, to close the sockets*/
  //terminaison.sa_handler=sigIntEvent;
  sigfillset(&terminaison.sa_mask);
  terminaison.sa_flags=0;

  sigaction(SIGINT,&terminaison,NULL);
}





void AudioMonitorServer::sigIntEvent(int sig){
  unsigned int i;

  close(servSockfd);	

  for(i=0;i<list_client->size();i++){
    //send(list_client[i].getSocket(),"000/END",8,0);
    close(list_client->at(i).getSocket());
  }

  exit(0);
}


void AudioMonitorServer::buildSocketList(){
  unsigned int i;

  FD_ZERO(&rdclient);
  FD_SET(servSockfd,&rdclient);

  for(i=0;i<list_client->size();i++){
    FD_SET(list_client->at(i).getSocket(),&rdclient);
  }

}

void AudioMonitorServer::newClient(){
  int tmp_sockfd;
  EASEAClientData* new_client;
  
  tmp_sockfd = accept(servSockfd,(struct sockaddr*)&my_addr,&addrlen);

  /*selected need to know the highest numerical socket value*/
  if(tmp_sockfd>max_select){
    max_select=tmp_sockfd;
  }

  if (debug) {
    std::cout<<"nouveaux client"<<std::endl;
  }

  /*Adding the newly connected client to the list of client*/
  new_client = new EASEAClientData(tmp_sockfd);
  list_client->push_back(*new_client);	

}

void AudioMonitorServer::recvSomething(){
  if(FD_ISSET(servSockfd,&rdclient))
    newClient();
  else
    recvFromClient();

}

/* Case new data from known client*/
/* Check whose fd changed and received from them*/
void AudioMonitorServer::recvFromClient(){
  char buf[1024];
  float* dec=(float*)buf;
  unsigned int i; 
    
  memset(buf,'\0',1024); //reset buffer
  
  for(i=0;i<list_client->size();i++){
    if(list_client->at(i).getSocket()!=0){
      if(FD_ISSET(list_client->at(i).getSocket(),&rdclient)){
        if(recv(list_client->at(i).getSocket(),buf,1024,0)==0){
          //client_disconnected=true;
        }//Envoi de packet vide => deconnecte/fini;
        else {
          if (!list_client->at(i).toIgnore()) {
            list_client->at(i).addData(dec[0],dec[1],dec[2],dec[3]);

            if (debug){
              std::cout<<"I have received something from ..."<<std::endl;
              std::cout<<dec[0]<<" "<<dec[1]<<" "<<dec[2]<<" "<<dec[3]<<std::endl;
            }
          }
          else
            list_client->at(i).setIgnoreFlag(false);
        }
      }
    }
  }

}


/**
 * /brief    Start the server, which will never stop listening  
 * /details  Create a EASEAClientData for each client 
 *
 **/
void AudioMonitorServer::start(){


  debug=1; 

  while(1){

    buildSocketList();

    if((select(max_select+1,&rdclient,NULL,NULL,NULL))>=1){
     recvSomething();
    }
  }
}
