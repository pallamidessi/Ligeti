#include "FluidCompositor.hpp"

namespace fs=boost::filesystem;

bool FluidCompositor::checkDir(fs::path p,std::vector<juce::MidiFile*> *listMidi){
  fs::directory_iterator end_iter;
  juce::MidiFile* midiToParse;
  juce::FileInputStream* midiInputStream;
  juce::File* midiFile;
  
  if (fs::exists(p) && fs::is_directory(p)) { 
    for (fs::directory_iterator dirIter(p); dirIter!=end_iter; dirIter++) {
      if (fs::is_regular_file(dirIter->status())) {
        if(dirIter->path().extension().compare(".mid")|| //check file extension
           dirIter->path().extension().compare(".midi")){
          
          std::string pp(dirIter->path().c_str());
          
          /* Open and Read midiFile */
          midiFile=new File(pp);

          if(!midiFile->existsAsFile()){
            perror("File does not exist");
            exit(1);
          }

          midiInputStream= new FileInputStream(*midiFile);
          midiToParse=new MidiFile();

          if(!midiToParse->readFrom(*midiInputStream)){
            perror("Can't read stream");
            exit(1);
          }

          listMidi->push_back(midiToParse);  
          
          delete midiInputStream;
          delete midiFile;
        } 
      }
    }
  return true;
  }
return false;
}


std::vector<juce::MidiFile*>* FluidCompositor::loadMidiFromPath(fs::path p, int nbArg){

  int i;
  std::string pp;
  std::vector<juce::MidiFile*> *listMidi;
  juce::MidiFile* midiToParse;
  juce::FileInputStream* midiInputStream;
  juce::File* midiFile;
  
  listMidi= new std::vector<juce::MidiFile*>;

  /* "Directory" mode*/ 
  if (checkDir(p.c_str(),listMidi)) {
  }
  /*List a file path given by hand*/
  else {
    for (i = 0; i < nbArg; i++) {
    
      std::string pp(p.c_str());
      
      /* Open and Read midiFile */
      midiFile=new File(pp);

      if(!midiFile->existsAsFile()){
        perror("File does not exist");
        exit(1);
      }

      midiInputStream= new FileInputStream(*midiFile);
      midiToParse=new MidiFile();

      if(!midiToParse->readFrom(*midiInputStream)){
        perror("Can't read stream");
        exit(1);
      }

      listMidi->push_back(midiToParse);  
      
      delete midiInputStream;
      delete midiFile;
    }
  }
  return listMidi;
}

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


FluidCompositor::FluidCompositor(std::string ip,int port,bool dbg,std::vector<juce::MidiFile*> *listMidi):Compositor::Compositor(ip,port,dbg){
  juce::StringArray deviceName;
  juce::MidiFile* midiToParse;
  juce::MidiOutput* fluidsynth;
  juce::MidiMessageSequence::MidiEventHolder* curEvent;
  juce::MidiBuffer chord;
  const juce::MidiMessageSequence* curTrack;
  int nbFile;
  int nbTrack;
  int nbEvent;
  int num;
  int i,j;
  double curTimestamp;
  double refTime;
  double fileDuration;
  deviceName=juce::MidiOutput::getDevices();
  std::cout<<"Available MIDI devices:"<<std::endl;

  /* Print found device */
  for (i = 0; i < deviceName.size(); i++) {
    std::cout<<i<<"\t"<<deviceName[i]<<std::endl;
  }
  fluidsynth=juce::MidiOutput::openDevice(1);
  fluidsynth->startBackgroundThread();

  /* Open and Read midiFile */
  nbFile=listMidi->size();

  for (k = 0; k < nbFile; k++) {
    midiToParse=(*listMidi)[k];
    
    /*Retrieve track(s) and info*/
    nbTrack=midiToParse->getNumTracks();
    midiToParse->convertTimestampTicksToSeconds(); 

    /* Start time */
    refTime=Time::getMillisecondCounter()+fileDuration;
    fileDuration=0;

    /* Loop on all events, add them on MidiBuffers if they're "chords"
     * and send the MidiBuffers with delay
     */
    for (i = 0; i < nbTrack; i++) {
      
      curTrack=midiToParse->getTrack(i);
      nbEvent=curTrack->getNumEvents();
      curTimestamp=curTrack->getStartTime();
      
      for (j = 0; j < nbEvent;) {
        num=0;

        /* Check if events form a "Chord" */
        while(curTrack->getEventTime(j)==curTimestamp && j< nbEvent){
          chord.addEvent(curTrack->getEventPointer(j)->message,num);
          num++;
          j++;
        }

        fluidsynth->sendBlockOfMessages(chord,refTime+curTimestamp*1000,100000);

        if(debug){ 
          std::cout<<"message block sent :"<< curTimestamp<<" with "
            <<chord.getNumEvents()<<" event(s) "<<std::endl;
        }

        chord.clear();
        curTimestamp=curTrack->getEventTime(j);
      }
      if (curTrack->getEndTime()>fileDuration) {
        fileDuration=curTrack->getEndTime()
      }
    }
  }
}



void FluidCompositor::aSending(EASEAClientData* cl){
  Compositor::aSending(cl); 
}


void FluidCompositor::aReception(EASEAClientData* cl){
  Compositor::aReception(cl);
}
