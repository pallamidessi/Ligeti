/**
 * @file MarkovAnalyzer.cpp
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
#include "MarkovAnalyzer.hpp"


void MarkovAnalyzer::parseMidiFile(const String& path){
  juce::midiFile midiToParse;
  juce::FileInputStream;
  juce::MidiMessageSequence* curTrack;
  juce::File midiFile;
  int nbTrack;

  midiFile(path);
  if(!midiFile.existsAsFile()){
    perror("File does not exist");
    return;
  }

  midiInputStream(midiFile);
  midiToParse();

  if(!midiToParse->readFrom(midiInputStream)){
    perror("Can't read stream");
    return;
  }

  midiToParse->convertTimestampTicksToSeconds();
  nbTrack=midiToParse->getNumTracks();

  for (i = 1; i < nbTrack; i++) {
    curTrack=midiFile->getTrack(i);
    parseTrack(curTrack);
  }

}

void MarkovAnalyzer::parseTrack(MidiMessageSequence* track){
  int nbEvent=track->getNumEvents();
  juce::MidiEventHolder* curEvent;
  std::vector<int>* chord;

  for (i = 0; i < nbEvent; i++) {
    curEvent=track->getEventPointer();
    if(curEvent->isNoteOn()){
      chord=getChord(curEvent,track);
      i+=chord.size();
      parseChord(chord)
    }
  }
}

void MarkovAnalyzer::parseChord(std::vector<>){


}
