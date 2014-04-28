// sc.solar 2001 ; basics: hairi 2001
// changes:
//  19.11.2003: sc3 version
MIDIFile { var <>format, <>ntrks, <>division, <>dataChunks, <>scores , <>tempos,
  <>offsets, <>timeSigns, <>texts, <>seqNums,<>node,<>sampler;
  classvar path;
  *new { ^super.new.init }
  init {  
      dataChunks = Array.new;
      scores = Array.new;
      tempos = Array.new;
      offsets = Array.new;
      timeSigns = Array.new;
      texts = Array.new;
      seqNums = Array.new;
      node=1000;
  } // init
  
  readHeader { arg pathname;
    // reads only header information: [format, tracks, division] ;
    // where division is either one element: number of delta-time ticks per quarter-note
    // or a two element array : [frames per second, resolution per frame]
    var rawArray, file, convert; 
    this.path=pathname;
      
      rawArray = Int8Array.new;
      file = File.new(pathname, "r");
      14.do({ arg i;
        rawArray = rawArray.add(file.getInt8)
      });
      file.close;
      convert = { arg raw ; if ( raw < 0 , { 256 + raw } , { raw }) };
      
      format = ((convert.value(rawArray.at(8))*256) + convert.value(rawArray.at(9)));
      ntrks = ((convert.value(rawArray.at(10))*256) + convert.value(rawArray.at(11)));
      division = 
        if( (rawArray.at(12)) >= 0, {
          (rawArray.at(12)*256) + convert.value(rawArray.at(13))
        },{
          [0-(rawArray.at(12)) ,convert.value(rawArray.at(13))]
        });
    
  } // end readHeader
  read { arg pathname;
    var  file, rawArray, convert, dataChunk, headerLength, pointer,
      chunkLengths, timesArrays ,channelsArrays ,notesArrays ,veloxArrays ,absTimesArrays ;
      //this.path=pathname;
          
      file = File.new(pathname, "r");
      //rawArray = file.readAllInt8;
      file.length.do({ arg i;rawArray = rawArray.add(file.getInt8)});
      file.close;
     convert = { arg raw ; if ( raw < 0 , { 256 + raw } , { raw }) };
      format = ((convert.value(rawArray.at(8))*256) + convert.value(rawArray.at(9)));
      ntrks = ((convert.value(rawArray.at(10))*256) + convert.value(rawArray.at(11)));
      division = 
        if( (rawArray.at(12)) >= 0, {
          (rawArray.at(12)*256) + convert.value(rawArray.at(13))
        },{
          [0-(rawArray.at(12)) ,convert.value(rawArray.at(13))]
        });
      dataChunk = Array.fill( rawArray.size , { arg  i ; convert.value(rawArray.at(i)) });  
                
      headerLength = dataChunk.at(7)+(dataChunk.at(6) * 256 ) + (dataChunk.at(5) * 256 * 256 ) + (dataChunk.at(4) * 256 * 256 * 256 ) ;
      // should always be 6 , no?
      
      pointer = 8 + headerLength ;
      // beginning of MTrk 1
      chunkLengths = Array.fill( ntrks, 0 );
      ntrks.do({ arg i; var length;
        length = dataChunk.at(7+pointer)+(dataChunk.at(6+pointer) * 256 ) + (dataChunk.at(5+pointer) * 256 * 256 ) + (dataChunk.at(4+pointer) * 256 * 256 * 256 ) ;
        chunkLengths.put(i,length);
        // lenght of each track
        pointer = pointer + 8 + chunkLengths.at(i) ;
        // beginning of next chunk or end
      });
      
      // ntrks.postln;
      //chunkLengths.postln;
          
      pointer = 8 + headerLength ;
      // again beginning of MTrk 1 
    
      dataChunks = Array.fill( chunkLengths.size, 0 );
      
      chunkLengths.do({ arg length,i;
        dataChunks.put(i,dataChunk.copyRange( pointer+8 , pointer + 8 + length) );
        pointer = pointer + 8 + length ;
        // beginning of next data or end
      });
      
      // dataChunks.do({arg item; item.postln});
      
      if ( pointer != dataChunk.size , { "There is something wrong ".postln; });
      
      scores = Array.fill( chunkLengths.size, 0 );
  // extract the scores and other information
  
    dataChunks.do({arg trackArray,i;
      var timesArray, channelsArray ,notesArray ,veloxArray ,absTimesArray, texte, text, len, tempi, offset, timeSign, seqNum,
        deltaFunction, deltaTime, absTime, deltaAkku, runningStatus;      
      
      runningStatus = 0;
      deltaAkku = 0;
      absTime = 0;
      pointer = 0;
      timesArray = [];
      notesArray = [];
      veloxArray = [];
      channelsArray = [];
      tempi = []; 
      texte = [];
      
      //trackArray.size.postln;
        
      deltaFunction = { deltaTime = 0 ;
        while({ trackArray.at(pointer) > 128 },{
          deltaTime = deltaTime * 128 ;
          deltaTime = deltaTime + ((trackArray.at(pointer) - 128 ) * 128);
          pointer = pointer + 1 ; 
        });
        deltaTime = deltaTime + trackArray.at(pointer) ;
        absTime = absTime + deltaTime ; 
        pointer = pointer + 1 ; 
      };
              
              
          
      while ({ pointer < trackArray.size}, 
        { deltaFunction.value ; 
          // meta events  
          if ( trackArray.at(pointer ) == 255 , 
            { pointer = pointer + 1 ; 
              // sequence number
              if( trackArray.at(pointer) == 0,{
                seqNum = (trackArray.at(3+pointer)+(trackArray.at(2+pointer) * 256 ));
                pointer = pointer + 4 ; 
                deltaAkku = deltaAkku + deltaTime ; 
              },{
              // any text
              if( trackArray.at(pointer) >= 1 and:{ trackArray.at(pointer) <=7 },{
                text = "";
                // "found text ".post; 
                pointer = pointer + 1;
                len = trackArray.at(pointer);
                len.do({
                  pointer = pointer + 1;
                  text = text ++ (trackArray.at(pointer).asAscii.asString);
                });
                texte = texte.add([absTime,text]);
                deltaAkku = deltaAkku + deltaTime ; 
              },{
              // end of track
              if( trackArray.at(pointer) == 47,{
                // "end track ".post; i.postln; 
                pointer = pointer + 3 ; // break  (pointer < trackArray.size)
                deltaAkku = deltaAkku + deltaTime ; 
              },{
              // set tempo
              if( trackArray.at(pointer) == 81,{
                // "found tempo at ".post;absTime.postln;
                pointer = pointer + 2 ; 
                tempi = tempi.add([absTime,trackArray.at(2+pointer)+(trackArray.at(1+pointer) * 256 ) 
                                  + (trackArray.at(pointer) * 256 * 256 )] );
                pointer = pointer + 3 ;
                deltaAkku = deltaAkku + deltaTime ; 
              },{
              // smpte offset
              if( trackArray.at(pointer) == 84,{
                // "found offset at ".post;absTime.postln;
                pointer = pointer + 2 ; 
                // offset format [hr, mn, se, fr, ff]
                offset = ([trackArray.at(pointer), trackArray.at(1+pointer), trackArray.at(2+pointer), 
                          trackArray.at(3+pointer), trackArray.at(4+pointer)] );
                pointer = pointer + 5 ;
                deltaAkku = deltaAkku + deltaTime ; 
              },{
              // time signature
              if( trackArray.at(pointer) == 88,{
                // "found time signature at ".post;absTime.postln;
                pointer = pointer + 2 ; 
                // time signature  format [numerator, denominator, midi clocks per mclick, 32th per 1/4 note]
                timeSign = ([trackArray.at(pointer), trackArray.at(1+pointer), 
                             trackArray.at(2+pointer), trackArray.at(3+pointer)] );
                pointer = pointer + 4 ;
                deltaAkku = deltaAkku + deltaTime ; 
              },{
                pointer = pointer + trackArray.at( pointer + 1 ) + 2 ;                    
                deltaAkku = deltaAkku + deltaTime ; 
              });
              });
              });
              });
              });
              });
          },{
                  
        // note offs (3 bytes)
        
          if ( trackArray.at(pointer) > 127 and: { trackArray.at(pointer) < 144 },
            { runningStatus = trackArray.at(pointer) ; 
            //timesArray = timesArray.add( deltaTime + deltaAkku ); 
            deltaAkku = 0 ; 
            //notesArray = notesArray.add( trackArray.at(pointer+1) );
            //veloxArray = veloxArray.add( trackArray.at(pointer+2) ); 
            //channelsArray = channelsArray.add( runningStatus - 127 ); 
            pointer = pointer + 3 ;
          },{
        
        // note ons (3 bytes)
          if ( trackArray.at(pointer) > 143 and: { trackArray.at(pointer) < 160 }, 
            { runningStatus = trackArray.at(pointer) ; 
            timesArray = timesArray.add( deltaTime + deltaAkku ); 
            deltaAkku = 0 ; 
            notesArray = notesArray.add( trackArray.at(pointer+1) );
            veloxArray = veloxArray.add( trackArray.at(pointer+2) ); 
            channelsArray = channelsArray.add( runningStatus - 143 );
            pointer = pointer + 3 ;                                                          
          },{
          
        // ignore polyphonic aftertouch ? (3 bytes)
          
        // controllers (3 bytes)
          if ( trackArray.at(pointer) > 175 and: { trackArray.at(pointer) < 192 }, 
                               { runningStatus = trackArray.at(pointer) ; 
                                 deltaAkku = deltaAkku + deltaTime ; 
                                        pointer = pointer + 3 ;
          },{
        // program (2 bytes)
          if ( trackArray.at(pointer) > 191 and: { trackArray.at(pointer) < 208 }, 
            { runningStatus = trackArray.at(pointer) ; 
            deltaAkku = deltaAkku + deltaTime ; 
            pointer = pointer + 2 ;
          },{
          
        // ignore channel aftertouch ? 208-223 (2 bytes)
          
        // pitch bend (3 bytes)
          if ( trackArray.at(pointer) > 223 and: { trackArray.at(pointer) < 240 }, 
                               { runningStatus = trackArray.at(pointer) ; 
                                 deltaAkku = deltaAkku + deltaTime ; 
                                        pointer = pointer + 3 ;
          },{
          
        // ignore sysex etc. 240-254 (different number of bytes)
          
        // running status ; using short form 
          // note ons
          if( runningStatus > 143 and: { runningStatus < 160 } , { 
            timesArray = timesArray.add( deltaTime + deltaAkku ); 
            deltaAkku = 0 ; 
            notesArray = notesArray.add( trackArray.at(pointer) );
            veloxArray = veloxArray.add( trackArray.at(pointer+1) ); 
            channelsArray = channelsArray.add( runningStatus - 143 );
            pointer = pointer + 2 ;
          },{ 
          // note offs
          if( runningStatus > 127 and: { runningStatus < 144 } , { 
            timesArray = timesArray.add( deltaTime + deltaAkku ); 
            deltaAkku = 0 ; 
            notesArray = notesArray.add( trackArray.at(pointer) );
            veloxArray = veloxArray.add( trackArray.at(pointer+1) ); 
            channelsArray = channelsArray.add( runningStatus - 127  );                           
            pointer = pointer + 2 ; 
          },{                                                  
          if( runningStatus > 175 and: { runningStatus < 192 } , { 
            deltaAkku = deltaAkku + deltaTime ; 
                  pointer = pointer + 2 ; 
          },{ 
          if( runningStatus > 223 and: { runningStatus < 240 } , { 
            deltaAkku = deltaAkku + deltaTime ; 
                  pointer = pointer + 2 ; 
          },{ 
        
          if( runningStatus > 191 and: { runningStatus < 208 } , { 
            deltaAkku = deltaAkku + deltaTime ; 
            pointer = pointer + 1 ; 
          }); }); }); }); }); }); }); }); }); }); }); 
      }); // while
            
                absTime = 0 ; 
                absTimesArray =  Array.fill( timesArray.size , { arg i ; absTime = absTime + timesArray.at(i) ; absTime  });
                scores = scores.put(i,Array.fill( timesArray.size , { arg i ; [ timesArray.at(i), channelsArray.at(i), notesArray.at(i), veloxArray.at(i) , absTimesArray.at(i)]}););
          
          tempos = tempos.add(tempi);
          offsets = offsets.add(offset);
          timeSigns = timeSigns.add(timeSign);
          texts = texts.add(texte);
          seqNums = seqNums.add(seqNum);
          
    }); // end dataChunks.do
    
    ^scores
                      
   } // end readFile
  
  initSampler{ arg server,pathToSample;
    
    //var d= ();                                          /*for mapping midinote to filename*/
    var sym;
    sampler= RedDiskInSamplerGiga(server);             /*sampler*/
    sampler.overlaps=11; 
    /*lowest note = midi 21*/
    //mezzo forte
    
    88.do{|x,index|
      var pathname,key,tmpIndex,tmpNote;
      tmpIndex=index+1;
      tmpNote=index+21;
      if(tmpNote<100,{
        pathname=pathToSample++"/"++tmpIndex++"_mcg_mf_0"++tmpNote++".wav";
      },{});
      
      if(tmpNote>=100,{
        pathname=pathToSample++"/"++tmpIndex++"_mcg_mf_"++tmpNote++".wav";
      },{});
      
      sym=""++tmpNote++"_mf";
      key= (sym).asSymbol;
      //d.put(index, key);            /*like (45 : A2_96)*/
      sampler.preload(key, pathname);
    };
    /*
    piano
    88.do{|x,index|
      var pathname,key,tmpIndex,tmpNote;
      tmpIndex=index+177;
      tmpNote=index+21;
      if(tmpNote<100,{
        pathname=pathToSample++"/"++tmpIndex++"_mcg_p_0"++tmpNote++".wav";
      },{});
      
      if(tmpNote>=100,{
        pathname=pathToSample++"/"++tmpIndex++"_mcg_p_"++tmpNote++".wav";
      },{});
      sym=""++tmpNote++"_p";
      key= (sym).asSymbol;
      d.put(index, key);            like (45 : A2_96)
      sampler.preload(key, pathname);
    };
    
    forte
    88.do{|x,index|
      var pathname,key,tmpIndex,tmpNote;
      tmpIndex=index+265;
      tmpNote=index+21;
      if(tmpNote<100,{
        pathname=pathToSample++"/"++tmpIndex++"_mcg_f_0"++tmpNote++".wav";
      },{});
      
      if(tmpNote>=100,{
        pathname=pathToSample++"/"++tmpIndex++"_mcg_f_"++tmpNote++".wav";
      },{});
      sym=""++tmpNote++"_f";
      key= (sym).asSymbol;
      //d.put(index, key);            like (45 : A2_96)
      sampler.preload(key, pathname);
    };
    */

    ^sampler; 
  }
  playTrack{ arg numTrack, synthName,server,funcArrayNote;
    // the score player
    var midifile, path, div, score, tempo=75, step=0;
    var currentTempo=0,tempi,minDelta,note;
    var velocity; 
    //var noteoff=Array.new;
    // where are you
    //if((this.format==1),{numTrack=numTrack+1;tempi=tempos.at(numTrack-1);},{tempi=tempos.at(numTrack);});
    score = this.scores.at(numTrack); 
    div = division;
    div.postln;
    tempi=tempos.at(0);
    tempos.at(1).postln;
    score.postln;
    "nombre note on :".post;
    score.size.postln;
    score.do({ arg item;
      if((currentTempo < tempi.size),{
        if(((item.at(4)>=tempi.at(currentTempo).at(0))), {
          //tempo=60000000/tempi.at(currentTempo).at(1);
          currentTempo=currentTempo+1;
          tempo.postln;
        });
      }
      ,{});
      
      //tempo.postln;
      
      item.put(0,item.at(0)/(div*tempo/60));
      item.put(1,item.at(1)-1);  // MIDI channel 1 == Sc channel 0
      item.put(4,item.at(4)/(div*tempo/60));  // MIDI channel 1 == Sc channel 0
      });
    

    // play the score
    SystemClock.sched(score.at(0).at(4),{ arg time; 
    //	score.at(step).at(2).postln;
      /*
      if(score.at(step).at(3)<128,{velocity="_f"});
      if(score.at(step).at(3)<85,{velocity="_mf"});
      if(score.at(step).at(3)<42,{velocity="_p"});
      velocity.postln;
      */
      velocity="_mf";
      sampler.play((""++(score.at(step).at(2))++velocity).asSymbol,0.1,1,1,0.7);
      //score.at(step).at(2).asSymbol.postln;
      note=funcArrayNote.value.at(0).at(1);
      if(note==2,{sampler.play((""++(score.at(step).at(2)+1)++velocity).asSymbol,0,1,1,0.2);});
      if(note==3,{sampler.play((""++(score.at(step).at(2)+2)++velocity).asSymbol,0,1,1,0.2);});
      if(note==4,{sampler.play((""++(score.at(step).at(2)+3)++velocity).asSymbol,0,1,1,0.2);});
      minDelta=score.at(step).at(0);      
     
     //chord 
     
     {score.at(step).at(4)==score.at(step+1).at(4)}.while({
        step = step+1; 
        /*
        if(score.at(step).at(3)<128,{velocity="_f"});
        if(score.at(step).at(3)<85,{velocity="_mf"});
        if(score.at(step).at(3)<42,{velocity="_p"});
        */
        velocity="_mf";
        sampler.play((""++(score.at(step).at(2))++velocity).asSymbol,0.1,1,1,0.7);
        if(note==2,{sampler.play((""++(score.at(step).at(2)+1)++velocity).asSymbol,0,1,1,0.2);});
        if(note==3,{sampler.play((""++(score.at(step).at(2)+2)++velocity).asSymbol,0,1,1,0.2);});
        if(note==4,{sampler.play((""++(score.at(step).at(2)+3)++velocity).asSymbol,0,1,1,0.2);});
      });
     
      step = step+1;
      if(step<score.size,{minDelta=(score.at(step).at(4))-(score.at(step-1).at(4));});
      if(step<score.size,{minDelta},{nil}) 
    });
  }

  playFile{ arg synthName,server;
    var start=0;
    if((this.format==1),{start=1},{});
    for(start,ntrks,{arg i;this.playTrack(i,synthName,server)});
  }

} // end MIDIFile
