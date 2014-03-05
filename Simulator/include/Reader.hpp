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
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <AudioMonitorModule.h>
#include <boost/filesystem.hpp>

class Reader {
public:
  Reader (char* path,AudioMonitorModule* sendingModule,MonitorParameter* params)
          :mPathTo(path),mSendingModule(sendingModule),mParams(params);
  virtual ~Reader ();
  
  void start();
  void read();
private:
  boost::filesystem::path mPathTo;
  AudioMonitorModule* mSendingModule;  
  MonitorParameter* mParams;  
};
