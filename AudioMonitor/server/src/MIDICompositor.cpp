#include "MIDICompositor.hpp"

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
}


void MIDICompositor::aSending(EASEAClientData* cl){
  Compositor::aSending(cl); 
}


void MIDICompositor::aReception(EASEAClientData* cl){
  Compositor::aReception(cl);
}
