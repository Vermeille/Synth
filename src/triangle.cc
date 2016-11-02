/**
** @file triangle.cc
*/

#include "triangle.hh"

float Triangle::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    float val = 2 * this->phase_ / M_TAU - 1;
    val = fabs(val);
    return 2 * (val - 0.5);
}
