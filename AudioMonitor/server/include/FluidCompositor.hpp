/**
 * @file FluidCompositor.cpp
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
#ifndef FLUIDCOMPOSITOR_H__
#define FLUIDCOMPOSITOR_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include"Compositor.hpp"
#include "../JuceLibraryCode/JuceHeader.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

class FluidCompositor:public Compositor {
  public:
    FluidCompositor(std::string synthesisIP,int portnum,bool dbg=false,std::vector<juce::MidiFile*> *listMidi=NULL);
    virtual ~FluidCompositor ();
    void send();
    void send(osc::OutboundPacketStream oscMsg);
    osc::OutboundPacketStream compose(EASEAClientData* cl);
    void notify(EASEAClientData* cl);
    void aSending(EASEAClientData* cl);
    void aReception(EASEAClientData* cl);
    static std::vector<juce::MidiFile*>* loadMidiFromPath(
                                                          boost::filesystem::path p, int nbArg);

  private:
    static bool checkDir(boost::filesystem::path p,std::vector<juce::MidiFile*> *listMidi);
  protected:
    
  private:
    /* data */
};

#endif /* end of include guard: FLUIDCOMPOSITOR_H__ */


