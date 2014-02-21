#include "Compositor.hpp"


Compositor::Compositor(std::string synthesisIP,int portnum,bool dbg):
          debug(dbg){
  
  synthServSocket=new UdpTransmitSocket( IpEndpointName(synthesisIP.c_str(), portnum) );
  OUTPUT_BUFFER_SIZE=1024;
}

Compositor::~Compositor(){}


void Compositor::send(){
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/simple" ) 
          <<  "hello" << osc::EndMessage
        << osc::EndBundle;
  
  synthServSocket->Send( p.Data(), p.Size() );
}

void Compositor::send(osc::OutboundPacketStream oscMsg){
  synthServSocket->Send(oscMsg.Data(),oscMsg.Size());  
}

osc::OutboundPacketStream Compositor::compose(EASEAClientData* cl){
  char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
  int freq = cl->getWorstVector()->back();
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/note" ) 
          <<  freq << osc::EndMessage
        << osc::EndBundle;
  
  return p; 
}

float Compositor::rescaling(int rangeMin,int rangeMax,float min,float max,float value){
  float normalized=((value-min)/(max-min));
  int rangeMult=rangeMax-rangeMin;
  
  return rangeMin+(normalized*rangeMult);
}

void Compositor::notify(EASEAClientData* cl){
  this->send();
}
