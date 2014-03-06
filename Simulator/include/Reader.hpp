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

class Reader {
public:
  Reader (char* path,AudioMonitorModule* sendingModule,MonitorParameter* params);
  virtual ~Reader ();
  
  void start();
  void join();
  void readAndSend();
  bool testLine(boost::filesystem::path extension,std::string buffer);
private:
  boost::filesystem::path mPathTo;
  boost::thread mThread;
  AudioMonitorModule* mSendingModule;  
  MonitorParameter* mParams;  

};

#endif /* end of include guard: READER_H__ */
