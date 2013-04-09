#pragma once

#include "params.hh"
#include "osc.hh"

class Square : public Oscillo
{
    public:
        virtual float Gen() override;
};

float Square::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    if (this->phase_ < M_TAUOVR2)
        return -1.f;
    else
        return 1.f;
}
