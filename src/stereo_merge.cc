/**
** @file stereo_merge.cc
*/

#include "stereo_merge.hh"

std::pair<float, float> StereoMerge::Gen()
{
    return std::make_pair(left_->Gen(), right_->Gen());
}

StereoMerge::StereoMerge(MonoSource* l, MonoSource* r)
    : left_(l)
    , right_(r)
{
}
