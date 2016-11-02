/**
** @file biquad_filter.cc
*/

#include <cmath>
#include <iostream>

#include "biquad_filter.hh"
#include "params.hh"

BiquadFilter::BiquadFilter(MonoSource* src)
    : src_(src)
    , buf_(3, 0)
{
    MkLowPass(800, 0.5);
}

void BiquadFilter::MkLowPass(float freq, float q)
{
    double k = tan(M_TAUOVR2 * freq / 44100.);

    double norm = 1. / (1. + k / q + k * k);
    a_[0] = k * k * norm;
    a_[1] = 2. * a_[0];
    a_[2] = a_[0];

    b_[0] = 2. * (k * k - 1) * norm;
    b_[1] = (1 - k / q + k * k) * norm;
}

void BiquadFilter::MkHighPass(float /* freq*/)
{
    // TODO
}

float BiquadFilter::Gen()
{
    double v = src_->Gen();
    buf_.push_front(v - b_[0] * buf_[0] - b_[1] * buf_[1]);
    v = a_[0] * buf_[0] + a_[1] * buf_[1] + a_[2] * buf_[2];
    return v;
}
