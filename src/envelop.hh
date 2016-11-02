#pragma once

#include <utility>

#include "mono_source.hh"

class Envelop : public MonoSource
{
  protected:
    float time_;
    float time_incr_;
    MonoSource* src_;
};
