ADD_EXECUTABLE(synth
    fm.cc
    osc.cc
    saw.cc
    main.cc
    sinus.cc
    square.cc
    triangle.cc
    wavetable.cc
    butterworth.cc
    stereo_merge.cc
    mono_to_stereo.cc
    resonant_filter.cc
    first_order_filter.cc
)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g -ggdb3")
