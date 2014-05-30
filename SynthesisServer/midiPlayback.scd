s.waitForBoot({

  var idHashMap= IdentityDictionary.new;
  var midifile, path, sampler;
  idHashMap.put(0,1);
  midifile=MIDIFile.new;
  sampler=midifile.initSampler(s,"~/Téléchargements/maestro".standardizePath);

  ~defineinput={
    OSCdef(\best,
    {
      arg msg;
      var note,id;
      
      note=msg[1];
      id=msg[2];
      
      "note :".post;
      note.postln;
      "id :".post;
      id.postln;
      "".postln;
      
      idHashMap.put(id,note);
    },
    \note);
  };

  ~array={idHashMap};
  
  ~truc={arg  noteNr, velo, dur, upVelo, track, channel, absTime,
              lastTime, counter;
      var velocity="_mf";
      sampler.play(((""++(noteNr))++velocity).asSymbol,0,1,1,velo/128);
      ~array.value.do({ arg note;
        if(note==2,{sampler.play((""++(noteNr+1)++velocity).asSymbol,0,0,1,0.2);});
        if(note==3,{sampler.play((""++(noteNr+2)++velocity).asSymbol,0,1,1,0.2);});
        if(note==4,{sampler.play((""++(noteNr+3)++velocity).asSymbol,0,1,1,0.2);});
      });
  };

  ~libPlay={
    var m;
    m = SimpleMIDIFile.read( "/home/pallamidessi/Téléchargements/gym3_1.mid" );
    m.playNotesWithFunction(~truc,0,1); 
  };
  
  ~defineinput.value;
  ~libPlay.value;
})
