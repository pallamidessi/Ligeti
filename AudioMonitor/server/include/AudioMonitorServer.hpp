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

#ifndef _AUDIOMONITORSERVER_HPP__
#define _AUDIOMONITORSERVER_HPP__

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<sys/select.h>
#include<fcntl.h>
#include<signal.h>
#include<vector>
#include"EASEAClientData.hpp"

class AudioMonitorServer{
  
  public:
    AudioMonitorServer(int port,int dbg);
    ~AudioMonitorServer();
    void start();

  private:
    void signalHandler();
    void sigIntEvent(int sig);
    
    /*Data*/
    std::vector<EASEAClientData>* list_client; 
    int servSockfd;
	  struct sigaction terminaison;
    int max_select;
    socklen_t addrlen;
    struct sockaddr_in my_addr;
    int debug;
    int port;

};

#endif
