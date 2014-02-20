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
#include <unistd.h>
#include"AudioMonitorClient.hpp"

int main(int argc, char* argv[]){
  int i;

  AudioMonitorModule* test=new AudioMonitorModule("127.0.0.1",27800);
  
  for (i = 0; i < 1000; i++) {
    sleep(1);
    
    if (atoi(argv[1])==1) {
      test->sendGenerationData(5.3,5.3,5.3,5.3);
    }
    else
      test->sendGenerationData(100.1,100.1,100.1,100.1);
  }

  return 0;
}
