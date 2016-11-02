/**
** @file fm.cc
*/

#include "fm.hh"

FM::FM(Oscillo* osc, MonoSource* mod)
    : carrier_(osc)
    , modulator_(mod)
    , freq_(440)
    , mod_amp_(20)
{
}

float FM::Gen()
{
    carrier_->freq(freq_ + modulator_->Gen() * mod_amp_);
    return carrier_->Gen();
}
