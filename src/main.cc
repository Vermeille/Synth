/**
** @file main.cc
*/

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "saw.hh"
#include "sinus.hh"
#include "square.hh"
#include "triangle.hh"
#include "wavetable.hh"

#include "biquad_filter.hh"
#include "butterworth.hh"
#include "envelop.hh"
#include "first_order_filter.hh"
#include "fm.hh"
#include "mono_to_stereo.hh"
#include "resonant_filter.hh"
#include "stereo_merge.hh"
#include "wav_export.hh"

int main(int argc, char const* argv[])
{
    // Sinus oscl;
    Sinus oscl;
    oscl.freq(440);
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
#if 1
    BiquadFilter r(&oscl);
    // MonoToStereo sm(&r);
    WavExporter wav(&oscl);
    wav.MkWav("le_caca.wav", 1);
#else
    MonoToStereo sm(&oscl);
#endif
#endif

    float f = 200;
    float q = 0.1;

#if 0
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
#endif
    return 0;
}
