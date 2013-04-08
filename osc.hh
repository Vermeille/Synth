#pragma once

#include <cmath>

#include "params.hh"

#define M_TAU (2 * M_PI)
#define M_TAUOVR2 M_PI

template <class Param = SInt16, int SR = 44100>
class Oscillo
{
    public:
        typedef typename Param::data_type data_type;

        Oscillo();

        virtual data_type Gen() = 0;
        void freq(float f);
        float freq();

    protected:
        float freq_;
        float phase_;
        float phase_incr_;
};

template <class Param, int SR>
void Oscillo<Param, SR>::freq(float f)
{
    freq_ = f;
    phase_incr_ = M_TAU * f / SR;
}

template <class Param, int SR>
float Oscillo<Param, SR>::freq()
{
    return freq;
}

template <class Param, int SR>
Oscillo<Param, SR>::Oscillo()
{
    freq(440);
}
