#pragma once

#include "osc.hh"
#include "params.hh"

class Triangle : public Oscillo
{
  public:
    virtual float Gen() override;
};
