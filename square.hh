#pragma once

#include "params.hh"
#include "osc.hh"

template <class Param = SInt16, int SampleRate = 44100>
class Square : public Oscillo<Param, SampleRate>
{
    public:
        typedef typename Param::data_type data_type;
        virtual data_type Gen() override;
};

template <class Param, int SR>
typename Param::data_type Square<Param, SR>::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    if (this->phase_ < M_TAUOVR2)
        return Param::min;
    else
        return Param::max;
}
