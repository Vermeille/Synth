/**
** @file main.cc
*/

#include <iostream>
#include <vector>

#include "wavetable.hh"
#include "triangle.hh"
#include "square.hh"
#include "sinus.hh"
#include "saw.hh"

#include "stereo_merge.hh"
#include "mono_to_stereo.hh"
#include "fm.hh"

int main(int argc, char const *argv[])
{
    //Sinus oscl;
    std::vector<float> tab;

    const int lol = 128;
    for (int i = 0; i < lol; ++i)
        tab.push_back(sin(i * M_TAU / lol + 10 * sin(i * 0.2 * M_TAU / lol)));
    tab.push_back(tab[0]);

    Wavetable oscl(tab);
    Sinus oscr;
    FM fm(&oscl, &oscr);
    fm.mod_amp(20);
    fm.carrier_freq(200);
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


