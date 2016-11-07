# Synth

[![Build Status](https://travis-ci.org/Vermeille/Synth.svg?branch=master)](https://travis-ci.org/Vermeille/Synth)

This is a synthesizer. It outputs sounds on stdout, so to hear what it actually
plays, do

    ./synth filename | aplay -f S16_LE -c2 -r44100

where `filename` is a script that contains lines like

    # declare an oscillator named `name`
    sinus|square|saw|triangle name

    # set the note of the osc `name` to `note`
    set_note name note

    # merges inputs `i1`, `i2` and `i3` into `out`
    merge out i1 i2 i3

    # create an envelop `name` that takes `input` in
    adsr name input

    # sets the attack of the envelop `name` to rise to `percent` of amplitude
    # at `time` milliseconds after creation or last `reset`
    # The same exists with `set_decay`, `set_sustain` and `set_release`
    set_attack name time percent

    # resets the envelop `name`
    reset name

    # play the `name` for `ms` millisecs
    play duration name

The lines will be read in order. If `filename` is unspecified or `-`, those
lines will be read on stdin and played on EOF (press ^D).

Look at examples.
