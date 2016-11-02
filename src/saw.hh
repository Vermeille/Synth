#pragma once

#include "params.hh"
#include "osc.hh"

class Saw : public Oscillo
{
    public:
        virtual float Gen() override;
};

