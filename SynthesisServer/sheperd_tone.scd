(
s.waitForBoot({
var from=0.015;

SynthDef("shep",{
	arg amp=0.08, freq=440;
	var sig;
	sig = SinOsc.ar([freq,freq]);
	sig = sig*amp;
	Out.ar(0, sig);
}).add;

SynthDef.new("bleep",{
  arg freq=440;
  var sine,env,env_gen;
  env=Env.perc(0.2,0.2,0.2,[-4,4]);
  env_gen=EnvGen.kr(env,doneAction:2);
  sine={SinOsc.ar(freq,0,0.9)};
  Out.ar(0,[sine*env_gen,sine*env_gen]);
}).add;


OSCdef(\best,
  {
    arg msg;
    from=(msg[1]/20000).squared;
    from.postln;},
  \note);

OSCdef(\reception,
  {Synth.new("bleep",[440]);},
  \Reception);

OSCdef(\sending,
  {Synth.new("bleep",[1000]);},
  \Sending);

~playShep = {
	
	arg	speed=0.015,
			volume=0.5,
			direction=0,
			centerFreqShift=0;
			
	var	pat0,pat1,pat2,pat3,pat4,pat5,pat6,pat7,pat8,
			midiArray,ampArray;
	
	midiArray=(6,6.01..113.99);

	ampArray = Array.newClear(10800);
	(-5400..5399).do{
		arg val, index;
		ampArray[index]=1.000001.pow((val.pow(2).neg));
	};
	
	if(
		direction > 0,
		{midiArray},
		{midiArray = midiArray.reverse});
	
	midiArray = midiArray+centerFreqShift;
	
	pat0 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray,inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
				],1) *
			volume,
		midinote:Pseq(midiArray,inf),]);
	
	pat1 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-1200),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
			],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-1200),inf),]);

	pat2 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-2400),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
			],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-2400),inf),]);
	
	pat3 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-3600),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
				],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-3600),inf),]);
	
	pat4 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-4800),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
				],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-4800),inf),]);
	
	pat5 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-6000),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
				],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-6000),inf),]);
	
	pat6 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-7200),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
				],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-7200),inf),]);
	
	pat7 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-8400),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
				],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-8400),inf),]);
	
	pat8 = Pmono(*[\shep,
		dur:Pfunc{from},
		amp:
			Pseq(ampArray.rotate(-9600),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
				],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-9600),inf),]);
	
	Pspawner({
		arg sp;
		sp.par(pat0);
		sp.par(pat1);
		sp.par(pat2);
		sp.par(pat3);
		sp.par(pat4);
		sp.par(pat5);
		sp.par(pat6);
		sp.par(pat7);
		sp.par(pat8);
	}).play;
};
~playShep.(0.030, 0.75,  0,  0);
})
)

/*
~playShep.(0.010, 0.75,  0,  0);

(
~playShep.(0.035, 0.24,  0,  0);
~playShep.(0.035, 0.24,  0,  3);
~playShep.(0.035, 0.24,  0,  7);
)

(
~playShep.(0.006,  0.122,  0,  -5.1);
~playShep.(0.017,  0.122,  0,   2.5);
~playShep.(0.035,  0.122,  0,   5.9);
~playShep.(0.043,  0.122,  0,   9.7);
~playShep.(0.012,  0.122,  0,   14.1);
~playShep.(0.025,  0.122,  0,   17.25);
~playShep.(0.075,  0.122,  0,   21.6);
~playShep.(0.051,  0.122,  0,   23.7);
)

(
~playShep.(0.005,  0.122,  1,  -5.5);
~playShep.(0.034,  0.122,  0,   22.7);
~playShep.(0.014,  0.122,  0,   1.83);
~playShep.(0.023,  0.122,  1,   2.4);
~playShep.(0.011,  0.122,  0,   2.5);
~playShep.(0.045,  0.122,  0,   11);
~playShep.(0.065,  0.122,  1,   17.1);
~playShep.(0.041,  0.122,  1,   5.7);
)
*/

/*
(
	Task({
		s.boot;
		2.wait;
		"je ne fais pas de son".postln;
	}).play;


	s.makeGui;

).value;


SynthDef.new("2sec",{
  arg freq=440;
  var sine,env,env_gen;
  env=Env.perc(1,1,1,[-4,4]);
  env_gen=EnvGen.kr(env,doneAction:2);
  sine={SinOsc.ar(freq,0,0.4)};
  Out.ar(0,[sine*env_gen,sine*env_gen]);
}).send(s);

Synth("2sec").play;

(
OSCdef(\newDef,
  {Synth("2sec");},
  \simple); 
)

(
OSCdef(\newDef2,
  {
    arg msg;
    Synth("2sec",[freq:msg[1]]);
    },
  \note); 
)

midinote
(
	~afunc={
		|test=0.5|	
		p={PinkNoise.ar([test,test])}.play;
	}
);

{~afunc.value}.defer(2);



(
~func={
  var volume=0.5;
	var midiArray=(6,6.01..113.99);
  var speed=0.001;	
	var ampArray = Array.newClear(10800);
  var pat1;	
	
  (-5400..5399).do{
		arg val, index;
		ampArray[index]=1.000001.pow((val.pow(2).neg));
	};

  pat1 = Pmono(*[\shep,
		dur:speed,
		amp:
			Pseq(ampArray.rotate(-1200),inf) *
			Pseq([
				Pseg(Pseq([0,1],1),Pseq([1,0],1),\sine),
				Pseq([1],inf)
			],1) *
			volume,
		midinote:Pseq(midiArray.rotate(-1200),inf),]).play;

	Pspawner({
		arg sp;
		sp.par(pat1);
  }).play;
};)
~func.play;

(
SynthDef("shep",{
	arg amp=0.08, freq=440;
	var sig;
	sig = SinOsc.ar([freq,freq]);
	sig = sig*amp;
	Out.ar(0, sig);
}).add;
)


(
p = Pmono("default", \dur, Pfunc({[1,2,3,4,5].choose}), \freq, Pwhite(1,8) * 100 ).play
p.free;
)
*/

