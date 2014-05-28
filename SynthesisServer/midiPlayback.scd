s.waitForBoot({

    var idHashMap= IdentityDictionary.new;
    var midifile, path, sampler;
    idHashMap.put(0,1);
    midifile=MIDIFile.new;
    sampler=midifile.initSampler(s,"~/Téléchargements/maestro".standardizePath);
  ~customPlay={
  
    path ="/home/pallamidessi/Téléchargements/con2-cm.mid";
    midifile.read(path);
    b={idHashMap};
    midifile.playTrack(0,"Nsec",s,b);
  };

  ~array={idHashMap};
  ~truc={arg  noteNr, velo, dur, upVelo, track, channel, absTime,
              lastTime, counter;
      var velocity="_mf";
      sampler.play(((""++(noteNr))++velocity).asSymbol,0,1,1,0.2);
      noteNr.postln;  
      ~array.value.do({ arg note;
        if(note==2,{sampler.play(((""++(noteNr)+1)++velocity).asSymbol,0,1,1,0.2);});
        if(note==3,{sampler.play(((""++(noteNr)+2)++velocity).asSymbol,0,1,1,0.2);});
        if(note==4,{sampler.play(((""++(noteNr)+3)++velocity).asSymbol,0,1,1,0.2);});
      });
  };

  ~libPlay={
    var m;
    m = SimpleMIDIFile.read( "/home/pallamidessi/Téléchargements/con2-cm.mid" );

    // play it (cmd-. to stop)
    m.playNotesWithFunction(~truc,0,0); // takes a few seconds to start because this midifile starts with a rest

  };
  ~customPlay.value;
  //~libPlay.value;
})
