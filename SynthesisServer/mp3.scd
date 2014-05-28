/*
s.boot; 
s.quit;
MP3.lamepath;
MP3.curlpath;
File.exists(MP3.lamepath)
File.exists(MP3.curlpath)
*/

s.waitForBoot({
  var mp3Playback=MP3.readToBuffer(s,"/home/pallamidessi/Musique2/test.mp3");
  var idHashMap= IdentityDictionary.new;
  var flangerEffect,reverbEffect,tremoloEffect,pitchEffect,chorusEffect,playbackEffect;

  idHashMap.put(0,1);

  ~defineOSCAndSynth={
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
    
    SynthDef.new(\playback, {arg inbus=0;
      var sig; 
      sig = In.ar(inbus, 1); 
      Out.ar(0,sig);
    }).add;

    SynthDef.new(\reverb, {arg inbus=0, outbus=0, predelay=0.048, combdecay=15, allpassdecay=1, revVol=0.31;
      var sig, y, z;
      sig = In.ar(inbus, 1); 
      // predelay
      z = DelayN.ar(sig, 0.1, predelay); // max 100 ms predelay
      // 7 length modulated comb delays in parallel :
      y = Mix.ar(Array.fill(7,{ CombL.ar(z, 0.05, rrand(0.03, 0.05), combdecay) })); 
      6.do({ y = AllpassN.ar(y, 0.050, rrand(0.03, 0.05), allpassdecay) });
      Out.ar(outbus, sig + (y * revVol) ! 2); // as fxlevel is 1 then I lower the vol a bit
    }).add;

    SynthDef.new(\flanger, { arg out=0, in=0, delay=0.1, depth=0.08, rate=0.06, fdbk=0.0, decay=0.0; 
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
  
    SynthDef.new(\chorus, { arg inbus=10, outbus=0, predelay=0.08, speed=0.05, depth=0.1, ph_diff=0.5;
      var in, sig, modulators, numDelays = 12;
      
      in = In.ar(inbus, 1) * numDelays.reciprocal;
      modulators = Array.fill(numDelays, {arg i;
              LFPar.kr(speed * rrand(0.94, 1.06), ph_diff * i, depth, predelay);}); 
      sig = DelayC.ar(in, 0.5, modulators);  
      sig = sig.sum; //Mix(sig); 
      Out.ar(outbus, sig!2); // output in stereo
    }).add;
  
    SynthDef.new(\tremolo, {arg inbus=0, outbus=0, freq=1, strength=1; 
      var fx, sig; 
      sig = In.ar(inbus, 1); 
      fx = sig * SinOsc.ar(freq, 0, strength, 0.5, 2); 
      Out.ar(outbus, (fx+ sig).dup );
    }).add;

    SynthDef.new(\pitcher,{
      var in, amp, freq, hasFreq, out, gate, threshold;
      threshold = 0.05; // change 
      // using a LowPassFilter to remove high harmonics
      in = LPF.ar(Mix.new(AudioIn.ar([1,2])), 2000);
      amp = Amplitude.kr(in, 0.25, 0.25);
      # freq, hasFreq = Pitch.kr(in, ampThreshold: 0.1, median: 7);
      gate = Lag.kr(amp > threshold, 0.01);	

      // -- to look at the values, uncomment the following lines 
      // -- (you need a recent build with the Poll class)
      //Poll.kr(Impulse.kr(10), freq, "frequency:");
      //Poll.kr(Impulse.kr(10), amp, "amplitude:");
      //Poll.kr(Impulse.kr(10), hasFreq, "hasFreq:");
      out = VarSaw.ar(freq, 0, 0.2, amp*hasFreq*gate);
      // uncomment (3 sines (octave lower, pitch and octave higher mixed into one signal (out)))
      //out = Mix.new(SinOsc.ar(freq * [0.5,1,2], 0, 0.2 * amp*hasFreq*gate));
      6.do({
        out = AllpassN.ar(out, 0.040, [0.040.rand,0.040.rand], 2)
      });
      Out.ar(0,out);
      }).add;
  };

  ~play={arg funcHash;
    {Out.ar(10, PlayBuf.ar(2, mp3Playback.bufnum, BufRateScale.kr(mp3Playback.bufnum),loop:1))}.play(addAction:\addToHead);
    //playbackEffect=Synth(\playback, [\inbus, 10], addAction:\addToTail);
    reverbEffect = Synth(\reverb, [\inbus, 10], addAction:\addToTail);
    
    reverbEffect.set(\revVol, 0.00);
    
    Task({
      inf.do({
        var newReverb=0;
        funcHash.value.do({arg note;
          if(note==2,{newReverb=newReverb+0.01});
          if(note==3,{newReverb=newReverb+0.05});
          if(note==4,{newReverb=newReverb+0.1});
        });
        newReverb.postln;
        reverbEffect.set(\revVol,newReverb);
        0.15.wait;
      });
    }).play;
    //flangerEffect=Synth(\flanger, [\in, 10], addAction:\addToTail);
    //pitchEffect=Synth(\pitcher, addAction:\addToTail);
    //chorusEffect=Synth(\chorus, [\inbus, 10], addAction:\addToTail);
    //tremoloEffect=Synth(\tremolo, [\inbus, 10], addAction:\addToTail);
  };
  

  /*
  reverb.set(\predelay, 0.080);
  reverb.set(\combdecay, 2.048);
  reverb.set(\allpassdecay, 3.048);
  reverb.set(\revVol, 0.005);

  flangerEffect.set(\delay, 0.00)
  flangerEffect.set(\depth, 0.04)
  flangerEffect.set(\rate, 1)
  flangerEffect.set(\fdbk, 0.08)
  flangerEffect.set(\decay, 0.01)

  // a parameter explosion results in a Chorus like effect:
  flangerEffect.set(\decay, 0)
  flangerEffect.set(\delay, 0.43)
  flangerEffect.set(\depth, 0.2)
  flangerEffect.set(\rate, 0.1)
  flangerEffect.set(\fdbk, 0.08)

  // or just go mad:
  flangerEffect.set(\delay, 0.93)
  flangerEffect.set(\depth, 0.9)
  flangerEffect.set(\rate, 0.8)
  flangerEffect.set(\fdbk, 0.8)
  */
  b={idHashMap};

  ~defineOSCAndSynth.value;
  ~play.value(b);
})
