// Written by Dan Stowell, September 2006
s.boot;
b = Buffer.read(s,"/home/shrimp/Ligeti/SynthesisServer/sample/sn-76-good-quality-amen.wav"); // Provide a simple breakbeat loop
(
var ampTable = Signal.hanningWindow(1024,100).squared;
var ampBuf = Buffer.loadCollection(s, ampTable);

SynthDef("accelerando_inf1", { arg out=0,bufnum=0;
	
	var pos, posses, pitches, amps, sons;
	
	// "pos" is a kind of master pitch control, linear varying between one and zero
	pos = Phasor.ar(1, 0.007 / SampleRate.ir, 0, 1);
	
	posses = (pos + ((0..4)/5)).wrap(0.0, 1.0); // Evenly spaced circularly within 0 to 1
	
 	pitches = (0.2 * 2.0.pow(posses * 5));
	
	amps = BufRd.kr(1, ampBuf.bufnum, posses * BufFrames.ir(ampBuf.bufnum));
	
	sons = (PlayBuf.ar(1, bufnum, pitches.poll(100), loop:1) * amps * 10);
	
	Out.ar(out,
		Pan2.ar(sons.mean.softclip)
	)
}).play(s,[\out, 0, \bufnum, b.bufnum]);
)

BufRd.ar(1,b,)
{ BufRd.ar(1, b, K2A.ar(MouseX.kr(0, BufFrames.kr(b)))) }.play;
{ BufRd.ar(1, b, Phasor.ar(0, BufRateScale.kr(b), 0, BufFrames.kr(b),MouseX.kr())) }.play;

SynthDef(\keyboard_synth, {
		|sine_level = 1.0, saw_level = 0.0, square_level = 0.0,
			filter_freq = 10000, filter_res = 0.0, amp = 0.0, freq = 200.0|
	
		var sine = SinOsc.ar(freq, 0.0, sine_level);
		var saw = Saw.ar(freq, saw_level);
		var square = Pulse.ar(freq, 0.5, square_level);
		var mix = Mix.new([sine, saw, square]);
		
		Out.ar(0, Pan2.ar(MoogFF.ar(mix, Lag2.kr(filter_freq, 0.3), filter_res) * amp));
	}).load(s);

Synth.new(\keyboard_synth,[amp:0.5]);
