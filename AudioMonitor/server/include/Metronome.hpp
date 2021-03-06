/**
 * @file Metronome.hpp
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
#include <iostream>
#include <unistd.h>

/*TODO Must used nanosleep instead of usleep*/
class Metronome {
  
  public:
    Metronome(float bpm):mBpm(bmp){}
    virtual ~Metronome (){}
    void beat(){ usleep((60/bmp)*(1000000)); }    

  private:
    float mBpm;
};

