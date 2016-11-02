/**
** @file osc.cc
*/

#include "osc.hh"

void Oscillo::freq(float f)
{
    freq_ = f;
    phase_incr_ = M_TAU * f / SAMPLE_RATE;
}

float Oscillo::freq() { return freq_; }

Oscillo::Oscillo()
{
    phase_ = 0;
    freq(440);
}
