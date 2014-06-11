Ligeti
======

Sonification du système évolutionnaire distribué GPGPU Easea


JUCE
====

Nécessite l'introjucer:
```
git clone https://github.com/julianstorer/JUCE.git
```

FluidSynth
==========

Nécessite FluidSynth avec des soundFonts (.sf2) et JACK

Pour lancer le serveur:
```
fluidsynth --server --audio-driver=jack --connect-jack-outputs /usr/share/sounds/sf2/FluidR3_GM.sf2 -d
```
