#pragma once

#include <utility>

#include "mono_source.hh"
#include "stereo_source.hh"

class MonoToStereo : public StereoSource
{
  public:
    MonoToStereo(MonoSource* src);

    std::pair<float, float> Gen();

  private:
    MonoSource* src_;
};
