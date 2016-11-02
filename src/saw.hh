#pragma once

#include "osc.hh"
#include "params.hh"

class Saw : public Oscillo
{
  public:
    virtual float Gen() override;
};
