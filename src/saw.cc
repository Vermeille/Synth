/**
** @file saw.cc
*/

#include "saw.hh"

float Saw::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    return this->phase_ / M_TAU - 1;
}
