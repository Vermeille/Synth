/**
** @file first_order_filter.cc
*/

#include <cmath>

#include "first_order_filter.hh"
#include "params.hh"

FirstOrderFilter::FirstOrderFilter(MonoSource* src)
    : src_(src)
    , prev_(0)
{
    MkLowPass(400);
}

float FirstOrderFilter::Gen()
{
    double v = src_->Gen();

    prev_ = a_ * v - b_ * prev_;
    return prev_;
}

void FirstOrderFilter::MkLowPass(float f)
{
    b_ = sqrt(pow(2. - cos(M_TAU * f / 44100.), 2) - 1) - 2 +
         cos(M_TAU * f / 44100.);
    a_ = 1 + b_;
}

void FirstOrderFilter::MkHighPass(float f)
{
    b_ = -(sqrt(pow(2. - cos(M_TAU * f / 44100.), 2) - 1) - 2 +
           cos(M_TAU * f / 44100.));
    a_ = 1 - b_;
}
