#pragma once

#include <utility>

#include "envelop.hh"

class ADSR : public Envelop
{
  public:
    ADSR(MonoSource* src);

    virtual float Gen() override;

    void adsr(int index, float time, float val);

    void start(float volume) { adsr(0, 0, volume); }
    void attack(float start, float volume) { adsr(1, start, volume); }
    void decay(float start, float volume) { adsr(2, start, volume); }
    void sustain(float start, float volume) { adsr(3, start, volume); }
    void release(float start, float volume) { adsr(4, start, volume); }

    void src(MonoSource* src);
    MonoSource* src();

    void reset()
    {
        time_ = 0;
        time_ = 0;
    }

  private:
    float adsr_[5][2];
    int index_;
};
