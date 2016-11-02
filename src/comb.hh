#pragma once

#include <cmath>

#include "circular.hh"
#include "mono_source.hh"

class Comb : public MonoSource
{
  public:
    Comb(MonoSource* src);
    virtual float Gen() override;

  private:
    CircularBuffer<float> buf_;
    MonoSource* src_;
    double g_;
};
