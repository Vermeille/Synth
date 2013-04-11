/**
** @file main.cc
*/

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "wavetable.hh"
#include "triangle.hh"
#include "square.hh"
#include "sinus.hh"
#include "saw.hh"

#include "fm.hh"
#include "envelop.hh"
#include "butterworth.hh"
#include "stereo_merge.hh"
#include "mono_to_stereo.hh"
#include "resonant_filter.hh"
#include "first_order_filter.hh"
#include "biquad_filter.hh"

int main(int argc, char const *argv[])
{
    //Sinus oscl;
    Saw oscl;
    oscl.freq(100);
#if 0
    Sinus oscr;

    //StereoMerge sm(&fm, &fm2);
    ADSR env(&oscr);
    env.adsr(0, 0, 0);
    env.adsr(1, 100, 1);
    env.adsr(2, 175, 0.50f);
    env.adsr(3, 200, 0.50f);
    env.adsr(4, 1000, 0.f);

    FM fm(&oscl, &env);
    fm.mod_amp(100);
    fm.carrier_freq(440);
    oscr.freq(100);

    Reverb r(&fm);
#else
# if 1
    BiquadFilter r(&oscl);
    MonoToStereo sm(&r);
# else
    MonoToStereo sm(&oscl);
# endif
#endif

    float f = 200;
    float q = 0.1;

    while (true)
    {
        for (int i = 0; i < 100; ++i)
        {
            auto res = Render<SInt16>(sm.Gen());
            std::cout.write(reinterpret_cast<char*>(&res.first), 2);
            std::cout.write(reinterpret_cast<char*>(&res.second), 2);
            //std::cerr << res.first << " ";
        }
        std::cout.flush();
#if 1
        if (f <= 22000)
        {
            f *= 1.001f;
            r.MkLowPass(f, q);
            //std::cerr << f << "\n";
        }
        else
        {
            f = 200;
            q += 0.1;
            std::cerr << "Q = " << q << "\n";
            sleep(1);
        }
#endif
    }
    return 0;
}


