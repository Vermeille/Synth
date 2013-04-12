/**
** @file comb.cc
*/

#include "comb.hh"

Comb::Comb(MonoSource* src)
    : src_(src),
    buf_(2001, 0),
    g_(0.8)
{
}

float Comb::Gen()
{
    double v = src_->Gen();

    buf_.push_front(v + buf_[2000] * g_);

    return buf_[0];
}

