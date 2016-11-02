/**
** @file wavetable.cc
*/

#include <iostream>

#include "wavetable.hh"

Wavetable::Wavetable(const std::vector<float>& table)
    : table_(table)
{
}

float Wavetable::Gen()
{
    phase_ += phase_incr_;

    if (phase_ >= M_TAU)
        phase_ -= M_TAU;

    float in_base = phase_ / M_TAU * (table_.size() - 1);
    int index = in_base;
    return table_[index] +
           (table_[index + 1] - table_[index]) * (in_base - index);
}
