/**
 * @file main.cpp
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
#include <boost/thread.hpp>
#include <vector>
#include "Reader.hpp"
int main(int argc, char* argv[]){
  int nbOfReader; 
  std::vector<Reader> listReader;

  if (argc<=3) {
    std::cerr<<
      "Spécifier au moins un fichier pour lancer la simulation."
    <<std::endl;
    return 1;
  }
  
  for (i = 0; i < nbOfReader; i++) {
    listReader.push_back(new Reader(argv[i+1],new AudioMonitorModule(argv[0],34500+i),new ClientMonitorParameter()));  
  }
  
  for (i = 0; i < nbOfReader; i++) {
    listReader[i].start();
  }

  return 0;
}


