/**
** @file main.cc
*/

#include <iostream>
#include <vector>

#include "triangle.hh"
#include "square.hh"
#include "sinus.hh"
#include "saw.hh"

#include "stereo_merge.hh"

int main(int argc, char const *argv[])
{
    Saw<SInt16, 44100> oscl;
    Square<SInt16, 44100> oscr;
    StereoMerge<> sm(&oscl, &oscr);
    oscr.freq(500);

    while (true)
    {
        for (int i = 0; i < 100; ++i)
        {
            auto res = sm.Gen();
            std::cout.write(reinterpret_cast<char*>(&res.first), 2);
            std::cout.write(reinterpret_cast<char*>(&res.second), 2);
        }
        std::cout.flush();
    }
    return 0;
}


