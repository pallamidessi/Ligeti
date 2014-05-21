#! /bin/bash

./AudioMonitor & sclang SynthesisServer/midi.scd &
sleep 1 ; cd weierstrass 
./weierstrass --serverPort 2930 --plotStats 0 & ./weierstrass --serverPort 2929 --plotStats 0 & ./weierstrass --serverPort 2931 --plotStats 0 & ./weierstrass --serverPort 2932 --plotStats 0 & ./weierstrass --serverPort 2933 --plotStats 0 & ./weierstrass --serverPort 2934 --plotStats 0 & ./weierstrass --serverPort 2935 --plotStats 0
