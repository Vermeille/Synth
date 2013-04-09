#pragma once

#include "params.hh"
#include "osc.hh"

class Triangle : public Oscillo
{
    public:
        virtual float Gen() override;
};

float Triangle::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    float val = 2 * this->phase_ / M_TAU - 1;
    val = fabs(val);
    return 2 * (val - 0.5);
}
