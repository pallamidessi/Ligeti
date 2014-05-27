s.boot; 
s.quit;
MP3.lamepath;
MP3.curlpath;
File.exists(MP3.lamepath)
File.exists(MP3.curlpath)
s;.freeAll;
u = MP3("/home/pallamidessi/Musique2/test.mp3");
m.start;
b=MP3.readToBuffer(s,"/home/pallamidessi/Musique2/test.mp3")

SynthDef(\reverb, {arg inbus=0, outbus=0, predelay=0.048, combdecay=15, allpassdecay=1, revVol=0.31;
  var sig, y, z;
  sig = In.ar(inbus, 1); 
  // predelay
  z = DelayN.ar(sig, 0.1, predelay); // max 100 ms predelay
  // 7 length modulated comb delays in parallel :
  y = Mix.ar(Array.fill(7,{ CombL.ar(z, 0.05, rrand(0.03, 0.05), combdecay) })); 
  6.do({ y = AllpassN.ar(y, 0.050, rrand(0.03, 0.05), allpassdecay) });
  Out.ar(outbus, sig + (y * revVol) ! 2); // as fxlevel is 1 then I lower the vol a bit
}).add;
{Out.ar(10, AudioIn.ar(1))}.play(addAction:\addToHead);
b = Buffer.read(s, "/usr/share/SuperCollider/sounds/a11wlk01.wav"); // replace this sound with a nice sounding one !!!
{Out.ar(10, PlayBuf.ar(1, b.bufnum, BufRateScale.kr(b.bufnum),loop:1))}.play(addAction:\addToHead);

Synth(\reverb, [\inbus, 10], addAction:\addToTail);
a = Synth(\reverb, [\inbus, 10], addAction:\addToTail);
a.set(\predelay, 0.080);
a.set(\combdecay, 2.048);
a.set(\allpassdecay, 3.048);
a.set(\revVol, 0.005);
test
test
(
  SynthDef(\flanger, { arg out=0, in=0, delay=0.1, depth=0.08, rate=0.06, fdbk=0.0, decay=0.0; 
    var input, maxdelay, maxrate, dsig, mixed, local;
    maxdelay = 0.013;
    maxrate = 10.0;
    input = In.ar(in, 1);
    local = LocalIn.ar(1);
    dsig = AllpassL.ar( // the delay (you could use AllpassC (put 0 in decay))
      input + (local * fdbk),
      maxdelay * 2,
      LFPar.kr( // very similar to SinOsc (try to replace it) - Even use LFTri
        rate * maxrate,
        0,
        depth * maxdelay,
        delay * maxdelay),
      decay);
    mixed = input + dsig;
    LocalOut.ar(mixed);
    Out.ar([out, out+1], mixed);
  }).add;
)
// audioIn on audio bus nr 10
{Out.ar(10, AudioIn.ar(1))}.play(s, addAction:\addToHead)
a = Synth(\flanger, [\in, 10], addAction:\addToTail)
a.set(\delay, 0.04)
a.set(\depth, 0.08)
a.set(\rate, 0.01)
a.set(\fdbk, 0.08)
a.set(\decay, 0.01)
// or if you prefer a buffer:
b = Buffer.read(s, "/usr/share/SuperCollider/sounds/a11wlk01.wav"); // replace this sound with a nice sounding one !!!
{Out.ar(10, PlayBuf.ar(1, b.bufnum, BufRateScale.kr(b.bufnum), loop:1))}.play(addAction:\addToHead)
a = Synth(\flanger, [\in, 10], addAction:\addToTail)
a.set(\delay, 0.04)
a.set(\depth, 0.04)
a.set(\rate, 1)
a.set(\fdbk, 0.08)
a.set(\decay, 0.01)
// a parameter explosion results in a Chorus like effect:
a.set(\decay, 0)
a.set(\delay, 0.43)
a.set(\depth, 0.2)
a.set(\rate, 0.1)
a.set(\fdbk, 0.08)
// or just go mad:
a.set(\delay, 0.93)
a.set(\depth, 0.9)
a.set(\rate, 0.8)
a.set(\fdbk, 0.8)

