#pragma once

#include <cmath>

#include "params.hh"

#define M_TAU (2 * M_PI)
#define M_TAUOVR2 M_PI

struct MonoSource
{
    virtual float Gen() = 0;
};

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

void Oscillo::freq(float f)
{
    freq_ = f;
    phase_incr_ = M_TAU * f / SAMPLE_RATE;
}

float Oscillo::freq()
{
    return freq_;
}

Oscillo::Oscillo()
{
    phase_ = 0;
    freq(440);
}
