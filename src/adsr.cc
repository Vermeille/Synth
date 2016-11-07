/**
** @file adsr.cc
*/

#include "adsr.hh"

ADSR::ADSR(MonoSource* src)
    : index_(0)
{
    time_incr_ = 1.f / 44100 * 1000;
    this->src_ = src;
    this->time_ = 0;
    adsr(0, 0, 0);
}

void ADSR::adsr(int index, float time, float val)
{
    adsr_[index][0] = time;
    adsr_[index][1] = val;
}

void ADSR::src(MonoSource* src) { src_ = src; }

MonoSource* ADSR::src() { return src_; }

float ADSR::Gen()
{
    float v = src_->Gen();

    time_ += time_incr_;

    if (index_ == 5)
        return adsr_[4][1];

    if (time_ > adsr_[index_ + 1][0])
        ++index_;

    double coeff = (adsr_[index_ + 1][1] - adsr_[index_][1]) /
                   (adsr_[index_ + 1][0] - adsr_[index_][0]);
    return v * (coeff * time_ + adsr_[index_][1] - coeff * adsr_[index_][0]);
}
