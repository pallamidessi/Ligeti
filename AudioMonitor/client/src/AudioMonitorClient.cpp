/**
 * @file name.c
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

#include <cstdio>
#include <cstdlib>
#include"AudioMonitorClient.hpp"

int main(int argc, char* argv[]){
  
  AudioMonitorModule* test=new AudioMonitorModule("127.0.0.1",27800);
  //test->sendGenerationData(5.3,6.3,7.3,8.);

  return 0;
}
