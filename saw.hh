#pragma once

#include "params.hh"
#include "osc.hh"

class Saw : public Oscillo
{
    public:
        virtual float Gen() override;
};

float Saw::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    return this->phase_ / M_TAU - 1;
}
