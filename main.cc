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
    Sinus oscl;
    Sinus oscr;
    StereoMerge sm(&oscl, &oscr);
    oscr.freq(450);

    while (true)
    {
        for (int i = 0; i < 100; ++i)
        {
            auto res = Render<SInt8>(sm.Gen());
            std::cout.write(reinterpret_cast<char*>(&res.first), 1);
            std::cout.write(reinterpret_cast<char*>(&res.second), 1);
        }
        std::cout.flush();
    }
    return 0;
}


