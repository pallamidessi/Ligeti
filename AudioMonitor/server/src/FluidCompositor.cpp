#include "FluidCompositor.hpp"


void FluidCompositor::send(){
  Compositor::send();
}


FluidCompositor::~FluidCompositor(){}


void FluidCompositor::send(osc::OutboundPacketStream oscMsg){
  Compositor::send(oscMsg);
}


osc::OutboundPacketStream FluidCompositor::compose(EASEAClientData* cl){
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


void FluidCompositor::notify(EASEAClientData* cl){
  Compositor::notify(cl);
}


FluidCompositor::FluidCompositor(std::string ip,int port,bool dbg):Compositor::Compositor(ip,port,dbg){
  juce::StringArray deviceName;
  juce::MidiFile* midiToParse;
  juce::FileInputStream* midiInputStream;
  juce::MidiOutput* fluidsynth;
  juce::MidiMessageSequence::MidiEventHolder* curEvent;
  juce::MidiBuffer chord;
  const juce::MidiMessageSequence* curTrack;
  juce::File* midiFile;
  int nbTrack;
  int nbEvent;
  int num;
  int i;
  double curTimestamp;
  double refTime;
  
  deviceName=juce::MidiOutput::getDevices();
  std::cout<<"Available MIDI devices:"<<std::endl;
  
  /* Print found device */
  for (i = 0; i < deviceName.size(); i++) {
    std::cout<<i<<"\t"<<deviceName[i]<<std::endl;
  }
  fluidsynth=juce::MidiOutput::openDevice(1);
  fluidsynth->startBackgroundThread();
  
  /* Open and Read midiFile */
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
  
  /*TODO: multi-track (drifting !!!) playback */
  /*Retrieve track(s) and info*/
  midiToParse->convertTimestampTicksToSeconds(); 
  curTrack=midiToParse->getTrack(1);
  nbEvent=curTrack->getNumEvents();
  curTimestamp=curTrack->getStartTime();

  /* Start time */
  refTime=Time::getMillisecondCounter();
  

  /* Loop on all events, add them on MidiBuffers if they're "chords"
   * and send the MidiBuffers with delay
   * */
  for (i = 0; i < nbEvent;) {
    num=0;
    
    /* Check if events form a "Chord" */
    while(curTrack->getEventTime(i)==curTimestamp){
      chord.addEvent(curTrack->getEventPointer(i)->message,num);
      num++;
      i++;
    }

    fluidsynth->sendBlockOfMessages(chord,refTime+curTimestamp*1000,100000);
    
    if(debug){ 
      std::cout<<"message block sent :"<< curTimestamp<<" with "
               <<chord.getNumEvents()<<" event(s) "<<std::endl;
    }

    chord.clear();
    curTimestamp=curTrack->getEventTime(i);
  }
}



void FluidCompositor::aSending(EASEAClientData* cl){
  Compositor::aSending(cl); 
}


void FluidCompositor::aReception(EASEAClientData* cl){
  Compositor::aReception(cl);
}
