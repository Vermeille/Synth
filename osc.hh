#pragma once

#include <cmath>

#include "params.hh"
#include "mono_source.hh"

#define M_TAU (2 * M_PI)
#define M_TAUOVR2 M_PI

class Oscillo : public MonoSource
{
    public:
        Oscillo();

        virtual float Gen() = 0;
        void freq(float f);
        float freq();

    protected:
        float freq_;
        float phase_;
        float phase_incr_;
};

