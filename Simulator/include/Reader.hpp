/**
 * @file Reader.hpp
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
#ifndef READER_H__
#define READER_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <AudioMonitorModule.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/thread.hpp>

/**
*  /struct   Reader 
*  /brief    Take an .csv .dat input file and simulated and EASEA node
*  /details  Used the communication modules from EASEA programs. Each Reader
*            object run in a separated thread.
**/
class Reader {
  
  public:
    /*Constructors/Destructors----------------------------------------------------*/
    /**
    * /brief    Constructor of Reader
    * /details  Use a pre-existing AudioMonitorModule which initialized the
    *           communication to the central server.
    *
    * @param    path          Path to a data file (currently supported : EASEA formated .csv and
    *                         .dat)
    * @param    sendingModule An AudioMonitorModule correctly linked to a monitoring server.
    * @param    params        A MonitorParameter derived object
    **/
    Reader (char* path,AudioMonitorModule* sendingModule,MonitorParameter* params);
    
    
    /**
    * /brief    Destructor of Reader
    * /details  Free the associated AudioMonitorModule and MonitorParameter 
    *
    **/
    virtual ~Reader ();
    
    
    /*Methods---------------------------------------------------------------------*/
    /**
    * /brief    Start the simulation in an encapsulated thread
    * /details  Call readAndSend() in a boost::thread.
    *
    **/
    void start();
    
    
    /**
    * /brief    Join the encapsulated thread.
    * /details  Wrap boost::thread join() on the encapsulated thread.
    *
    **/
    void join();
    
    
    /**
    * /brief    The main loop, read from the input file to send a
    *           monitoring message.
    * /details  
    **/
    void readAndSend();
    
    
    /**
    * /brief    Test if the given buffer correspond to a data line or not
    * /details  Check if '#' if the first letter of a .dat line, or if the first
    *           element is a letter in case of a .csv file
    *
    * @param    extension The input file path extension 
    * @param    buffer    A buffer corresponding to a line of the file 
    * @return   bool      True if it's a data line, false otherwise.
    **/
    bool testLine(boost::filesystem::path extension,std::string buffer);
  
  
  private:
    /*Datas-----------------------------------------------------------------------*/
    boost::filesystem::path mPathTo;
    boost::thread mThread;
    AudioMonitorModule* mSendingModule;  
    MonitorParameter* mParams;  

};

#endif /* end of include guard: READER_H__ */
