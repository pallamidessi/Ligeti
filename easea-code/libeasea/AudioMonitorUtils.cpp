/**
 * @file AudioMonitorUtils.cpp
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

#include "include/AudioMonitorUtils.h"

/*MonitorParameter---------------------------------------------*/
MonitorParameter::MonitorParameter():
                  strType(NOTUSE){
}


MonitorParameter::~MonitorParameter(){
}

void MonitorParameter::sending(){
}

void MonitorParameter::reception(){
}

void MonitorParameter::fill(){
}


size_t MonitorParameter::size(){
  return sizeof(this);
}

bool MonitorParameter::isData(){
  return dataFlag;
}

bool MonitorParameter::isReception(){
  return (migration && recv);
}

bool MonitorParameter::isSending(){
  return (migration && send);
}

