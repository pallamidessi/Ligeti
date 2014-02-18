/**
 * @file AudioMonitorServer.c
 * @author Pallamidessi Joseph
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
**/  

#include<sys/types.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/select.h>
#include<fcntl.h>
#include<signal.h>

/*For each node of an EASEA Cloud, store the received data*/
typedef struct str_EASEAClient {
  int clientSockfd;
  std::vector<>;
} EASEAClient;

class AudioMonitorServer{
  
  public:
    AudioMonitorServer(int port);
    ~AudioMonitorServer();
    void start();

  private:
    void signalHandler();
    void sigIntEvent(int sig);
    
    /*Data*/
    std::vector<EASEAClient> list_client; 
    int servSockfd;
	  struct sigaction terminaison;
    int max_select;

}
