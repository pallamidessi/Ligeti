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

/**
* /brief    Module managing and sending current data to the audio monitoring server.
* /details  Is mean to be included in EASEA compiled program. (Currently
* CEvolutionaryAlgorithme). 
*
**/
class AudioMonitorModule{
  
  public:
    /**
    * /brief    Constructor of AudioMonitorModule.
    * /details  Create and initialize a TCP/IP connection to a central monitoring 
    *  server.
    *
    *  @param  serverIP A string representing the server IPv4 adresse
    *  (xxx.xxx.xxx.xxx).
    *  @param  port The listening port of the monitoring server.
    **/
    AudioMonitorModule(std::string serverIP,int port);
    
    
    /**
    * /brief   Destructor of AudioMonitorModule.
    * /details Proprely Close the TCP connection. 
    *
    **/
    virtual ~AudioMonitorModule ();
    
    
    /**
    * /brief    Send various essential information of the last generation
    * evaluation to the assciated server.
    *
    * /details  Send rather basic information and straightforward, can easily be extended/override.
    *
    *  @param  best             Best genome's fitness
    *  @param  worst            Worst genome's fitness.
    *  @param  stdev            Population's standard deviation 
    *  @param  averageFitness   Population's average fitness
    **/
    void sendGenerationData(float best,float worst,float stdev,float averageFitness);


  private  :
    /* data */
    int sockfd;
    bool debug; //show various information during exec (stdout)
};


