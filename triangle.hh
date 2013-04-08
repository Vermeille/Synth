#pragma once

#include "params.hh"
#include "osc.hh"

template <class Param = SInt16, int SampleRate = 44100>
class Triangle : public Oscillo<Param, SampleRate>
{
    public:
        typedef typename Param::data_type data_type;
        virtual data_type Gen() override;
};

template <class Param, int SR>
typename Param::data_type Triangle<Param, SR>::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    float val = 2 * this->phase_ / M_TAU - 1;
    val = fabs(val);
    return Param::amp * (val - 0.5) + Param::zero;
}
