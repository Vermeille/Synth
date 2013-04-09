/**
** @file mono_to_stereo.cc
*/

#include "mono_to_stereo.hh"

MonoToStereo::MonoToStereo(MonoSource* src)
    : src_(src)
{
}

std::pair<float, float> MonoToStereo::Gen()
{
    float val = src_->Gen();
    return std::make_pair(val, val);
}

