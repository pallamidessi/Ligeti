/**
 * @file MarkovAnalyzer.hpp
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
#ifndef MARKOVANALYZER_H__
#define MARKOVANALYZER_H__

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <map>
#include "Matrix.hpp"
#include "../JuceLibraryCode/JuceHeader.h"
#define PITCH_MODE 0
#define VELOCITY_MODE 1
#define DURATION_MODE 2

typedef int midiNote_t;
typedef int midiVelocity_t;
typedef int midiDuration_t; //In millisecond
typedef int parseMode_t; 

class TransitionMatrix {
public:
  TransitionMatrix (std::map<std::list<int>,int>* chordMap);
  virtual ~TransitionMatrix ();

  int addNewIndexKey(std::list<int>*); //Add a dimension
  void addTransition(int from,int to);
  int find(std::list<int>* someChord);
  void computeProbabilities();
  void print();

private:
  Matrix<float> mTransition;
  int mTotal;
  std::vector< std::list<int> > mIndex; //the element vector containing vector are sorted
};

class MarkovAnalyzer {
public:
  MarkovAnalyzer ();
  MarkovAnalyzer(const std::string& path);
  virtual ~MarkovAnalyzer ();
  
  void parseMidiFile(const std::string& path);
  
private:
  void parseTrack(const juce::MidiMessageSequence* track);
  std::list<int>* getChord(juce::MidiMessageSequence::MidiEventHolder* current,const juce::MidiMessageSequence* track,int pos);
  void analyzeChord(std::list<int>* chordMidiNote);
  TransitionMatrix** mTransition; //There is one transition matrix per track
};

#endif /* end of include guard: MARKOVANALYZER_H__ */
