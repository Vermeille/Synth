#pragma once

#include <vector>

#include "circular.hh"
#include "mono_source.hh"

/*
**
*http://www.music.mcgill.ca/~gary/307/week2/filters.html#SECTION00018000000000000000
*/

class ResonantFilter1 : public MonoSource
{
  public:
    ResonantFilter1(MonoSource* src);
    virtual float Gen() override;

    void MkLowPass(float freq, float q);
    void MkHighPass(float freq);

  private:
    MonoSource* src_;
    CircularBuffer<float> buf_;
    double a_[2];
    double b_[3];
};

class ResonantFilter2 : public MonoSource
{
  public:
    ResonantFilter2(MonoSource* src);
    virtual float Gen() override;

    void MkLowPass(float freq, float q);
    void MkHighPass(float freq);

  private:
    MonoSource* src_;
    CircularBuffer<float> buf_;
    double b_[2];
    double r_;
};
