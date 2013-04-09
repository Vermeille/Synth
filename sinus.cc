/**
** @file sinus.cc
*/

#include "sinus.hh"

float Sinus::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    return sin(this->phase_);
}

