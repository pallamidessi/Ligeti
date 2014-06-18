#include "FluidCompositor.hpp"

namespace fs=boost::filesystem;

MidiOutputControlled::run(){
  while (! threadShouldExit())
  {
    uint32 now = Time::getMillisecondCounter();
    uint32 eventTime = 0;
    uint32 timeToWait = 500;

    PendingMessage* message;

    {
      const ScopedLock sl (lock);
      message = firstMessage;

      if (message != nullptr)
      {
        eventTime = (uint32) roundToInt (message->message.getTimeStamp());

        if (eventTime > now + 20)
        {
          timeToWait = eventTime - (now + 20);
          message = nullptr;
        }
        else
        {
          firstMessage = message->next;
        }
      }
    }

    if (message != nullptr)
    {
      const ScopedPointer<PendingMessage> messageDeleter (message);

      if (eventTime > now)
      {
        Time::waitForMillisecondCounter (eventTime);

        if (threadShouldExit())
          break;
      }

      if (eventTime > now - 200)
        juce::sendMessageNow (message->message);
        sendMessageError(message->message);
    }
    else
    {
      juce::jassert (timeToWait < 1000 * 30);
      wait ((int) timeToWait);
    }
  }

  clearAllPendingMessages();
}

void MidiOutputControlled::sendMessageError(message->message){
  

}

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


std::vector<juce::MidiFile*>* FluidCompositor::loadMidiFromPath(char** argv, int argc){

  int i;
  std::string pp;
  std::vector<juce::MidiFile*> *listMidi;
  juce::MidiFile* midiToParse;
  juce::FileInputStream* midiInputStream;
  juce::File* midiFile;

  listMidi= new std::vector<juce::MidiFile*>;

  /* "Directory" mode*/ 
  if (checkDir(argv[1],listMidi)) {
  }
  /*List a file path given by hand*/
  else {
    for (i = 1; i < argc; i++) {

      std::string pp(argv[i]);

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
  (*amalgamatedNote)[cl->mID]=cl->computeNote();
}

/*TODO move code from constructor to a specific function*/
FluidCompositor::FluidCompositor(std::string ip,int port,bool dbg,std::vector<juce::MidiFile*> *listMidi):Compositor::Compositor(ip,port,dbg){
  juce::StringArray deviceName;
  juce::MidiFile* midiToParse;
  juce::MidiOutput* fluidsynth;
  juce::MidiMessageSequence::MidiEventHolder* curEvent;
  juce::MidiBuffer chord;
  juce::MidiBuffer stopAndReset;
  const juce::MidiMessageSequence* curTrack;
  int nbFile;
  int nbTrack;
  int nbEvent;
  int num;
  int i,j,k;
  int channel;
  double curTimestamp;
  double refTime;
  double fileDuration;
  deviceName=juce::MidiOutput::getDevices();
  std::cout<<"Available MIDI devices:"<<std::endl;

  /* Print found device */
  for (i = 0; i < deviceName.size(); i++) {
    std::cout<<i<<"\t"<<deviceName[i]<<std::endl;
  }

  /*TODO: DEVICE iNDEX HARDCODED 
   * find device with id Fluidsynth and use its index*/
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
      if (curTrack->getEndTime()*1000>fileDuration) {
        fileDuration=curTrack->getEndTime()*1000;
      }
    }
    for (channel = 1; channel <= 16; channel++) {
      stopAndReset.addEvent((juce::MidiMessage::allNotesOff(channel)),1);
      stopAndReset.addEvent((juce::MidiMessage::allControllersOff(channel)),1);
      stopAndReset.addEvent(*(new juce::MidiMessage(175+channel,121,0)),1);
    }
    fluidsynth->sendBlockOfMessages(stopAndReset,refTime+fileDuration,100000);
  }
}



void FluidCompositor::aSending(EASEAClientData* cl){
  Compositor::aSending(cl); 
}


void FluidCompositor::aReception(EASEAClientData* cl){
  Compositor::aReception(cl);
}
