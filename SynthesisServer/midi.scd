s.boot;
s.quit;

(
  
  var timeout= 60; //timeout de 60 seconde s
  var midifile, path, sampler;
  var tmpindex;
  
  var idArray= Array.new;
  idArray.add([0,1]);

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
      //if(~isAlreadyDefined(id,idArray)!=-1,{idArray.add([id,note])});
      idArray.at(0).put(1,note);
      },
    \note);
  };
  midifile=MIDIFile.new;
  sampler=midifile.initSampler(s,"~/Téléchargements/maestro".standardizePath);
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
  /*
  //midifile.scores.at(0).postln;
  //midifile.scores.at(1).postln;
  //midifile.scores.at(2).postln;
  "format :".post;
  midifile.format.postln;
  "nb track :".post;
  midifile.ntrks.postln;
  "division :".post;
  midifile.division.postln;
  */

  b={idArray};

  midifile.playTrack(0,"Nsec",s,b);
  //midifile.playTrack(2,"Nsec",s,b);
  };
  ~freesampler={
    Buffer.freeAll;
  };

  ~testNote={arg note;
    sampler.play(note.asSymbol,0.1,1,1,1);
  }
)
s.freeAll;
~defineinput.value;
~play.value;
~playkeyboard.("_f");
~freesampler.value;
~testNote.("80_f");
s.freeAll;
OSCdef(\best).enabled;
s.options.numBuffers=4096;
"launchctl limit maxfiles 16384 unlimited".unixCmd;
"launchctl limit".unixCmd;
