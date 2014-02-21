#include "Compositor.hpp"


Compositor::OSCSender(std::string synthesisIP,int portnum,bool dbg):
          debug(dbg){
  
  synthServSocket(IpEndpointName(synthesisIP, portnum));
  OUTPUT_BUFFER_SIZE=1024;
}

Compositor::~OSCSender(){}


void Compositor::send(){
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/simple" ) 
          <<  "hello" << osc::EndMessage
        << osc::EndBundle;
  
  synthServSocket.Send( p.Data(), p.Size() );
}

bool Compositor::send(osc::OutboundPacketStream oscMsg){
  synthServSocket.Send(oscMsg.Data(),oscMsg.Size());  
}

osc::OutboundPacketStream Compositor::compose(EASEAClientData* cl){
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
  int freq = cl->getWorstVector()->back();
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/note" ) 
          <<  freq << osc::EndMessage
        << osc::EndBundle;
  
  synthServSocket.Send( p.Data(), p.Size() );
}

int Compositor::rescaling(int rangeMin,int rangeMax,float min,float max,float value){
  float normalized=((value-min)/(max-min));
  int rangeMult=rangeMax-rangeMin;
  
  return rangeMin+(normalized*rangeMult);
}

void Compositor::notify(EASEAClientData* cl){
  this->send();
}
