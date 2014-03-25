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
  srand(time(NULL)); 
  MarkovAnalyzer* test=new MarkovAnalyzer();
  test->parseMidiFile(argv[1]);
  test->createNewMelody(argv[2]); 
  return 0;
}
