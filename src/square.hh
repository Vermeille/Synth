#pragma once

#include "osc.hh"
#include "params.hh"

class Square : public Oscillo
{
  public:
    virtual float Gen() override;
};
