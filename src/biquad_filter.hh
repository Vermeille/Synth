#pragma once

#include <vector>

#include "circular.hh"
#include "mono_source.hh"

/*
** http://www.earlevel.com/main/2011/01/02/biquad-formulas/
**
** http://www.earlevel.com/main/2010/12/20/biquad-calculator/
*/

class BiquadFilter : public MonoSource
{
  public:
    BiquadFilter(MonoSource* src);
    virtual float Gen() override;

    void MkLowPass(float freq, float q);
    void MkHighPass(float freq);

  private:
    MonoSource* src_;
    CircularBuffer<float> buf_;
    double a_[3];
    double b_[2];
};
