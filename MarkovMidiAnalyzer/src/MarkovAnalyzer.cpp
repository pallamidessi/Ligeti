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

MarkovAnalyzer::MarkovAnalyzer(){
}

MarkovAnalyzer::MarkovAnalyzer(const std::string& path){
  parseMidiFile(path);
}

MarkovAnalyzer::~MarkovAnalyzer(){}

void MarkovAnalyzer::parseMidiFile(const std::string& path){
  juce::MidiFile* midiToParse;
  juce::FileInputStream* midiInputStream;
  const juce::MidiMessageSequence* curTrack;
  juce::File* midiFile;
  int nbTrack;
  int i;

  midiFile=new File(path);
  if(!midiFile->existsAsFile()){
    perror("File does not exist");
    return;
  }

  midiInputStream= new FileInputStream(*midiFile);
  midiToParse=new MidiFile();

  if(!midiToParse->readFrom(*midiInputStream)){
    perror("Can't read stream");
    return;
  }

  midiToParse->convertTimestampTicksToSeconds();
  nbTrack=midiToParse->getNumTracks();
  
   mTransition=new TransitionMatrix*[nbTrack];
   mTransition[0]=new TransitionMatrix();
  //for (i = 0; i < nbTrack; i++) {
    curTrack=midiToParse->getTrack(1);
    parseTrack(curTrack);
    delete midiToParse;
    delete midiInputStream;
    delete midiFile;
    //}
  mTransition[0]->computeProbabilities(); 
  mTransition[0]->print();
  mTransition[0]->sumProbabilities();
}

void MarkovAnalyzer::parseTrack(const juce::MidiMessageSequence* track){
  int nbEvent=track->getNumEvents();
  int i;
  juce::MidiMessageSequence::MidiEventHolder* curEvent;
  std::list<int>* chord;

  for (i = 0; i < nbEvent; i++) {
    curEvent=track->getEventPointer(i);
    if(curEvent->message.isNoteOn()){
      chord=getChord(curEvent,track,i);
      i+=chord->size()-1;
      analyzeChord(chord);
    }
  }
}

std::list<int>* MarkovAnalyzer::getChord(juce::MidiMessageSequence::MidiEventHolder* current,
                                            const juce::MidiMessageSequence* track,
                                            int pos){
  int timestamp;
  int i=1;
  juce::MidiMessage message;
  std::list<int>* chord=new std::list<int>(); //BAD PRACTICE YOLO
  
  timestamp=current->message.getTimeStamp();
  chord->push_back(current->message.getNoteNumber());
  // 
  while((message=track->getEventPointer(pos+i)->message).getTimeStamp()==timestamp){
    if(message.isNoteOn()){
      chord->push_back(message.getNoteNumber());
      i++;
    }
  }
  chord->sort();

  return chord;
}

void MarkovAnalyzer::analyzeChord(std::list<int>* chordMidiNote){
  static int lastIndex=-1; 
  int newIndex;

  if (lastIndex!=-1) {
    if((newIndex=mTransition[0]->find(chordMidiNote))==-1){
      newIndex=mTransition[0]->addNewIndexKey(chordMidiNote);
    }
    mTransition[0]->addTransition(lastIndex,newIndex);
    lastIndex=newIndex;
  }
  else {
    lastIndex=mTransition[0]->addNewIndexKey(chordMidiNote);
  }
}


void MarkovAnalyzer::createNewMelody(const std::string& path){
  juce::MidiMessageSequence* newTrack;
  juce::MidiFile* mid;
  juce::File* newMelo;
  juce::FileOutputStream* outputStream;
  int i;
  int lastIndex;
  
  newTrack=new juce::MidiMessageSequence();
  newMelo=new juce::File(path);
  outputStream=new juce::FileOutputStream(*newMelo);
  mid=new MidiFile();

  lastIndex=mTransition[0]->createFirstChord(newTrack);
  
  for (i = 0; i < 500; i++) {
    lastIndex=mTransition[0]->createNewChord(newTrack,lastIndex);
  }

  newTrack->addEvent(juce::MidiMessage::endOfTrack());
  newTrack->sort
  mid->addTrack(*newTrack);
  mid->writeTo(*outputStream);

}

