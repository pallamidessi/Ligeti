(
// read intire file
var midifile, path,div, score, tempo= 160, step=0;
// where are you
path ="/home/pallamidessi/Téléchargements/gp_bolro.mid";

midifile = MIDIFile.new;
midifile.read(path);
midifile.format.postln;
midifile.ntrks.postln;
midifile.division.postln;
score=midifile.scores.at(1).postln; // midifile.scores.at(0).postln; // for format 0 
"tempos".postln;
midifile.tempos.postln;
"offset".postln;
midifile.offsets.postln;
"timesign".postln;
midifile.timeSigns.postln;
"text".postln;
midifile.texts.at(4).postln;
"seqnum".postln;
midifile.seqNums.postln;
)
(
SynthDef("midiplayer",{ arg out=0, freq=0, vol=0.5;
	Out.ar(out,SinOsc.ar(freq, 0, vol))
}).writeDefFile;
s.sendSynthDef("midiplayer");
)

s.boot;
s.quit;

(
// the score player
var midifile, path, div, score, tempo= 120, step=0;
var currentTempo=0,tempi;
// where are you

path ="/home/pallamidessi/Téléchargements/gym3_1.mid";
midifile=MIDIFile.new;
midifile.read(path);
score = midifile.scores.at(1); // score = midifile.scores.at(0); // for format 0
div = midifile.division;
tempi=midifile.tempos.at(0);
"tempi size".postln;
tempi.size.postln;
//"avant division".postln;
//10.do({arg i; score.at(i).postln});

score.do({ arg item;
  if((currentTempo < tempi.size),{
    if(((item.at(4)>=tempi.at(currentTempo).at(0))), {
      tempo=60000000/tempi.at(currentTempo).at(1);
      currentTempo=currentTempo+1;
      tempo.postln;
    });
  }
  ,{"Arf.postln";});
	
  item.put(0,item.at(0)/(div*tempo/60));
  item.put(1,item.at(1)-1);  // MIDI channel 1 == Sc channel 0
  });
//"apres division".postln;
//10.do({arg i; score.at(i).postln});
s.sendMsg("/s_new", "midiplayer", 1000, 1, 0, \out, 0, \freq, 0, \vol, 0.5);

// play the score
SystemClock.sched(0.0,{ arg time; 
	
//	score.at(step).at(2).postln;
	s.sendMsg("/n_set", 1000, \freq, score.at(step).at(2).midicps);
	s.sendMsg("/n_set", 1000, \vol, score.at(step).at(3).midicps/1000);
	step = step+1; 
	if(step<score.size,{score.at(step).at(0)},{nil}) 
});
)

// play two handed
// synth definition
(
SynthDef("midiplayer2",{ arg out=0, freq=0, vol=0.5;
	Out.ar(out,Formant.ar(freq, 900, 880.0, vol))
}).writeDefFile;
s.sendSynthDef("midiplayer2");
)
(
// scoreplayer
var midifile, path, div, score1, score2, tempo= 160, step=0;
// where are you
//path ="/Volumes/n/Home/Users/heiko/Documents/Music/supercollider/works/aaSC_in_out/other/out/midi/waechter.mid";
//path ="/Volumes/n/Home/Users/heiko/Documents/Music/supercollider/works/aaSC_in_out/other/out/midi/duf2.mid";
path ="/home/pallamidessi/Téléchargements/gp_bolro.mid";

midifile=MIDIFile.new;
midifile.read(path);
score1 = midifile.scores.at(1); // score = midifile.scores.at(0); // for format 0
score2 = midifile.scores.at(2); 
div = midifile.division;
score1.do({ arg item; 
	item.put(0,item.at(0)/(div*tempo/60));
	item.put(1,item.at(1)-1);
});
score2.do({ arg item; 
	item.put(0,item.at(0)/(div*tempo/60));
	item.put(1,item.at(1)-1);
});
10.do({arg i; score1.at(i).postln});
10.do({arg i; score2.at(i).postln});
s.sendMsg("/s_new", "midiplayer", 1000, 1, 0, \out, 0, \freq, 0, \vol, 0.5);
s.sendMsg("/s_new", "midiplayer", 1001, 1, 0, \out, 1, \freq, 0, \vol, 0.5);

// play the score
SystemClock.sched(0.0,{ arg time; 
	
	//score.at(step).at(2).postln;
	s.sendMsg("/n_set", 1000, \freq, score1.at(step).at(2).midicps);
	s.sendMsg("/n_set", 1001, \freq, score2.at(step).at(2).midicps);
	s.sendMsg("/n_set", 1000, \vol, score1.at(step).at(3).midicps/1000);
	s.sendMsg("/n_set", 1001, \vol, score2.at(step).at(3).midicps/1000);
	step = step+1; 
	if(step<score1.size,{score1.at(step).at(0)},{nil}) 
});
)

