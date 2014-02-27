#! /bin/bash

./AudioMonitor & sclang SynthesisServer/sheperd_tone.scd &
sleep 1 ; cd weierstrass 
./weierstrass --serverPort 2930 --plotStats 0 & ./weierstrass --serverPort 2929 --plotStats 0
