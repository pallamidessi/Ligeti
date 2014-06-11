#include "MIDICompositor.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

void MIDICompositor::send(){
  Compositor::send();
}


MIDICompositor::~MIDICompositor(){}


void MIDICompositor::send(osc::OutboundPacketStream oscMsg){
  Compositor::send(oscMsg);
}


osc::OutboundPacketStream MIDICompositor::compose(EASEAClientData* cl){
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
  int freq = cl->getBestVector()->back();
  freq=rescaling(freq);
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/note" ) 
          <<  cl->computeNote() 
          << cl->getID() 
          << osc::EndMessage
        << osc::EndBundle;
  
  return p; 
}


void MIDICompositor::notify(EASEAClientData* cl){
  Compositor::notify(cl);
}


MIDICompositor::MIDICompositor(std::string ip,int port,bool dbg):Compositor::Compositor(ip,port,dbg){
  juce::StringArray deviceName=juce::MidiOutput::getDevices();
  int i;
  std::cout<<"MIDI devices"<<std::endl;
  for (i = 0; i < deviceName.size(); i++) {
    std::cout<<i<<"\t"<<deviceName[i]<<std::endl;
  }
  float vel=0.5;
  juce::MidiOutput* fluidsynth=juce::MidiOutput::openDevice(1);
  juce::MidiMessage laR=juce::MidiMessage::noteOn(1,60,vel);
  juce::MidiMessage laL=juce::MidiMessage::noteOn(2,40,vel);
  //fluidsynth->sendMessageNow(laR);
  //fluidsynth->sendMessageNow(laL);
  //sleep(5);
  //la=juce::MidiMessage::noteOff(0,60,(uint8)60);
  juce::MidiFile* midiToParse;
  juce::FileInputStream* midiInputStream;
  const juce::MidiMessageSequence* curTrack;
  juce::File* midiFile;
  int nbTrack;
  //int i;
  fluidsynth->startBackgroundThread();

  midiFile=new File("/home/pallamidessi/Ligeti/Test_and_demo/midi/gym3_1.mid");
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
  curTrack=midiToParse->getTrack(1);
  int nbEvent=curTrack->getNumEvents();
  juce::MidiMessageSequence::MidiEventHolder* curEvent;
  juce::MidiBuffer chord;
  double curTimestamp=curTrack->getStartTime();
  int num;
  chord.addEvent(laR,1);
  chord.addEvent(laL,1);
  fluidsynth->sendBlockOfMessages(chord,1,10000);
  /*
  for (i = 0; i < nbEvent;) {
    num=0;
    while(curTrack->getEventTime(i)==curTimestamp){
      chord.addEvent(curTrack->getEventPointer(i)->message,num);
      num++;
      i++;
    }
    fluidsynth->sendBlockOfMessages(chord,curTimestamp+10,10);
    std::cout<<"message block sent :"<< curTimestamp<<" with "<<chord.getNumEvents()<<" event(s) "<<std::endl;
    chord.clear();
    curTimestamp=curTrack->getEventTime(i);
  }
  */
}


void MIDICompositor::aSending(EASEAClientData* cl){
  Compositor::aSending(cl); 
}


void MIDICompositor::aReception(EASEAClientData* cl){
  Compositor::aReception(cl);
}
