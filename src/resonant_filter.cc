/**
** @file resonant_filter.cc
*/

#include "resonant_filter.hh"

#include <cmath>
#include <iostream>

#include "params.hh"

ResonantFilter1::ResonantFilter1(MonoSource* src)
    : src_(src)
    , buf_(3, 0)
{
    MkLowPass(800, 0.2);
}

void ResonantFilter1::MkLowPass(float freq, float q)
{
    a_[0] = -2. * q * cos(M_TAU * freq / 44100.);
    a_[1] = q * q;

    b_[0] = (1. - q * q) / 2.;
    b_[1] = 0;
    b_[2] = -b_[0];
}

void ResonantFilter1::MkHighPass(float /* freq */)
{
    // TODO
}

float ResonantFilter1::Gen()
{
    double v = src_->Gen();
    buf_.push_front(v - a_[0] * buf_[0] - a_[1] * buf_[1]);
    v = b_[0] * buf_[0] + b_[1] * buf_[1] + b_[2] * buf_[2];
    return v;
}

ResonantFilter2::ResonantFilter2(MonoSource* src)
    : src_(src)
    , buf_(2, 0)
{
    MkLowPass(800, 0.2);
}

void ResonantFilter2::MkLowPass(float freq, float q)
{
    r_ = q; // 1 - M_TAUOVR2 * (20000. / 44100.);
    b_[0] = -(4 * r_ * r_ / (1. + r_ * r_)) * cos(M_TAU * freq / 44100.);
    b_[1] = r_ * r_;
}

void ResonantFilter2::MkHighPass(float /* freq */)
{
    // TODO
}

float ResonantFilter2::Gen()
{
    double v = src_->Gen();
    v = v - b_[0] * buf_[0] - b_[1] * buf_[1];
    buf_.push_front(v);
    return v;
}
