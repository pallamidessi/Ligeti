Server.internal.boot;
s.makeGui;
Server.internal.makeGui;
Server.internal.freeAll;
{ PinkNoise.ar(0.1)+Saw.ar(600,0.1)+SinOsc.ar(440,0,0.1)}.scope;
Server.internal.freeAll;
{ SinOsc.ar(MouseX.kr(40, 10000, 1), 0, 0.1)*0.5 }.play;
{ SinOsc.ar(MouseX.kr(40, 10000, 1), 0, 0.1)*0.5 }.scope;
s.freeAll;
s.boot;
(
 f= {var f,zout;
    f = LFSaw.kr(0.4, 0, 24, LFSaw.kr([8,7.23], 0, 3, 80)).midicps; // glissando function
    zout = CombN.ar(SinOsc.ar(f, 0, 0.04), 0.2, 0.2, 4); // echoing sine wave
};
f.free;
f.scope;
)
x=Synth.new("bubbles");
{SinOsc.ar(800,0,0.4)}.play;

SynthDef.new("2sec",{
  arg freq=440;
  var sine,env,env_gen;
  env=Env.perc(1,1,1,[-4,4]);
  env.value.plot;
  env_gen=EnvGen.kr(env,doneAction:2);
  sine={SinOsc.ar(freq,0,0.4)};
  Out.ar(0,[sine*env_gen,sine*env_gen]);
}).send(s);

(
x=Synth.new("2sec");
x.set("freq",800);
//x.play;
)
x.free;

~drop ={|dur=0.0005| Env.perc(dur/2,dur/2,1,[-4,4])};
~drop.value.plot;

SynthDef.new("rain",{
  arg rfreq,leftL=1,rightL=1;
  var sine,env_gen,drop,dur=0.0005; 
  drop = Env.perc(dur/2,dur/2,1,[-4,4]);
  env_gen=EnvGen.kr(drop,doneAction:2);
  sine={SinOsc.ar(rfreq,0,[1,2])};
  OffsetOut.ar(0,[sine*env_gen*leftL,sine*env_gen*rightL]);
}).send(s);

  {SinOsc.ar(rrand(330,780),0,[rrand(0.4,0.8),rrand(0.2,0.9)])}.play;
(
~truc = {
	var gaus, osc;
	gaus = {WhiteNoise.ar}.dup(12).sum;
	gaus = LPF.ar(BPF.ar(gaus, 50, 1/0.4), 500);
 
	// 
	osc = SinOsc.ar(gaus.linlin(-1, 1, 40, 80)) * gaus.squared * 10;
	osc = (osc - 0.35).max(0);
 
	2.do{
		osc = HPF.ar(osc, 500);
	};
 
	osc.dup
}
)

~truc.play;

  {SinOsc.ar(440,0,[0.7483,0.3484])}.play;

x.plqy;

(
t= 
  Task({
    100.do({
      Synth("rain",[\rfreq,rrand(100,1000),\leftL,rrand(0.3,0.8),\rightL,rrand(0.2,0.9)]);
      rrand(0.05,0.15).wait;
    });
  });

)

(
y= 
  Task({
    100.do({
      Synth("rain",[\rfreq,rrand(10,100),\leftL,rrand(0.3,0.8),\rightL,rrand(0.2,0.9)]);
      rrand(0.05,0.15).wait;
    });
  });
)
t={Pulse.ar(80)*EnvGen.kr(Env.perc,doneAction: 2)};

(



)
Task({
  1.do({
    t.play;
    0.005.wait;
    t.play;
  });
}).play;

t.play;
s.freeAll;
(
u = 
  Task({
    100.do({
      Synth("rain",[\rfreq,rrand(1000,2000),\leftL,rrand(0.3,0.8),\rightL,rrand(0.2,0.9)]);
      rrand(0.05,0.15).wait;
    });
  });
)

(
f=({
  ~truc.play;
  
  t.play;
  
  y.play;
  
  u.play;

});

)

f.value;
~totalrain.play;
s.;
s.freeAll;

(
  Synth("2sec",["freq",300]);
  Synth("2sec",["freq",600]);
  Synth("2sec",["freq",900]);
)

(
{
var drop ={|dur=0.0005| Env.perc(dur,dur,1,[-4,4])};
var sine={SinOsc.ar(400,0,0.4)};
sine*drop
}
).play;
      
      (
      var sw=500,x;
      //x=Synth.new("2sec");
      Task({
        2.do({
          Synth("2sec",["freq",sw]);
          sw=(sw+100);
          1.9.wait;
        });
      }).play;
      
      sw=800;
      Task({
        2.do({
          Synth("2sec",["freq",sw]);
          sw=(sw+100);
          1.9.wait;
        });
      }).play;
      )
(
  var p, l,sw,x,i=0,value=Array.new(256);

  p = Pipe.new("cat /home/shrimp/test.sh", "r");	// list directory contents in long format
  l = p.getLine;	// get the first line

  while({l.notNil},
    {
      sw = l.asInteger;
      value.add(sw);
      l.postln;
      l = p.getLine; 
    });	// post until l = nil

  Task({
    value.size.do({
      sw=value.at(i);
      Synth("2sec",["freq",sw]);
      2.wait;
      i=i+1;
    });
  }).play;
  p.close;	// close the pipe to avoid that nasty buildup
)

()
