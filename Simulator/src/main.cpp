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

namespace fs=boost::filesystem;
/**
* /brief    Check directory to find .csv and .dat file.
* /details  If the given path is a directory, then list its content (non-recursive) to find
*           .csv and .dat file and add one Reader per found file to the vector. Return true if
*           the path is a directory, false otherwise.
*
* @param    p           The path to check.
* @param    listReader  The vector in which to add newly created reader.
* @return   bool        True if the path linked to a directory, false otherwise.
**/
bool checkDir(fs::path p,std::vector<Reader*> *listReader){
  fs::directory_iterator end_iter;
  
  if (fs::exists(p) && fs::is_directory(p)) { 
    for (fs::directory_iterator dirIter(p); dirIter!=end_iter; dirIter++) {
      if (fs::is_regular_file(dirIter->status())) {
        if(dirIter->path().extension().compare(".dat")|| //check file extension
           dirIter->path().extension().compare(".csv")){
          
          std::string pp(dirIter->path().c_str());
          listReader->push_back(new Reader(pp.c_str(),
                               new AudioMonitorModule(),
                               new ClientMonitorParameter(NULL)));  
          
        } 
      }
    }
  return true;
  }
return false;
}

int main(int argc, char* argv[]){
  int nbOfReader=argc-2; 
  int i;
  std::vector<Reader*> listReader;

  if (argc<=2) {
    std::cerr<<
      "Specified at least one path to start the simulation"
    <<std::endl;
    return 1;
  }

  /* "Directory" mode*/ 
  if (checkDir(argv[2],&listReader)) {
    nbOfReader=listReader.size();
  }
  /*List a file path given by hand*/
  else {
    for (i = 0; i < nbOfReader; i++) {
      listReader.push_back(new Reader(argv[i+2],new AudioMonitorModule(),new ClientMonitorParameter(NULL)));  
    }
  }
  
  /*Start every reader*/
  for (i = 0; i < nbOfReader; i++) {
    listReader[i]->start();
  }
  
  /*Wait for every reader to finish*/
  for (i = 0; i < nbOfReader; i++) {
    listReader[i]->join();
  }

  return 0;
}


