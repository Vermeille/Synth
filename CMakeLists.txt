ADD_EXECUTABLE(synth
    fm.cc
    osc.cc
    saw.cc
    main.cc
    sinus.cc
    square.cc
    triangle.cc
    stereo_merge.cc
    mono_to_stereo.cc
)

SET(CMAKE_CXX_FLAGS -std=c++11)
