#pragma once

#include <vector>

#include "circular.hh"
#include "mono_source.hh"

class Butterworth : public MonoSource
{
  public:
    Butterworth(MonoSource* src);
    virtual float Gen() override;

    void MkLowPass(float freq);
    void MkHighPass(float freq);

  private:
    MonoSource* src_;
    CircularBuffer<float> buf_;
    double a_[3];
    double b_[2];
};
