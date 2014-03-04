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
    
  int freq = cl->getBestVector()->back();
  freq=rescaling(freq);
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

float Compositor::rescaling(float value){
  float normalized=((value-projectedMinValue)/(projectedMaxValue-projectedMinValue));
  int rangeMult=freqRangeMax-freqRangeMin;
  
  return freqRangeMin+(normalized*rangeMult);
}


void Compositor::notify(EASEAClientData* cl){
  aSending(cl);
  aReception(cl);
  this->send(compose(cl));
}


void Compositor::setNormalization(float rangeMin,float rangeMax,float projectedMin,float projectedMax){
  this->projectedMinValue=projectedMin;
  this->projectedMaxValue=projectedMax;
  this->freqRangeMin=rangeMin;
  this->freqRangeMax=rangeMax;

}

void Compositor::aSending(EASEAClientData* cl){
  if (cl->isASending()) {
 char buffer[OUTPUT_BUFFER_SIZE];
  osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/Sending" ) 
        << osc::EndMessage
        << osc::EndBundle;
  
  synthServSocket->Send( p.Data(), p.Size() );
   
  }
}

void Compositor::aReception(EASEAClientData* cl){
  if (cl->isAReception()) {
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
      
      p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/Reception" ) 
          << osc::EndMessage
          << osc::EndBundle;
    
    synthServSocket->Send( p.Data(), p.Size() );
  }
}

void SimpleCompositor::send(){
  Compositor::send();
}

void SimpleCompositor::send(osc::OutboundPacketStream oscMsg){
  Compositor::send(oscMsg);
}

void SimpleCompositor::notify(EASEAClientData* cl){
  aSending(cl);
  aReception(cl);
  Compositor::notify(cl);
}


SimpleCompositor::SimpleCompositor(std::string ip,int port,bool dbg):Compositor::Compositor(ip,port,dbg){
}

void SimpleCompositor::aSending(EASEAClientData* cl){
  Compositor::aSending(cl); 
}

void SimpleCompositor::aReception(EASEAClientData* cl){
  Compositor::aReception(cl);
}
