/**
 * @file Reader.cpp
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
#include "Reader.hpp"

/*Constructor/Destructor----------------------------------------------------------*/
Reader::Reader(char* path,AudioMonitorModule* sendingModule,MonitorParameter* params)
              :mPathTo(path),mSendingModule(sendingModule),mParams(params){

  mSendingModule->setParams(params);
}


Reader::~Reader(){
}

/*Methods-------------------------------------------------------------------------*/
void Reader::readAndSend(){
  boost::filesystem::fstream fs;
  std::string buffer;

  fs.open(boost::filesystem::system_complete(mPathTo),std::ios_base::in);
  boost::filesystem::path extension=mPathTo.extension();
  
  /*Read a line,than wait the specified time and send the message*/
  while(std::getline(fs,buffer)){
    if(testLine(extension,buffer)){
      mParams->processBuffer(buffer);
      usleep(mParams->getTime());       
      mSendingModule->send();
    }
    else{
      if(extension.compare(".dat")==0){ //Jump an extra line after 
        std::getline(fs,buffer);        //an non data line in a .dat file  
      }
    }
  }
}


/*Check the current line, return true if it's a data line, false otherwise*/
bool Reader::testLine(boost::filesystem::path extension,std::string line){
  char firstChar=0;
  
  /*CSV case*/
  if(extension.compare(".csv")==0) {
    firstChar=line[0];
    if (firstChar>='A'&& firstChar<='z'){
      return false;
    }
    else{
      return true;
    }
  }
  /*DAT case*/
  else if(extension.compare(".dat")==0) {
    firstChar=line[0];
    if (firstChar=='#') {
      return false;
    }
    else {
      return true;
    }
  }
  /*Not a supported extension : always false*/
  return false;
}


/*Start the lecture on the thread*/
void Reader::start(){
  mThread=boost::thread(&Reader::readAndSend,this);
}


/*Wait for the encapsulated thread to finish*/
void Reader::join(){
  mThread.join();
}
