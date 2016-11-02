#pragma once

#include <utility>

#include "stereo_source.hh"
#include "mono_source.hh"

class MonoToStereo : public StereoSource
{
    public:
        MonoToStereo(MonoSource* src);

        std::pair<float, float> Gen();
    private:
        MonoSource* src_;
};

