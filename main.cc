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
#include "mono_to_stereo.hh"
#include "fm.hh"

int main(int argc, char const *argv[])
{
    Sinus oscl;
    Saw oscr;
    FM fm(&oscl, &oscr);
    fm.mod_amp(100);
    //StereoMerge sm(&fm, &fm);
    MonoToStereo sm(&fm);
    oscr.freq(2);

    while (true)
    {
        for (int i = 0; i < 100; ++i)
        {
            auto res = Render<SInt16>(sm.Gen());
            std::cout.write(reinterpret_cast<char*>(&res.first), 2);
            std::cout.write(reinterpret_cast<char*>(&res.second), 2);
        }
        std::cout.flush();
    }
    return 0;
}


