(
s.options.numBuffers=4096;
s.waitForBoot({
  
  var timeout= 60; //timeout de 60 seconde s
  var midifile, path, sampler;
  var tmpindex;
  
  var idHashMap= IdentityDictionary.new;
  
  idHashMap.put(0,1);

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
  midifile=MIDIFile.new;
  sampler=midifile.initSampler(s,"/home/pallamidessi/Téléchargements/maestro".standardizePath);
  ~play={
  path ="/home/pallamidessi/Téléchargements/con2-cm.mid";
  midifile.read(path);

  ~playkeyboard={ arg intensity;
  Task({
    88.do{arg x,index;
     tmpindex=""++(index+21)++intensity;
     sampler.play(tmpindex.asSymbol,0,1,1);
     0.3.wait;
   };
  }).play;
 };
  
 b={idHashMap};

  midifile.playTrack(0,"Nsec",s,b);
  //midifile.playTrack(2,"Nsec",s,b);
  };
  ~freesampler={
    Buffer.freeAll;
  };

  ~testNote={arg note;
    sampler.play(note.asSymbol,0.1,1,1,1);
  };
  /*
  ~isAlreadyDefined={arg id,idArray
    idHashMap 
  };
  */
~defineinput.value;
~play.value;
})
)
/*
s.quit;
Buffer.freeAll;
s.freeAll;
~play.value;
~playkeyboard.("_f");
~freesampler.value;
~testNote.("80_f");
s.freeAll;
OSCdef(\best).enabled;
s.options.numBuffers=4096;
"launchctl limit maxfiles 16384 unlimited".unixCmd;
"launchctl limit".unixCmd;
*/
