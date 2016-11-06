# Synth

This is a synthesizer. It outputs sounds on stdout, so to hear what it actually
plays, do

    ./synth filename | aplay -f S16_LE -c2 -r44100

where `filename` is a script that contains lines like

    sinus|square|saw|triangle name #declare an oscillator named `name`
    set_note name note             #set the note of the osc `name` to `note`
    play duration name             #play the oscillo `name` for `ms` millisecs

The lines will be read in order. If `filename` is unspecified or `-`, those
lines will be read on stdin and played on EOF (press ^D).

Look at examples.
