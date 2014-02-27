/**
 * @file AudioMonitorModule.hpp
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

#ifndef AUDIOMONITORMODULE_H__
#define AUDIOMONITORMODULE_H__

#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>

class AudioMonitorModule{
  
  public:
    AudioMonitorModule(std::string serverIP="127.0.0.1",int port=27800,bool recvMsg=true,bool sendMsg=false);
    virtual ~AudioMonitorModule ();
    void sendGenerationData(float best,float worst,float stdev,float averageFitness);
    void receivedIndividuals();
    void sendingIndividuals();
    void setMigrationNotification(bool onRecv,bool onSend);
  private  :
    /* data */
    int sockfd;
    bool debug;
    bool notifyReception;
    bool notifySending;
};

#endif /* end of include guard: AUDIOMONITORMODULE_H__ */


