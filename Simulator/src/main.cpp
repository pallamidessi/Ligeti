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
#include "main.hpp"

int main(int argc, char* argv[]){
  int nbOfReader=argc-2; 
  int i;
  std::vector<Reader*> listReader;

  if (argc<=2) {
    std::cerr<<
      "Spécifier au moins un fichier pour lancer la simulation."
    <<std::endl;
    return 1;
  }
  
  std::string ip(argv[1]);
  std::cout<<ip<<std::endl;
  for (i = 0; i < nbOfReader; i++) {
    listReader.push_back(new Reader(argv[i+2],new AudioMonitorModule(),new ClientMonitorParameter(NULL)));  
  }
  
  for (i = 0; i < nbOfReader; i++) {
    listReader[i]->start();
  }
  
  for (i = 0; i < nbOfReader; i++) {
    listReader[i]->join();
  }

  return 0;
}


