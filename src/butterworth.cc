/**
** @file butterworth.cc
*/

#include <cmath>
#include <iostream>

#include "butterworth.hh"
#include "params.hh"

Butterworth::Butterworth(MonoSource* src)
    : src_(src)
    , buf_(3, 0)
{
    MkLowPass(800);
}

void Butterworth::MkLowPass(float freq)
{
    float lambda = 1. / tan(M_TAUOVR2 * freq / 44100.);
    a_[0] = 1. / (1. + 2. * lambda + lambda * lambda);
    a_[1] = 2. * a_[0];
    a_[2] = a_[0];

    b_[0] = 2. * a_[0] * (1. - lambda * lambda);
    b_[1] = a_[0] * (1. - 2. * lambda + lambda * lambda);
}

void Butterworth::MkHighPass(float freq)
{
    float lambda = tan(M_TAUOVR2 * freq / 44100.);
    a_[0] = 1. / (1. + 2. * lambda + lambda * lambda);
    a_[1] = 2. * a_[0];
    a_[2] = a_[0];
    b_[0] = 2. * a_[0] * (lambda * lambda - 1.);
    b_[1] = a_[0] * (1. - 2. * lambda + lambda * lambda);
}

float Butterworth::Gen()
{
    double v = src_->Gen();
    buf_.push_front(v - b_[0] * buf_[0] - b_[1] * buf_[1]);
    v = a_[0] * buf_[0] + a_[1] * buf_[1] + a_[2] * buf_[2];
    return v;
}
