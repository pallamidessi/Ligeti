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

Reader:: Reader(char* path,AudioMonitorModule* sendingModule,MonitorParameter* params){
 
 mSendingModule->setParams(params);

}

void Reader::Read(){
  boost::filesystem::fstream fs;
  fs.open(mPathTo.system_complete(),ios_base::in);
  path extension=mPathTo.extension();
  
  if(extension.compare(".csv")) {
  }
  else  if(extension.compare(".dat")) {
  }

  mParams-> 
}

bool nextLine
