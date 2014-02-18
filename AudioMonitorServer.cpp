#include "AudioMonitorServer.hpp"
/*Constructor of AudioMonitorServer, create the server socket and initialize the data
 * structure*/
AudioMonitorServer::AudioMonitorServer(int port){
	int i,j;
	int servSockfd2;
	int max=0;
	int nbr_client=0;
	bool next_is_name=false,client_disconnected=false;
	fd_set rdclient; 
	socklen_t addrlen;
	char buf[1024];
	char buf2[1024];

	struct sockaddr_in my_addr;


	/* socket factory*/
	if((servSockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	

	/* init local addr structure and other params */
	my_addr.sin_family      = AF_INET;
	my_addr.sin_port        = htons(atoi(port));
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addrlen                 = sizeof(struct sockaddr_in);
	memset(buf,'\0',1024);

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

	max=servSockfd;
}

void AudioMonitorServer::signalHandler(){
	/*Signal handler in case of ^C, to close the sockets*/
	terminaison.sa_handler=sigIntEvent;
	sigfillset(&terminaison.sa_mask);
	terminaison.sa_flags=0;
		
	sigaction(SIGINT,&terminaison,NULL);
}

/*Example of command the chat can support */
/*
void who_is_connected(int servSockfd,int* list_client,char** nom_client,int max_client){
	int i=0;

	for(i=0;i<MAX_CLIENT;i++){
		if(list_client[i]!=0 && servSockfd!=list_client[i]){
			send(servSockfd,nom_client[i],16,0);
			
		}
	}
}
*/

/* Close the server and all opened sockets when a SIGINT is received and send a terminaison (interpreted) 
 * string to the connected clients*/



void AudioMonitorServer::sigIntEvent(int sig){
	int i;

	close(servSockfd);	
	
	for(i=0;i<list_client.size;i++){
	  //send(list_client[i].getSocket(),"000/END",8,0);
		close(list_client[i].getSocket());
	}

	exit(0);
}


int main(int argc, char **argv)
{
	int i,j;
	int sockfd2;
	int max=0;
	int nbr_client=0;
	bool next_is_name=FALSE,client_disconnected=FALSE;
	char name_client[MAX_CLIENT][16];
	socklen_t addrlen;
	char buf[1024];
	char buf2[1024];


	struct sockaddr_in my_addr;
	struct sigaction terminaison;

	/*Initializing the client array */
	for(i=0;i<MAX_CLIENT;i++){
		list_client[i]=0;
	}

	/* check the number of args on command line*/
	if(argc != 2)
	{
		printf("USAGE: %s port_num\n", argv[0]);
		exit(-1);
	}

	/* socket factory*/
	if((sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	/*Signal handler in case of ^C, to close the sockets*/
	terminaison.sa_handler=fin;
	sigfillset(&terminaison.sa_mask);
	terminaison.sa_flags=0;
		
	sigaction(SIGINT,&terminaison,NULL);

	/* init local addr structure and other params */
	my_addr.sin_family      = AF_INET;
	my_addr.sin_port        = htons(atoi(argv[1]));
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addrlen                 = sizeof(struct sockaddr_in);
	memset(buf,'\0',1024);

	/* bind addr structure with socket */
	if(bind(sockfd,(struct sockaddr*)&my_addr,addrlen) == -1)
	{
		perror("bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	/*Set sockfd to be non-blocking*/
	fcntl(sockfd,F_SETFL,O_NONBLOCK);

	/* set the socket in passive mode (only used for accept())
	 * and set the list size for pending connection*/
	listen(sockfd,SOMAXCONN);

	max=sockfd;

void AudioMonitorServer::start(){
  
	fd_set rdclient; 
  int nbr_client;
  int tmp_sockfd;
  EASEAClient* new_client;

  while(1){
    
    nbr_client=list_client.size();
		FD_ZERO(&rdclient);
		FD_SET(servSockfd,&rdclient);

		for(i=0;i<list_client.size;i++){
		  FD_SET(list_client[i],&rdclient);
		}

			if((select(max+1,&rdclient,NULL,NULL,NULL))>=1){
				if(FD_ISSET(servSockfd,&rdclient)){
					tmp_sockfd = accept(servSockfd,(struct sockaddr*)&my_addr,&addrlen);

          /*selected need to know the highest numerical socket*/
					if(tmp_sockfd>max){
						max=tmp_sockfd;
					}
          
          if (debug) {
					  printf("nouveaux client\n");
          }

					/*Adding the newly connected client to the list of client*/
          new_client = new EASEAClient(tmp_sockfd);
				  list_client.push_back(new_client);	
          
				}

				/* Check whose fd changed and received from him and then send the OSC message to
         * the audio synthesis server */

				else{
					for(i=0;i<list_client.size;i++){
						if(list_client[i]!=0){
							if(FD_ISSET(list_client[i].getSocket(),&rdclient)){
								if(recv(list_client[i].getSocket(),buf,1024,0)==0){
									client_disconnected=TRUE;
								}//Envoi de packet vide => deconnecte/fini;
								else if (debug){
									printf("%s\n",buf);
                }
							}
						}
					}
				}
			}
		}
	}
