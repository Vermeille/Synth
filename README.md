# Synth

This is a synthesizer. It outputs sounds on stdout, so to hear what it actually
plays, do

    ./synth filename | aplay -f S16_LE -c2 -r44100

where `filename` is a script that contains lines like

    sinus|square|saw freq ms

The lines will be read in order, plaing the frequency `freq` for `ms`
milliseconds. If `filename` is unspecified or `-`, those lines will be read on
stdin and played on EOF (press ^D).
